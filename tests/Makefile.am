noinst_PROGRAMS = $(TEST_PROGS)

PRODUCTION_CODE_INCLUDES = -I$(top_srcdir)/src
PRODUCTION_CODE_LIBS = $(top_builddir)/src/libretail_rfid_reader_gateway.la

AM_CPPFLAGS = \
	$(CPPUTEST_CFLAGS)\
	$(PRODUCTION_CODE_INCLUDES)

AM_CFLAGS =	-Werror\
	-Wall\
	-g

AM_CXXFLAGS = $(AM_CFLAGS)
AM_CXXFLAGS += -std=c++11

TEST_PROGS = retail_rfid_reader_gateway_tests

retail_rfid_reader_gateway_tests_SOURCES = retail_rfid_reader_gateway_tests.cpp
retail_rfid_reader_gateway_tests_LDADD = $(CPPUTEST_LIBS)\
	$(PRODUCTION_CODE_LIBS)

check_PROGRAMS = $(TEST_PROGS)

TESTS = $(TEST_PROGS)
