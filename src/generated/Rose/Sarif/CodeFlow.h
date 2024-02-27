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
#ifndef ROSE_Sarif_CodeFlow_H
#define ROSE_Sarif_CodeFlow_H

#include <rosePublicConfig.h>
#ifdef ROSE_HAVE_CEREAL
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>
#endif

#include <featureTests.h>
#ifdef ROSE_ENABLE_SARIF
#include <Rose/Sarif/Node.h>

#include <string>

#ifdef ROSE_Sarif_CodeFlow_IMPL
#include <Rose/Sarif/ThreadFlow.h>
#endif

namespace Rose {
namespace Sarif {

/** Progress of one or more programs through one or more thread flows.
 *
 *  A CodeFlow object describes the progress of one or more programs through one or more thread flows, which together lead to the
 *  detection of a problem in the system being analyzed. A thread flow is a temporally ordered sequence of code locations occurring
 *  within a single thread of execution, typically an operating system thread or a fiber. The thread flows in a code flow may lie
 *  within a single process, within multiple processes on the same machine, or within multiple processes on multiple machines.
 *
 *  Example:
 *
 *  @snippet{trimleft} sarifUnitTests.C sarif_flow */
class CodeFlow: public Node {
public:
    // Automatically generated; do not modify!
    /** Shared-ownership pointer to @ref CodeFlow.
     *
     *  @{ */
    using Ptr = CodeFlowPtr;
    using ConstPtr = CodeFlowConstPtr;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /** Property: Message string.
     *
     *  Optional message associated a code flow. 
     *  
     *  @{ */
public:
    // Automatically generated; do not modify!
    std::string const& message() const;
public:
    // Automatically generated; do not modify!
    void message(std::string const&);
private:
    // Automatically generated; do not modify!
    std::string message_P8759_;
    /** @} */

    /** Code flows per thread. 
     * 
     * @{ */
public:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlow> const& threadFlows() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlow>& threadFlows();
private:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlow> threadFlows_P4678_;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Allocating constructor. */
    static Ptr instance(const std::string &message);

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
    CodeFlow();

public:
    // Automatically generated; do not modify!
    /** Default allocating constructor. */
    static Ptr instance();

public:
    virtual ~CodeFlow();

#ifdef ROSE_HAVE_CEREAL
private:
    friend class cereal::access;

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_SAVE_FUNCTION_NAME(Archive &archive) const {
        archive(cereal::base_class<Node>(this));
        archive(cereal::make_nvp("message", message_P8759_));
        archive(cereal::make_nvp("threadFlows", threadFlows_P4678_));
    }

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_LOAD_FUNCTION_NAME(Archive &archive) {
        archive(cereal::base_class<Node>(this));
        archive(cereal::make_nvp("message", message_P8759_));
        archive(cereal::make_nvp("threadFlows", threadFlows_P4678_));
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
