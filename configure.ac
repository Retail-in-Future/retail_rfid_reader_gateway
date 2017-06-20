AC_INIT([retail_rfid_reader_gateway],
        [0.1],
        [tangcheng2005@gmail.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.11])

AC_PROG_CC
AC_PROG_CXX

LT_INIT

#BOOST_REQUIRE
#BOOST_THREAD
#PKG_CHECK_MODULES(DEPENDENCIES, [])
#AC_CONFIG_LINKS([file:file])

AC_ARG_WITH(aws_iot_sdk_cpp,
            [AC_HELP_STRING([--with-aws-iot-sdk-cpp[[=DIR]]], [aws iot device sdk install dir])],
            [with_aws_iot_sdk_cpp=$withval],
            [with_aws_iot_sdk_cpp=""])
AC_CACHE_CHECK([for aws iot device sdk directory], ac_cv_aws_iot_sdk_cpp_dir, [
    saved_LIBS="$LIBS"
    saved_LDFLAGS="$LDFLAGS"
    saved_CPPFLAGS="$CPPFLAGS"
    aws_found=no
    for awsdir in $with_aws_iot_sdk_cpp "" $prefix /usr/local ; do
        LDFLAGS="$saved_LDFLAGS"
        LIBS="$saved_LIBS -laws-iot-sdk-cpp"
        CPPFLAGS="$saved_CPPFLAGS"

        # skip the directory if it isn't there
        if test ! -z "$awsdir" -a ! -d "$awsdir" ; then
            continue;
        fi
        if test ! -z "$awsdir" ; then
            if test -d "$awsdir/lib" ; then
                LDFLAGS="-L$awsdir/lib $LDFLAGS"
            else
                LDFLAGS="-L$awsdir $LDFLAGS"
            fi
            if test -d "$awsdir/include" ; then
                CPPFLAGS="-I$awsdir/include $CPPFLAGS"
            else
                CPPFLAGS="-I$awsdir $CPPFLAGS"
            fi
        fi

        # can I compile and link it?
        AC_LANG(C++)
        AC_TRY_LINK([#include <iostream>
                     #include <util/logging/Logging.hpp>],
                    [awsiotsdk::util::Logging::ShutdownAWSLogging()],
                    [aws_iot_sdk_cpp_linkd=yes],
                    [aws_iot_sdk_cpp_linkd=no])
        if test $aws_iot_sdk_cpp_linkd = yes; then
            if test ! -z "$awsdir" ; then
                ac_cv_aws_iot_sdk_cpp_dir=$awsdir
            else
                ac_cv_aws_iot_sdk_cpp_dir="(system)"
            fi
            aws_found=yes
            break
        fi
    done
    LIBS="$saved_LIBS"
    LDFLAGS="$saved_LDFLAGS"
    CPPFLAGS="$saved_CPPFLAGS"
    if test $aws_found = no; then
        AC_MSG_ERROR([AWS IoT device sdk not found.])
    fi
])
AWS_IOT_LIBS="-laws-iot-sdk-cpp"
AC_SUBST(AWS_IOT_LIBS)
if test $ac_cv_aws_iot_sdk_cpp_dir != "(system)"; then
    if test -d "$ac_cv_aws_iot_sdk_cpp_dir/lib" ; then
        AWS_IOT_LDFLAGS="-L$ac_cv_aws_iot_sdk_cpp_dir/lib"
    else
        AWS_IOT_LDFLAGS="-L$ac_cv_aws_iot_sdk_cpp_dir"
    fi
    AC_SUBST(AWS_IOT_LDFLAGS)
    if test -d "$ac_cv_aws_iot_sdk_cpp_dir/include" ; then
        AWS_IOT_CPPFLAGS="-I$ac_cv_aws_iot_sdk_cpp_dir/include"
    else
        AWS_IOT_CPPFLAGS="-I$ac_cv_aws_iot_sdk_cpp_dir"
    fi
    AC_SUBST(AWS_IOT_CPPFLAGS)
fi

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
