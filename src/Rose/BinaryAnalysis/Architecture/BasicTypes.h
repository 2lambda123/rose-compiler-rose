#ifndef ROSE_BinaryAnalysis_Architecture_BasicTypes_H
#define ROSE_BinaryAnalysis_Architecture_BasicTypes_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/Architecture/Exception.h> // needed for Result<T,NotFound>

#include <Sawyer/Message.h>
#include <Sawyer/Result.h>
#include <memory>
#include <set>
#include <string>
#include <vector>

// Basic types needed by almost all architectures

namespace Rose {
namespace BinaryAnalysis {
namespace Architecture {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward class declarations for built-in architectures and their reference-counting pointers.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Amd64;
using Amd64Ptr = std::shared_ptr<Amd64>;                /**< Reference counted pointer for @ref Amd64. */

class ArmAarch32;
using ArmAarch32Ptr = std::shared_ptr<ArmAarch32>;      /**< Reference counted pointer for @ref ArmAarch32. */

class ArmAarch64;
using ArmAarch64Ptr = std::shared_ptr<ArmAarch64>;      /**< Reference counted pointer for @ref ArmAarch64. */

class Base;
using BasePtr = std::shared_ptr<Base>;                  /**< Reference counted pointer for @ref Base. */
using BaseConstPtr = std::shared_ptr<const Base>;       /**< Reference counted pointer for @ref Base. */

class Cil;
using CilPtr = std::shared_ptr<Cil>;                    /**< Reference counted pointer for @ref Cil. */

class Intel80286;
using Intel80286Ptr = std::shared_ptr<Intel80286>;      /**< Reference counted pointer for @ref Intel80286. */

class Intel8086;
using Intel8086Ptr = std::shared_ptr<Intel8086>;        /**< Reference counted pointer for @ref Intel8086. */

class Intel8088;
using Intel8088Ptr = std::shared_ptr<Intel8088>;        /**< Reference counted pointer for @ref Intel8088. */

class IntelI386;
using IntelI386Ptr = std::shared_ptr<IntelI386>;        /**< Reference counted pointer for @ref IntelI386. */

class IntelI486;
using IntelI486Ptr = std::shared_ptr<IntelI486>;        /**< Reference counted pointer for @ref IntelI486. */

class IntelPentium;
using IntelPentiumPtr = std::shared_ptr<IntelPentium>;  /**< Reference counted pointer for @ref IntelPentium. */

class IntelPentiumii;
using IntelPentiumiiPtr = std::shared_ptr<IntelPentiumii>; /**< Reference counted pointer for @ref IntelPentiumii. */

class IntelPentiumiii;
using IntelPentiumiiiPtr = std::shared_ptr<IntelPentiumiii>; /**< Reference counted pointer for @ref IntelPentiumiii. */

class IntelPentium4;
using IntelPentium4Ptr = std::shared_ptr<IntelPentium4>; /**< Reference counted pointer for @ref IntelPentium4. */

class Jvm;
using JvmPtr = std::shared_ptr<Jvm>;                    /**< Reference counted pointer for @ref Jvm. */

class Mips32;
using Mips32Ptr = std::shared_ptr<Mips32>;              /**< Reference counted pointer for @ref Mips32. */

class Motorola;
using MotorolaPtr = std::shared_ptr<Motorola>;          /**< Reference counted pointer for @ref Motorola. */

class Motorola68040;
using Motorola68040Ptr = std::shared_ptr<Motorola68040>; /**< Reference counted pointer for @ref Motorola68040. */

class NxpColdfire;
using NxpColdfirePtr = std::shared_ptr<NxpColdfire>;    /**< Reference counted pointer for @ref NxpColdfire. */

class Powerpc;
using PowerpcPtr = std::shared_ptr<Powerpc>;            /**< Reference counted pointer for @ref Powerpc. */

class Powerpc32;
using Powerpc32Ptr = std::shared_ptr<Powerpc32>;        /**< Reference counted pointer for @ref Powerpc32. */

class Powerpc64;
using Powerpc64Ptr = std::shared_ptr<Powerpc64>;        /**< Reference counted pointer for @ref Powerpc64. */

class X86;
using X86Ptr = std::shared_ptr<X86>;                    /**< Reference counted pointer for @ref X86. */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Diagnostics
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Diagnostic facility for architecture definitions. */
extern Sawyer::Message::Facility mlog;

/** Initialize and registers architecture diagnostic streams.
 *
 *  See @ref Rose::Diagnostics::initialize. */
void initDiagnostics();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Subclass registration functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Register a new architecture definition.
 *
 *  The specified definition is added to the ROSE library. When searching for an architecture, architectures registered later
 *  are preferred over architectures registered earlier.
 *
 *  Thread safety: This function is thread safe. */
void registerDefinition(const BasePtr&);

/** Remove the specified architecture from the list of registered architectures.
 *
 *  If the specified architecture object is found, then the latest such object is removed from the registration. This function
 *  is a no-ip if the argument is a null pointer.
 *
 *  Returns true if any architecture definition object was removed, false if the object was not found.
 *
 *  Thread safety: This function is thread safe. */
bool deregisterDefinition(const BasePtr&);

/** Registered architectures.
 *
 *  Returns the registered architectures in the reverse order they were registered.
 *
 *  Thread safety: This function is thread safe. */
std::vector<BasePtr> registeredDefinitions();

/** Names of all registered architectures.
 *
 *  Returns the names of all registered architectures. This is returned as a set, although there is no requirement that the
 *  registered architectures have unique names.
 *
 *  Thread safety: This function is thread safe. */
std::set<std::string> registeredNames();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Searching for suitable architectures
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Look up a new architecture by name.
 *
 *  Looks through the list of registered architectures (from most recently registered to earliest registered) and returns
 *  the first one whose @c matchesName predicate returns true. If none match, then a @ref Architecture::NotFound error is returned.
 *
 *  Thread safety: This function is thread safe. */
Sawyer::Result<BasePtr, NotFound> findByName(const std::string&);

/** Finds a suitable architecture for a file header.
 *
 *  Looks through the list of registered architectures (from most recently registered to earliest registered) and returns the first
 *  one whose matchesHeader() predicate returns true. If none match, then a @ref Architecture::NotFound error is returned.
 *
 *  Thread safety: This function is thread safe. However, no other thread can be modifying the AST at the same time. */
Sawyer::Result<BasePtr, NotFound> findByHeader(SgAsmGenericHeader*);

/** Finds a suitable architecture for a binary interpretation.
 *
 *  Looks through the list of registered architectures (from most recently registered to earliest registered) and returns the first
 *  one whose matchesHeader() predicate returns true for all the headers in the interpration. Returns the architecture that matches,
 *  or a @ref Architecture::NotFound error.
 *
 *  Thread safety: This function is thread safe. However, no other thread can be modifying the AST at the same time. */
Sawyer::Result<BasePtr, NotFound> findByInterpretation(SgAsmInterpretation*);

/** Finds the architecture that matches the most file headers.
 *
 *  Given an interpretation containing zero of more file headers, find the architecture that matches the most headers and return
 *  it along with now many headers it matched. If there is a tie, then the latest such registered architecture is returned. If no
 *  architecture matches any of the headers, then a null pointer and zero is returned.
 *
 *  Thread safety: This function is thread safe. However, no other thread can be modifying the AST at the same time. */
std::pair<BasePtr, size_t> findBestByInterpretation(SgAsmInterpretation*);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Architecture name free function.
 *
 *  This is a convenient way to obtain an architecture definition's name without having to include "Base.h", and is therefore useful
 *  in header files that try to include a minimal number of type definitions. Returns a null pointer if the argument is a null
 *  pointer. */
const std::string& name(const BaseConstPtr&);

} // namespace
} // namespace
} // namespace

#endif
#endif
