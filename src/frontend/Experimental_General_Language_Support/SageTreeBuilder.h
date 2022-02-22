#ifndef ROSE_SAGE_TREE_BUILDER_H_
#define ROSE_SAGE_TREE_BUILDER_H_

#include "general_language_translation.h"
#include "PosInfo.h"
#include "Tokens.h"
#include <boost/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <sstream>

// WARNING: This file has been designed to compile with -std=c++17
// This limits the use of ROSE header files at the moment.
//
class SgBasicBlock;
class SgCaseOptionStmt;
class SgCastExp;
class SgCommonBlock;
class SgCommonBlockObject;
class SgContainsStatement;
class SgDefaultOptionStmt;
class SgDerivedTypeStatement;
class SgEnumDeclaration;
class SgEnumType;
class SgEnumVal;
class SgExpression;
class SgExprListExp;
class SgExprStatement;
class SgFunctionCallExp;
class SgFunctionDeclaration;
class SgFunctionDefinition;
class SgFunctionParameterList;
class SgFunctionParameterScope;
class SgGlobal;
class SgIfStmt;
class SgImplicitStatement;
class SgInitializedName;
class SgLocatedNode;
class SgModuleStatement;
class SgNamedType;
class SgNamespaceDeclarationStatement;
class SgPntrArrRefExp;
class SgPointerType;
class SgPrintStatement;
class SgProcessControlStatement;
class SgProgramHeaderStatement;
class SgReplicationOp;
class SgReturnStmt;
class SgScopeStatement;
class SgSourceFile;
class SgSwitchStatement;
class SgType;
class SgTypedefDeclaration;
class SgVariableDeclaration;
class SgUseStatement;
class SgVarRefExp;
class SgWhileStmt;

namespace Rose {
namespace builder {

// This is similar to F18 Fortran::parser::SourcePosition
struct SourcePosition {
   std::string path;  // replaces Fortran::parser::SourceFile
   int line, column;
};

struct TraversalContext {
  TraversalContext() : type(nullptr), is_initialization(false),
                       actual_function_param_scope(nullptr) {}
  SgType* type;
  bool is_initialization;
  SgScopeStatement* actual_function_param_scope;
};

//using SourcePositionPair = boost::tuple<SourcePosition, SourcePosition>;
//using SourcePositions    = boost::tuple<SourcePosition, SourcePosition, SourcePosition>;
typedef boost::tuple<SourcePosition, SourcePosition> SourcePositionPair;
typedef boost::tuple<SourcePosition, SourcePosition, SourcePosition> SourcePositions;

SgGlobal* initialize_global_scope(SgSourceFile* file);

// Create a builder class that does nothing
class SageTreeBuilderNull {
public:
   // Default action for a sage tree node is to do nothing.
   template<typename T, typename... Options> void Enter(T* &, Options...) {}
   template<typename T>                      void Leave(T*) {}
};


class SageTreeBuilder {
public:

   enum class LanguageEnum{Fortran, Jovial};

   // C++11: disallow default constructor, ...
   SageTreeBuilder() = delete;
   SageTreeBuilder(const SageTreeBuilder &) = delete;
   SageTreeBuilder &operator=(const SageTreeBuilder &) = delete;
   SageTreeBuilder(SageTreeBuilder &&) = delete;
   SageTreeBuilder &operator=(SageTreeBuilder &&) = delete;

   SageTreeBuilder(SgSourceFile* source, LanguageEnum language, std::istringstream &tokens);

   // WARNING: this constructor requires source_ to be set before usage (called by flang main)
   SageTreeBuilder(LanguageEnum language) : language_{language}, source_{nullptr} {
     // Sort out how to get token stream from flang
     tokens_ = new TokenStream(iss_empty_);
   }
   void setSourceFile(SgSourceFile* source) {
     source_ = source;
   }

   const TokenStream& getTokens() {
     return *tokens_;
   }

   // Default action for a sage tree node is to do nothing.
   template<typename T> void Enter(T* &) {}
   template<typename T> void Leave(T*)   {}

