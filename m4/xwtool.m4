# CITIZEN_INIT
# ------------
# Initializes a project for Citizen.
AC_DEFUN([CITIZEN_INIT],
[AC_CHECK_PROGS([CITIZEN], [citizen])
AC_ARG_VAR([CITIZENFLAGS], [flags to pass to Citizen])
])

# CITIZEN_CONFIG_INSTANCE(HEADER)
# -------------------------------
# Set header file for Citizen to generate.
AC_DEFUN([CITIZEN_CONFIG_INSTANCE], [])
