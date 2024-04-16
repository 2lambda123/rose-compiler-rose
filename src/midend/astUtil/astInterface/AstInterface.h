
#ifndef AST_TREE_INTERFACE_H
#define AST_TREE_INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "ObserveObject.h"
#include <rosedll.h>
#include <Rose/Diagnostics.h>

class AstNodePtr;

class AST_Error { 
   std::string msg;
  public:
   AST_Error(const std::string& _msg) : msg(_msg) {}
   std::string get_msg() { return msg; }
};

class AstInterfaceImpl;
class AstNodePtr {
 protected:
  void* repr;
 public:
  AstNodePtr(void* _repr=0) : repr(_repr) {}
  AstNodePtr( const AstNodePtr& that) : repr(that.repr) {}
  ~AstNodePtr() {}
  AstNodePtr& operator = (const AstNodePtr &that) 
      { repr = that.repr; return *this; }
  bool operator != (const AstNodePtr &that) const
    { return repr != that.repr; }
  bool operator == (const AstNodePtr &that) const
    { return repr == that.repr; }
  bool operator == (void *p) const
    { return repr == p; }
  bool operator != (void *p) const
    { return repr != p; }
  bool operator < (const AstNodePtr &that) const
    { return repr < that.repr; }
  void * get_ptr() const { return repr; }
  void *& get_ptr() { return repr; }
};
#define AST_NULL AstNodePtr()

class AstNodeType {
 protected:
  void* repr;
 public:
  AstNodeType() : repr(0) {}
  AstNodeType( const AstNodeType& that) : repr(that.repr) {}
  AstNodeType& operator = (const AstNodeType &that) 
      { repr = that.repr; return *this; }
  ~AstNodeType() {}
  void * get_ptr() const { return repr; }
  void *& get_ptr() { return repr; }
};

//! This is the base class for anyone who wants to be notified when AST nodes are being copied.
class AstObserver {
  public:
   virtual void ObserveCopyAst( AstInterfaceImpl& fa, const AstNodePtr& orig, const AstNodePtr& n) = 0;
};

class CopyAstRecord : public ObserveInfo< AstObserver>
{
  AstNodePtr orig, n;
  AstInterfaceImpl& fa;
 public:
  CopyAstRecord(AstInterfaceImpl& _fa, const AstNodePtr& o, const AstNodePtr& _n) 
      : orig(o), n(_n), fa(_fa) {}
  virtual void UpdateObserver( AstObserver& o) const 
         {  o.ObserveCopyAst(fa, orig, n); }
  virtual ~CopyAstRecord() {}
};
 

// AstInterface
/**
 *  @brief  provides an abstract interface to access/modify AST nodes.
 */
class AstInterface 
{
protected:
  AstInterfaceImpl *impl;
  
public:
  typedef ::AstNodePtr AstNodePtr;
  // Adding Robb's meageage mechanism (data member and function).
  static Sawyer::Message::Facility mlog;
  static void initDiagnostics();

  // Types:
  typedef enum {OP_NONE = 0, 
           UOP_MINUS, UOP_ADDR, UOP_DEREF, UOP_ALLOCATE, UOP_NOT,
           UOP_CAST, UOP_INCR1, UOP_DECR1, UOP_BIT_COMPLEMENT,
           BOP_DOT_ACCESS, BOP_ARROW_ACCESS, 
           BOP_TIMES, BOP_DIVIDE, BOP_MOD, BOP_PLUS, BOP_MINUS, 
           BOP_EQ, BOP_LE, BOP_LT, BOP_NE, BOP_GT, BOP_GE, 
           BOP_AND, BOP_OR,
           BOP_BIT_AND,BOP_BIT_OR, BOP_BIT_RSHIFT, BOP_BIT_LSHIFT,
           OP_ARRAY_ACCESS, OP_ASSIGN, OP_UNKNOWN} OperatorEnum;
  // convert the enum type to a string
  static std::string toString (OperatorEnum op);
  typedef void* Ast;
  typedef std::vector<Ast>  AstList;
  typedef std::vector<Ast>  AstNodeList;
  typedef std::vector<AstNodeType> AstTypeList;

