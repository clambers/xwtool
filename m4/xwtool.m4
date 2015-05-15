# XW_INIT
# -------
# Initializes a project for XWtool.
AC_DEFUN([XW_INIT],
[AC_CHECK_PROGS([XWTOOL], [xwtool])
AC_ARG_VAR([XWTOOL], [xwtool implementation to use])
AC_ARG_VAR([XWFLAGS], [flags to pass to xwtool])
])

# XW_CONFIG_SPEC(PATH)
# --------------------
# Tells XWtool to generate its makefile at PATH.
AC_DEFUN([XW_CONFIG_FILE],
[m4_pushdef([PATH], [$1])

m4_popdef([PATH])
])
