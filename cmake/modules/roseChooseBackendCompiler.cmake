# Check compilers and version number
#  Liao 11/25/2009
# This is translated from config/choose-backend-compiler.m4
#
# use the results to setup rose_config.h later on
# --------check C compiler -----------------------
include (CMakeDetermineCCompiler)

# Support for Visual Studio is handled in a separate file
if(WIN32)
  include(roseWindowsSupport)
  return()
endif()

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  if(NOT BACKEND_C_COMPILER)
    set(BACKEND_C_COMPILER  ${CMAKE_C_COMPILER})
  endif()
  execute_process(
    COMMAND ${BACKEND_C_COMPILER} -dumpversion
    COMMAND cut -d. -f1
    OUTPUT_VARIABLE BACKEND_C_COMPILER_MAJOR_VERSION_NUMBER)
  # for unknown reason, some tail control character will show up in OUTPUT_VARIABLE
  # We use regex to fill out non numeric characters to get the right numbers
  string(REGEX MATCH "[0-9]+" BACKEND_C_COMPILER_MAJOR_VERSION_NUMBER ${BACKEND_C_COMPILER_MAJOR_VERSION_NUMBER})
  if(VERBOSE)
    message("CMAKE_C_COMPILER= ${CMAKE_C_COMPILER}^")
  endif()

  execute_process(
    COMMAND basename ${BACKEND_C_COMPILER}
    OUTPUT_VARIABLE BACKEND_C_COMPILER_NAME_WITHOUT_PATH)
  string(REGEX MATCH "[a-zA-Z0-9/.+-]+" BACKEND_C_COMPILER_NAME_WITHOUT_PATH ${BACKEND_C_COMPILER_NAME_WITHOUT_PATH})
  if(VERBOSE)
    message("BACKEND_C_COMPILER_NAME_WITHOUT_PATH=${BACKEND_C_COMPILER_NAME_WITHOUT_PATH}^")
  endif()

  execute_process(
    COMMAND ${BACKEND_C_COMPILER} -dumpversion
    COMMAND cut -d. -f2
    OUTPUT_VARIABLE BACKEND_C_COMPILER_MINOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_C_COMPILER_MINOR_VERSION_NUMBER ${BACKEND_C_COMPILER_MINOR_VERSION_NUMBER})
  execute_process(
    COMMAND ${BACKEND_C_COMPILER} -dumpversion
    COMMAND cut -d. -f3
    OUTPUT_VARIABLE BACKEND_C_COMPILER_PATCH_LEVEL_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_C_COMPILER_PATCH_LEVEL_NUMBER ${BACKEND_C_COMPILER_PATCH_LEVEL_NUMBER})

elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  if(NOT BACKEND_C_COMPILER)
    set(BACKEND_C_COMPILER  ${CMAKE_C_COMPILER})
  endif()
  execute_process(
    COMMAND basename ${BACKEND_C_COMPILER}
    OUTPUT_VARIABLE BACKEND_C_COMPILER_NAME_WITHOUT_PATH)
  string(REGEX MATCH "[a-zA-Z0-9/.+-]+" BACKEND_C_COMPILER_NAME_WITHOUT_PATH ${BACKEND_C_COMPILER_NAME_WITHOUT_PATH})
  if(VERBOSE)
    message("BACKEND_C_COMPILER_NAME_WITHOUT_PATH=${BACKEND_C_COMPILER_NAME_WITHOUT_PATH}^")
  endif()

  execute_process(
    COMMAND ${BACKEND_C_COMPILER} --version
    COMMAND grep -Po "(?<=version )[^;]+"
    COMMAND cut -d. -f1
    OUTPUT_VARIABLE BACKEND_C_COMPILER_MAJOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_C_COMPILER_MAJOR_VERSION_NUMBER  ${BACKEND_C_COMPILER_MAJOR_VERSION_NUMBER})
  execute_process(
    COMMAND ${BACKEND_C_COMPILER} --version
    COMMAND grep -Po "(?<=version )[^;]+"
    COMMAND cut -d. -f2
    OUTPUT_VARIABLE BACKEND_C_COMPILER_MINOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_C_COMPILER_MINOR_VERSION_NUMBER  ${BACKEND_C_COMPILER_MINOR_VERSION_NUMBER})
endif()

