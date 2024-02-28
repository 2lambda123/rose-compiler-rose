

#ifndef _SAGEINTERFACE_ADA_H
#define _SAGEINTERFACE_ADA_H 1

#include "sage3basic.hhh"
#include "sageInterface.h"

#include <tuple>

#include <boost/optional.hpp>

namespace SageInterface
{

/// Contains Ada-specific functionality
namespace Ada
{

namespace
{
  template <class SageRefExp>
  auto symOf(const SageRefExp& n) -> decltype( *n.get_symbol() )
  {
    auto* symp = n.get_symbol();
    ASSERT_not_null(symp);

    return *symp;
  }

  template <class SageSymbol>
  auto declOf(const SageSymbol& n) -> decltype( *n.get_declaration() )
  {
    auto* dclp = n.get_declaration();
    ASSERT_not_null(dclp);

    return *dclp;
  }

  inline
  SgFunctionDeclaration& declOf(const SgFunctionRefExp& n)
  {
    return declOf(symOf(n));
  }

  inline
  SgInitializedName& declOf(const SgVarRefExp& n)
  {
    return declOf(symOf(n));
  }


  // \todo normalize Sage nodes that use this function
  //       and make them go through symbols, like any other
  //       ref exp.
  template <class SageAdaRefExp>
  auto declOfRef(const SageAdaRefExp& n) -> decltype( *n.get_decl() )
  {
    auto* dclp = n.get_decl();
    ASSERT_not_null(dclp);

    return *dclp;
  }

  inline
  SgAdaRenamingDecl& declOf(const SgAdaRenamingRefExp& n)
  {
    return declOfRef(n);
  }

  inline
  SgDeclarationStatement& declOf(const SgAdaUnitRefExp& n)
  {
    return declOfRef(n);
  }

  inline
  SgAdaTaskSpecDecl& declOf(const SgAdaTaskRefExp& n)
  {
    SgAdaTaskSpecDecl* res = isSgAdaTaskSpecDecl(&declOfRef(n));

    ASSERT_not_null(res);
    return *res;
  }

  inline
  SgAdaProtectedSpecDecl& declOf(const SgAdaProtectedRefExp& n)
  {
    SgAdaProtectedSpecDecl* res = isSgAdaProtectedSpecDecl(&declOfRef(n));

    ASSERT_not_null(res);
    return *res;
  }

  inline
  SgLabelStatement& declOf(const SgLabelRefExp& n)
  {
    return declOf(symOf(n));
  }


/*
  inline
  SgVariableDeclaration& declOf(const SgVariableSymbol& n)
  {
    SgNode* varnode = SG_DEREF(n.get_declaration()).get_parent();

    return SG_DEREF(isSgVariableDeclaration(varnode));
  }

  inline
  SgVariableDeclaration& declOf(const SgVarRefExp& n)
  {
    return declOf(symOf(n));
  }
*/

  inline
  SgName nameOf(const SgSymbol& sy)
  {
    return sy.get_name();
  }


  template <class SageRefExp>
  inline
  auto nameOf(const SageRefExp& n) -> decltype( nameOf(symOf(n)) )
  {
    return nameOf(symOf(n));
  }

  inline
  SgName nameOf(const SgEnumVal& n)
  {
    return n.get_name();
  }

  inline
  SgName nameOf(const SgAdaUnitRefExp& n)
  {
    return SageInterface::get_name(n.get_decl());
  }


/*
  inline
  SgName
  nameOf(const SgAdaRenamingDecl& n)
  {
    return n.get_name();
  }
*/


/*
  inline
  SgName nameOf(const SgImportStatement& import)
  {
    const SgExpressionPtrList& lst = import.get_import_list();
    ROSE_ASSERT(lst.size() == 1);

    return nameOf(SG_DEREF(isSgVarRefExp(lst.back())));
  }
*/

} // anononymous namespace for convenience functions


  extern const std::string roseOperatorPrefix;
  extern const std::string packageStandardName;
  extern const std::string durationTypeName;
  extern const std::string exceptionName;

  /// tests if the declaration \ref dcl defines a public type that is completed
  ///   in a private section.
  /// \return true, iff dcl is public and completed in a private section.
  /// \pre dcl is not null and points to a first-nondefining declaration.
  /// @{
  bool withPrivateDefinition(const SgDeclarationStatement* dcl);
  bool withPrivateDefinition(const SgDeclarationStatement& dcl);
  /// @}

  /// tests if \ref ty is an unconstrained array
  /// \return true iff ty is unconstrained
  /// @{
  bool unconstrained(const SgArrayType* ty);
  bool unconstrained(const SgArrayType& ty);
  /// @}

  /// tests if \ref ty is an anonymous access type
  /// \return true iff ty is an anonymous access type
  /// @{
  bool anonymousAccess(const SgType* ty);
  bool anonymousAccess(const SgType& ty);
  /// @}

  using StatementRange = std::pair<SgDeclarationStatementPtrList::iterator, SgDeclarationStatementPtrList::iterator>;

