#ifndef SAGE_PYTHON_INTERFACE_H_
#define SAGE_PYTHON_INTERFACE_H_

#include <Python.h>

#include "SagePythonSupport.h"

PyObject* sage_buildAssert(PyObject *self, PyObject *args);
PyObject* sage_buildAssign(PyObject *self, PyObject *args);
PyObject* sage_buildAugAssign(PyObject *self, PyObject *args);
PyObject* sage_buildBinOp(PyObject *self, PyObject *args);
PyObject* sage_buildBreak(PyObject *self, PyObject *args);
PyObject* sage_buildCall(PyObject *self, PyObject *args);
PyObject* sage_buildCompare(PyObject *self, PyObject *args);
PyObject* sage_buildComprehension(PyObject *self, PyObject *args);
PyObject* sage_buildComplexVal(PyObject *self, PyObject *args);
PyObject* sage_buildContinue(PyObject *self, PyObject *args);
PyObject* sage_buildDelete(PyObject *self, PyObject *args);
PyObject* sage_buildDict(PyObject *self, PyObject *args);
PyObject* sage_buildDictComp(PyObject *self, PyObject *args);
PyObject* sage_buildExceptHandler(PyObject *self, PyObject *args);
PyObject* sage_buildExpr(PyObject *self, PyObject *args);
PyObject* sage_buildExprListExp(PyObject *self, PyObject *args);
PyObject* sage_buildFloat(PyObject *self, PyObject *args);
PyObject* sage_buildFor(PyObject *self, PyObject *args);
PyObject* sage_buildFunctionDef(PyObject *self, PyObject *args);
PyObject* sage_buildGlobal(PyObject *self, PyObject *args);
PyObject* sage_buildIf(PyObject *self, PyObject *args);
PyObject* sage_buildInitializedName(PyObject *self, PyObject *args);
PyObject* sage_buildKeyword(PyObject *self, PyObject *args);
PyObject* sage_buildKeyDatumPair(PyObject *self, PyObject *args);
PyObject* sage_buildLongIntVal(PyObject *self, PyObject *args);
PyObject* sage_buildLambda(PyObject *self, PyObject *args);
PyObject* sage_buildListExp(PyObject *self, PyObject *args);
PyObject* sage_buildListComp(PyObject *self, PyObject *args);
PyObject* sage_buildName(PyObject *self, PyObject *args);
PyObject* sage_buildPass(PyObject *self, PyObject *args);
PyObject* sage_buildPrintStmt(PyObject *self, PyObject *args);
PyObject* sage_buildReturnStmt(PyObject *self, PyObject *args);
PyObject* sage_buildSetComp(PyObject *self, PyObject *args);
PyObject* sage_buildStringVal(PyObject *self, PyObject *args);
PyObject* sage_buildSuite(PyObject *self, PyObject *args);
PyObject* sage_buildTryExcept(PyObject *self, PyObject *args);
PyObject* sage_buildTryFinally(PyObject *self, PyObject *args);
PyObject* sage_buildTuple(PyObject *self, PyObject *args);
PyObject* sage_buildUnaryOp(PyObject *self, PyObject *args);
PyObject* sage_buildWhile(PyObject *self, PyObject *args);
PyObject* sage_buildWith(PyObject *self, PyObject *args);
PyObject* sage_buildYield(PyObject *self, PyObject *args);

