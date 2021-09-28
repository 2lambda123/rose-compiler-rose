#ifndef ROSE_BinaryAnalysis_ModelChecker_Settings_H
#define ROSE_BinaryAnalysis_ModelChecker_Settings_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/ModelChecker/Types.h>
#include <Sawyer/CommandLine.h>

namespace Rose {
namespace BinaryAnalysis {
namespace ModelChecker {

/** Simple settings for the model checker.
 *
 *  These are the simple, non-programming settings for the model checker. Most of these can be adjusted easily from
 *  command-line parsers. */
class Settings {
public:
    using Ptr = SettingsPtr;
public:
    bool showInitialStates = false;                     /**< Show initial execution unit states when debugging. */
    bool showIntermediateStates = false;                /**< Show intermediate execution unit states when debugging. */
    bool showFinalStates = false;                       /**< Show final execution unit states when debugging. */
    bool showAssertions = false;                        /**< Show SMT assertions at the beginning of each execution unit. */
    bool ignoreSemanticFailures = false;                /**< Treat failed instructions as if they completed. */
    size_t k = 1000;                                    /**< Maximum path length in steps. */
    Sawyer::Optional<uint64_t> maxTime;                 /**< Maximum path time in seconds. */
    bool rejectUnknownInsns = true;                     /**< Reject "unknown" instructions even if semantic failure is allowed. */
    Sawyer::Optional<uint64_t> solverTimeout;           /**< Timeout per SMT solver call in seconds. */
    SourceListerPtr sourceLister;                       /**< Object responsible for listing lines of a source code file. */
    uint64_t maxSymbolicSize = 0;                       /**< If nonzero, maximum size of symbolic expressions. */
    bool exploreDuplicateStates = true;                 /**< Look for duplicate states and suppress them? */

public:
    Settings();
    virtual ~Settings();
    static Ptr instance();

public:
    /** Command-line switches to adjust settings.
     *
     *  Returns a switch group describing the command line switches that adjust the data members of this object.
     *  This object must not be deleted before the returned switch group is used to parse a command-line.
     *
     *  Thread safety: This method is not thread safe. */
    Sawyer::CommandLine::SwitchGroup commandLineSwitches();
};


} // namespace
} // namespace
} // namespace

#endif
#endif
