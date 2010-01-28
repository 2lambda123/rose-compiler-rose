AC_DEFUN([GET_COMPILER_SPECIFIC_DEFINES],
dnl First written by Bobby Philip, 11/25/2001
dnl define GET_COMPILER_SPECIFIC_DEFINES.
dnl this macro tries to automatically
dnl determine the macros that are
dnl predefined by a specific compiler
[
# AC_LANG_SAVE
# AC_LANG_CPLUSPLUS
  AC_LANG_PUSH(C++)
  changequote(<<, >>) dnl For some reason the quotes '' below are being thrown away, so do this
# Use the selected back-end C++ compiler instead of $CXX
# case $CXX in

# DQ (12/2/2006): This macro is required even because it sets up the CXX_SPEC_DEF and C_SPEC_DEF macros in rose_config.h (generated by autoheader).
# echo "This GET COMPILER SPECIFIC DEFINES macro is no longer used, see create_system_headers file instead!"
# exit 1

# DQ (4/1/2005): Modified to get compiler name from path
  compilerName=`basename $BACKEND_CXX_COMPILER`
  echo "Using back-end C++ compiler = \"$BACKEND_CXX_COMPILER\" compiler name = \"$compilerName\" for processing of unparsed source files from ROSE preprocessors."

# case $BACKEND_CXX_COMPILER in
  case $compilerName in

  # Support for GNU gcc or g++ as a backend for compiling ROSE generated code
  # JJW 7/25/2008: Added mpi* in here, assuming they are like gcc
    g++|gcc|mpicc|mpic++|mpicxx|mpiCC)
             BACKEND_GCC_MAJOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f1`
             BACKEND_GCC_MINOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f2`
             BACKEND_GCC_PATCHLEVEL=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f3`
             macroString="{\"-D__GNUG__=$BACKEND_GCC_MAJOR\", \"-D__GNUC__=$BACKEND_GCC_MAJOR\", \"-D__GNUC_MINOR__=$BACKEND_GCC_MINOR\", \"-D__GNUC_PATCHLEVEL__=$BACKEND_GCC_PATCHLEVEL\""
             if test x$enable_new_edg_interface = xyes; then
               :
             else
               macroString="${macroString}, \"--preinclude\", \"rose_edg_required_macros_and_functions.h\""
             fi
             macroString="${macroString}}"

             compilerVendorName=GNU
             ;;

  # Support for Intel icc as a backend for compiling ROSE generated code
    icpc|icc)

             tmpFile="/tmp/tmpICCMacroExtraction`uname -n`$$.C"
             echo "int main(int argc, char **argv){return 0;}" > "$tmpFile"
             extra_icc_defines=`"icpc" -# "test.C" 2>&1 |  grep "\-D" | grep "GNUG\|__GNUC_PATCHLEVEL__\|__GNUC_MINOR__\|__GNUC__"  | sed ':a; /\\$/N; s/\\\n//; ta' | sed 's/\\\//' `
             tmp_macro=""
             for macro_i in $extra_icc_defines
                 do
                    echo $macro_i
                  # DQ (1/9/2010): Fixing support for Intel icc and icpc compiler.
                  # tmp_macro="$tmp_macro, $macro_i"
                    tmp_macro="$tmp_macro, \"$macro_i\""
                    echo " tmp_macro  $tmp_macro"
                 done
           # macroString=" -D__PURE_INTEL_C99_HEADERS__ ${tmp_macro} --preinclude rose_edg_macros_and_functions_required_for_icc.h "
           # DQ (1/9/2010): I put this back and commented out the problem directly in the UPC file: lock.upc directly.
           # DQ (1/9/2010): This causes an error in math.h with an inconstant use of __THROW with the declaration of "abs()".
           #   from math.h _LIBIMF_EXT _LIBIMF_INT   _LIBIMF_PUBAPI abs( _LIBIMF_INT __x );
           # macroString="{\"-D__PURE_INTEL_C99_HEADERS__\" ${tmp_macro}"
             macroString="{ \"-D__PURE_INTEL_C99_HEADERS__\" ${tmp_macro}"
             if test x$enable_new_edg_interface = xyes; then
               :
             else
               macroString="${macroString}, \"--preinclude\", \"rose_edg_required_macros_and_functions.h\""
             fi
             macroString="${macroString}}"
              echo "ICC MACRO DEFS: $ICC_MACRO_DEFS"
             echo "macroString: $macroString"

             compilerVendorName=Intel

             #BACKEND_GCC_MAJOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f1`
             #BACKEND_GCC_MINOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f2`
             #BACKEND_GCC_PATCHLEVEL=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f3` 
             ;;

  # Support for ROSE "roseTranslator" as a backend for compiling ROSE generated code
  # Or support "roseAnalysis" as a backend which generates object files from the original source code.
    roseTranslator|roseAnalysis)
           # macroString=" -D__GNUG__=$BACKEND_GCC_MAJOR -D__GNUC__=$BACKEND_GCC_MAJOR -D__GNUC_MINOR__=$BACKEND_GCC_MINOR -D__GNUC_PATCHLEVEL__=$BACKEND_GCC_PATCHLEVEL -D_GNU_SOURCE --preinclude rose_edg_macros_and_functions_required_for_gnu.h "
           # macroString="{\"-D__GNUG__=$BACKEND_GCC_MAJOR\", \"-D__GNUC__=$BACKEND_GCC_MAJOR\", \"-D__GNUC_MINOR__=$BACKEND_GCC_MINOR\", \"-D__GNUC_PATCHLEVEL__=$BACKEND_GCC_PATCHLEVEL\", \"-D_GNU_SOURCE\""
           # if test x$enable_new_edg_interface = xyes; then
           #   :
           # else
           #   macroString="${macroString}, \"--preinclude\", \"rose_edg_required_macros_and_functions.h\""
           # fi
           # macroString="${macroString}}"
           # BACKEND_GCC_MAJOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f1`
           # BACKEND_GCC_MINOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f2`
           # BACKEND_GCC_PATCHLEVEL=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f3`
           #
           # echo "This is the case of using roseTranslator to compile ROSE.";
           # exit 1;
           # ;;
           #
           # DQ (8/22/2009): This is the same as the g++ case above (we can us that because rose acts like g++ by default).
             BACKEND_GCC_MAJOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f1`
             BACKEND_GCC_MINOR=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f2`
             BACKEND_GCC_PATCHLEVEL=`echo|$BACKEND_CXX_COMPILER -dumpversion | cut -d\. -f3`
             macroString="{\"-D__GNUG__=$BACKEND_GCC_MAJOR\", \"-D__GNUC__=$BACKEND_GCC_MAJOR\", \"-D__GNUC_MINOR__=$BACKEND_GCC_MINOR\", \"-D__GNUC_PATCHLEVEL__=$BACKEND_GCC_PATCHLEVEL\""
             if test x$enable_new_edg_interface = xyes; then
               :
             else
               macroString="${macroString}, \"--preinclude\", \"rose_edg_required_macros_and_functions.h\""
             fi
             macroString="${macroString}}"

             compilerVendorName=GNU
             echo "Support for ROSE roseTranslator|roseAnalysis as a backend for compiling ROSE generated code \"$BACKEND_CXX_COMPILER\" ";
             echo "Support for ROSE roseTranslator|roseAnalysis as a backend for compiling ROSE generated code \"$macroString\" ";
             ;;

    *)
             echo "we reached here for some reason (cannot identify back-end C++ compiler \"$BACKEND_CXX_COMPILER\")";
             exit 1;
             macroString="";;
  esac

  changequote([, ])
  AC_DEFINE_UNQUOTED([CXX_SPEC_DEF],$macroString,[-D options to hand to EDG C++ front-end.])

