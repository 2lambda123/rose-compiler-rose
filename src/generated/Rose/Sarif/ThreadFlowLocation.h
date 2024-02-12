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
#ifndef ROSE_Sarif_ThreadFlowLocation_H
#define ROSE_Sarif_ThreadFlowLocation_H

#include <featureTests.h>
#ifdef ROSE_ENABLE_SARIF
#include <Rose/Sarif/Node.h>

#ifdef ROSE_Sarif_ThreadFlowLocation_IMPL
#include <Rose/Sarif/Location.h>
#endif

namespace Rose {
namespace Sarif {

/** A location visited by an analysis tool.
 *
 *  This object represents a location visited by an analysis tool in the course of simulating or monitoring the execution of a
 *  program.
 *
 *  Example:
 *
 *  @snippet{trimleft} sarifUnitTests.C sarif_flow */
class ThreadFlowLocation: public Node {
public:
    // Automatically generated; do not modify!
    /** Shared-ownership pointer to @ref ThreadFlowLocation.
     *
     *  @{ */
    using Ptr = ThreadFlowLocationPtr;
    using ConstPtr = ThreadFlowLocationConstPtr;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /** Property: Message.
     *
     *  The message is optional, but a non-empty message must be present if the location is null when this object is emitted. 
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

public:

    /** Optional location.
     *
     *  Some analyses are not able to provide a location for every step in the code flow. If there is no location, then a @ref
     *  message should be present. 
     *  
     *  @{ */
private:
    // Automatically generated; do not modify!
    Edge<Location> location_P9311_;
public:
    // Automatically generated; do not modify!
    Edge<Location> const& location() const;
public:
    // Automatically generated; do not modify!
    Edge<Location>& location();
public:
    // Automatically generated; do not modify!
    void location(LocationPtr const&);
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Allocating constructor.
     *
     *  Although the constructor accepts an empty message and/or null location, a thread flow location should have a non-empty
     *  message, a non-null location, or both at the time it is emitted.
     *
     * @{ */
    static Ptr instance(const std::string &message);
    static Ptr instance(const LocationPtr&);
    static Ptr instance(const std::string &message, const LocationPtr&);
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
    ThreadFlowLocation();

public:
    ~ThreadFlowLocation();
};

} // namespace
} // namespace
#endif

#endif // include once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