  /// returns all statements/declarations in the global scope that were defined
  /// in the source file.
  /// \param   globalScope a reference to the global scope
  /// \param   mainfile    a reference to the main source file (name)
  /// \returns a range [first-in-sequence, limit-of-sequence) of
  ///          global-scope level statements in \ref mainFile
  /// \details
  ///   In other words, the declarations in the with'ed packages are excluded from the returned range.
  /// \{
  StatementRange
  declsInPackage(SgGlobal& globalScope, const std::string& mainFile);

  StatementRange
  declsInPackage(SgGlobal& globalScope, const SgSourceFile& mainFile);
  /// \}


  /// returns an integer value for args[0] as used by type attributes first and last
  /// \throws throws an exception if args[0] cannot be constant folded
  /// \note currently only constant values are supported
  /// \{
  int firstLastDimension(SgExprListExp& args);
  int firstLastDimension(SgExprListExp* args);
  /// \}

  /// defines the result type for \ref getArrayTypeInfo
  struct FlatArrayType : std::tuple<SgArrayType*, std::vector<SgExpression*> >
  {
    using base = std::tuple<SgArrayType*, std::vector<SgExpression*> >;
    using base::base;

    SgArrayType*                      type() const { return std::get<0>(*this); }
    std::vector<SgExpression*> const& dims() const { return std::get<1>(*this); }
    std::vector<SgExpression*>&       dims()       { return std::get<1>(*this); }
  };

  /// returns a flattened representation of Ada array types.
  /// \param   atype the type of the array to be flattened.
  /// \return  iff \ref atype is not an arraytype, a pair <nullptr, empty vector> is returned
  ///          otherwise a pair of a array pointer, and a vector of index ranges.
  ///          Index ranges can be specified in terms of a range (SgRangeExp), a type
  ///          attribute (SgAdaAttributeExp), or full type range (SgTypeExpression).
  ///          (the expressions are part of the AST and MUST NOT BE DELETED).
  /// \pre     \ref atype is not null.
  /// @{
  FlatArrayType getArrayTypeInfo(SgType* atype);
  FlatArrayType getArrayTypeInfo(SgType& atype);
  /// @}

  struct RecordField : std::tuple<const SgSymbol*>
  {
    using base = std::tuple<const SgSymbol*>;
    using base::base;

    const SgSymbol&          symbol()         const;
    const SgSymbol&          originalSymbol() const;
    const SgClassDefinition& record()         const;
    bool                     inherited()      const { return isSgAliasSymbol(&symbol()); }
    bool                     discriminant()   const;
  };


  /// returns all fields (defined and inherited) of a record.
  /// \param rec the class definition for which the fields are sought
  /// \note
  ///    currently the entries in the returned vector are unordered.
  /// \{
  std::vector<RecordField>
  getAllRecordFields(const SgClassDefinition& rec);

  std::vector<RecordField>
  getAllRecordFields(const SgClassDefinition* rec);
  /// \}


  /// represents a branch in an if elsif else context (either statement or expression).
  template <class SageLocatedNode>
  struct IfInfo : std::tuple<SgExpression*, SageLocatedNode*>
  {
    using base = std::tuple<SgExpression*, SageLocatedNode*>;
    using base::base;

    SgExpression*    condition()  const { return std::get<0>(*this); }
    SageLocatedNode* trueBranch() const { return std::get<1>(*this); }
    bool             isElse()     const { return condition() == nullptr; }
  };

  /// returns a sequence of if (x) then value
  ///   the last else does not have
  using IfExpressionInfo = IfInfo<SgExpression>;
  using IfStatementInfo  = IfInfo<SgStatement>;

  /// returns a flat representation of if expressions
  std::vector<IfExpressionInfo>
  flattenIfExpressions(const SgConditionalExp& n);

  /// returns a flat representation of if-elsif-else statements
  std::vector<IfStatementInfo>
  flattenIfStatements(const SgIfStmt& n);

  /// integer constant folding
  /// \returns an integral value for an Ada expression if possible
  /// \throws  an exception otherwise.
  long long int
  staticIntegralValue(SgExpression* n);


  /// returns the expression of an expression statement, or nullptr if s is some other node
  SgExpression*
  underlyingExpr(const SgStatement* s);

  /// returns a range for the range attribute \ref rangeAttribute.
  /// \return a range if rangeAttribute is a range attribute and a range expression is in the AST;
  ///         nullptr otherwise.
  /// \throws a std::runtime_error if the rangeAttribute uses an index specification
  ///         that is not an integral constant expression.
  /// \pre    \ref rangeAttribute is not null
  /// @{
  SgRangeExp* range(const SgAdaAttributeExp* rangeAttribute);
  SgRangeExp* range(const SgAdaAttributeExp& rangeAttribute);
  /// @}

  /// returns the declaration node for the package specification
  /// @{
  SgAdaPackageSpecDecl& getSpecificationDeclaration(const SgAdaPackageBodyDecl& bodyDecl);
  SgAdaPackageSpecDecl* getSpecificationDeclaration(const SgAdaPackageBodyDecl* bodyDecl);
  /// @}

