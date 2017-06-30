AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(DEPENDENCIES_CFLAGS)

AM_CFLAGS =\
	-Wextra\
	-fPIC
	-Werror\
	-Wall\
	-g

AM_CXXFLAGS = $(AM_CFLAGS)
AM_CXXFLAGS += -std=c++11

if ENABLE_TESTS
libretail_rfid_reader_gateway_la_includedir = $(includedir)/retail_rfid_reader_gateway

lib_LTLIBRARIES = libretail_rfid_reader_gateway.la

libretail_rfid_reader_gateway_la_SOURCES = \
	retail_rfid_reader_gateway.cpp \
	parameters/parameters.cpp \
	parameters/options.cpp

libretail_rfid_reader_gateway_la_CFLAGS = $(AM_CFLAGS)

libretail_rfid_reader_gateway_la_CXXFLAGS = $(AM_CXXFLAGS)

libretail_rfid_reader_gateway_la_CPPFLAGS = $(AM_CPPFLAGS)
libretail_rfid_reader_gateway_la_CPPFLAGS += $(AWS_IOT_CPPFLAGS)
libretail_rfid_reader_gateway_la_CPPFLAGS += $(BOOST_CPPFLAGS)

libretail_rfid_reader_gateway_la_LDFLAGS = $(AM_LDFLAGS)
libretail_rfid_reader_gateway_la_LDFLAGS += $(AWS_IOT_LDFLAGS) 
libretail_rfid_reader_gateway_la_LDFLAGS += $(BOOST_PROGRAM_OPTIONS_LDFLAGS)

libretail_rfid_reader_gateway_la_LIBADD = $(DEPENDENCIES_LIBS)
libretail_rfid_reader_gateway_la_LIBADD += $(AWS_IOT_LIBS)
libretail_rfid_reader_gateway_la_LIBADD += $(BOOST_PROGRAM_OPTIONS_LIBS)

libretail_rfid_reader_gateway_la_include_HEADERS = \
	retail_rfid_reader_gateway.h

#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = retail_rfid_reader_gateway.pc

#EXTRA_DIST = \
#	retail_rfid_reader_gateway.pc.in
endif

bin_PROGRAMS = retail_rfid_reader_gateway

retail_rfid_reader_gateway_SOURCES = \
	retail_rfid_reader_gateway.cpp \
	parameters/parameters.cpp \
	parameters/options.cpp \
	aws_iot/client.cpp \
	aws_iot/OpenSSLConnection.cpp

retail_rfid_reader_gateway_CFLAGS = $(AM_CFLAGS)

retail_rfid_reader_gateway_CXXFLAGS = $(AM_CXXFLAGS)

retail_rfid_reader_gateway_CPPFLAGS = $(AM_CPPFLAGS)
retail_rfid_reader_gateway_CPPFLAGS += $(AWS_IOT_CPPFLAGS)
retail_rfid_reader_gateway_CPPFLAGS += $(BOOST_CPPFLAGS)

retail_rfid_reader_gateway_LDFLAGS = $(AM_LDFLAGS)
retail_rfid_reader_gateway_LDFLAGS += $(AWS_IOT_LDFLAGS)
retail_rfid_reader_gateway_LDFLAGS += $(BOOST_PROGRAM_OPTIONS_LDFLAGS)

retail_rfid_reader_gateway_LDADD = $(DEPENDENCIES_LIBS)
retail_rfid_reader_gateway_LDADD += $(AWS_IOT_LIBS)
retail_rfid_reader_gateway_LDADD += $(BOOST_PROGRAM_OPTIONS_LIBS)

if ENABLE_TESTS
if ENABLE_COVERAGE
AM_CFLAGS +=\
	-fprofile-arcs\
	-ftest-coverage

libretail_rfid_reader_gateway_la_LIBADD += -lgcov
endif
endif
