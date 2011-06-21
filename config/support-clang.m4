AC_DEFUN([ROSE_SUPPORT_CLANG],
[

AC_MSG_NOTICE([Clang support enabled])
AC_DEFINE([ROSE_USE_CLANG], 1, [Use Clang for parsing C/C++-like languages])

AC_PATH_TOOL([LLVM_CONFIG], [llvm-config])

AC_MSG_CHECKING([for Clang include path])
    if test -z "$CLANG_CPPFLAGS"; then
        llvm_include_path=`$LLVM_CONFIG --cxxflags | sed 's/\n//g'`
        if test -n "${llvm_include_path}"; then
            llvm_include_path="$llvm_include_path"
        fi
        CLANG_CPPFLAGS=$llvm_include_path
    fi
AC_MSG_RESULT([$CLANG_CPPFLAGS])
AC_SUBST([CLANG_CPPFLAGS])

AC_MSG_CHECKING([for Clang ld flags])
    if test -z "$CLANG_LDFLAGS"; then
        llvm_ldflags=`$LLVM_CONFIG --ldflags --libs | sed 's/\n//g'`
        if test -n "${llvm_ldflags}"; then
            llvm_ldflags="$llvm_ldflags"
        fi
        CLANG_LDFLAGS=$llvm_ldflags
    fi
AC_MSG_RESULT([$CLANG_LDFLAGS])
AC_SUBST([CLANG_LDFLAGS])

]
)

