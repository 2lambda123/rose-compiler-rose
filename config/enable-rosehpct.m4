dnl
dnl ACROSE_ENABLE_HPCT
dnl
dnl Checks whether the user explicitly requested that the
dnl ROSE-HPCT module be built. Sets the shell variable
dnl 'acrose_enable_rosehpct' to 'yes' or 'no', accordingly.
dnl Also defines the automake conditional,
dnl ROSE_BUILD_ROSEHPCT, and modifies CXXFLAGS and
dnl LIBS to include and link against the appropriate
dnl prerequisite libraries.
dnl
dnl Author: Rich Vuduc <richie@llnl.gov>
dnl
dnl $Id: enable-rosehpct.m4,v 1.1 2005/10/23 07:52:04 vuduc2 Exp $
dnl

AC_DEFUN([ACROSE_ENABLE_ROSEHPCT], [

AC_MSG_CHECKING([whether user wants to build ROSE-HPCT])
AC_ARG_ENABLE([rosehpct],
  AC_HELP_STRING([--enable-rosehpct],
    [enable build of the ROSE-HPCT module]),
  [acrose_enable_rosehpct=$enableval],
  [acrose_enable_rosehpct=no])
AC_MSG_RESULT([${acrose_enable_rosehpct}])

if test x"${acrose_enable_rosehpct}" = xyes ; then
  ACROSE_CHECK_ROSEHPCT([], [acrose_enable_rosehpct=no])
fi

AM_CONDITIONAL(ROSE_BUILD_ROSEHPCT,
  test x"${acrose_enable_rosehpct}" = xyes)
])

dnl
dnl ACROSE_CHECK_ROSEHPCT([ACTION-IF-OK], [ACTION-ELSE])
dnl
dnl Checks for all the prerequisite libraries needed to
dnl build the ROSE-HPCT module. Exports the automake
dnl variables ROSEHPCT_DEP_INCLUDES and ROSEHPCT_DEP_LIBS
dnl to specify include paths and linker flags needed to
dnl build ROSE-HPCT and its example programs.
dnl
AC_DEFUN([ACROSE_CHECK_ROSEHPCT], [
AC_LANG_PUSH([C++])

AC_MSG_NOTICE([checking for ROSE-HPCT build-prerequisites])
ROSEHPCT_DEP_INCLUDES=""
ROSEHPCT_DEP_LIBS=""

ACX_LIBXML2([ROSEHPCT_DEP_LIBS="${ROSEHPCT_DEP_LIBS} ${acx_libxml2_libs}"
  ROSEHPCT_DEP_INCLUDES="${ROSEHPCT_DEP_INCLUDES} ${acx_libxml2_includes}"])

if test x"${acx_libxml2_ok}" = xyes ; then
  AC_MSG_NOTICE([all known ROSE-HPCT build-prerequisites satisfied])
  $1
else  # At least one prerequisite failed
  :
  AC_MSG_NOTICE([one or more ROSE-HPCT build-prerequisites not satisfied])
  $2
fi

AC_SUBST([ROSEHPCT_DEP_INCLUDES])
AC_SUBST([ROSEHPCT_DEP_LIBS])
AC_LANG_POP([C++])
])

dnl eof
