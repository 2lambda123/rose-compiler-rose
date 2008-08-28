#ifndef ROSE_SAGE_BUILDER_INTERFACE
#define ROSE_SAGE_BUILDER_INTERFACE

#include "rose.h"
#include <string>

/*!
  \defgroup frontendSageHighLevelInterface High level AST builders
  \ingroup ROSE_FrontEndGroup
  \brief This namespace contains high level SAGE III AST node and subtree builders

  Building AST trees using raw SgNode constructors is tedious and error-prone. It becomes 
  even more difficult with the presence of symbol tables. This namespace contains major
  AST node builders on top of the constructors to take care of symbol tables, various
  edges to scope,  parent and so on.

  \authors Chunhua Liao (last modified 2/12/2008)
  
*/
namespace SageBuilder{

#if 0
//---------------------AST creation/building/construction-----------------
  SgExpression* buildConst(SgType* t, const string & val);
  SgExpression* buildConstInt(int val);

  // build sth in languages, but not in SAGE AST
  // how to specify position info?  then

  SgClassDeclaration* buildClassDeclaration(...,class_type);
  // or
  SgClassDeclaration* buildStruct(...);
  SgClassDeclaration* buildClass(...);
  SgClassDeclaration* buildUnion(...);

  // build B from dependent A
 SgTemplateInstantiationMemberFunctionDecl*  buildForwardFunctionDeclaration
     (SgTemplateInstantiationMemberFunctionDecl * memberFunctionInstantiation);