   void Enter(SgScopeStatement* &);
   void Leave(SgScopeStatement*);

   void Enter(SgBasicBlock* &);
   void Leave(SgBasicBlock*);

   void Enter(SgProgramHeaderStatement* &,
              const boost::optional<std::string> &, const std::vector<std::string> &, const SourcePositions &);
   void Leave(SgProgramHeaderStatement*);

   void setFortranEndProgramStmt(SgProgramHeaderStatement*,
                                 const boost::optional<std::string> &,
                                 const boost::optional<std::string> &);

   void Enter(SgFunctionParameterList* &, SgScopeStatement* &, const std::string &, SgType*, bool);
   void Leave(SgFunctionParameterList*, SgScopeStatement*, const std::list<LanguageTranslation::FormalParameter> &);
   void Leave(SgFunctionParameterList*, SgScopeStatement*, const std::list<std::string> &);

   void Enter(SgFunctionDeclaration* &, const std::string &, SgType*, SgFunctionParameterList*,
                                        const LanguageTranslation::FunctionModifierList &, bool);
   void Leave(SgFunctionDeclaration*, SgScopeStatement*);
   void Leave(SgFunctionDeclaration*, SgScopeStatement*, bool, const std::string &result_name = "");

   void Enter(SgFunctionDefinition* &);
   void Leave(SgFunctionDefinition*);

   void Enter(SgDerivedTypeStatement* &, const std::string &);
   void Leave(SgDerivedTypeStatement*);

   void Enter(SgVariableDeclaration* &, const std::string &, SgType*, SgExpression*);
   void Enter(SgVariableDeclaration* &, SgType*, std::list<std::tuple<std::string, SgType*, SgExpression*>> &);
   void Leave(SgVariableDeclaration*);
   void Leave(SgVariableDeclaration*, std::list<LanguageTranslation::ExpressionKind> &);

   void Enter(SgEnumDeclaration* &, const std::string &);
   void Leave(SgEnumDeclaration*);

   void Enter(SgEnumVal* &, const std::string &, SgEnumDeclaration*, int);

   void Enter(SgTypedefDeclaration* &, const std::string &, SgType*);
   void Leave(SgTypedefDeclaration*);

// Statements
//
   void Enter(SgNamespaceDeclarationStatement* &, const std::string &, const SourcePositionPair &);
   void Leave(SgNamespaceDeclarationStatement*);

   void Enter(SgExprStatement* &, const std::string &, SgExprListExp*, const std::string &);
   void Enter(SgExprStatement* &, SgExpression* &, const std::vector<SgExpression*> &, const std::string &);
   void Leave(SgExprStatement*);

   void Enter(SgIfStmt* &, SgExpression*, SgBasicBlock*, SgBasicBlock*, bool is_ifthen = false, bool has_end_stmt = false, bool is_else_if = false);
   void Leave(SgIfStmt*);

   void Enter(SgProcessControlStatement* &, const std::string &, const boost::optional<SgExpression*> &);
   void Enter(SgProcessControlStatement* &, const std::string &, const boost::optional<SgExpression*> &,
                                                                 const boost::optional<SgExpression*> &);
   void Leave(SgProcessControlStatement*);

   void Enter(SgSwitchStatement* &, SgExpression*, const SourcePositionPair &);
   void Leave(SgSwitchStatement*);

   void Enter(SgReturnStmt* &, const boost::optional<SgExpression*> &);
   void Leave(SgReturnStmt*);

   void Enter(SgCaseOptionStmt* &, SgExprListExp*);
   void Leave(SgCaseOptionStmt*);

   void Enter(SgDefaultOptionStmt* &);
   void Leave(SgDefaultOptionStmt*);

   void Enter(SgPrintStatement* &, SgExpression*, std::list<SgExpression*> &);
   void Leave(SgPrintStatement*);

   void Enter(SgWhileStmt* &, SgExpression*);
   void Leave(SgWhileStmt*, bool has_end_do_stmt=false);

