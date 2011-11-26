INCLUDES = -I$(top_srcdir)
CFLAGS = @CFLAGS@ -std=gnu99

h_sources = mathtools.h prng.h

c_sources = trig.c rounding.c gcflcm.c prng.c logtools.c prettyint.c statistics.c simplefft.c sinusoid.c

lib_LTLIBRARIES = libbrahe.la

libbrahe_la_SOURCES = $(h_sources) $(c_sources)
libbrahe_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

DEFS = -I. -I$(srcdir)
