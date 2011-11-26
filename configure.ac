AC_INIT(src/mathtools.h)
AC_CONFIG_MACRO_DIR([m4])

GENERIC_LIBRARY_NAME=libbrahe

#release versioning
GENERIC_MAJOR_VERSION=1
GENERIC_MINOR_VERSION=3
GENERIC_MICRO_VERSION=2

#shared library versioning
GENERIC_LIBRARY_VERSION=3:1:0

AC_SUBST(GENERIC_LIBRARY_VERSION)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, [no-define dist-bzip2 dist-zip])
AM_SANITY_CHECK

AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_CHECK_HEADERS(stdint.h unistd.h fcntl.h)

AC_ARG_ENABLE([docgen],
              AS_HELP_STRING([--enable-docgen], [generate documentation with Doxygen]),
              [docgen=$enableval],
              [docgen=no])

if test "x$docgen" = "xyes"
then
    AC_CHECK_PROG(HAVE_DOXYGEN, doxygen, true, false)
        if test $HAVE_DOXYGEN = "false"; then
            AC_MSG_WARN([*** doxygen not found, code documentation will not be built])
        fi
    AM_CONDITIONAL(HAVE_DOXYGEN, $HAVE_DOXYGEN)
else
    AM_CONDITIONAL(HAVE_DOXYGEN, "false")
fi

AC_OUTPUT(Makefile libbrahe.pc src/Makefile test/Makefile docs/Makefile)