# --------check CXX compiler -----------------------
include(roseCMakeDetermineCXXCompiler)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(NOT BACKEND_CXX_COMPILER)
    set(BACKEND_CXX_COMPILER  ${CMAKE_CXX_COMPILER})
  endif()
  execute_process(
    COMMAND ${BACKEND_CXX_COMPILER} -dumpversion
    COMMAND cut -d. -f1
    OUTPUT_VARIABLE BACKEND_CXX_COMPILER_MAJOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_CXX_COMPILER_MAJOR_VERSION_NUMBER  ${BACKEND_CXX_COMPILER_MAJOR_VERSION_NUMBER})
  execute_process(
    COMMAND basename ${BACKEND_CXX_COMPILER}  
    OUTPUT_VARIABLE BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH)
  if(VERBOSE)
    message("BACKEND_CXX_COMPILER= ${BACKEND_CXX_COMPILER}")
  endif()
  string(REGEX MATCH "[a-zA-Z0-9/.+-]+" BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH ${BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH})
  if(VERBOSE)
    message("BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH= ${BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH}")
  endif()
  
  execute_process(
    COMMAND ${BACKEND_CXX_COMPILER} -dumpversion
    COMMAND cut -d. -f2
    OUTPUT_VARIABLE BACKEND_CXX_COMPILER_MINOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_CXX_COMPILER_MINOR_VERSION_NUMBER ${BACKEND_CXX_COMPILER_MINOR_VERSION_NUMBER})

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(NOT BACKEND_CXX_COMPILER)
    set(BACKEND_CXX_COMPILER  ${CMAKE_CXX_COMPILER})
  endif()
  execute_process(
    COMMAND basename ${BACKEND_CXX_COMPILER}  
    OUTPUT_VARIABLE BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH)
  if(VERBOSE)
    message("BACKEND_CXX_COMPILER= ${BACKEND_CXX_COMPILER}")
  endif()
  string(REGEX MATCH "[a-zA-Z0-9/.+-]+" BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH ${BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH})
  if(VERBOSE)
    message("BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH= ${BACKEND_CXX_COMPILER_NAME_WITHOUT_PATH}")
  endif()
  execute_process(
    COMMAND ${BACKEND_CXX_COMPILER} --version
    COMMAND grep -Po "(?<=version )[^;]+"
    COMMAND cut -d. -f1
    OUTPUT_VARIABLE BACKEND_CXX_COMPILER_MAJOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_CXX_COMPILER_MAJOR_VERSION_NUMBER  ${BACKEND_CXX_COMPILER_MAJOR_VERSION_NUMBER})
  execute_process(
    COMMAND ${BACKEND_CXX_COMPILER} --version
    COMMAND grep -Po "(?<=version )[^;]+"
    COMMAND cut -d. -f2
    OUTPUT_VARIABLE BACKEND_CXX_COMPILER_MINOR_VERSION_NUMBER)
  string(REGEX MATCH "[0-9]+" BACKEND_CXX_COMPILER_MINOR_VERSION_NUMBER  ${BACKEND_CXX_COMPILER_MINOR_VERSION_NUMBER})
endif()

if(enable-fortran)
  # --------check Fortran compiler -----------------------
  # CMakeDetermineFortranCompiler does not recognize gfortran first
  # we use a slightly modified CMakeDetermineFortranCompiler.cmake to put gfortran to the highest priority
  include(roseCMakeDetermineFortranCompiler)
  if("${CMAKE_Fortran_COMPILER}"  MATCHES ".*gfortran$")
    if(VERBOSE)
      message("find gfortran compiler ${CMAKE_Fortran_COMPILER}")
    endif()
    if(NOT BACKEND_FORTRAN_COMPILER)
      set (BACKEND_FORTRAN_COMPILER  ${CMAKE_Fortran_COMPILER})
    endif()

    execute_process(
      COMMAND ${BACKEND_FORTRAN_COMPILER} --version
      COMMAND head -1
      COMMAND cut -f2 -d\)
      COMMAND tr -d \ # must have a space
      COMMAND cut -d. -f1
      OUTPUT_VARIABLE BACKEND_FORTRAN_COMPILER_MAJOR_VERSION_NUMBER)
    string(REGEX MATCH "[0-9]+" BACKEND_FORTRAN_COMPILER_MAJOR_VERSION_NUMBER ${BACKEND_FORTRAN_COMPILER_MAJOR_VERSION_NUMBER})
    execute_process(
      COMMAND basename ${BACKEND_FORTRAN_COMPILER}
      OUTPUT_VARIABLE BACKEND_FORTRAN_COMPILER_NAME_WITHOUT_PATH)
    string(REGEX MATCH "[a-zA-Z0-9/.+-]+" BACKEND_FORTRAN_COMPILER_NAME_WITHOUT_PATH ${BACKEND_FORTRAN_COMPILER_NAME_WITHOUT_PATH})

    execute_process(
      COMMAND ${BACKEND_FORTRAN_COMPILER} --version
      COMMAND head -1
      COMMAND cut -f2 -d\)
      COMMAND tr -d \ # must have a space
      COMMAND cut -d. -f2
      OUTPUT_VARIABLE BACKEND_FORTRAN_COMPILER_MINOR_VERSION_NUMBER)
    string(REGEX MATCH "[0-9]+" BACKEND_FORTRAN_COMPILER_MINOR_VERSION_NUMBER ${BACKEND_FORTRAN_COMPILER_MINOR_VERSION_NUMBER})
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  set(BACKEND_CXX_IS_CLANG_COMPILER 1)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set(BACKEND_CXX_IS_GNU_COMPILER 1)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
  set(BACKEND_CXX_IS_INTEL_COMPILER 1)
endif()
