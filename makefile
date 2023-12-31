CC = gcc
PROGRAM = bball

CFLAGS = -Iinclude -Wall -Wextra -g
LFLAGS = -lm -lraylib

_OBJ = main.o
_DEPS = raylib.h

SDIR = src
IDIR = include

OBJ = $(_OBJ:%=$(SDIR)/%)
DEPS = $(_DEPS:%=$(IDIR)/%)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	rm -f $(OBJ)

purge:
	rm -f $(OBJ) $(PROGRAM)