  AstInterface(AstInterfaceImpl* __impl) : impl(__impl) {}
  ~AstInterface() {}
  AstInterfaceImpl* get_impl() { return impl; }

  static std::string AstToString( const AstNodePtr& s, bool unparseClassName=true);
  static std::string getAstLocation( const AstNodePtr& s);
  static std::string unparseToString( const AstNodePtr& s);
  AstNodePtr GetRoot() const;
  AstNodePtr getNULL() const { return AstNodePtr(); }
  void SetRoot( const AstNodePtr& root);

  typedef enum { PreOrder, PostOrder, ReversePreOrder, ReversePostOrder, 
                 PreAndPostOrder } TraversalOrderType;
  typedef enum {PreVisit, PostVisit} TraversalVisitType;

  void AttachObserver(AstObserver* ob);
  void DetachObserver(AstObserver* ob);

  static bool get_fileInfo(const AstNodePtr& n, std:: string* fname= 0, int* lineno = 0);

  void InsertStmt( const AstNodePtr& orig, const AstNodePtr& n, 
                   bool before = true, bool extractFromBlock = false);
  void InsertAnnot( const AstNodePtr& n, const std::string& annot, 
                   bool before = true);
  bool ReplaceAst( const AstNodePtr& orig, const AstNodePtr& n);
  bool RemoveStmt( const AstNodePtr& n);
  void FreeAstTree( const AstNodePtr& n);
  AstNodePtr CopyAstTree( const AstNodePtr& n);

  void SetParent(const AstNodePtr& n, const AstNodePtr& p);
  AstNodePtr GetParent( const AstNodePtr &n);
  AstNodePtr GetPrevStmt( const AstNodePtr& s);
  AstNodePtr GetNextStmt( const AstNodePtr& s);
  static AstList GetChildrenList( const AstNodePtr &n);

  bool IsDecls( const AstNodePtr& s) ;
  bool IsVariableDecl( const AstNodePtr& exp, AstList* vars = 0,
                                 AstList* inits = 0);
  bool IsExecutableStmt( const AstNodePtr& s) ;
  static bool IsStatement( const AstNodePtr& s);
  //! Check whether the given AST n is an expresion statement, and if yes, save the expression in the given exp.
  static bool IsExprStmt(const AstNodePtr& n, AstNodePtr* exp = 0);
  //! Check whether the given AST is a block of statements that may include local variables. Save the list of 
  //! statements if true.
  static bool IsBlock( const AstNodePtr& exp, std::string* blockname = 0, AstNodeList* stmts = 0);
  //! Check whether the two given AST are identical syntax trees.
  //! If call_on_diff is given, it is invoked on each pair of different AST nodes, and the pair are treated 
  //! different only if the function returns true.
  static bool AstIdentical(const AstNodePtr& first, const AstNodePtr& second, 
                           std::function<bool(const AstNodePtr& first, const AstNodePtr& second)>* call_on_diff = 0,
                   std::function<bool(const AstNodeType& first, const AstNodeType& second)>* call_on_diff_type = 0);
  //! Check whether the two given AST types are identical syntax trees.
  //! If call_on_diff is given, it is invoked on each pair of different AST nodes, and the pair are treated 
  //! different only if the function returns true.
  static bool AstIdentical(const AstNodeType& first, const AstNodeType& second, 
                           std::function<bool(const AstNodeType& first, const AstNodeType& second)>* call_on_diff = 0);
  //! Check whether the two given lists are identical syntax trees.
  //! If call_on_diff is given, it is invoked on each pair of different AST nodes, and the pair are treated 
  //! different only if the function returns true.
  template <class List, class Node>
  static bool AstIdentical(const List& first, const List& second, 
                           std::function<bool(const Node& first, const Node& second)>* call_on_diff = 0) {
    if (first.size() != second.size()) {
       return false;
    }
    for (typename List::const_iterator p1 = first.begin(), p2 = second.begin();
         p1 != first.end(); p1++, p2++) {
       Node cur1 = *p1, cur2 = *p2;
       if (!AstIdentical(cur1, cur2, call_on_diff)) {
         return false;
       }
    }
    return true;
  }
  AstNodePtr CreateBlock( const AstNodePtr& orig = AstNodePtr()) ;
  /* if flatter_s == true, always flatten s if it is a block*/
  void BlockAppendStmt( AstNodePtr& b, const AstNodePtr& s, bool flatten_s=false);
  void BlockPrependStmt( AstNodePtr& b, const AstNodePtr& s);
  
