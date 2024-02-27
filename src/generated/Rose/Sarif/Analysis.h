//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This file was generated by Rosebud
//     ./rosebud --no-locations --backend=sawyer --serializer=cereal
//         --sawyer-generated=/home/matzke/rose-wip/rose/src/generated/Rose/Sarif --sawyer-header-prefix=rose/Rose/Sarif
//
// See documentation for the ::Rosebud namespace for information about the input language and how to best run
// the commands to (re)generate this file. See `rosebud --help` for documentation about command-line switches.
//
// The ::Rosebud namespace might be documented at one of these places:
//     https://rpm.is/rose
//     http://rosecompiler.org/ROSE_HTML_Reference/index.html
//
#ifndef ROSE_Sarif_Analysis_H
#define ROSE_Sarif_Analysis_H

#include <rosePublicConfig.h>
#ifdef ROSE_HAVE_CEREAL
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>
#endif

#include <featureTests.h>
#ifdef ROSE_ENABLE_SARIF
#include <Rose/Sarif/Node.h>

#include <Sawyer/Optional.h>
#include <string>
#include <vector>

#ifdef ROSE_Sarif_Analysis_IMPL
#include <Rose/Sarif/Artifact.h>
#include <Rose/Sarif/Rule.h>
#include <Rose/Sarif/Result.h>
#endif

namespace Rose {
namespace Sarif {

/** One run of one analysis.
 *
 *  This class represents one run of one analysis and all the results from that run. An analysis can be one of many analyses run by
 *  a single tool, or can be the only analysis run by a tool.  Each analysis has a name and an optional command-line invocation. All
 *  the results for one analysis are stored in that object's @ref results vector. The results may point to specific @ref rules and
 *  @ref artifacts associated with this analysis.
 *
 *  Example:
 *
 *  @snippet{trimleft} sarifUnitTests.C sarif_analysis */
class Analysis: public Node {
public:
    // Automatically generated; do not modify!
    /** Shared-ownership pointer to @ref Analysis.
     *
     *  @{ */
    using Ptr = AnalysisPtr;
    using ConstPtr = AnalysisConstPtr;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /** Property: Analysis name.
     *
     *  The analysis name is any string, usually one line, breifly describing the analysis. This property is set by the
     *  constructor. 
     *  
     *  @{ */
public:
    // Automatically generated; do not modify!
    std::string const& name() const;
private:
    // Automatically generated; do not modify!
    void name(std::string const&);
private:
    // Automatically generated; do not modify!
    std::string name_P8119_;
    /** @} */

    /** Property: Version.
     *
     *  Version string for the tool. 
     *  
     *  @{ */
public:
    // Automatically generated; do not modify!
    std::string const& version() const;
public:
    // Automatically generated; do not modify!
    void version(std::string const&);
private:
    // Automatically generated; do not modify!
    std::string version_P9295_;
    /** @} */

    /** Property: Information URI.
     *
     *  URI pointing to more information about this analysis. 
     *  
     *  @{ */
public:
    // Automatically generated; do not modify!
    std::string const& informationUri() const;
public:
    // Automatically generated; do not modify!
    void informationUri(std::string const&);
private:
    // Automatically generated; do not modify!
    std::string informationUri_P4102_;
    /** @} */

    /** Rules associated with this analysis. 
     * 
     * @{ */
public:
    // Automatically generated; do not modify!
    EdgeVector<Rule> const& rules() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<Rule>& rules();
private:
    // Automatically generated; do not modify!
    EdgeVector<Rule> rules_P743_;
    /** @} */

    /** Property: Command-line.
     *
     *  The array of strings forming the command-line for this analysis.  The first member of the array is the name of the tool, and
     *  subsequent members are the arguments passed to that tool. 
     *  
     *  @{ */
public:
    // Automatically generated; do not modify!
    std::vector<std::string> const& commandLine() const;
public:
    // Automatically generated; do not modify!
    std::vector<std::string>& commandLine();
public:
    // Automatically generated; do not modify!
    void commandLine(std::vector<std::string> const&);
private:
    // Automatically generated; do not modify!
    std::vector<std::string> commandLine_P9065_;
    /** @} */

    /** Property: Command exit status.
     *
     *  This is the exit status of the command if the command did not exit because of a signal. 
     *  
     *  @{ */
public:
    // Automatically generated; do not modify!
    Sawyer::Optional<int> const& exitStatus() const;
public:
    // Automatically generated; do not modify!
    void exitStatus(Sawyer::Optional<int> const&);
private:
    // Automatically generated; do not modify!
    Sawyer::Optional<int> exitStatus_P7357_;
    /** @} */

    /** Artifacts for this analysis. 
     * 
     * @{ */
public:
    // Automatically generated; do not modify!
    EdgeVector<Artifact> const& artifacts() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<Artifact>& artifacts();
private:
    // Automatically generated; do not modify!
    EdgeVector<Artifact> artifacts_P9780_;
    /** @} */

    /** Results for this analysis. 
     * 
     * @{ */
public:
    // Automatically generated; do not modify!
    EdgeVector<Result> const& results() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<Result>& results();
private:
    // Automatically generated; do not modify!
    EdgeVector<Result> results_P9495_;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Public functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Find a rule by its ID.
     *
     *  Scans through the @ref rules and returns the first one whose ID is the specified string, or null if no such rule exists. */
    RulePtr findRuleById(const std::string&);

    /** Find a rule by its name.
     *
     *  Scans through the @ref rules and returns the first one whose name property matches the specified string, or null if no such
     *  rule exists. */
    RulePtr findRuleByName(const std::string&);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Overrides
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    bool emit(std::ostream&) override;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Private functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    // Construct a shell command-line from the command-line arguments
    static std::string makeShellCommand(const std::vector<std::string>&);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generated constructors, etc.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
    /** Constructor. */
    explicit Analysis(std::string const& name);

public:
    /** Allocating constructor. */
    static Ptr instance(std::string const& name);

protected:
    /** Default constructor. */
    Analysis();

private:
    // Automatically generated; do not modify!
    /** Default allocating constructor. */
    static Ptr instance();

public:
    virtual ~Analysis();

#ifdef ROSE_HAVE_CEREAL
private:
    friend class cereal::access;

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_SAVE_FUNCTION_NAME(Archive &archive) const {
        archive(cereal::base_class<Node>(this));
        archive(cereal::make_nvp("name", name_P8119_));
        archive(cereal::make_nvp("version", version_P9295_));
        archive(cereal::make_nvp("informationUri", informationUri_P4102_));
        archive(cereal::make_nvp("rules", rules_P743_));
        archive(cereal::make_nvp("commandLine", commandLine_P9065_));
        archive(cereal::make_nvp("exitStatus", exitStatus_P7357_));
        archive(cereal::make_nvp("artifacts", artifacts_P9780_));
        archive(cereal::make_nvp("results", results_P9495_));
    }

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_LOAD_FUNCTION_NAME(Archive &archive) {
        archive(cereal::base_class<Node>(this));
        archive(cereal::make_nvp("name", name_P8119_));
        archive(cereal::make_nvp("version", version_P9295_));
        archive(cereal::make_nvp("informationUri", informationUri_P4102_));
        archive(cereal::make_nvp("rules", rules_P743_));
        archive(cereal::make_nvp("commandLine", commandLine_P9065_));
        archive(cereal::make_nvp("exitStatus", exitStatus_P7357_));
        archive(cereal::make_nvp("artifacts", artifacts_P9780_));
        archive(cereal::make_nvp("results", results_P9495_));
    }
#endif // ROSE_HAVE_CEREAL
};

} // namespace
} // namespace
#endif

#endif // include once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