  /// returns the declaration node for the package body, if available
  /// @{
  SgAdaPackageBodyDecl& getPackageBodyDeclaration(const SgAdaPackageSpecDecl& specDecl);
  SgAdaPackageBodyDecl* getPackageBodyDeclaration(const SgAdaPackageSpecDecl* specDecl);
  /// @}

  /// returns the declaration node (either SgAdaTaskSpecDecl or SgAdaTaskTypeDecl) for the task specification
  /// @{
  SgDeclarationStatement& getSpecificationDeclaration(const SgAdaTaskBodyDecl& bodyDecl);
  SgDeclarationStatement* getSpecificationDeclaration(const SgAdaTaskBodyDecl* bodyDecl);
  /// @}

  /// returns the declaration node (either SgAdaProtectedSpecDecl or SgAdaProtectedTypeDecl)
  ///   for the protected object specification
  /// @{
  SgDeclarationStatement& getSpecificationDeclaration(const SgAdaProtectedBodyDecl& bodyDecl);
  SgDeclarationStatement* getSpecificationDeclaration(const SgAdaProtectedBodyDecl* bodyDecl);
  /// @}

  /// returns the body scope (aka definition) of a task, package, or protected object.
  /// \param  scope a task, package, protected object spec or body
  /// \return the corresponding body scope (i.e., SgAdaProtectedBody, SgAdaPackageBody, SgAdaTaskBody)
  ///         returns null when a body cannot be found
  /// \details
  ///   given a spec or body, the function returns the body, null otherwise
  ///   e.g., getBodyScope(SgAdaPackageSpec) -> SgAdaPackageBody
  ///         getBodyScope(SgAdaPackageBody) -> SgAdaPackageBody
  ///         getBodyScope(SgFunctionDefinition) -> nullptr
  const SgScopeStatement* correspondingBody(const SgScopeStatement* scope);

  /// returns the iterator to one past the last declaration (the limit)
  /// in the statement sequence.
  /// @{
  SgStatementPtrList::iterator declarationLimit(SgStatementPtrList& list);
  SgStatementPtrList::iterator declarationLimit(SgBasicBlock& block);
  SgStatementPtrList::iterator declarationLimit(SgBasicBlock* block);
  SgStatementPtrList::const_iterator declarationLimit(const SgStatementPtrList& list);
  SgStatementPtrList::const_iterator declarationLimit(const SgBasicBlock& block);
  SgStatementPtrList::const_iterator declarationLimit(const SgBasicBlock* block);
  /// @}

  /// returns true iff \ref n is a try block following a declarative region
  /// \note an ada try block is a function block, whose non-declarative
  ///       range includes exactly one try stmt. In this case, the unparser
  ///       can omit the separate begin and end statement.
  /// @{
  bool tryFollowsDeclarativeBlock(const SgTryStmt& n);
  bool tryFollowsDeclarativeBlock(const SgTryStmt* n);
  /// @}


  /// returns true iff \ref n is an Ada package try block
  /// \note an ada try block is a function block, whose non-declarative
  ///       range includes exactly one try stmt. In this case, the unparser
  ///       can omit the separate begin and end statement.
  /// @{
  bool isPackageTryBlock(const SgTryStmt& n);
  bool isPackageTryBlock(const SgTryStmt* n);
  /// @}


  /// returns true iff \ref n has an unknown discriminant part
  /// @{
  bool hasUnknownDiscriminants(const SgAdaDiscriminatedTypeDecl& n);
  bool hasUnknownDiscriminants(const SgAdaDiscriminatedTypeDecl* n);
  /// @}


  /// return if the type @ref ty is the corresponding universal type representation in ROSE
  /// @{
  bool isModularType(const SgType& ty);
  bool isModularType(const SgType* ty);
  bool isIntegerType(const SgType& ty);
  bool isIntegerType(const SgType* ty);
  bool isFloatingPointType(const SgType& ty);
  bool isFloatingPointType(const SgType* ty);
  bool isDiscreteType(const SgType* ty);
  bool isDiscreteType(const SgType& ty);
  bool isBooleanType(const SgType* ty);
  bool isBooleanType(const SgType& ty);
  /// @}

  /// returns if the type @ref ty is a fixed point type
  /// \details
  ///    also return true for decimal fixed points
  /// @{
  bool isFixedType(const SgType* ty);
  bool isFixedType(const SgType& ty);
  /// @}

  /// returns true if @ref ty refers to a scalar type
  /// \details
  ///   true if the ty's root type is a modular type, signed integer type,
  ///   enumeration type, discrete type, fixed type, decimal fixed type,
  ///   or enum type.
  /// @{
  bool isScalarType(const SgType* ty);
  bool isScalarType(const SgType& ty);
  /// @}

  /// returns true if @ref ty refers to a discrete array type
  /// @{
  bool isDiscreteArrayType(const SgType& ty);
  bool isDiscreteArrayType(const SgType* ty);
  /// @}

