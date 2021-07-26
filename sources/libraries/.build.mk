LIBS_BIN = $(BUILDDIR_CROSS)/libbrutal.a

LIBS_SRC = \
	$(wildcard sources/libraries/syscalls/*.c) \
	$(wildcard sources/libraries/ansi/*.c) \
	$(wildcard sources/libraries/posix/*.c) \
	$(wildcard sources/libraries/gnu/*.c) \
	$(wildcard sources/libraries/bsd/*.c) \
	$(wildcard sources/libraries/brutal/*.c) \
	$(wildcard sources/libraries/brutal/*/*.c) \
	$(wildcard sources/libraries/brutal/host/brutal/*.c) \
	$(wildcard sources/libraries/handover/*.c) \
	$(wildcard sources/libraries/math/*.c) \
	$(wildcard sources/libraries/elf/*.c)

LIBS_OBJ = $(patsubst sources/%.c, $(BUILDDIR_CROSS)/%.c.o, $(LIBS_SRC))

DEPENDENCIES += $(LIBS_OBJ:.o=.d)

$(BUILDDIR_CROSS)/libraries/%.c.o: sources/libraries/%.c
	$(MKCWD)
	$(CROSS_CC) -c -o $@ $< $(CROSS_UCFLAGS)

$(LIBS_BIN): $(LIBS_OBJ)
	$(MKCWD)
	$(CROSS_AR) $(CROSS_ARFLAGS) $@ $^
