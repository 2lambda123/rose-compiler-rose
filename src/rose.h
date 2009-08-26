// rose.h -- header file for the ROSE Optimizing Preprocessor

#ifndef ROSE_H
#define ROSE_H

// DQ (4/21/2009): Andreas needs to add a comment about what this is for...
#define BOOST_WAVE_PREPROCESS_PRAGMA_BODY 1

#if 0
// Forward references to namespaces used in the binary execuable file format support.
namespace Exec{
namespace ELF{
   int xxx;
}
   int xxx;
}
#endif

// DQ (4/21/2009): This header file contains the definitions of the IR nodes.
#include "sage3.h"

// DQ (3/22/2009): This is already included in sage3.h"
// #include "roseInternal.h"

// DQ (10/27/2003): Needed access to global function defined in unparser.h
// I think it makes sense to include all of the unparser into the interface
// of ROSE (don't know why this was left out previously).
#include "unparser.h"

// DQ:7/29/2002, MS:12/11/2002
// Place this at the end (since it is dependent upon ROSE classes.)
// added here to avoid placing it in each header file using the AstProcessingLib
#include <typeinfo>
#include "AstProcessing.h"
#include "AstReverseProcessing.h"
#include "AstPDFGeneration.h"
#include "AstDOTGeneration.h"
#include "AstDiagnostics.h"
// #include "AstStatistics.h"
#include "Ast.h"

// DQ (10/18/2003) Why is this commented out (what is it)
//#include "AgProcessing.h"

// Not sure that we want this here since it uses the rewrite system
// which has not defined yet (circular reference in the header files)
// #include "AstRestructure.h"

#include "rewrite.h"
#include "roseTranslators.h"

// this is a temporary fix (will become obsolete)
#include "AstClearVisitFlags.h"

// DQ (5/26/2007): This is not depricated
// DQ (8/1/2005): Included Milind's AstMerge mechanism as standard part of ROSE.
// #include "AstMerge.h"

// DQ (5/26/2007): Use the new AST merge mechanism.
#include "merge.h"

// JH (01/18/2006): adding the include file for the AST file I/O (by Jochen)
#include "AST_FILE_IO.h"

// DQ (9/9/2007): Can't use astVisualization/ prefix since it then does not permit use from the install tree
// DQ (5/27/2007): Added astVisualization/ prefix to the header file
// DQ (2/22/2006): Added Andreas' work to graph the AST.
// #include "astVisualization/astGraph.h"
#include "astGraph.h"

// DQ (9/9/2007): Can't use astVisualization/ prefix since it then does not permit use from the install tree
// DQ (5/27/2007): Added astVisualization/ prefix to the header file
// DQ (6/23/2006): Added Andreas's work to support custom DOT graphs using persistant attributes.
// #include "astVisualization/AstAttributeDOT.h"
#include "AstAttributeDOT.h"

// DQ (3/11/2006): Jeremiah Willcock's inliner
#include "inliner.h"

// DQ (3/18/2006): Jeremiah Willcock's partial redundancy elimination (PRE)
#include "pre.h"

// DQ (4/8/2006): Constant folding of the AST (cleans out redundant
// constant expresion trees save in translation from the frontend).
// Required to be run before PRE!
#include "constantFolding.h"

// DQ (5/8/2007): Added Robert Preissl's support for hidden type and declartion lists.
#include "HiddenList.h"
#include "HiddenList_Output.h"
#include "HiddenList_Intersection.h"

// DQ (1/25/2008): Added cfgToDot.h as suggested by Jeremiah
#include "cfgToDot.h"

// DQ (1/24/2008): Add these here to permit simple and uniform support of binaries.
// File in src/frontend/BinaryDisassembly
#include "RoseBin_support.h"
#ifdef HASH_ROSE_USE_BINARYSQL
  #include "RoseBin.h"
#endif

#include "MemoryMap.h"
#include "RoseBin_abstract.h"
#include "RoseFile.h"
#include "RoseObj.h"

#include "RoseBin_DotGraph.h"
#include "RoseBin_GmlGraph.h"
#include "RoseBin_ControlFlowAnalysis.h"
#include "RoseBin_DataFlowAnalysis.h"
#include "RoseBin_CallGraphAnalysis.h"

#include "AST_BIN_Traversal.h"

#include "AssemblerX86Init.h"
#include "x86InstructionEnum.h"
#include "x86InstructionProperties.h"

#include "armInstructionEnum.h"

#include "powerpcInstructionEnum.h"
#include "powerpcInstructionProperties.h"

// Files in src/frontend/Disassemblers
#include "Disassembler.h"
#include "DisassemblerArm.h"
#include "DisassemblerPowerpc.h"
#include "DisassemblerX86.h"
#include "Partitioner.h"
#include "Assembler.h"
#include "AssemblerX86.h"

// Files in src/backend/asmUnparser
#include "unparseAsm.h"

// Endian access wrappers in src/frontend/SageIII/sageInterface
#include "endianWrappers.h"

// ABI struct layout and similar helpers in src/frontend/SageIII/sageInterface
#include "abiStuff.h"

// DQ (3/8/2009): Why is this here?
// added .h file for error check transformations
//#include "RuntimeInstrumentation.h"

#include "PHPFrontend.h"

#if 0
// DQ (3/13/2009): Trying to get Dwarf in ROSE to work with Intel Pin.
#if USE_ROSE_DWARF_SUPPORT && USE_ROSE_INTEL_PIN_SUPPORT
// DQ (3/10/2009): This fails with Intel Pin, which uses it's own version of dwarf and 
// thus causes a problem (compiles and links but fails at dwarf_init()).
#error "Support for both DWARF and Intel Pin fails, these configure options are incompatable."
#endif
#endif

// DQ (11/7/2008): Added Dwarf support to ROSE AST (applies only to binary executables generated with dwarf debugging information).
#if USE_ROSE_DWARF_SUPPORT
#include "dwarfSupport.h"
#endif

// DQ (3/8/2009): Added support for Intel Pin (Dynamic binary Instrumentation)
#ifdef USE_ROSE_INTEL_PIN_SUPPORT
// Note that pin.H (in it's header files) will define "TRUE" and "FALSE" as macros.
#include "IntelPinSupport.h"
#endif

// DQ (4/20/2009): Added support to optionally get more information out about new delete operators.
// #define COMPILE_DEBUG_STATEMENTS 1

// ifndef ROSE_H
#endif