  /// returns if the type @ref ty resolves to a fixed point type
  /// \details
  ///    also return true for decimal fixed points
  /// @{
  bool resolvesToFixedType(const SgType* ty);
  bool resolvesToFixedType(const SgType& ty);
  /// @}

  /// returns if the type @ref ty is a decimal fixed point type
  /// \details
  ///    implementation is incomplete and only detects formal decimal fixed point constraints
  /// @{
  bool isDecimalFixedType(const SgType* ty);
  bool isDecimalFixedType(const SgType& ty);
  /// @}


  /// if e denotes an Ada boolean constant, it is returned; otherwise
  ///   an empty result is returned.
  /// \details
  ///   the function does not perform any constant folding
  /// @{
  boost::optional<bool>
  booleanConstant(const SgExpression* e);

  boost::optional<bool>
  booleanConstant(const SgExpression& e);
  /// @}


  /// Returns the SgAdaGenericDecl node that makes a declaration (either function/procedure or package)
  /// generic.
  /// \param n a declaration that is possibly part of a generic declaration.
  /// \returns the generic declaration of \ref n, where \ref n is a either function/procedure or package
  ///          that is declared directly under an SgAdaGenericDecl;
  ///          nullptr otherwise.
  /// \details
  ///   For a subtree SgAdaGenericDecl->SgAdaGenericDefn->n, the SgAdaGenericDecl node is returned.
  /// @{
  SgAdaGenericDecl* isGenericDecl(const SgDeclarationStatement& n);
  SgAdaGenericDecl* isGenericDecl(const SgDeclarationStatement* n);
  /// @}

  /// returns true iff \ref n refers to a generic declaration from inside said declaration
  ///         false otherwise (e.g., if n does not refer to a generic unit)
  /// @{
  bool unitRefDenotesGenericInstance(const SgAdaUnitRefExp& n);
  bool unitRefDenotesGenericInstance(const SgAdaUnitRefExp* n);
  /// @}

  /// Returns SgAdaGenericDecl for a given SgAdaGenericInstanceDecl.
  /// \details
  ///    skips over intermediate renaming declarations.
  /// @{
  SgAdaGenericDecl& getGenericDecl(const SgAdaGenericInstanceDecl& n);
  SgAdaGenericDecl* getGenericDecl(const SgAdaGenericInstanceDecl* n);
  /// @}


  /// returns the SgAdaDiscriminatedTypeDecl iff \ref n is discriminated
  ///         null otherwise
  /// @{
  SgAdaDiscriminatedTypeDecl* getAdaDiscriminatedTypeDecl(const SgDeclarationStatement& n);
  SgAdaDiscriminatedTypeDecl* getAdaDiscriminatedTypeDecl(const SgDeclarationStatement* n);
  /// @}

  /// tests if the declaration \ref decl corresponds to a stub (aka separated unit)
  /// @{
  bool hasSeparatedBody(const SgDeclarationStatement& dcl);
  bool hasSeparatedBody(const SgDeclarationStatement* dcl);
  /// @}

  /// returns true iff \ref n is a unit definition that has been separated
  /// @{
  bool isSeparatedBody(const SgDeclarationStatement& n);
  bool isSeparatedBody(const SgDeclarationStatement* n);
  /// @}

  /// returns true iff \ref n is a separated function definition is separated
  /// @{
  bool isSeparatedDefinition(const SgFunctionDeclaration& n);
  bool isSeparatedDefinition(const SgFunctionDeclaration* n);
  /// @}

  struct TypeDescription : std::tuple<SgType*, bool, std::vector<SgAdaTypeConstraint*> >
  {
    static constexpr bool classwide = true;

    using base = std::tuple<SgType*, bool, std::vector<SgAdaTypeConstraint*> >;

    explicit
    TypeDescription(SgType& ty, bool polymorph = false, std::vector<SgAdaTypeConstraint*> constr = {})
    : base(&ty, polymorph, std::move(constr))
    {}

    explicit
    TypeDescription(SgType* ty = nullptr)
    : base(ty, false, {})
    {}

    SgType* typerep()     const { return std::get<0>(*this); }
    SgType& typerep_ref() const;
    bool    polymorphic() const { return std::get<1>(*this); }

    const std::vector<SgAdaTypeConstraint*>&
    toplevelConstraints() const & { return std::get<2>(*this); }

    std::vector<SgAdaTypeConstraint*>
    toplevelConstraints() &&    { return std::move(std::get<2>(*this)); }
  };

  /// returns the most fundamental type
  ///   after skipping subtypes, typedefs, etc.
  /// @{
  TypeDescription typeRoot(SgType&);
  TypeDescription typeRoot(SgType*);
  /// @}

  /// returns the type of an expression
  ///   corrects for some peculiarities in the AST
  /// \todo could be integrated into SgExpression::get_type ...
  /// @{
  TypeDescription typeOfExpr(const SgExpression&);
  TypeDescription typeOfExpr(const SgExpression*);
  /// @}

