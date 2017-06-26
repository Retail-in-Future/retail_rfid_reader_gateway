AC_INIT([retail_rfid_reader_gateway],
        [0.1],
        [tangcheng2005@gmail.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.11])

AC_PROG_CC
AC_PROG_CXX

LT_INIT

BOOST_REQUIRE
#PKG_CHECK_MODULES(DEPENDENCIES, [])
AC_CONFIG_LINKS([conf/retail_rfid_reader_gateway.conf:conf/retail_rfid_reader_gateway.conf])

AWS_IOT_SDK_CPP_REQUIRE

AC_ARG_ENABLE(tests,
              AS_HELP_STRING([--enable-tests],[Enable usage of unit tests [default=no]]),
              [enable_tests=yes],
              [enable_tests=no])

AS_IF([test "x$enable_tests" = "xyes"],
      [AM_CONDITIONAL([ENABLE_TESTS], [true])
      PKG_CHECK_MODULES(CPPUTEST, [cpputest])
      AC_CONFIG_FILES([tests/Makefile])],
      [AM_CONDITIONAL([ENABLE_TESTS], [false])])

AC_ARG_ENABLE(coverage, AS_HELP_STRING([--enable-coverage],
              [Enable code coverage [default=no]]))

AS_IF([test "x$enable_coverage" = "xyes"],
      [AM_CONDITIONAL([ENABLE_COVERAGE], true)],
      [AM_CONDITIONAL([ENABLE_COVERAGE], false)])

AC_CONFIG_FILES([Makefile
                src/Makefile])

#AC_CONFIG_FILES([Makefile
#                src/retail_rfid_reader_gateway.pc
#                src/Makefile])

AC_OUTPUT
