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
#ifndef ROSE_Sarif_Node_H
#define ROSE_Sarif_Node_H
#include <RoseFirst.h>

#include <rosePublicConfig.h>
#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/shared_ptr.hpp>
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
#include <Sawyer/Tree.h>
#include <Rose/Sarif/BasicTypes.h>
#include <Rose/Sarif/NodeDeclarations.h>

namespace Rose {
namespace Sarif {

/** Base class for Sarif nodes. */
class Node: public Sawyer::Tree::Vertex<Node> {
public:
    // Automatically generated; do not modify!
    /** Shared-ownership pointer to @ref Node.
     *
     *  @{ */
    using Ptr = NodePtr;
    using ConstPtr = NodeConstPtr;
    /** @} */

public:
    /** Emit this node and its children as JSON.
     *
     *  Returns true if this node produced (or tried to produce) any output, false if not. */
    virtual bool emit(std::ostream&) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generated constructors, etc.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
    /** Default constructor. */
    Node();

public:
    virtual ~Node();

    //----------------------- Boost serialization for Node -----------------------
#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
private:
    friend class boost::serialization::access;

    template<class S>
    void serialize(S &s, const unsigned /*version*/) {
    }
#endif // ROSE_HAVE_BOOST_SERIALIZATION_LIB

#ifdef ROSE_HAVE_CEREAL
private:
    friend class cereal::access;

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_SAVE_FUNCTION_NAME(Archive &archive) const {
    }

    // Automatically generated; do not modify!
    template<class Archive>
    void CEREAL_LOAD_FUNCTION_NAME(Archive &archive) {
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