  /// returns the base type if ty is an access type
  /// \param  ty some type
  /// \return the base type of ty, iff ty is some access type
  ///         nullptr otherwise;
  /// @{
  SgType* baseOfAccessType(const SgType* ty);
  SgType* baseOfAccessType(const SgType& ty);
  /// @}

  struct DominantArgInfo : std::tuple<const SgType*, std::size_t>
  {
    using base = std::tuple<const SgType*, std::size_t>;
    using base::base;

    const SgType* type() const { return std::get<0>(*this); }
    std::size_t   pos()  const { return std::get<1>(*this); }
  };

  DominantArgInfo
  operatorArgumentWithNamedRootIfAvail(const SgTypePtrList& argtypes);

  struct OperatorScopeInfo : std::tuple<SgScopeStatement*, std::size_t>
  {
    using base = std::tuple<SgScopeStatement*, std::size_t>;
    using base::base;

    // the scope associated with the dominant parameter
    SgScopeStatement* scope()  const { return std::get<0>(*this); }

    // the position of the dominant parameter in the parameter list
    std::size_t       argpos() const { return std::get<1>(*this); }
  };

  /// returns the scope where an operator with name \ref opname and argument types
  ///    in \ref argtypes shall be declared.
  /// \param  opname   the operator name
  /// \param  argtypes a list of argument types
  /// \return a scope where the described operator shall be declared, and the argument position
  ///         associated with the scope.
  OperatorScopeInfo
  operatorScope(const std::string& opname, const SgTypePtrList& argtypes);


  /// returns the scope where an operator associated with type \ref ty
  ///    shall be declared.
  /// \param  opname   the operator name
  /// \param  ty       the type name
  /// \return a scope where the described operator shall be declared.
  /// \note the main difference to declarationScope is that fixed types
  ///       require certain operators to exist in package standard.
  /// \{
  SgScopeStatement&
  operatorScope(const std::string& opname, const SgType& ty);

  SgScopeStatement*
  operatorScope(const std::string& opname, const SgType* ty);
  /// \}


  /// returns the scope where type \ref ty has been declared
  /// \param  ty some type
  /// \return the scope where ty was declared
  /// \{
  SgScopeStatement* declarationScope(const SgType* ty);
  SgScopeStatement* declarationScope(const SgType& ty);
  /// \}

  /// describes properties of imported units
  struct ImportedUnitResult : std::tuple< std::string,
                                          const SgDeclarationStatement*,
                                          const SgAdaRenamingDecl*,
                                          const SgExpression*
                                        >
  {
    using base = std::tuple<std::string, const SgDeclarationStatement*, const SgAdaRenamingDecl*, const SgExpression*>;
    using base::base;

    const std::string&            name()         const { return std::get<0>(*this); }

    const SgDeclarationStatement& decl()         const
    {
      ASSERT_not_null(std::get<1>(*this));
      return *(std::get<1>(*this));
    }

    const SgAdaRenamingDecl*      renamingDecl() const { return std::get<2>(*this); }

    const SgExpression&           unitref()      const
    {
      ASSERT_not_null(std::get<3>(*this));
      return *std::get<3>(*this);
    }
  };

  /// queries properties of all units in an import statement
  std::vector<ImportedUnitResult>
  importedUnits(const SgImportStatement& impdcl);

#if OBSOLETE_CODE
  /// returns the imported element (i.e., the first entry in n's import_list
  const SgExpression&
  importedElement(const SgImportStatement& n);
#endif /* OBSOLETE_CODE */


  /// do not use, this is temporary
  SgScopeStatement* pkgStandardScope();

  /// takes a function name as used in ROSE and converts it to a name in Ada
  ///   (i.e., '"' + operator_text + '"').
  ///   if \ref nameInRose does not name an operator, then the name is returned as is.
  std::string convertRoseOperatorNameToAdaName(const std::string& nameInRose);

  /// takes a function name as used in ROSE and converts it to an operator in Ada
  ///   (i.e., operator_text).
  ///   if \ref nameInRose does not name an operator, an empty string is returned
  std::string convertRoseOperatorNameToAdaOperator(const std::string& nameInRose);

  /// Details of expression aggregates
  struct AggregateInfo : std::tuple< SgAdaAncestorInitializer*,
                                     SgExpressionPtrList::const_iterator,
                                     SgExpressionPtrList::const_iterator
                                   >
  {
    using base = std::tuple< SgAdaAncestorInitializer*,
                             SgExpressionPtrList::const_iterator,
                             SgExpressionPtrList::const_iterator
                           >;
    using base::base;

    /// returns the ancestor initializer iff it exists, otherwise null
    SgAdaAncestorInitializer* ancestor() const { return std::get<0>(*this); }

    /// returns the remaining range-begin without the ancestor initializer (if it existed)
    SgExpressionPtrList::const_iterator begin() const { return std::get<1>(*this); }

    /// returns the underlying's list end iterator
    SgExpressionPtrList::const_iterator end() const { return std::get<2>(*this); }

    /// returns if the remaining range (w/o the ancestor initializer) indicates a null record.
    bool nullRecord() const { return begin() == end(); }
  };

