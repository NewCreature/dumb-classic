# This file contains the main rules for compiling the library. It is included
# twice with different values for CFLAGS and OBJDIR, so the optimised and
# debugging libraries are both built.

CORE_OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(CORE_MODULES))))
ALLEGRO_OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(ALLEGRO_MODULES))))


# Pass the current value of CFLAGS through to the commands. Or, more
# accurately, create a local copy of the current CFLAGS variable. This is
# necessary because Make doesn't expand variables in commands until they are
# executed.
$(CORE_LIB_FILE): CFLAGS := $(CFLAGS)
$(ALLEGRO_LIB_FILE): CFLAGS := $(CFLAGS)


$(OBJDIR)/%.o: src/core/%.c include/dumb-classic.h include/internal/dumb-classic.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: src/helpers/%.c include/dumb-classic.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/resample.o: src/helpers/resample.inc src/helpers/resamp2.inc src/helpers/resamp3.inc

$(OBJDIR)/%.o: src/it/%.c include/dumb-classic.h include/internal/it.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: src/sigtypes/%.c include/dumb-classic.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: src/allegro/%.c include/aldumb-classic.h include/dumb-classic.h \
                      include/internal/aldumb-classic.h include/internal/dumb-classic.h
	$(CC) $(CFLAGS) $(WFLAGS_ALLEGRO) -c -o $@ $<

$(CORE_LIB_FILE): $(CORE_OBJECTS)
	$(AR) rs $@ $^

$(ALLEGRO_LIB_FILE): $(ALLEGRO_OBJECTS)
	$(AR) rs $@ $^