  static bool IsLoop( const AstNodePtr& s, 
                          AstNodePtr* init=0, AstNodePtr* cond=0,
                         AstNodePtr* incr = 0, AstNodePtr* body = 0) ;
  bool IsPostTestLoop( const AstNodePtr& s);

  //! Check whether $s$ is a Fortran-style loop in the form: for (ivar=lb;ivar<=ub;ivar+=step)
  static bool IsFortranLoop( const AstNodePtr& s, AstNodePtr* ivar = 0,
                       AstNodePtr* lb = 0, AstNodePtr* ub=0,
                       AstNodePtr* step =0, AstNodePtr* body=0);
  AstNodePtr CreateLoop( const AstNodePtr& cond, const AstNodePtr& body); 
  AstNodePtr CreateLoop( const AstNodePtr& ivar, const AstNodePtr& lb, 
                         const AstNodePtr& ub, const AstNodePtr& step, 
                         const AstNodePtr& stmts, bool negativeStep);

  static bool IsIf( const AstNodePtr& s, AstNodePtr* cond = 0, 
                       AstNodePtr* truebody = 0, AstNodePtr* falsebody = 0);

  ///  Creates if-else-statement, or if-statement (if \a __else_stmt is null).
  AstNodePtr
  CreateIf(const AstNodePtr& __cond, const AstNodePtr& __if_stmt, const AstNodePtr& __else_stmt = AST_NULL)  const;

  // I/O Statements (Fortran oriented, to be refined):

  ///  Creates a statement that reads \a __refs from \e stdin.
  AstNodePtr CreateReadStatement(const AstList& __refs) const;

  ///  Creates a statement that writes \a __refs to \e stdout.
  AstNodePtr CreateWriteStatement(const AstList& __vals) const;

  ///  Creates a statement that prints \a __refs to \e stdout.
  AstNodePtr CreatePrintStatement(const AstList& __vals) const;

  ///  Creates an empty statement.
  AstNodePtr CreateNullStatement() const;

  //! Check whether $s$ is a jump (goto, return, continue, break, etc) stmt;
  //! if yes, grab the jump destination in 'dest'
  bool IsGoto( const AstNodePtr& s, AstNodePtr* dest = 0);
  bool IsGotoBefore( const AstNodePtr& s); // goto the point before destination
  bool IsGotoAfter( const AstNodePtr& s); // goto the point after destination
  bool IsLabelStatement( const AstNodePtr& s);
  bool IsReturn(const AstNodePtr& s, AstNodePtr* val=0);

  //!  Returns whether s is a function call, and if yes, returns information
  //!  about its parameters and return values.
  static bool IsFunctionCall( const AstNodePtr& s, AstNodePtr* f = 0, 
                       AstList* args = 0, AstList* outargs = 0, 
                       AstTypeList* paramtypes = 0, AstNodeType* returntype=0);