  /// returns the ancestor initializer, if \ref exp refers to an extension aggregate
  ///         null otherwise
  /// @{
  AggregateInfo splitAggregate(const SgExprListExp& exp);
  AggregateInfo splitAggregate(const SgExprListExp* exp);
  /// @}


  /// returns a package spec decl if the declaration \ref n renames a package
  /// returns nullptr otherwise
  /// @{
  SgAdaPackageSpecDecl* renamedPackage(const SgAdaRenamingDecl& n);
  SgAdaPackageSpecDecl* renamedPackage(const SgAdaRenamingDecl* n);
  /// @}


  /// returns true iff \ref ty refers to a function type (as opposed to procedure)
  /// @{
  bool isFunction(const SgFunctionType& ty);
  bool isFunction(const SgFunctionType* ty);
  bool isFunction(const SgAdaSubroutineType& ty);
  bool isFunction(const SgAdaSubroutineType* ty);
  /// @}

  /// returns the static type of the function symbol \ref fnsy
  /// \note
  ///   The pointer based version returns nullptr if fnsy is nullptr.
  /// @{
  const SgFunctionType* functionType(const SgFunctionSymbol* fnsy);
  const SgFunctionType& functionType(const SgFunctionSymbol& fnsy);
  /// @}


  /// returns true iff \ref ty refers to an object renaming
  /// @{
  bool isObjectRenaming(const SgAdaRenamingDecl* dcl);
  bool isObjectRenaming(const SgAdaRenamingDecl& dcl);
  /// @}

  /// returns true iff \ref ty refers to an exception renaming
  /// @{
  bool isExceptionRenaming(const SgAdaRenamingDecl* dcl);
  bool isExceptionRenaming(const SgAdaRenamingDecl& dcl);
  /// @}

  struct PrimitiveParameterDesc : std::tuple<size_t, const SgInitializedName*>
  {
    using base = std::tuple<size_t, const SgInitializedName*>;
    using base::base;

    /// the position within the parameter list
    size_t
    pos()  const { return std::get<0>(*this); }

    /// the parameter's name in form of an SgInitializedName
    const SgInitializedName*
    name() const { return std::get<1>(*this); }
  };

  /// returns the descriptions for parameters that make an operation primitive
  /// @{
  std::vector<PrimitiveParameterDesc>
  primitiveParameterPositions(const SgFunctionDeclaration&);

  std::vector<PrimitiveParameterDesc>
  primitiveParameterPositions(const SgFunctionDeclaration*);
  /// @}

  /// returns \ref n or a pointer to \ref n if \ref n declares an exception type.
  /// \param  n an exception declaration candidate
  /// \return a pointer to a exception declaration or nullptr
  /// \{
  const SgVariableDeclaration*
  exceptionTypeDecl(const SgVariableDeclaration& n);

  const SgVariableDeclaration*
  exceptionTypeDecl(const SgVariableDeclaration* n);

  SgVariableDeclaration*
  exceptionTypeDecl(SgVariableDeclaration& n);

  SgVariableDeclaration*
  exceptionTypeDecl(SgVariableDeclaration* n);
  /// \}

  /// returns a list of arguments with named arguments placed at the correct position by taking into
  ///   account the supplied argument list.
  /// \param n       the call expression
  /// \param arglist a argument list
  /// \throws std::logic_error when named arguments cannot be identified.
  /// \note
  ///    * defaulted arguments are not represented and the list may contain holes (nullptr)
  ///    * use this function during AST construction
  SgExpressionPtrList
  normalizedCallArguments2(const SgFunctionCallExp& n, const SgFunctionParameterList& arglist);

  /// attempts to identify the argument list automatically and uses it to invoke the preceding
  ///   normalizedCallArguments2 function.
  /// \param n       the call expression
  /// \throws std::logic_error when there is no function associated with the call,
  ///         or when normalizedCallArguments2 throws.
  /// \note
  ///   calling this function is preferred in the general case.
  /// \{
  SgExpressionPtrList
  normalizedCallArguments(const SgFunctionCallExp& n);
  /// \}

  /// returns the function parameter list of the associated callee (if available).
  /// \param  n a function call expression
  /// \return the list of the parameter list of the associated function declaration or renaming declaration.
  ///         nullptr, if no such function can be identified.
  /// \todo handle computed functions (e.g., access to routine)
  /// \{
  SgFunctionParameterList*
  calleeParameterList(const SgFunctionCallExp& n);

  SgFunctionParameterList*
  calleeParameterList(const SgFunctionCallExp* n);
  /// \}


  /// returns the parameter position of arg in the callee, after the parameters have been
  /// normalized.
  /// \throws a std::logic_error when a position cannot be found.
  /// \details
  ///    assume declaration: procedure X(left, right : integer := 1);
  ///              and call: X(right => 3)
  ///    then normalizedArgumentPosition(call, "3") -> 1
  std::size_t
  normalizedArgumentPosition(const SgFunctionCallExp& call, const SgExpression& arg);