static PyMethodDef SageBuilderMethods[] = {
    {"buildAssert", sage_buildAssert, METH_VARARGS, "Builds an assert node."},
    {"buildAssign", sage_buildAssign, METH_VARARGS, "Builds an assignment node."},
    {"buildAugAssign", sage_buildAugAssign, METH_VARARGS, "Builds an augmented assignment node."},
    {"buildBinOp", sage_buildBinOp, METH_VARARGS, "Builds a binary expression node."},
    {"buildBreak", sage_buildBreak, METH_VARARGS, "Builds a break node."},
    {"buildCall", sage_buildCall, METH_VARARGS, "Builds an SgFunctionCallExp node."},
    {"buildCompare", sage_buildCompare, METH_VARARGS, "Builds a comparison node."},
    {"buildComprehension", sage_buildComprehension, METH_VARARGS, "Builds a complex value node."},
    {"buildComplexVal", sage_buildComplexVal, METH_VARARGS, "Builds a complex value node."},
    {"buildContinue", sage_buildContinue, METH_VARARGS, "Builds a continue stmt node."},
    {"buildDelete", sage_buildDelete, METH_VARARGS, "Builds a delete stmt node."},
    {"buildDict", sage_buildDict, METH_VARARGS, "Builds a dictionary display node."},
    {"buildDictComp", sage_buildDictComp, METH_VARARGS, "Builds a dictionary comprehension node."},
    {"buildExceptHandler", sage_buildExceptHandler, METH_VARARGS, "Builds an exception handler node."},
    {"buildExpr", sage_buildExpr, METH_VARARGS, "Builds an Expr node."},
    {"buildExprListExp", sage_buildExprListExp, METH_VARARGS, "Builds an expression list."},
    {"buildFloat", sage_buildFloat, METH_VARARGS, "Builds a float."},
    {"buildFor", sage_buildFor, METH_VARARGS, "Builds a for stmt."},
    {"buildFunctionDef", sage_buildFunctionDef, METH_VARARGS, "Builds an SgFunctionDeclaration node."},
    {"buildFunctionParameterList", sage_buildFunctionParameterList, METH_VARARGS, "Builds an SgFunctionParameterList node."},
    {"buildGlobal", sage_buildGlobal, METH_VARARGS, "Builds an SgGlobal node."},
    {"buildIf", sage_buildIf, METH_VARARGS, "Builds an if stmt  node."},
    {"buildInitializedName", sage_buildInitializedName, METH_VARARGS, "Builds an initialized name node."},
    {"buildKeyword", sage_buildKeyword, METH_VARARGS, "Builds a keyword node."},
    {"buildKeyDatumPair", sage_buildKeyDatumPair, METH_VARARGS, "Builds a key datum pair node."},
    {"buildLongIntVal", sage_buildLongIntVal, METH_VARARGS, "Builds an SgIntVal node."},
    {"buildLambda", sage_buildLambda, METH_VARARGS, "Builds a lambda node."},
    {"buildListExp", sage_buildListExp, METH_VARARGS, "Builds a list node."},
    {"buildListComp", sage_buildListComp, METH_VARARGS, "Builds a list node."},
    {"buildPass", sage_buildPass, METH_VARARGS, "Builds a pass node."},
    {"buildPrintStmt", sage_buildPrintStmt, METH_VARARGS, "Builds an SgPrintStmt node."},
    {"buildName", sage_buildName, METH_VARARGS, "Builds an SgVarRefExp from a Name node."},
    {"buildReturnStmt", sage_buildReturnStmt, METH_VARARGS, "Builds an SgReturnStmt node."},
    {"buildSetComp", sage_buildSetComp, METH_VARARGS, "Builds a set comprehension node."},
    {"buildStringVal", sage_buildStringVal, METH_VARARGS, "Builds an SgStringVal node."},
    {"buildSuite", sage_buildSuite, METH_VARARGS, "Builds a suite in a basic block node."},
    {"buildTryExcept", sage_buildTryExcept, METH_VARARGS, "Builds an try stmt node."},
    {"buildTryFinally", sage_buildTryFinally, METH_VARARGS, "Builds an try/finally stmt node."},
    {"buildTuple", sage_buildTuple, METH_VARARGS, "Builds an tuple exp node."},
    {"buildUnaryOp", sage_buildUnaryOp, METH_VARARGS, "Builds unary operation node."},
    {"buildWhile", sage_buildWhile, METH_VARARGS, "Builds while stmt node."},
    {"buildWith", sage_buildWith, METH_VARARGS, "Builds with stmt node."},
    {"buildYield", sage_buildYield, METH_VARARGS, "Builds a yield node."},

    {"appendStatements", (PyCFunction)sage_appendStatements, METH_VARARGS | METH_KEYWORDS, "Add children to a given SgNode."},

    {NULL, NULL, 0, NULL}
};

#endif /* SAGE_PYTHON_INTERFACE_H_ */
