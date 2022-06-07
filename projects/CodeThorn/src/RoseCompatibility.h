#ifndef ROSE_MAPPING
#define ROSE_MAPPING 1

// minimal header for mapping rose onto the class hierarchy analysis

#include <sage3basic.h>

//~ #include <VariableIdMapping.h>

#include <string>
#include <functional>

namespace CodeThorn
{

constexpr
unsigned char STRIP_MODIFIER_ALIAS = SgType::STRIP_MODIFIER_TYPE | SgType::STRIP_TYPEDEF_TYPE;


using ClassKeyType        = const SgClassDefinition*;
using FunctionTypeKeyType = const SgFunctionType*;
using TypeKeyType         = const SgType*;
using CastKeyType         = const SgCastExp*;
using VariableKeyType     = const SgInitializedName*;
using FunctionKeyType     = const SgMemberFunctionDeclaration*;
using ASTRootType         = SgProject*;

/// type of a class naming function
using ClassNameFn   = std::function<std::string(ClassKeyType)>;

/// type of a function naming function
using FuncNameFn    = std::function<std::string(FunctionKeyType)>;

/// type of a variable naming function
using VarNameFn     = std::function<std::string(VariableKeyType)>;


class ClassAnalysis;
class CastAnalysis;

/// a compatibility layer that abstracts functions and queries of
///   the AST and implements those capabilities for ROSE.
class RoseCompatibilityBridge
{
  public:
    enum ReturnTypeRelation : int
    {
      unrelated = 0,
      sametype  = 1,
      covariant = 2
    };

    RoseCompatibilityBridge()  = default;
    ~RoseCompatibilityBridge() = default;

    /// returns the variable-id for a variable or parameter \ref var
    /// \{
    VariableKeyType variableId(SgInitializedName* var) const;
    VariableKeyType variableId(SgVariableDeclaration* var) const;
    /// \}

    /// returns the function-id for a (member) function \ref fun
    FunctionKeyType functionId(const SgMemberFunctionDeclaration* fun) const;

    /// returns a string representation for \ref vid
    std::string nameOf(VariableKeyType vid) const;

    /// returns a string representation for \ref vid
    std::string nameOf(FunctionKeyType fid) const;

    /// compares the name of functions \ref lhs and \ref rhs
    /// \param lhs some function
    /// \param rhs some function
    /// \returns 0 iff lhs and rhs have the same name (wrt virtual function overriding)
    ///          1 iff lhs > rhs
    ///          -1 iff lhs < rhs
    int compareNames(FunctionKeyType lhs, FunctionKeyType rhs) const;

    /// compares the types of \ref lhs and \ref rhs
    /// \param lhs some function type
    /// \param rhs some function type
    /// \param exclReturnType if true the return types of \ref lhs and \ref rhs
    ///        are not considered (though the return types of potential arguments
    ///        and return types are). This can be useful for obtaining equality of
    ///        functions that have covariant return types.
    /// \returns 0 iff lhs and rhs have the same type
    ///          1 iff lhs > rhs
    ///          -1 iff lhs < rhs
    /// \details
    ///    The comparison skips over typedef aliases and handles array to pointer decay.
    int compareFunctionTypes(FunctionTypeKeyType lhs, FunctionTypeKeyType rhs, bool exclReturnType = true) const;

    /// compares the types of \ref lhs and \ref rhs
    /// \param lhs some function
    /// \param rhs some function
    /// \param exclReturnType if true the return types of \ref lhs and \ref rhs
    ///        are not considered (though the return types of potential arguments
    ///        and return types are). This can be useful for obtaining equality of
    ///        functions that have covariant return types.
    /// \returns 0 iff lhs and rhs have the same type
    ///          1 iff lhs > rhs
    ///          -1 iff lhs < rhs
    /// \details
    ///    The comparison skips over typedef aliases and handles array to pointer decay.
    int compareTypes(FunctionKeyType lhs, FunctionKeyType rhs, bool exclReturnType = true) const;