  /// finds the symbol with @ref name in the context of @ref scope or its logical parents in the range
  ///   [scope, limit).
  /// @param  name   an identifier of the sought symbol
  /// @param  scope  current scope
  /// @param  limit  the scope in the chain that terminates the search (this scope will not be considered)
  /// @return a tuple of scope and first symbol inthat scope with the name @ref name.
  ///         or <nullptr, nullptr> if no such symbol exists in the context.
  /// @details
  ///         a scope can contain multiple symbols with the same name, so the caller
  ///         may iterate over the remaining names using the scope's accessor functions
  ///         (next_XXX_symbol).
  /// @{
  std::tuple<const SgScopeStatement*, const SgSymbol*>
  findSymbolInContext(std::string id, const SgScopeStatement& scope, const SgScopeStatement* limit = nullptr);
  /// @}



  /// returns the overriding scope of a primitive function based on the
  ///   associated arguments as defined by the argument list \ref args and
  ///   the primitive argument positions defined by \ref primitiveArgs.
  /// \return the scope of an overriding argument (incl. the original associated type);
  ///         nullptr if no such scope can be found.
  /// \note does not resolve conflicting scopes
  /// \see also \ref primitiveParameterPositions
  /// @{
  SgScopeStatement*
  overridingScope(const SgExprListExp& args, const std::vector<PrimitiveParameterDesc>& primitiveArgs);

  SgScopeStatement*
  overridingScope(const SgExprListExp* args, const std::vector<PrimitiveParameterDesc>& primitiveArgs);
  /// @}

  /// returns the canonical scope of some Ada scope \ref scope.
  /// \details
  ///   The canonical scope of an entity is its declarative scope
  ///   e.g., The canonical scope of an SgAdaPackageBody is its spec, a SgAdaPackageSpec
  const SgScopeStatement* canonicalScope(const SgScopeStatement* scope);
  const SgScopeStatement& canonicalScope(const SgScopeStatement& scope);

  /// tests if \ref lhs and \ref have the same canonical scope.
  bool sameCanonicalScope(const SgScopeStatement* lhs, const SgScopeStatement* rhs);

  /// returns the logical parent scope of a scope @ref s.
  /// \details
  ///    Compared to si::getEnclosingScope, this function
  ///    returns the spec as the logical parent for Ada bodies
  ///    (e.g., packages, tasks, protected objects). Otherwise,
  ///    the parent scope is the same as returned by si::getEnclosingScope.
  /// @{
  SgScopeStatement*
  logicalParentScope(const SgScopeStatement& s);

  SgScopeStatement*
  logicalParentScope(const SgScopeStatement* s);
  /// @}


  /// returns the associated declaration for symbol @ref n
  ///   or nullptr if there is none.
  SgDeclarationStatement* associatedDeclaration(const SgSymbol& n);

  /// returns the decl where \ref ty was defined
  ///   nullptr if no such declaration can be found.
  /// \todo remove after integrating functionality into SgType...
  /// \details
  ///    Skips over intermediate derived types, subtypes, etc. until a SgNamedType is found.
  ///    Returns the declaration of said type.
  /// \{
  SgDeclarationStatement* associatedDeclaration(const SgType& ty);
  SgDeclarationStatement* associatedDeclaration(const SgType* ty);
  /// \}

  /// returns the base type of a type \ref ty
  /// \details
  ///   In the following type hierarchy baseTypes(Y) would return { X, S1, S2 } but not Integer.
  ///   \code
  ///   type X is new Integer;
  ///   subtype S1 is X range 0..X'Last;
  ///   subtype S2 is S1 range 10..20;
  ///   type Y is new S1;
  ///   \endcode
  /// \todo
  ///    extend for discriminated types.
  /// \{
  SgType*
  baseType(const SgType& ty);

  SgType*
  baseType(const SgType* ty);
  /// \}


  /// finds the underlying enum declaration of a type \ref ty
  /// \returns an enum declaration associated with ty
  ///          nullptr if no declaration can be found
  /// \details
  ///    baseEnumDeclaration skips over intermediate SgTypedefDeclarations
  ///    that introduce a new type (\todo can new enum types be introduced with SgTypedefDeclaration?)
  ///    or a subtype.
  /// \{
  SgEnumDeclaration*
  baseEnumDeclaration(SgType* ty);

  SgEnumDeclaration*
  baseEnumDeclaration(SgType& ty);
  /// \}

  /// returns true, iff \ref fndef is the body of an explicit null procedure
  bool explicitNullProcedure(const SgFunctionDefinition& fndef);

  /// returns true, iff \ref recdef is the body of an explicit null record
  bool explicitNullRecord(const SgClassDefinition& recdef);

  /// returns true, iff \ref n is a reverse for loop; returns false otherwise
  /// \{
  bool isReverseForLoop(const SgForStatement* n);
  bool isReverseForLoop(const SgForStatement& n);
  bool isReverseForLoop(const SgForInitStatement* n);
  bool isReverseForLoop(const SgForInitStatement& n);
  /// \}


