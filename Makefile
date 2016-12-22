#
# Variables
#

# Compiler options
CC = gcc
CFLAGS = -std=c99

# Directories (build)
SRCDIR = src
INCLDIR = include
LIBDIR = lib
BUILDDIR = build

# Directories (install)
#DESTDIR =
PREFIX = /usr/bin
INSTTARGET = bestfriend

# Directoroes (test)
TESTDIR = test
TESTTARGET = bin/test.out

# Extension
SRCEXT = c

# Specific files
TARGET = bin/a.out
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

#
# Recipes
#

# Build binary from objects
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

# Build objects from source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -I $(INCLDIR) -c -o $@ $<

# TODO: Run tests
# Reference (based on test_stack, have cutest.h in include dir):
# gcc -std=c99 -I include -c -o build/test_stack.o test/test_stack.c
# gcc -std=c99 -I include -c -o build/stack.o src/stack.c
# gcc build/stack.o build/test_stack.o -o bin/test
# bin/test

# Install to $(PREFIX)
.PHONY: install
install: $(TARGET)
	cp $< $(DESTDIR)$(PREFIX)/$(INSTTARGET)

# Uninstall from $(PREFIX)
.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/$(INSTTARGET)

# Clean objects
.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o