  //previous attempt: src/midend/astUtil/astInterface
  //  AstNodePtr AstInterface::CreateConst( const string& val, const string& valtype) const
  //  AstNodePtr AstInterfaceBase::CreateConstInt( int val)
#endif

//----------------------------------------------------------
//@{
/*! @name Scope stack interfaces
    \brief  a global data structure to store current scope and parent scopes. 

Scope stack is provided as an alternative to manually passing scope parameters to builder functions. It is not required to be used. Please use the recommendeded operation functions for maintaining the scope stack. Don't use raw container access functions to ScopeStack.  e.g. avoid ScopeStack.push_back(), using pushScopeStack() instead. 

 \todo consider complex cases:   
	- how many scope stacks to keep? one. examine only one transparently
	- regular: push a child scope of current scope, add symbols etc.
	- irregular: push an arbitrary scope temporarily,  add some symbol, then pop
	- even push a chain of scopes
	- restore scopes
*/

/*! \brief intended to be a private member, don't access it directly. could be changed any time
*/
extern std::list<SgScopeStatement*> ScopeStack;

//! Public interfaces of the scope stack, should be stable
void pushScopeStack (SgScopeStatement* stmt);
void pushScopeStack (SgNode* node);
void popScopeStack();
SgScopeStatement* topScopeStack() ;
bool emptyScopeStack();
void clearScopeStack();
   
//@} 

//--------------------------------------------------------------
//@{
/*! @name Builders for SgType
  \brief Builders for simple and complex SgType nodes, such as integer type, function type, array type, struct type, etc.

  \todo SgModifierType,SgNamedType(SgClassType,SgEnumType,SgTypedefType), SgQualifiedNameType, SgTemplateType,SgTypeComplex, SgTypeDefault,SgTypeEllipse,SgTypeGlobalVoid,SgTypeImaginary
*/

//! Built in simple types
SgTypeBool *  buildBoolType();
SgTypeChar *  buildCharType();
SgTypeDouble* buildDoubleType();
SgTypeFloat*  buildFloatType();
SgTypeInt *   buildIntType();
SgTypeLong*    buildLongType();
SgTypeLongDouble* buildLongDoubleType();
SgTypeLongLong * buildLongLongType();
SgTypeShort*    buildShortType();
SgTypeString* buildStringType();
SgTypeVoid * buildVoidType();
SgTypeWchar* buildWcharType();

SgTypeSignedChar*  buildSignedCharType();
SgTypeSignedInt*   buildSignedIntType();
SgTypeSignedLong*  buildSignedLongType();
SgTypeSignedShort* buildSignedShortType();

SgTypeUnsignedChar* buildUnsignedCharType();
SgTypeUnsignedInt* buildUnsignedIntType();
SgTypeUnsignedLong*    buildUnsignedLongType();
SgTypeUnsignedLongLong*    buildUnsignedLongLongType();
SgTypeUnsignedShort*    buildUnsignedShortType();

//! Build a pointer type
SgPointerType* buildPointerType(SgType *base_type = NULL);

//! Build a reference type
SgReferenceType* buildReferenceType(SgType *base_type = NULL);

//! Build a const type.
SgType* buildConstType(SgType* base_type = NULL);

//! Build a volatile type.
SgType* buildVolatileType(SgType* base_type = NULL);

//! Build a restrict type.
SgType* buildRestrictType(SgType* base_type);

//! Build ArrayType
SgArrayType* buildArrayType(SgType* base_type=NULL, SgExpression* index=NULL);

//! Build function type from return type and parameter type list
SgFunctionType * 
buildFunctionType(SgType* return_type, SgFunctionParameterTypeList * typeList=NULL);

//! Build function type from return type and parameter list
SgFunctionType * 
buildFunctionType(SgType* return_type, SgFunctionParameterList * argList=NULL);
 //! Build an opaque type with a name, useful when a type's details are unknown during transformation, especially for a runtime library's internal type. Must provide scope here. 
 /*! Some types are not known during translation but nevertheless are needed. For example, some 
  * internal types from a runtime library.  To work around this problem: this function prepends a hidden typedef declaration into scope
  * 'typedef int OpaqueTypeName;' 
  * The translation-generated code is expected to include the runtime library's headers to 
  * have the real type declarations. 
  */
SgType* buildOpaqueType(std::string const type_name, SgScopeStatement * scope);
//@}

//--------------------------------------------------------------
//@{
/*! @name Builders for expressions
  \brief handle side effects of parent pointers, Sg_File_Info, lvalue etc.

Expressions are usually built using bottomup approach, i.e. buiding operands first, then the expression operating on the operands. It is also possible to build expressions with NULL operands or empty values first, then set them afterwards. 
  - Value string is not included in the argument list for simplicty. It can be set afterwards using set_valueString()
  - Expression builders are organized roughtly in the order of class hierarchy list of ROSE Web Reference
  - default values for arguments are provided to support top-down construction. Should use SageInterface::setOperand(),setLhsOperand(), setRhsOperand() etc to set operands and handle side effects.
  \todo SgActualArgumentExpression, SgAsmOp, SgAsteriskShapeExp, 
  SgValueExp, SgEnumVal,
  SgThrowOp,
*/
//! Build a null expression
SgNullExpression* buildNullExpression();
SgNullExpression* buildNullExpressionFi(Sg_File_Info* start, Sg_File_Info* end);

//! Build a bool value expression, the name convention of SgBoolValExp is little different from others for some unknown reason
SgBoolValExp* buildBoolValExp(int value = 0);
SgBoolValExp* buildBoolValExp(bool value = 0);
SgBoolValExp* buildBoolValExpFi(int value, Sg_File_Info* start, Sg_File_Info* end);

SgCharVal* buildCharVal(char value = 0);
SgCharVal* buildCharValFi(char value, const std::string& str, Sg_File_Info* start, Sg_File_Info* end);

SgComplexVal* buildComplexVal(long double real_value = 0.0, long double imaginary_value = 0.0 );

//! Build a double value expression
SgDoubleVal* buildDoubleVal(double value = 0.0);

SgFloatVal* buildFloatVal(float value = 0.0);

//! Build an integer value expression
SgIntVal* buildIntVal(int value = 0);
SgIntVal* buildIntValHex(int value = 0);

SgLongDoubleVal* buildLongDoubleVal(long double value = 0.0);

SgShortVal* buildShortVal(short value = 0);
SgShortVal* buildShortValHex(short value = 0);

SgStringVal* buildStringVal(std::string value="");

//! Build an unsigned char
SgUnsignedCharVal* buildUnsignedCharVal(unsigned char v = 0);
SgUnsignedCharVal* buildUnsignedCharValHex(unsigned char v = 0);

//! Build an unsigned short integer
SgUnsignedShortVal* buildUnsignedShortVal(unsigned short v = 0);
SgUnsignedShortVal* buildUnsignedShortValHex(unsigned short v = 0);

//! Build an unsigned integer
SgUnsignedIntVal* buildUnsignedIntVal(unsigned int v = 0);
SgUnsignedIntVal* buildUnsignedIntValHex(unsigned int v = 0);

//! Build a unsigned long integer
SgUnsignedLongVal* buildUnsignedLongVal(unsigned long v = 0);
SgUnsignedLongVal* buildUnsignedLongValHex(unsigned long v = 0);

//! Build an unsigned long long integer
SgUnsignedLongLongIntVal* buildUnsignedLongLongIntVal(unsigned long long v = 0);
SgUnsignedLongLongIntVal* buildUnsignedLongLongIntValHex(unsigned long long v = 0);

//! Build UPC THREADS (integer expression)
SgUpcThreads* buildUpcThreads();

//! Build UPC  MYTHREAD (integer expression)
SgUpcMythread* buildUpcMythread();

//!  Template function to build a unary expression of type T. Instantiated functions include:buildAddressOfOp(),buildBitComplementOp(),buildBitComplementOp(),buildMinusOp(),buildNotOp(),buildPointerDerefExp(),buildUnaryAddOp(),buildMinusMinusOp(),buildPlusPlusOp(). 
/*! The instantiated functions' prototypes are not shown since they are expanded using macros.
 * Doxygen is not smart enough to handle macro expansion. 
 */
template <class T> T* buildUnaryExpression(SgExpression* operand = NULL);
//!  Template function to build a unary expression of type T with advanced information specified such as parenthesis and file info. Instantiated functions include:buildAddressOfOp(),buildBitComplementOp(),buildBitComplementOp(),buildMinusOp(),buildNotOp(),buildPointerDerefExp(),buildUnaryAddOp(),buildMinusMinusOp(),buildPlusPlusOp(). 
/*! The instantiated functions' prototypes are not shown since they are expanded using macros.
 * Doxygen is not smart enough to handle macro expansion. 
 */
template <class T> T* buildUnaryExpressionFi(SgExpression* operand, bool needParen, Sg_File_Info* start, Sg_File_Info* end, Sg_File_Info* opPos);

#define BUILD_UNARY_PROTO(suffix) \
Sg##suffix * build##suffix(SgExpression* op =NULL); \
Sg##suffix * build##suffix##Fi(SgExpression* op, bool needParen, Sg_File_Info* start, Sg_File_Info* end, Sg_File_Info* opPos);

BUILD_UNARY_PROTO(AddressOfOp)
BUILD_UNARY_PROTO(BitComplementOp)
BUILD_UNARY_PROTO(MinusOp)
BUILD_UNARY_PROTO(NotOp)
BUILD_UNARY_PROTO(PointerDerefExp)
BUILD_UNARY_PROTO(UnaryAddOp)
BUILD_UNARY_PROTO(MinusMinusOp)
BUILD_UNARY_PROTO(PlusPlusOp)

//! Build a type casting expression
SgCastExp * buildCastExp(SgExpression *  operand_i = NULL,
		SgType * expression_type = NULL,
		SgCastExp::cast_type_enum cast_type = SgCastExp::e_C_style_cast);
//! Build -- expression, Sgop_mode is a value of either SgUnaryOp::prefix or SgUnaryOp::postfix
SgMinusMinusOp *buildMinusMinusOp(SgExpression* operand_i, SgUnaryOp::Sgop_mode  a_mode);

//! Build ++x or x++ , specify prefix or postfix using either SgUnaryOp::prefix or SgUnaryOp::postfix
SgPlusPlusOp* buildPlusPlusOp(SgExpression* operand_i, SgUnaryOp::Sgop_mode  a_mode);

#undef BUILD_UNARY_PROTO

//! Template function to build a binary expression of type T, taking care of parent pointers, file info, lvalue, etc. Available instances include: buildAddOp(), buildAndAssignOp(), buildAndOp(), buildArrowExp(),buildArrowStarOp(), buildAssignOp(),buildBitAndOp(),buildBitOrOp(),buildBitXorOp(),buildCommaOpExp(), buildConcatenationOp(),buildDivAssignOp(),buildDivideOp(),buildDotExp(),buildEqualityOp(),buildExponentiationOp(),buildGreaterOrEqualOp(),buildGreaterThanOp(),buildIntegerDivideOp(),buildIorAssignOp(),buildLessOrEqualOp(),buildLessThanOp(),buildLshiftAssignOp(),buildLshiftOp(),buildMinusAssignOp(),buildModAssignOp(),buildModOp(),buildMultAssignOp(),buildMultiplyOp(),buildNotEqualOp(),buildOrOp(),buildPlusAssignOp(),buildPntrArrRefExp(),buildRshiftAssignOp(),buildRshiftOp(),buildScopeOp(),buildSubtractOp()buildXorAssignOp()
/*! The instantiated functions' prototypes are not shown since they are expanded using macros.
 * Doxygen is not smart enough to handle macro expansion. 
 */
template <class T> T* buildBinaryExpression(SgExpression* lhs =NULL, SgExpression* rhs =NULL);
//! Template function to build a binary expression of type T,with extra information for parenthesis and file info,  Instantiated functions include: buildAddOp(), buildAndAssignOp(), buildAndOp(), buildArrowExp(),buildArrowStarOp(), buildAssignOp(),buildBitAndOp(),buildBitOrOp(),buildBitXorOp(),buildCommaOpExp(), buildConcatenationOp(),buildDivAssignOp(), buildDivideOp(),buildDotExp(),buildEqualityOp(),buildExponentiationOp(),buildGreaterOrEqualOp(),buildGreaterThanOp(),buildIntegerDivideOp(),buildIorAssignOp(),buildLessOrEqualOp(),buildLessThanOp(),buildLshiftAssignOp(),buildLshiftOp(),buildMinusAssignOp(),buildModAssignOp(),buildModOp(),buildMultAssignOp(),buildMultiplyOp(),buildNotEqualOp(),buildOrOp(),buildPlusAssignOp(),buildPntrArrRefExp(),buildRshiftAssignOp(),buildRshiftOp(),buildScopeOp(),buildSubtractOp()buildXorAssignOp()
/*! The instantiated functions' prototypes are not shown since they are expanded using macros.
 * Doxygen is not smart enough to handle macro expansion. 
 */
template <class T>
T* buildBinaryExpressionFi(SgExpression* lhs, SgExpression* rhs, bool needParen, Sg_File_Info* start, Sg_File_Info* end, Sg_File_Info* opPos);

#define BUILD_BINARY_PROTO(suffix) \
Sg##suffix * build##suffix(SgExpression* lhs =NULL, SgExpression* rhs =NULL); \
Sg##suffix * build##suffix##Fi(SgExpression* lhs, SgExpression* rhs, bool needParen, Sg_File_Info* start, Sg_File_Info* end, Sg_File_Info* opPos);

BUILD_BINARY_PROTO(AddOp)
BUILD_BINARY_PROTO(AndAssignOp)
BUILD_BINARY_PROTO(AndOp)
BUILD_BINARY_PROTO(ArrowExp)
BUILD_BINARY_PROTO(ArrowStarOp)
BUILD_BINARY_PROTO(AssignOp)
BUILD_BINARY_PROTO(BitAndOp)
BUILD_BINARY_PROTO(BitOrOp)
BUILD_BINARY_PROTO(BitXorOp)

BUILD_BINARY_PROTO(CommaOpExp)
BUILD_BINARY_PROTO(ConcatenationOp)
BUILD_BINARY_PROTO(DivAssignOp)
BUILD_BINARY_PROTO(DivideOp)
BUILD_BINARY_PROTO(DotExp)
BUILD_BINARY_PROTO(EqualityOp)

BUILD_BINARY_PROTO(ExponentiationOp)
BUILD_BINARY_PROTO(GreaterOrEqualOp)
BUILD_BINARY_PROTO(GreaterThanOp)
BUILD_BINARY_PROTO(IntegerDivideOp)
BUILD_BINARY_PROTO(IorAssignOp)

BUILD_BINARY_PROTO(LessOrEqualOp)
BUILD_BINARY_PROTO(LessThanOp)
BUILD_BINARY_PROTO(LshiftAssignOp)
BUILD_BINARY_PROTO(LshiftOp)

BUILD_BINARY_PROTO(MinusAssignOp)
BUILD_BINARY_PROTO(ModAssignOp)
BUILD_BINARY_PROTO(ModOp)
BUILD_BINARY_PROTO(MultAssignOp)
BUILD_BINARY_PROTO(MultiplyOp)

BUILD_BINARY_PROTO(NotEqualOp)
BUILD_BINARY_PROTO(OrOp)
BUILD_BINARY_PROTO(PlusAssignOp)
BUILD_BINARY_PROTO(PntrArrRefExp)
BUILD_BINARY_PROTO(RshiftAssignOp)

BUILD_BINARY_PROTO(RshiftOp)
BUILD_BINARY_PROTO(ScopeOp)
BUILD_BINARY_PROTO(SubtractOp)
BUILD_BINARY_PROTO(XorAssignOp)

#undef BUILD_BINARY_PROTO

//! Build a conditional expression ?:
SgConditionalExp * buildConditionalExp(SgExpression* test =NULL, SgExpression* a =NULL, SgExpression* b =NULL);

//! Build a SgExprListExp, used for function call parameter list etc.
SgExprListExp * buildExprListExp(SgExpression * expr1 = NULL, SgExpression* expr2 = NULL, SgExpression* expr3 = NULL, SgExpression* expr4 = NULL, SgExpression* expr5 = NULL, SgExpression* expr6 = NULL, SgExpression* expr7 = NULL, SgExpression* expr8 = NULL, SgExpression* expr9 = NULL, SgExpression* expr10 = NULL);


//! Build SgVarRefExp based on a variable's Sage name. It will lookup symbol table internally starting from scope. A variable name is unique so type can be inferred (double check this).

/*! 
It is possible to build a reference to a variable with known name before the variable is declaration, especially during bottomup construction of AST. In this case, SgTypeUnknown is used to indicate the variable reference needing postprocessing fix using fixVariableReferences() once the AST is complete and all variable declarations exist. But the side effect is some get_type() operation may not recognize the unknown type before the fix. So far, I extended SgPointerDerefExp::get_type() and SgPntrArrRefExp::get_type() for SgTypeUnknown. There may be others needing the same extension. 
*/
SgVarRefExp *
buildVarRefExp(const SgName& name, SgScopeStatement* scope=NULL);

//! Build SgVarRefExp based on a variable's name. It will lookup symbol table internally starting from scope. A variable is unique so type can be inferred.
SgVarRefExp *
buildVarRefExp(const std::string& varName, SgScopeStatement* scope=NULL);

//! Build a variable reference using a C style char array
SgVarRefExp *
buildVarRefExp(const char* varName, SgScopeStatement* scope=NULL);

//! Build a variable reference from an existing symbol
SgVarRefExp *
buildVarRefExp(SgVariableSymbol* varSymbol);

//! Build a variable reference from an existing variable declaration. The assumption is a SgVariableDeclartion only declares one variable in the ROSE AST.
SgVarRefExp *
buildVarRefExp(SgVariableDeclaration* vardecl);
 
//!build a variable reference from an initialized name
//! It first tries to grab the associated symbol, then call buildVarRefExp(const SgName& name, SgScopeStatement*) if symbol does not exist.
SgVarRefExp *
buildVarRefExp(SgInitializedName* initname, SgScopeStatement* scope=NULL);

//!Build a variable reference expression at scope to an opaque variable which has unknown information except for its name.  Used when referring to an internal variable defined in some headers of runtime libraries.(The headers are not yet inserted into the file during translation). Similar to buildOpaqueType(); 
/*! It will declare a hidden int varName  at the specified scope to cheat the AST consistence tests.
 */
SgVarRefExp* 
buildOpaqueVarRefExp(const std::string& varName,SgScopeStatement* scope=NULL);

//! Build SgFunctionRefExp based on a C++ function's name and function type. It will lookup symbol table internally starting from scope. A hidden prototype will be created internally to introduce a new function symbol if the function symbol cannot be found. 
SgFunctionRefExp *
buildFunctionRefExp(const SgName& name, const SgType* func_type, SgScopeStatement* scope=NULL);

SgFunctionRefExp *
buildFunctionRefExp(const char* name, const SgType* func_type, SgScopeStatement* scope=NULL);

//! Build SgFunctionRefExp based on a C function's name. It will lookup symbol table internally starting from scope and return the first matching function.
SgFunctionRefExp *
buildFunctionRefExp(const SgName& name,SgScopeStatement* scope=NULL);

SgFunctionRefExp *
buildFunctionRefExp(const char* name,SgScopeStatement* scope=NULL);

//! Build SgFunctionRefExp based on a function's symbol.
SgFunctionRefExp *
buildFunctionRefExp(SgFunctionSymbol* sym);

//! Build a function call expression
SgFunctionCallExp* 
buildFunctionCallExp(SgFunctionSymbol* sym, SgExprListExp* parameters);

//! Build a function call expression,it will automatically search for function symbols internally to build a right function reference etc.
SgFunctionCallExp* 
buildFunctionCallExp(const SgName& name, SgType* return_type, \
                SgExprListExp* parameters, SgScopeStatement* scope=NULL);

//! Build the rhs of a variable declaration which includes an assignment
SgAssignInitializer * buildAssignInitializer(SgExpression * operand_i = NULL);

//! Build an aggregate initializer
SgAggregateInitializer * buildAggregateInitializer(SgExprListExp * initializers = NULL);

//! Build sizeof() expression with an expression parameter
SgSizeOfOp* buildSizeOfOp(SgExpression* exp= NULL);

//! Build sizeof() expression with a type parameter
SgSizeOfOp* buildSizeOfOp(SgType* type = NULL);



//@}

//--------------------------------------------------------------
//@{
/*! @name Builders for support nodes
  \brief AST high level builders for SgSupport nodes

*/
//! Initialized names are tricky, their scope vary depending on context, so scope and symbol information are not needed until the initialized name is being actually used somewhere.

/*!e.g the scope of arguments of functions are different for defining and nondefining functions.
*/ 
SgInitializedName* buildInitializedName(const SgName & name, SgType* type);
SgInitializedName* buildInitializedName(const std::string &name, SgType* type);
SgInitializedName* buildInitializedName(const char* name, SgType* type);

//! Build SgFunctionParameterTypeList from SgFunctionParameterList
SgFunctionParameterTypeList * 
buildFunctionParameterTypeList(SgFunctionParameterList * paralist);

//! Build SgFunctionParameterTypeList from an expression list, useful when building a function call
SgFunctionParameterTypeList *
buildFunctionParameterTypeList(SgExprListExp * expList);

//--------------------------------------------------------------
//@{
/*! @name Builders for statements
  \brief AST high level builders for SgStatement, explicit scope parameters are allowed for flexibility. 
  Please use SageInterface::appendStatement(), prependStatement(), and insertStatement() to attach the newly built statements into an AST tree. Calling member functions like SgScopeStatement::prepend_statement() or using container functions such as pushback() is discouraged since they don't handle many side effects for symbol tables, source file information, scope and parent pointers etc.

*/

//! Build a variable declaration, handle symbol table transparently
SgVariableDeclaration* 
buildVariableDeclaration(const SgName & name, SgType *type, SgInitializer *varInit=NULL, SgScopeStatement* scope=NULL);

SgVariableDeclaration* 
buildVariableDeclaration(const std::string & name, SgType *type, SgInitializer *varInit=NULL, SgScopeStatement* scope=NULL);

SgVariableDeclaration* 
buildVariableDeclaration(const char* name, SgType *type, SgInitializer *varInit=NULL, SgScopeStatement* scope=NULL);

//!Build a typedef declaration, such as: typedef int myint; 
SgTypedefDeclaration* 
buildTypedefDeclaration(const std::string& name, SgType* base_type);

//! Build an empty SgFunctionParameterList, possibly with some initialized names filled in
SgFunctionParameterList * buildFunctionParameterList(SgInitializedName* in1 = NULL, SgInitializedName* in2 = NULL, SgInitializedName* in3 = NULL, SgInitializedName* in4 = NULL, SgInitializedName* in5 = NULL, SgInitializedName* in6 = NULL, SgInitializedName* in7 = NULL, SgInitializedName* in8 = NULL, SgInitializedName* in9 = NULL, SgInitializedName* in10 = NULL);

//! Build an SgFunctionParameterList from SgFunctionParameterTypeList, like (int, float,...), used for parameter list of prototype functions when function type( including parameter type list) is known.
SgFunctionParameterList*
buildFunctionParameterList(SgFunctionParameterTypeList * paraTypeList);

//! A template function for function prototype declaration builders
template <class actualFunction>
actualFunction*
buildNondefiningFunctionDeclaration_T \
(const SgName & name, SgType* return_type, SgFunctionParameterList * paralist, SgScopeStatement* scope=NULL);

//! Build a prototype for a function, handle function type, symbol etc transparently
SgFunctionDeclaration *
buildNondefiningFunctionDeclaration (const SgName & name, SgType* return_type, SgFunctionParameterList *parlist, SgScopeStatement* scope=NULL);

//! Build a prototype for an existing function declaration (defining or nondefining is fine) 
SgFunctionDeclaration *
buildNondefiningFunctionDeclaration (const SgFunctionDeclaration* funcdecl, SgScopeStatement* scope=NULL);

//! Build a prototype member function declaration
SgMemberFunctionDeclaration *
buildNondefiningMemberFunctionDeclaration (const SgName & name, SgType* return_type, SgFunctionParameterList *parlist, SgScopeStatement* scope=NULL);

//! Build a defining ( non-prototype) member function declaration
SgMemberFunctionDeclaration *
buildDefiningMemberFunctionDeclaration (const SgName & name, SgType* return_type, SgFunctionParameterList *parlist, SgScopeStatement* scope=NULL);

//! A template function for function declaration builders
template <class actualFunction>
actualFunction *
buildDefiningFunctionDeclaration_T (const SgName & name, SgType* return_type, SgFunctionParameterList * parlist, SgScopeStatement* scope=NULL);

//! Build a function declaration with a function body
SgFunctionDeclaration *
buildDefiningFunctionDeclaration (const SgName & name, SgType* return_type, SgFunctionParameterList * parlist, SgScopeStatement* scope=NULL);

SgFunctionDeclaration *
buildDefiningFunctionDeclaration (const std::string & name, SgType* return_type, SgFunctionParameterList * parlist, SgScopeStatement* scope=NULL);

SgFunctionDeclaration *
buildDefiningFunctionDeclaration (const char* name, SgType* return_type, SgFunctionParameterList * parlist, SgScopeStatement* scope=NULL);

//! Build a function call statement
SgExprStatement*
buildFunctionCallStmt(const SgName& name, SgType* return_type, SgExprListExp* parameters, SgScopeStatement* scope=NULL);

//! Build a label statement, handling label symbol and scope internally.

//! Note that the scope of a label statement is special. It is SgFunctionDefinition,
//! not the closest scope statement such as SgBasicBlock. 
SgLabelStatement * buildLabelStatement(const SgName& name, SgStatement * stmt = NULL, SgScopeStatement* scope=NULL);

//! Build a goto statement
SgGotoStatement * buildGotoStatement(SgLabelStatement *  label=NULL,SgScopeStatement* scope=NULL);

//! Build a case option statement
SgCaseOptionStmt * buildCaseOptionStmt( SgExpression * key = NULL,SgStatement *body = NULL);

//! Build a default option statement
SgDefaultOptionStmt * buildDefaultOptionStmt( SgStatement *body = NULL);

//! Build a SgExprStatement, set File_Info automatically 
SgExprStatement*
buildExprStatement(SgExpression*  exp = NULL);

//! Build a switch statement
SgSwitchStatement* buildSwitchStatement(SgStatement *item_selector = NULL,SgBasicBlock *body = NULL);
inline SgSwitchStatement* buildSwitchStatement(SgExpression *item_selector, SgBasicBlock *body = NULL) {
  return buildSwitchStatement(buildExprStatement(item_selector), body);
}

//! Build if statement
SgIfStmt * buildIfStmt(SgStatement* conditional, SgStatement * true_body, SgStatement * false_body);
inline SgIfStmt * buildIfStmt(SgExpression* conditional, SgStatement * true_body, SgStatement * false_body) {
  return buildIfStmt(buildExprStatement(conditional), true_body, false_body);
}

//!Build a for statement, assume none of the arguments is NULL
SgForStatement * buildForStatement(SgStatement* initialize_stmt,  SgStatement * test, SgExpression * increment, SgStatement * loop_body);

//! Build while statement
SgWhileStmt * buildWhileStmt(SgStatement *  condition, SgStatement *body);
inline SgWhileStmt * buildWhileStmt(SgExpression *  condition, SgStatement *body) {
  return buildWhileStmt(buildExprStatement(condition), body);
}

//! Build pragma declaration, handle SgPragma and defining/nondefining pointers internally
SgPragmaDeclaration * buildPragmaDeclaration(const std::string & name, SgScopeStatement* scope=NULL);

//! Build a SgBasicBlock, setting file info internally
SgBasicBlock * buildBasicBlock(SgStatement * stmt1 = NULL, SgStatement* stmt2 = NULL, SgStatement* stmt3 = NULL, SgStatement* stmt4 = NULL, SgStatement* stmt5 = NULL, SgStatement* stmt6 = NULL, SgStatement* stmt7 = NULL, SgStatement* stmt8 = NULL, SgStatement* stmt9 = NULL, SgStatement* stmt10 = NULL);

//! Build an assignment statement from lefthand operand and right hand operand 
SgExprStatement* 
buildAssignStatement(SgExpression* lhs,SgExpression* rhs);

//! Build a break statement
SgBreakStmt* buildBreakStmt();

//! Build a continue statement
SgContinueStmt* buildContinueStmt();

//! Build a class definition scope statement
SgClassDefinition* buildClassDefinition(SgClassDeclaration *d = NULL);

//! Build a structure, It is also a declaration statement in SAGE III
SgClassDeclaration * buildStructDeclaration(const SgName& name, SgScopeStatement* scope=NULL);
SgClassDeclaration * buildStructDeclaration(const std::string& name, SgScopeStatement* scope=NULL);
SgClassDeclaration * buildStructDeclaration(const char* name, SgScopeStatement* scope=NULL);

//! Build a return statement
SgReturnStmt* buildReturnStmt(SgExpression* expression = NULL);

//! Build a NULL statement
SgNullStatement* buildNullStatement();

//Build a statement from an arbitrary string, used for irregular statements with macros, platform-specified attributes etc.
//This does not work properly since the global scope expects declaration statement, not just SgNullStatement
//SgStatement* buildStatementFromString(std::string str);

//@}

//--------------------------------------------------------------
//@{
/*! @name Builders for others
  \brief AST high level builders for others 

*/
//! Build a SgFile node and attach it to SgProject 
/*! The input file will be loaded if exists, or an empty one will be generated from scratch transparently. Output file name is used to specify the output file name of unparsing. The final SgFile will be inserted to project automatically. If not provided, a new SgProject will be generated internally. Using SgFile->get_project() to retrieve it in this case.
 */
SgFile* buildFile(const std::string& inputFileName,const std::string& outputFileName, SgProject* project=NULL);

//! Build and attach a comment, comment style is inferred from the language type of the target node if not provided. It is indeed a wrapper of SageInterface::attachComment().
PreprocessingInfo* buildComment(SgLocatedNode* target, const std::string & content,
               PreprocessingInfo::RelativePositionType position=PreprocessingInfo::before,
               PreprocessingInfo::DirectiveType dtype= PreprocessingInfo::CpreprocessorUnknownDeclaration);

//! Build and attach #define XX directives, pass "#define xxx xxx" as content.
PreprocessingInfo* buildCpreprocessorDefineDeclaration(SgLocatedNode* target, 
                const std::string & content,
               PreprocessingInfo::RelativePositionType position=PreprocessingInfo::before);
//@}

} // end of namespace
#endif //ROSE_SAGE_BUILDER_INTERFACE