   void Enter(SgImplicitStatement* &implicit_stmt, bool none_external = false, bool none_type = false);
   void Enter(SgImplicitStatement* &, std::list<std::tuple<SgType*, std::list<std::tuple<char, boost::optional<char>>>>> &);
   void Leave(SgImplicitStatement*);

   void Enter(SgModuleStatement* &, const std::string &);
   void Leave(SgModuleStatement*);

   void Enter(SgUseStatement* &, const std::string &, const std::string &);
   void Leave(SgUseStatement*);

   void Enter(SgContainsStatement* &);
   void Leave(SgContainsStatement*);

   SgEnumVal* getEnumVal(SgEnumType*, SgEnumVal* old_val);

// Expressions
//
   void Enter(SgFunctionCallExp* &, const std::string &name, SgExprListExp* params);
   void Enter(SgReplicationOp* &, const std::string &name, SgExpression* value);
   void Enter(SgCastExp* &, const std::string &name, SgExpression* cast_operand);
   void Enter(SgPntrArrRefExp* &, const std::string &name, SgExprListExp* subscripts, SgExprListExp* cosubscripts);
   void Enter(SgVarRefExp* &, const std::string &name, bool compiler_generate=false);

// Jovial specific nodes
//
#ifdef ROSE_EXPERIMENTAL_JOVIAL_ROSE_CONNECTION
   void Enter(SgJovialDefineDeclaration* &, const std::string &define_string);
   void Leave(SgJovialDefineDeclaration*);

   void Enter(SgJovialDirectiveStatement* &, const std::string &directive_string);
   void Enter(SgJovialDirectiveStatement* &, const std::string &compool_name, std::vector<std::string> &);
   void Leave(SgJovialDirectiveStatement*);

   void Enter(SgJovialForThenStatement* &, const std::string &);
   void Enter(SgJovialForThenStatement* &, SgExpression*, SgExpression*, SgExpression*,
                                           SgJovialForThenStatement::loop_statement_type_enum);
   void Leave(SgJovialForThenStatement*);

   void Enter(SgJovialCompoolStatement* &, const std::string &, const SourcePositionPair &);
   void Leave(SgJovialCompoolStatement*);

   void Enter(SgJovialOverlayDeclaration* &, SgExpression* address, SgExprListExp* overlay);
   void Leave(SgJovialOverlayDeclaration*);

   void Enter(SgJovialTableStatement* &, const std::string &, const SourcePositionPair &, bool is_block=false);
   void Leave(SgJovialTableStatement*);
#endif

// Fortran specific nodes
//
   void Enter(SgCommonBlock* &, std::list<SgCommonBlockObject*> &);
   void Leave(SgCommonBlock* common_block);

private:

   LanguageEnum language_;
   SgSourceFile* source_;
   TokenStream* tokens_;
   TraversalContext context_;
   std::istringstream iss_empty_{};
   std::map<const std::string, SgVarRefExp*> forward_var_refs_;
   std::multimap<const std::string, SgPointerType*> forward_type_refs_;

   void importModule(const std::string &module_name);

   void reset_forward_type_refs(const std::string &type_name, SgNamedType* type);

public:
   bool is_Fortran_language() {return (language_ == LanguageEnum::Fortran);}
   bool is_Jovial_language()  {return (language_ == LanguageEnum::Jovial);}

   const TraversalContext & get_context(void) {return context_;}
   void setContext(SgType* type) {context_.type = type;}
   void setActualFunctionParameterScope(SgScopeStatement* scope) {context_.actual_function_param_scope = scope;}

   void setInitializationContext(bool flag) {context_.is_initialization = flag;}
   bool  isInitializationContext()          {return context_.is_initialization;}

