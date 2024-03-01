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
#ifndef ROSE_src_generated_Rose_Sarif_NodeDeclarations_H
#define ROSE_src_generated_Rose_Sarif_NodeDeclarations_H

#include <Sawyer/Tree.h>

namespace Rose {
namespace Sarif {

class Analysis;

/** Shared-ownership pointer to @ref Analysis
 *
 * @{ */
using AnalysisPtr = std::shared_ptr<Analysis>;
using AnalysisConstPtr = std::shared_ptr<const Analysis>;
/** @} */

class Artifact;

/** Shared-ownership pointer to @ref Artifact
 *
 * @{ */
using ArtifactPtr = std::shared_ptr<Artifact>;
using ArtifactConstPtr = std::shared_ptr<const Artifact>;
/** @} */

class CodeFlow;

/** Shared-ownership pointer to @ref CodeFlow
 *
 * @{ */
using CodeFlowPtr = std::shared_ptr<CodeFlow>;
using CodeFlowConstPtr = std::shared_ptr<const CodeFlow>;
/** @} */

class Location;

/** Shared-ownership pointer to @ref Location
 *
 * @{ */
using LocationPtr = std::shared_ptr<Location>;
using LocationConstPtr = std::shared_ptr<const Location>;
/** @} */

class Log;

/** Shared-ownership pointer to @ref Log
 *
 * @{ */
using LogPtr = std::shared_ptr<Log>;
using LogConstPtr = std::shared_ptr<const Log>;
/** @} */

class Node;

/** Shared-ownership pointer to @ref Node
 *
 * @{ */
using NodePtr = std::shared_ptr<Node>;
using NodeConstPtr = std::shared_ptr<const Node>;
/** @} */

class Result;

/** Shared-ownership pointer to @ref Result
 *
 * @{ */
using ResultPtr = std::shared_ptr<Result>;
using ResultConstPtr = std::shared_ptr<const Result>;
/** @} */

class Rule;

/** Shared-ownership pointer to @ref Rule
 *
 * @{ */
using RulePtr = std::shared_ptr<Rule>;
using RuleConstPtr = std::shared_ptr<const Rule>;
/** @} */

class ThreadFlow;

/** Shared-ownership pointer to @ref ThreadFlow
 *
 * @{ */
using ThreadFlowPtr = std::shared_ptr<ThreadFlow>;
using ThreadFlowConstPtr = std::shared_ptr<const ThreadFlow>;
/** @} */

class ThreadFlowLocation;

/** Shared-ownership pointer to @ref ThreadFlowLocation
 *
 * @{ */
using ThreadFlowLocationPtr = std::shared_ptr<ThreadFlowLocation>;
using ThreadFlowLocationConstPtr = std::shared_ptr<const ThreadFlowLocation>;
/** @} */
} // namespace
} // namespace

#endif // ROSE_src_generated_Rose_Sarif_NodeDeclarations_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         THIS FILE IS MACHINE GENERATED  --  DO NOT MODIFY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
