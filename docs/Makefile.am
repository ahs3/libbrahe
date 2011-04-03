EXTRA_DIST = libbrahe.doxygen libbrahe_foot.html libbrahe_head.html

CLEANFILES = html/*

htmldir = $(datadir)/doc/$(GENERIC_LIBRARY_NAME)/api

html_DATA = html/index.html

html/index.html: libbrahe.doxygen
	doxygen libbrahe.doxygen

install-data-hook:
	cp -dR html/* $(DESTDIR)$(htmldir)
