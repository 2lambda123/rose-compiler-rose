
/*
 * this includes the forward declarations of all the sage node classes
 * from the generated files (i.e. gives just the class names.)
 *
 */

#ifndef SAGE3_CLASSES_H
#define SAGE3_CLASSES_H
#include "sage3basic.h"


// DQ (12/9/2004): The name of this file has been changed to be the new location
// of many future Sage III AST manipulation functions in the future.  A namespace
// (SageInterface) is defined in sageInterface.h.
// #include "sageSupport.h"
#include "sageInterface.h"

#include "AstProcessing.h"

// Markus Kowarschik: Support for preprocessors declarations and comments
#include "attachPreprocessingInfo.h"

// Lingxiao's work to add comments from all header files to the AST.
#include "attach_all_info.h"

// DQ (8/20/2005): Changed name to make sure that we don't use the old 
// header file (which has been removed).
// #include "AstFixes.h"
#include "astPostProcessing.h"



//Liao, 10/9/2008, support for abstract handles for language constructs
#include "abstract_handle.h"
#include "roseAdapter.h"

//Liao, 2/8/2008. SAGE III node building interface
#include "sageBuilder.h"
#include "sageBuilderAsm.h"


// Liao, 11/14/2008, support for annotation-based array optimization
// The headers bring some garbage which cannot be compiled
//#include "ArrayAnnot.h"
//#include "ArrayInterface.h"
//include "ArrayRewrite.h"
// Liao, 8/11/2009, support for OpenMP lowering
#include "omp_lowering.h" 


// DQ (5/28/2007): Added new AST Merge API
#include "astMergeAPI.h"

// JJW 10-23-2007
// Add possibility to include Valgrind header for memcheck
#if ROSE_USE_VALGRIND
#include <valgrind/valgrind.h>
#include <valgrind/memcheck.h>
#endif

/* The SgFile node needs default settings defined in Disassembler::SEARCH_DEFAULT */
#include "Disassembler.h"

#endif















