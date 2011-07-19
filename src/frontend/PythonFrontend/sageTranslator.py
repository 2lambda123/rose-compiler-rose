import sys, ast

import sage

UNARY_OPERATOR_MAP = {
    ast.UAdd:     "+",
    ast.USub:     "-",
    ast.Invert:   "~"
}

class FileInfo():

  def __init__(self, filename, node):
    self.filename = filename
    self.lineno = node.lineno
    self.col_offset = node.col_offset


class stack():

  def __init__(self):
    self._stack = []

  def push(self, obj):
    self._stack.append(obj)

  def pop(self, expected=None):
    if expected != None and expected != self.peek():
        raise Exception("Popped unexpected value from stack.")
    self._stack.pop()

  def peek(self):
    return self._stack[-1]


class SageTranslator(ast.NodeVisitor):

  def __init__(self, filename):
    self.filename = filename
    self.scopeStack = stack()

  def __call__(self, syntax_tree):
    return self.visit(syntax_tree)

  def file_info(self, node):
    return FileInfo(self.filename, node)

  def generic_visit(self, node):
    #print "generic_visit for class: ", node.__class__.__name__
    return map(self.visit, ast.iter_child_nodes(node))

  def visit_alias(self, node):
    scope = self.scopeStack.peek()
    id = node.asname or node.name
    init = node.asname and self.visit(node.name)
    name = sage.buildName(id, scope)
    return (init and sage.buildAssign(name, init)) or name

  def visit_arguments(self, node):
    args = map(lambda arg: sage.buildInitializedName(arg.id), node.args)
    kwargs = map(self.visit, node.defaults)
    return sage.buildFunctionParameterList(args, kwargs)

  def visit_Assert(self, node):
    test = self.visit(node.test)
    return sage.buildAssert(test)

  def visit_Assign(self, node):
    targets = map(self.visit, node.targets)
    value = self.visit(node.value)
    assert len(targets) == 1, "target assignment lists are yet to be supported"
    return sage.buildAssign(targets[0], value)

  def visit_AugAssign(self, node):
    target = self.visit(node.target)
    value  = self.visit(node.value)
    op = node.op.__class__
    return sage.buildAugAssign(target, value, op)

  def visit_BinOp(self, node):
    lhs = self.visit(node.left)
    rhs = self.visit(node.right)
    op_str = node.op.__class__
    return sage.buildBinOp(lhs, rhs, op_str)

  def visit_Break(self, node):
    return sage.buildBreak()

  def visit_Call(self, node):
    name = node.func.id
    args = map(self.visit, node.args)
    kwargs = map(self.visit, node.keywords)
    scope = self.scopeStack.peek()
    return sage.buildCall(name, args, kwargs, scope)

  def visit_ClassDef(self, node):
    scope = self.scopeStack.peek()
    #bases = node.bases
    decorators = node.decorator_list and sage.buildExprListExp(map(self.visit, node.decorator_list))
    class_decl, scope = \
        sage.buildClassDef(node.name, decorators, scope)

    self.scopeStack.push(scope)
    body = map(self.visit, node.body)
    sage.appendStatements(scope, body)
    self.scopeStack.pop(scope)
    return class_decl

  def visit_Compare(self, node):
    # Until n-ary comparators are implemented in sage, only allow binary comparisons
    assert len(node.comparators) == 1
    lhs = self.visit(node.left)
    rhs = self.visit(node.comparators[0])
    op = node.ops[0].__class__
    #comparators = map(self.visit, node.comparators)
    #ops = map(lambda op: op.__class__, node.ops)
    return sage.buildCompare(op, lhs, rhs)

  def visit_complex(self, n):
    return sage.buildComplexVal(n)

  def visit_comprehension(self, node):
    ifs = sage.buildExprListExp(map(self.visit, node.ifs))
    target = self.visit(node.target)
    iter = self.visit(node.iter)
    return sage.buildComprehension(target, iter, ifs)

  def visit_Continue(self, node):
    return sage.buildContinue()

  def visit_Delete(self, node):
    target = sage.buildExprListExp(map(self.visit, node.targets))
    return sage.buildDelete(target)

  def visit_Dict(self, node):
    keys = map(self.visit, node.keys)
    values = map(self.visit, node.values)
    pairs = [sage.buildKeyDatumPair(keys[i], values[i]) for i in range(len(keys))]
    return sage.buildDict(pairs)

  def visit_DictComp(self, node):
    key = self.visit(node.key)
    value = self.visit(node.value)
    elt = sage.buildKeyDatumPair(key, value)
    gens = sage.buildExprListExp(map(self.visit, node.generators))
    return sage.buildDictComp(elt, gens)

  def visit_ExceptHandler(self, node):
    name = node.name and node.name.id
    type = node.type and node.type.id
    body = map(self.visit, node.body)
    scope = self.scopeStack.peek()
    return sage.buildExceptHandler(name, type, body, scope)

  def visit_Expr(self, node):
    value = self.visit(node.value)
    return sage.buildExpr(value)

  def visit_FunctionDef(self, node):
    scope = self.scopeStack.peek()
    decorators = node.decorator_list and sage.buildExprListExp(map(self.visit, node.decorator_list))
    params = self.visit(node.args)
    (capsule, scope) = \
        sage.buildFunctionDef(node.name, params, decorators, scope)
    self.scopeStack.push(scope)
    body_forest = map(self.visit, node.body)
    sage.appendStatements(capsule, body_forest)
    self.scopeStack.pop(scope)
    return capsule

  def visit_If(self, node):
    test = self.visit(node.test)
    body = map(self.visit, node.body)
    orelse = map(self.visit, node.orelse)
    return sage.buildIf(test, body, orelse)

  def visit_Import(self, node):
    names = map(self.visit, node.names)
    return sage.buildImport(names)

  def visit_int(self, n):
    return sage.buildLongIntVal(n)

  def visit_float(self, n):
    return sage.buildFloat(n)

  def visit_For(self, node):
    scope = self.scopeStack.peek()

    target = self.visit(node.target)
    iter = self.visit(node.iter)
    body = sage.buildSuite(map(self.visit, node.body))
    orelse = node.orelse and sage.buildSuite(map(self.visit, node.orelse))
    return sage.buildFor(target, iter, body, orelse)

  def visit_keyword(self, node):
    arg = self.visit(node.arg)
    value = self.visit(node.value)
    return sage.buildKeyword(arg, value)

  def visit_Lambda(self, node):
    scope = self.scopeStack.peek()
    params = self.visit(node.args)
    (lambda_capsule, lambda_scope) = sage.buildLambda(params, scope)

    self.scopeStack.push(scope)
    expr = self.visit(node.body)
    self.scopeStack.pop(scope)

    sage.appendStatements(lambda_capsule, [expr])
    return lambda_capsule

  def visit_List(self, node):
    return sage.buildListExp(map(self.visit, node.elts))

  def visit_ListComp(self, node):
    elt = self.visit(node.elt)
    gens = sage.buildExprListExp(map(self.visit, node.generators))
    return sage.buildListComp(elt, gens)

  def visit_long(self, n):
    return sage.buildLongIntVal(n)

  def visit_Module(self, node):
    scope = sage.buildGlobal(self.filename)

    self.scopeStack.push(scope)
    subforest = self.generic_visit(node)
    self.scopeStack.pop(scope)

    sage.appendStatements(scope, subforest)
    return scope

  def visit_Name(self, node):
    scope = self.scopeStack.peek()
    return sage.buildName(node.id, scope)

  def visit_NoneType(self, node):
    scope = self.scopeStack.peek()
    return sage.buildName("None", scope)

  def visit_Num(self, node):
    return self.visit(node.n)

  def visit_Pass(self, node):
    return sage.buildPass()

  def visit_Print(self, node):
    dest = node.dest and self.visit(node.dest)
    values = sage.buildExprListExp(map(self.visit, node.values))
    return sage.buildPrintStmt(dest, values)

  def visit_Return(self, node):
    value = self.visit(node.value)
    return sage.buildReturnStmt(value)

  def visit_SetComp(self, node):
    elt = self.visit(node.elt)
    gens = sage.buildExprListExp(map(self.visit, node.generators))
    return sage.buildSetComp(elt, gens)

  def visit_Str(self, node):
    return sage.buildStringVal(node.s)

  def visit_str(self, str):
    return sage.buildStringVal(str)

  def visit_TryExcept(self, node):
    body = sage.buildSuite(map(self.visit, node.body))
    handlers = map(self.visit, node.handlers)
    orelse = sage.buildSuite(map(self.visit, node.orelse))
    return sage.buildTryExcept(body, handlers, orelse)

  def visit_TryFinally(self, node):
    body = sage.buildSuite(map(self.visit, node.body))
    finalbody = sage.buildSuite(map(self.visit, node.finalbody))
    return sage.buildTryFinally(body, finalbody)

  def visit_Tuple(self, node):
    return sage.buildTuple(map(self.visit, node.elts))

  def visit_UnaryOp(self, node):
    operand = self.visit(node.operand)
    op = node.op.__class__
    return sage.buildUnaryOp(op, operand)

  def visit_While(self, node):
    test = self.visit(node.test)
    body = sage.buildSuite(map(self.visit, node.body))
    #orelse = sage.buildSuite(map(self.visit, node.orelse))
    #return sage.buildWhile(test, body, orelse)
    return sage.buildWhile(test, body)

  def visit_With(self, node):
    expr = self.visit(node.test)
    vars = map(self.visit, node.optional_vars)
    body = sage.buildSuite(map(self.visit, node.body))
    return sage.buildWith(expr, vars, body)

  def visit_Yield(self, node):
    value = self.visit(node.value)
    return sage.buildYield(value)

def translate(infilename):
  try:
    infile = open(infilename)
    contents = infile.read()
    infile.close()
  except IOError:
    print >>sys.stderr, "IO error when reading file: %s" % infilename
    exit(1)
  syntax_tree = ast.parse(contents)
  return SageTranslator(infilename).visit(syntax_tree)

def main(argv):
  map(translate, argv[1:])

if __name__ == "__main__":
  main(sys.argv)
