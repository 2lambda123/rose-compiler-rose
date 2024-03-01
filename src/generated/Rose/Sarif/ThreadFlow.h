//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This file was generated by Rosebud
//     ./rosebud --no-locations --backend=sawyer '--serializer=boost,cereal'
//         --sawyer-generated=/home/matzke/rose-wip/rose/src/generated/Rose/Sarif --sawyer-header-prefix=rose/Rose/Sarif
//
// See documentation for the ::Rosebud namespace for information about the input language and how to best run
// the commands to (re)generate this file. See `rosebud --help` for documentation about command-line switches.
//
// The ::Rosebud namespace might be documented at one of these places:
//     https://rpm.is/rose
//     http://rosecompiler.org/ROSE_HTML_Reference/index.html
//
#ifndef ROSE_Sarif_ThreadFlow_H
#define ROSE_Sarif_ThreadFlow_H

#include <rosePublicConfig.h>
#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#endif

#include <rosePublicConfig.h>
#ifdef ROSE_HAVE_CEREAL
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#endif

#include <featureTests.h>
#ifdef ROSE_ENABLE_SARIF
#include <Rose/Sarif/Node.h>

#include <string>

#ifdef ROSE_Sarif_ThreadFlow_IMPL
#include <Rose/Sarif/ThreadFlowLocation.h>
#endif

namespace Rose {
namespace Sarif {

/** Sequence of code locations that specify a single-threaded path.
 *
 *  A thread flow is a sequence of code locations that specify a possible path through a single thread of execution such as an
 *  operating system thread or a fiber.
 *
 *  Example:
 *
 *  @snippet{trimleft} sarifUnitTests.C sarif_flow */
class ThreadFlow: public Node {
public:
    // Automatically generated; do not modify!
    /** Shared-ownership pointer to @ref ThreadFlow.
     *
     *  @{ */
    using Ptr = ThreadFlowPtr;
    using ConstPtr = ThreadFlowConstPtr;
    /** @} */

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /** Property: Message string.
     *
     *  Optional message string. 
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

public:

    /** Locations visited by an analysis tool. 
     * 
     * @{ */
public:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlowLocation> const& locations() const;
public:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlowLocation>& locations();
private:
    // Automatically generated; do not modify!
    EdgeVector<ThreadFlowLocation> locations_P2292_;
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Allocating constructor.
     *
     *  The message may be an empty string. */
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
    ThreadFlow();

public:
    // Automatically generated; do not modify!
    /** Default allocating constructor. */
    static Ptr instance();

public:
    virtual ~ThreadFlow();

    //----------------------- Boost serialization for ThreadFlow -----------------------
#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
private:
    friend class boost::serialization::access;

    template<class S>
    void serialize(S &s, const unsigned /*version*/) {
        s & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Node);
        s & BOOST_SERIALIZATION_NVP(message_P8759_);
        s & BOOST_SERIALIZATION_NVP(locations_P2292_);
    }
#endif // ROSE_HAVE_BOOST_SERIALIZATION_LIB

#ifdef ROSE_HAVE_CEREAL
private:
    friend class cereal::access;

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_SAVE_FUNCTION_NAME(Archive &archive) const {
        archive(cereal::base_class<Node>(this));
        archive(cereal::make_nvp("message", message_P8759_));
        archive(cereal::make_nvp("locations", locations_P2292_));
    }

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_LOAD_FUNCTION_NAME(Archive &archive) {
        archive(cereal::base_class<Node>(this));
        archive(cereal::make_nvp("message", message_P8759_));
        archive(cereal::make_nvp("locations", locations_P2292_));
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
