ACLOCAL_AMFLAGS = -I m4

if HAVE_DOXYGEN
DOC_DIR = docs
else
DOC_DIR =
endif

SUBDIRS = src test $(DOC_DIR)
EXTRA_DIST = LicenseClosedSource.txt LicenseOpenSource.txt reconf cleanup Brahe.sln

dist-hook:

	if test -d BraheDLL; then \
		mkdir $(distdir)/BraheDLL; \
		cp -p BraheDLL/* $(distdir)/BraheDLL; \
	fi

	if test -d BraheTest; then \
		mkdir $(distdir)/BraheTest; \
		cp -p BraheTest/* $(distdir)/BraheTest; \
	fi

uninstall-local:
	rm -rf $(distdir)/BraheDLL
	rm -rf $(distdir)/BraheTest
