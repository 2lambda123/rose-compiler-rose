//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This file was generated by Rosebud
//     ./rosebud --no-locations --backend=sawyer --serializer=none
//         --sawyer-generated=/home/matzke/rose-wip/rose/src/generated/Rose/Sarif --sawyer-header-prefix=rose/Rose/Sarif
//
// See documentation for the ::Rosebud namespace for information about the input language and how to best run
// the commands to (re)generate this file. See `rosebud --help` for documentation about command-line switches.
//
// The ::Rosebud namespace might be documented at one of these places:
//     https://rpm.is/rose
//     http://rosecompiler.org/ROSE_HTML_Reference/index.html
//
#ifndef ROSE_Sarif_Result_H
#define ROSE_Sarif_Result_H

#include <featureTests.h>
#ifdef ROSE_ENABLE_SARIF
#include <Rose/Sarif/Node.h>

#ifdef ROSE_Sarif_Result_IMPL
#include <Rose/Sarif/CodeFlow.h>
#include <Rose/Sarif/Location.h>
#endif

namespace Rose {
namespace Sarif {

/** A single result from an analysis.
 *
 *  A result is the child of an @ref Analysis in a SARIF @ref Log. A result has a @ref Kind such as @c PASS or @c FAIL. A failure
 *  result has a @ref Severity such as @c WARNING or @c ERROR. Other result properties are a @ref message, an @ref id "ID", a
 *  reference to a particular @ref rule, a reference to the @ref analysisTarget "analysis target artifact", etc. A result also has
 *  a list of @ ref locations.
 *
 *  Example:
 *
 *  @snippet{trimleft} sarifUnitTests.C sarif_result */
class Result: public Node {
public:
    // Automatically generated; do not modify!
    /** Shared-ownership pointer to @ref Result.
     *
     *  @{ */
    using Ptr = ResultPtr;
    using ConstPtr = ResultConstPtr;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /** Property: Kind of result.
     *
     *  The kind is set by the constructor and is read-only. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    Kind kind_P4703_;
public:
    // Automatically generated; do not modify!
    Kind const& kind() const;
private:
    // Automatically generated; do not modify!
    void forceSetKind(Kind const&);
    /** @} */

    /** Property: Severity of result.
     *
     *  The severity is set by the constructor and is read-only. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    Severity severity_P3287_;
public:
    // Automatically generated; do not modify!
    Severity const& severity() const;
private:
    // Automatically generated; do not modify!
    void forceSetSeverity(Severity const&);
    /** @} */

    /** Property: Message.
     *
     *  An optional multi-line text message. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    std::string message_P8759_;
public:
    // Automatically generated; do not modify!
    std::string const& message() const;
public:
    // Automatically generated; do not modify!
    void message(std::string const&);
    /** @} */

    /** Property: Stable ID.
     *
     *  A result may have a stable ID. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    std::string id_P6463_;
public:
    // Automatically generated; do not modify!
    std::string const& id() const;
public:
    // Automatically generated; do not modify!
    void id(std::string const&);
    /** @} */

    /** Property: Associated rule.
     *
     *  Pointer to an optional rule associated with this result. If this result points to a rule, then the rule must be attached to
     *  the same @ref Analysis as this result before this result can be emitted. Attempting to emit a result pointing to a detached
     *  rule will result in an exception. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    RulePtr rule_P2631_;
public:
    // Automatically generated; do not modify!
    RulePtr const& rule() const;
public:
    // Automatically generated; do not modify!
    void rule(RulePtr const&);
    /** @} */

    /** Property: Analysis target.
     *
     *  Pointer to an optional artifact associated with this result. If this result points to an analysis target, then that target
     *  must be attached to the same @ref Analysis as one of its artifacts before this result can be emitted. Attempting to emit a
     *  result pointing to a detached artifact will result in an exception. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    ArtifactPtr analysisTarget_P3770_;
public:
    // Automatically generated; do not modify!
    ArtifactPtr const& analysisTarget() const;
public:
    // Automatically generated; do not modify!
    void analysisTarget(ArtifactPtr const&);
    /** @} */

public:

    /** Locations associated with this result. 
     * 
     * @{ */
private:
    // Automatically generated; do not modify!
    EdgeVector<Location> locations_P2292_;
public:
    // Automatically generated; do not modify!
    EdgeVector<Location> const& locations() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<Location>& locations();
    /** @} */

    /** Code flows associated with this result. 
     * 
     * @{ */
private:
    // Automatically generated; do not modify!
    EdgeVector<CodeFlow> codeFlows_P1620_;
public:
    // Automatically generated; do not modify!
    EdgeVector<CodeFlow> const& codeFlows() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<CodeFlow>& codeFlows();
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Public functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    // Find index, if any, of the specified rule within the parent analysis.
    Sawyer::Optional<size_t> findRuleIndex(const RulePtr&);

    // Find index, if any, of the specified artifact within the parent analysis.
    Sawyer::Optional<size_t> findArtifactIndex(const ArtifactPtr&);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Allocating constructor.
     *
     *  If a @ref Kind is specified then it must not be @ref Kind::FAIL. If a @ref Severity is specified then is must not be @ref
     *  Severity::NONE.
     *
     *  If a location is specified, then it becomes the first location. Locations can be added/removed/modified later by adjusting
     *  the @ref locations property.
     *
     * @{ */
    static Ptr instance(Kind, const std::string &mesg);
    static Ptr instance(Kind, const std::string &mesg, const LocationPtr &location);
    static Ptr instance(Severity, const std::string &mesg);
    static Ptr instance(Severity, const std::string &mesg, const LocationPtr &location);
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Overrides
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    bool emit(std::ostream&) override;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generated constructors, etc.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
    /** Default constructor. */
    Result();

public:
    ~Result();
};

} // namespace
} // namespace
#endif

#endif // include once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
