# Initialize autoconf
AC_INIT([cserio], [1.4.0])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([..])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Define the source directory and the build directory
AC_CONFIG_SRCDIR([src/cserio.c])
AC_CONFIG_HEADERS([config.h])

# necessary for library
AC_PROG_RANLIB
AM_PROG_AR

# Checks for programs
AC_PROG_CC

# Output files to generate
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

