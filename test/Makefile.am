CFLAGS = @CFLAGS@ -std=gnu99

bin_PROGRAMS = brahe_test_prng brahe_test_trig brahe_test_rounding brahe_test_gcflcm brahe_test_fft brahe_test_pretty

brahe_test_prng_SOURCES = brahe_test_prng.c
brahe_test_trig_SOURCES = brahe_test_trig.c
brahe_test_rounding_SOURCES = brahe_test_rounding.c
brahe_test_pretty_SOURCES = brahe_test_pretty.c
brahe_test_gcflcm_SOURCES = brahe_test_gcflcm.c
brahe_test_fft_SOURCES = brahe_test_fft.c

LIBS = -L../src -lbrahe -lm -lrt