# This is now setup in a separate macro and can be specified on the command line
# AC_DEFINE_UNQUOTED(CXX_COMPILER_NAME, "$CXX")

# DQ (1/9/2010): Detec the type of compiler being used. This is used to add the
# library libimf with libm to support use of the Intel compiler.  I have added
# AM conditional for GNu just for completeness.
  AM_CONDITIONAL(USING_INTEL_COMPILER,test "x$compilerVendorName" = xIntel)
  AM_CONDITIONAL(USING_GNU_COMPILER,test "x$compilerVendorName" = xGNU)

# DQ (1/27/2010): Setup automake conditionals so that we can optionally skip files in ROSE that don't compile.
  AM_CONDITIONAL(ROSE_USING_ROSE,test "x$compilerName" = xroseTranslator || test "x$compilerName" = xroseAnalysis)
  AM_CONDITIONAL(ROSE_USING_ROSE_TRANSLATOR,test "x$compilerName" = xroseTranslator)
  AM_CONDITIONAL(ROSE_USING_ROSE_ANALYSIS,test "x$compilerName" = xroseAnalysis)

  if test "x$compilerVendorName" = xIntel; then
   # using_intel_compiler=true
     AC_DEFINE([CXX_IS_INTEL_COMPILER],[1],[Is this an Intel compiler being used to compile ROSE.])
  fi
  if test "x$compilerVendorName" = xGNU; then
   # using_gnu_compiler=true
     AC_DEFINE([CXX_IS_GNU_COMPILER],[1],[Is this a GNU compiler being used to compile ROSE.])
  fi
