AC_DEFUN([ROSE_SUPPORT_JAVA],
[
# Begin macro ROSE_SUPPORT_JAVA.

AC_MSG_CHECKING(for Java)
AC_ARG_WITH(Java,
[  --with-Java=PATH	Specify the prefix where Java is installed],
,
if test ! "$with_Java" ; then
   with_Java=no
fi
)

echo "In ROSE SUPPORT MACRO: with_Java $with_Java"

if test "$with_Java" = no; then
   # If Java is not specified, then don't use it.
   echo "Skipping use of Java (and Fortran2003 support)!"
else
   JAVA_PATH=$with_Java
   echo "Setup Java support in ROSE! path = $JAVA_PATH"
   AC_DEFINE([USE_ROSE_JAVA_SUPPORT],1,[Controls use of ROSE support for Java (required for the Open Fortran Parser from LANL).])
fi

AC_SUBST(JAVA_PATH)

# End macro ROSE_SUPPORT_FORTRAN.
]
)