  //! Returns whether t is a function type and if yes, returns its parameter
  //! types and return type.
  static bool IsFunctionType( const AstNodeType& t, 
                       AstTypeList* paramtypes = 0, AstNodeType* returntype=0);
  bool IsMin(const AstNodePtr& exp);
  bool IsMax(const AstNodePtr& exp);
  AstNodePtr CreateFunctionCall(const std::string& func, AstList::const_iterator args_begin, AstList::const_iterator args_end);
  AstNodePtr CreateFunctionCall(const AstNodePtr& func, AstList::const_iterator args_begin, AstList::const_iterator args_end);

  AstNodePtr GetFunctionDefinition( const AstNodePtr &n, std::string* name=0);
  static bool IsFunctionDefinition(  const AstNodePtr& s, std::string* name = 0,
                    AstList* params = 0, AstList* outpars = 0,
                    AstNodePtr* body = 0,
                    AstTypeList* paramtypes = 0, AstNodeType* returntype=0,
                    bool use_global_unique_name = false);

  static bool IsAssignment( const AstNodePtr& s, AstNodePtr* lhs = 0, 
                               AstNodePtr* rhs = 0, bool* readlhs = 0); 
  AstNodePtr CreateAssignment( const AstNodePtr& lhs, const AstNodePtr& rhs);

  bool IsIOInputStmt( const AstNodePtr& s, AstList* varlist = 0);
  bool IsIOOutputStmt( const AstNodePtr& s, AstList* explist = 0);

  bool IsAddressOfOp( const AstNodePtr& _s);
  bool IsMemoryAccess( const AstNodePtr& s);
  static AstNodePtr IsExpression( const AstNodePtr& s, AstNodeType* exptype =0);
  AstNodeType GetExpressionType( const AstNodePtr& s);

  bool IsConstInt( const AstNodePtr& exp, int* value = 0) ;
  AstNodePtr CreateConstInt( int val)  ;

  //!Check whether $exp$ is a constant value of type int, float, string, etc.
  static bool IsConstant( const AstNodePtr& exp, std::string* valtype=0, std::string* value = 0) ;
  //! Create AST for constant values of  types int, bool, string, float, etc. as well as names of variable and function references. e.g: CreateConstant("memberfunction","floatArray::length")
  AstNodePtr CreateConstant( const std::string& valtype, const std::string& val);

  static std::string GetGlobalUniqueName(const AstNodePtr& exp, std::string expname);
  //! Check whether $exp$ is a variable reference; If yes, return type, name, scope, and global/local etc.
  static bool IsVarRef( const AstNodePtr& exp, AstNodeType* vartype = 0,
                   std::string* varname = 0, AstNodePtr* scope = 0, 
                    bool *isglobal = 0, bool use_global_unique_name=false) ;

  static std::string GetVarName( const AstNodePtr& exp, bool use_global_unique_name = false);

  bool IsSameVarRef( const AstNodePtr& v1, const AstNodePtr& v2);

  /*QY: by default variable declarations are merely saved to be inserted later*/
  std::string NewVar (const AstNodeType& t, const std::string& name = "", 
                bool makeunique = false, bool delayInsert=true,
                const AstNodePtr& declLoc=AstNodePtr(),
                const AstNodePtr& init = AstNodePtr());
  /*Invoke this function to add the list of new variable declarations*/
  void AddNewVarDecls();
  /* copy new var declarations to a new given basic block; by default, the new var declarations are removed from their original block*/
  void CopyNewVarDecls(const AstNodePtr& nblock, bool clearNewVars=true);

  AstNodePtr CreateVarRef( std::string varname, const AstNodePtr& declLoc = AstNodePtr()); 

  bool IsScalarType(const AstNodeType& t);
  bool IsPointerType(const AstNodeType& t);
  static bool IsArrayType(const AstNodeType& t, int* dim = 0, AstNodeType* base = 0, std::string* annotation=0);

