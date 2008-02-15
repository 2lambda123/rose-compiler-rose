AC_DEFUN([ROSE_SUPPORT_BDDBDDB],
[
# Begin macro ROSE_SUPPORT_BDDBDDB.

AC_REQUIRE([ROSE_SUPPORT_PYTHON])

# Inclusion of test for bddbddb and it's location.

AC_MSG_CHECKING(for bddbddb)
AC_ARG_WITH(bddbddb,
[  --with-bddbddb       Specify the use of bddbddb (distributed internally)],
,
if test ! "$with_bddbddb" ; then
  with_bddbddb=no
fi
)

echo "In ROSE SUPPORT MACRO: with_bddbddb $with_bddbddb"
if test "$with_bddbddb" = no; then
  # If bddbddb is not specified, then don't use it.
  echo "Skipping use of bddbddb!"
else
    if test -n "$python_path";
    then
        # We currently ignore the path, but it might be used
        # later if BDDBDDB is installed external to ROSE.
        bddbddb_path=$with_bddbddb
        echo "Setup bddbddb support in ROSE! path = $bddbddb_path"
        AC_DEFINE([USE_ROSE_BDDBDDB_SUPPORT],1,[Controls use of ROSE support for bddbddb (Binary decision diagrams (BDD) BDD-Based Deductive DataBase.])
    else
        cat << EOF

No Python >=2.4.0 found.  Disabling support for bddbddb.
Try setting the --with-python option to the location of
a good python interpreter:
--with-python=/path/to/python/bin/python

EOF
    fi

fi

AC_SUBST(bddbddb_path)

# End macro ROSE_SUPPORT_BDDBDDB.
]
)

