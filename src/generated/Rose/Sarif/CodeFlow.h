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
#ifndef ROSE_Sarif_CodeFlow_H
#define ROSE_Sarif_CodeFlow_H

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

    /** Code flows per thread. 
     * 
     * @{ */
private:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlow> threadFlows_P4678_;
public:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlow> const& threadFlows() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlow>& threadFlows();
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
};

} // namespace
} // namespace
#endif

#endif // include once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