  AstNodeType GetType(const std::string& name);
  bool IsCompatibleType( const AstNodeType& t1, const AstNodeType& t2);
  static void GetTypeInfo( const AstNodeType& t, std::string* name = 0, 
                           std::string* stripname = 0, int* size = 0);
  static std::string GetTypeName(const AstNodeType& t) 
     { std::string r; GetTypeInfo(t, &r); return r; }
  static std::string GetBaseTypeName(const AstNodeType& t) 
     { std::string r; GetTypeInfo(t, 0, &r); return r; }

  bool GetArrayBound( const AstNodePtr& arrayname, int dim, int &lb, int &ub) ;
  AstNodeType GetArrayType( const AstNodeType& base, const AstList& indexsize);

  AstNodePtr CreateAllocateArray( const AstNodePtr& arr, const AstNodeType& elemtype, 
                                const AstList& indexsize);
  AstNodePtr CreateDeleteArray( const AstNodePtr& arr);
  static bool IsArrayAccess( const AstNodePtr& s, AstNodePtr* array = 0,
                                   AstList* index = 0)  ;
  static AstNodePtr CreateArrayAccess( const AstNodePtr& arr, const AstNodePtr& index);

  static bool IsBinaryOp(  const AstNodePtr& exp, OperatorEnum* opr=0, 
                    AstNodePtr* opd1 = 0, AstNodePtr* opd2 = 0);
  static bool IsUnaryOp( const AstNodePtr& exp, OperatorEnum* op = 0, 
                   AstNodePtr* opd = 0); 
  AstNodePtr CreateBinaryOP( OperatorEnum op, const AstNodePtr& a0, 
                                   const AstNodePtr& a2);
  AstNodePtr CreateUnaryOP( OperatorEnum op, const AstNodePtr& arg);

  ///  Returns the enclosing block.
  AstNodePtr
  GetParentBlock(const AstNodePtr& __n)
  {
    if (__n == AST_NULL)
      return AST_NULL;

    AstNodePtr p = GetParent(__n);
    while (p != AST_NULL && !IsBlock(p))
      p = GetParent(p);
    return p;
  }

  ///  Returns the enclosing statement.
  AstNodePtr
  GetParentStatement(const AstNodePtr& __n)
  {
    if (__n == AST_NULL)
      return AST_NULL;

    AstNodePtr p = GetParent(__n);
    while (p != AST_NULL && !IsStatement(p))
      p = GetParent(p);
    return p;
  }

  static bool IsFortranLanguage();
};

typedef AstInterface::AstList AstNodeList;
typedef AstInterface::AstTypeList AstTypeList;

//! Interface class for processing each AstNode from within the ReadAstTraverse function.
template <class AstNodePtr>
class ProcessAstNode
{
  public:
    //! return true if asking the traversal to continue; false otherwise
   virtual bool Traverse( AstInterface &fa, const AstNodePtr& n, 
                             AstInterface::TraversalVisitType t) = 0;
};

//! Traverse an entire AST, where $op$ is invoked on each AST node to gather information. 
bool ReadAstTraverse(AstInterface& fa, const AstNodePtr& root, 
                        ProcessAstNode<AstNodePtr>& op, 
                        AstInterface::TraversalOrderType t = AstInterface::PreOrder);

//! Interface class for processing each AstNode from within the TransformAstTraverse function.
class TransformAstTree
{
 public:
    //! return true if asking the traversal to continue; false otherwise
  virtual bool operator()( AstInterface& fa, const AstNodePtr& n, 
                           AstNodePtr& result) = 0;
};

//! Traverse and transform an entire AST, where $op$ is invoked to transform each sub-Tree.
AstNodePtr TransformAstTraverse( AstInterface& fa, const AstNodePtr& r, 
                    bool (*op)( AstInterface& fa, const AstNodePtr& head, 
                                AstNodePtr& result), 
                    AstInterface::TraversalVisitType t = AstInterface::PreVisit );
AstNodePtr TransformAstTraverse( AstInterface& fa, const AstNodePtr& r, 
                              TransformAstTree& op,
                        AstInterface::TraversalVisitType t = AstInterface::PreVisit);

#endif
