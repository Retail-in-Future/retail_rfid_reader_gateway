ACLOCAL_AMFLAGS = -I build-aux

SUBDIRS = src

if ENABLE_TESTS
SUBDIRS += tests
endif

DIST_SUBDIRS = $(SUBDIRS)

retail_rfid_reader_gatewaydocdir = ${prefix}/doc/retail_rfid_reader_gateway
retail_rfid_reader_gatewaydoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(retail_rfid_reader_gatewaydoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(retail_rfid_reader_gatewaydocdir)

coverage:
if ENABLE_COVERAGE
	gcovr -x -r .. -e ".+\.test\.cpp" --object-directory=src > coverage.xml
else
	@echo "To generate coverage report, please run ./configure with --enable-coverage"
endif