# AC_DEFINE([CXX_IS_INTEL_COMPILER],test "x$compilerVendorName" = xIntel,[Is this an Intel compiler being used to compile ROSE.])
# AC_DEFINE([CXX_IS_INTEL_COMPILER],[`test $using_intel_compiler`],[Is this an Intel compiler being used to compile ROSE.])
# AC_DEFINE([CXX_IS_GNU_COMPILER],[`test $using_gnu_compiler`],[Is this a GNU compiler being used to compile ROSE.])

# This string has all compiler specific predefined macros listed
  echo "Backend compiler specific macroString = $macroString"

# DQ (9/13/2009): Add information about the backend compiler (which matches the associated header files generated).
# These values are used to control tests that are backend compiler and or compiler version dependent.
  BACKEND_COMPILER_VERSION_NAME=$compilerVendorName
  BACKEND_COMPILER_VERSION_MAJOR_NUMBER=$BACKEND_GCC_MAJOR
  BACKEND_COMPILER_VERSION_MINOR_NUMBER=$BACKEND_GCC_MINOR
  BACKEND_COMPILER_VERSION_PATCHLEVEL_NUMBER=$BACKEND_GCC_PATCHLEVEL

# DQ (9/14/2009): generate a name to use with the name of the ROSE EDG binary so that we can be version number specific.
  GENERATED_COMPILER_NAME_AND_VERSION_SUFFIX="$BACKEND_COMPILER_VERSION_NAME-$BACKEND_COMPILER_VERSION_MAJOR_NUMBER.$BACKEND_COMPILER_VERSION_MINOR_NUMBER"

  if test x$BACKEND_COMPILER_VERSION_NAME = xGNU; then
    if test x$BACKEND_COMPILER_VERSION_MAJOR_NUMBER = x4; then
      if test x$BACKEND_COMPILER_VERSION_MINOR_NUMBER = x2; then
        ok_for_testing=true
      fi
    fi
  fi

  echo "BACKEND_COMPILER_VERSION_NAME              = $BACKEND_COMPILER_VERSION_NAME"
  echo "BACKEND_COMPILER_VERSION_MAJOR_NUMBER      = $BACKEND_COMPILER_VERSION_MAJOR_NUMBER"
  echo "BACKEND_COMPILER_VERSION_MINOR_NUMBER      = $BACKEND_COMPILER_VERSION_MINOR_NUMBER"
  echo "BACKEND_COMPILER_VERSION_PATCHLEVEL_NUMBER = $BACKEND_COMPILER_VERSION_PATCHLEVEL_NUMBER"

  echo "GENERATED_COMPILER_NAME_AND_VERSION_SUFFIX = $GENERATED_COMPILER_NAME_AND_VERSION_SUFFIX"

  echo "This version of backend compiler is OK for compiler and compiler version dependent testing: ok_for_testing = $ok_for_testing"

  AM_CONDITIONAL(BACKEND_COMPILER_VERSION_OK_FOR_ROSE_TESTING,test "x$ok_for_testing" = xtrue)

# DQ (9/30/2009): Exempt a set of old compiler versions from some testing
# This is an attept to define a class of compiler versions that 
# we should not test because it can generate internal compiler errors.
# Specifically I am turning off the projects/interpretation directory
# when using GNU version 3.4 (this is an example of this class).
  if test x$BACKEND_COMPILER_VERSION_NAME = xGNU; then
    if test x$BACKEND_COMPILER_VERSION_MAJOR_NUMBER = x3; then
      if test x$BACKEND_COMPILER_VERSION_MINOR_NUMBER = x4; then
        echo "Warning: This is classified as an OLD compiler to ROSE (some parts of ROSE will not be compiled)."
        old_compiler=true
      fi
    fi
  fi

  echo "This version of backend compiler is condidered too old for parts of ROSE: old_compiler = $old_compiler"

  AM_CONDITIONAL(OLD_COMPILER_VERSION,test "x$old_compiler" = xtrue)


  AC_SUBST(BACKEND_COMPILER_VERSION_NAME)
  AC_SUBST(BACKEND_COMPILER_VERSION_MAJOR_NUMBER)
  AC_SUBST(BACKEND_COMPILER_VERSION_MINOR_NUMBER)
  AC_SUBST(BACKEND_COMPILER_VERSION_PATCHLEVEL_NUMBER)

  AC_SUBST(GENERATED_COMPILER_NAME_AND_VERSION_SUFFIX)


# AC_LANG_RESTORE
  AC_LANG_POP(C++)
])