    /// tests if \ref drvId has the same or covariant return type with respect to \ref basId
    /// \param classes the extracted class analysis
    /// \param basId   ID of a function in a base class
    /// \param drvId   ID of a function in a derived class
    /// \details
    ///    The function only checks the return type, and does not check whether the classes in which
    ///    the functions \ref drvId and \ref basId are defined are in a inheritance relationship.
    ReturnTypeRelation
    haveSameOrCovariantReturn(const ClassAnalysis&, FunctionKeyType basId, FunctionKeyType drvId) const;

    /// extracts class and cast information under the root
    void extractFromProject(ClassAnalysis&, CastAnalysis&, ASTRootType) const;

    /// returns iff \ref id is a pure virtual member function
    bool isPureVirtual(FunctionKeyType id) const;

    /// returns a function that maps a FunctionKeyType to std::string
    FuncNameFn functionNomenclator() const;

    /// returns a function that maps a ClassKeyType to std::string
    ClassNameFn classNomenclator() const;

    /// returns a function that maps a VariableId to std::string
    VarNameFn variableNomenclator() const;

    std::vector<FunctionKeyType>
    constructors(ClassKeyType) const;

  private:
    //~ RoseCompatibilityBridge()                                          = delete;
    RoseCompatibilityBridge(RoseCompatibilityBridge&&)                 = delete;
    RoseCompatibilityBridge& operator=(RoseCompatibilityBridge&&)      = delete;
    RoseCompatibilityBridge(const RoseCompatibilityBridge&)            = delete;
    RoseCompatibilityBridge& operator=(const RoseCompatibilityBridge&) = delete;
};

/// wrapper class to produce informative debug output about casts
struct CastWriterDbg
{
    CastWriterDbg(CastKeyType n)
    : node(n)
    {}

    CastKeyType node;
};

std::ostream& operator<<(std::ostream& os, const CastWriterDbg&);

/// returns a string representation of \ref key
std::string typeNameOf(ClassKeyType key);


/// calls the callback function \ref fn(derived, base, isvirtual)
///   for all direct base classes of \ref clkey
void inheritanceEdges( ClassKeyType clkey,
                       std::function<void(ClassKeyType, ClassKeyType, bool)> fn
                     );
/// returns the class/base-type information for a given type \ref tykey
/// \details
///   - if the type \ref tykey does not refer to a class ClassKeyType{}
///     is returned.
///   - base type refers to a type after aliases, references, pointers, decltype, and modifiers.
std::pair<ClassKeyType, TypeKeyType> getClassCastInfo(TypeKeyType tykey);

//
// ROSE utilities

/// returns the class definition for \ref n.
/// \pre isSgClassDeclaration(n.get_definingDeclaration())
SgClassDefinition& getClassDef(const SgDeclarationStatement& n);

/// returns the class definition where \ref n is defined
SgClassDefinition& getClassDef(const SgMemberFunctionDeclaration& n);

/// returns the class definition associated with expression \ref n
/// \details
///    strips modifiers, aliases, references, and pointers
/// returns nullptr if a class definition cannot be found
SgClassDefinition* getClassDefOpt(const SgExpression& n, bool skipUpCasts = false);

/// returns the class definition of \ref n
/// returns nullptr if a class definition cannot be found
SgClassDefinition* getClassDefOpt(const SgClassType& n);

/// returns the associated class definitions of \ref n
/// \details
///   strips arrays, modifiers, and typedefs.
///   DOES NOT strip references and pointers.
/// returns nullptr if a class definition cannot be found
SgClassDefinition* getClassDefOpt(const SgInitializedName& n);

/// returns the representative declaration for \ref memfn
SgMemberFunctionDeclaration& keyDecl(SgMemberFunctionDeclaration& memfn);

}
#endif /* ROSE_MAPPING */