   void attachComment(SgLocatedNode* locatedNode);
   void attachComment(SgLocatedNode* locatedNode, const PosInfo &pos);
   void setSourcePosition(SgLocatedNode* node, const SourcePosition &start, const SourcePosition &end);

// Helper function
   bool list_contains(const std::list<LanguageTranslation::FunctionModifier>& lst, const LanguageTranslation::FunctionModifier& item)
     {
        return (std::find(lst.begin(), lst.end(), item) != lst.end());
     }

// Builder function manages implicitly declared variable references
   SgVarRefExp* buildVarRefExp_nfi(const std::string & name);

// Builder function manages pointer references to undeclared types
   SgPointerType* buildPointerType(const std::string &base_type_name, SgType* base_type);

// Symbols (Jovial specific, should this go in SageInterface?)
   void injectAliasSymbol(const std::string &name);

};

// Temporary wrappers for SageInterface functions (needed until ROSE builds with C++17)
//
namespace SageBuilderCpp17 {

// Types
   SgType* buildBoolType();
   SgType* buildIntType();
   SgType* buildFloatType();
   SgType* buildCharType();
   SgType* buildDoubleType();
   SgType* buildComplexType(SgType* base_type = nullptr);
   SgType* buildBoolType(SgExpression* kind_expr);
   SgType* buildIntType(SgExpression* kind_expr);
   SgType* buildFloatType(SgExpression* kind_expr);
   SgType* buildStringType(SgExpression* stringLengthExpression);
   SgType* buildArrayType(SgType* base_type, std::list<SgExpression*> &explicit_shape_list);

// SgBasicBlock
   SgBasicBlock* buildBasicBlock_nfi();
   void pushScopeStack(SgBasicBlock* stmt);
   void popScopeStack();

// Operators
   SgExpression*  buildAddOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildAndOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildConcatenationOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildDivideOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildEqualityOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildLessThanOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildLessOrEqualOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildGreaterThanOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildGreaterOrEqualOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildMultiplyOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildNotEqualOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildOrOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildMinusOp_nfi(SgExpression* i, bool is_prefix = true);

// Expressions
   SgExpression*  buildBoolValExp_nfi(bool value);
   SgExpression*  buildIntVal_nfi(int);
   SgExpression*  buildStringVal_nfi(std::string);
   SgExpression*  buildFloatVal_nfi(const std::string &);
   SgExpression*  buildComplexVal_nfi(SgExpression* real_value, SgExpression* imaginary_value, const std::string &str);
   SgExpression*  buildExprListExp_nfi();
   SgExpression*  buildVarRefExp_nfi(std::string &name, SgScopeStatement* scope = nullptr);
   SgExpression*  buildSubtractOp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildSubscriptExpression_nfi(SgExpression* lower_bound, SgExpression* upper_bound, SgExpression* stride);
   SgExpression*  buildPntrArrRefExp_nfi(SgExpression* lhs, SgExpression* rhs);
   SgExpression*  buildAggregateInitializer_nfi(SgExprListExp* initializers, SgType* type = nullptr);
   SgExpression*  buildAsteriskShapeExp_nfi();
   SgExpression*  buildNullExpression_nfi();
   SgExpression*  buildFunctionCallExp(SgFunctionCallExp*);
   SgExprListExp* buildExprListExp_nfi(const std::list<SgExpression*> &);

// Other
   SgCommonBlockObject* buildCommonBlockObject(std::string name = "", SgExprListExp* expr_list = nullptr);
// This is new and should be added to SageBuilder?
   SgFunctionCallExp* buildIntrinsicFunctionCallExp_nfi(const std::string &name,
                                                        SgExprListExp* params=nullptr, SgScopeStatement* scope=nullptr);

// Non builder helper functions
   void set_false_body(SgIfStmt* &if_stmt, SgBasicBlock* false_body);
   void set_need_paren(SgExpression* &expr);
   void fixUndeclaredResultName(const std::string &result_name, SgScopeStatement* scope, SgType* result_type);


} // namespace SageBuilderCpp17
} // namespace builder
} // namespace Rose

#endif  // ROSE_SAGE_TREE_BUILDER_H_