  /// finds the one past the last positional argument (aka the first named argument position).
  /// \return one past the index of the last positional argument.
  /// \details
  ///   examples:
  ///   - argument lists without positional arguments => 0
  ///   - argument lists without named arguments => args.size()
  ///   - empty argument lists => 0
  ///   - (1, 2, LEN => 3) => 2
  /// @{
  size_t
  positionalArgumentLimit(const SgExpressionPtrList& arglst);

  size_t
  positionalArgumentLimit(const SgExprListExp& args);

  size_t
  positionalArgumentLimit(const SgExprListExp* args);
  /// @}

  /// checks if the block \ref blk is present in the Ada source code.
  /// \param  blk a reference ot pointer to a ROSE basic block object.
  /// \return true  of the block is in the source code.
  ///         false if the block is ROSE artifact (or nullptr).
  /// @{
  bool blockExistsInSource(const SgBasicBlock* blk);
  bool blockExistsInSource(const SgBasicBlock& blk);
  /// @}

  /// finds the function symbol for a publicly accessible function.
  /// \param  fnsym    the function symbol (maybe be private)
  /// \param  drvFunTy the derived function type
  /// \param  dervTy   the derived type for which the symbol is sought
  /// \return a function that is publicly accessible and can be used
  ///         for default argument resolution. if none is found
  ///         a pointer to fnsym is returned..
  /// \todo   if no public function can be found return nullptr
  SgFunctionSymbol*
  findPubliclyVisibleFunction( SgFunctionSymbol& fnsym,
                               const SgFunctionType& drvFunTy,
                               const SgNamedType& dervTy
                             );

  /// tests if \ref attr is an attribute with name \ref attrname.
  bool isAttribute(const SgAdaAttributeExp& attr, const std::string& attrname);

  /// Traverses all AST nodes in an unspecified order.
  /// \details
  ///   Only traverses the links that are commonly traversed by ROSE's standard
  ///   traversal mechanism.
  /// \note
  ///   \ref fn is typically a functor that collects all nodes that need to be
  ///   converted in a first pass.
  ///   A second pass, triggered by fn's destructor carries out the
  ///   actual transformations.
  void conversionTraversal(std::function<void(SgNode*)>&& fn, SgNode* root);


  /// converts text to constant values
  /// \{
  long long int convertIntegerLiteral(const char* img);

  std::string convertStringLiteral(const char* img);

  long double convertRealLiteral(const char* img);

  char convertCharLiteral(const char* img);
  /// \}

  /// \brief stores a path from an innermost scope to the global scope (not part of the path)
  ///        in form of a sequence of Sage nodes that represent scopes
  ///        (SgScopeStatements or SgDeclarationStatements).
  /// \details
  ///    - The path is traversed using the range [rbegin(), rend()) to get the scopes
  ///      in order from outermost scope to innermost scope.
  ///    - The path may contain scopes without names. Those will be skipped
  ///      when the qualified name is stringified.
  struct ScopePath : private std::vector<const SgScopeStatement*>
  {
      using base = std::vector<const SgScopeStatement*>;
      using base::base;

      using base::const_reverse_iterator;
      using base::reverse_iterator;
      using base::const_iterator;
      using base::rend;
      using base::rbegin;
      using base::value_type;
      using base::reference;
      using base::size;

      using base::end;
      using base::begin;

      /// overload vector's push_back to check element validity
      void push_back(base::value_type ptr)
      {
        ROSE_ASSERT(isSgScopeStatement(ptr) || isSgDeclarationStatement(ptr));
        ROSE_ASSERT(!isSgGlobal(ptr));

        base::push_back(ptr);
      }
  };

  /// Constructs a path from a scope statement to the top-level (global)
  /// scope. The path contains [n, global)
  /// \param n innermost scope
  /// \todo consider adding global into the sequence
  ///       (the namequalification already adds pkgStandard...)
  ScopePath pathToGlobal(const SgScopeStatement& n);


  /// converts all Ada style comments to C++ comments
  // \todo mv into Ada to C++ converter
  void convertAdaToCxxComments(SgNode* root, bool cxxLineComments = true);

  /// converts all symbol tables from case insensitive to case sensitive
  // \todo mv into Ada to C++ converter
  void convertToCaseSensitiveSymbolTables(SgNode* root);

  /// converts AST from a function call representation to operator form
  ///   for fundamental operator declarations.
  /// \param root                  the subtree is traversed to find operator calls (using the traversal mechanism)
  /// \param convertCallSyntax     false, only convert those calls where get_uses_operator_syntax() returns false
  ///                              true,  convert all calls (may result in invalid Ada)
  /// \param convertNamedArguments not relevant, when \ref convertCallSyntax == false
  ///                              true, named arguments are resolved
  ///                              false, named arguments are preserved
  // \todo mv into Ada to C++ converter
  void convertToOperatorRepresentation(SgNode* root, bool convertCallSyntax = false, bool convertNamedArguments = false);
} // Ada
} // SageInterface

#endif /* _SAGEINTERFACE_ADA_H */
