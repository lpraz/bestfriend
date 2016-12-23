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
PREFIX = /usr/bin
INSTTARGET = bestfriend

# Directories (test)
TESTDIR = test
TESTTARGET = bin/test.out

# Extension
SRCEXT = c

# Specific files (build/install)
TARGET = bin/a.out
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Test subject (blank, specify in command line)
TESTSUBJ = 

#
# Recipes
#

# Build binary from objects
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

# Build objects from source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -I $(INCLDIR) -c -o $@ $<

# Run tests (TODO: Improve on this?)
tester:
	$(CC) $(SRCDIR)/$(TESTSUBJ).$(SRCEXT) $(TESTDIR)/test_$(TESTSUBJ).$(SRCEXT) -I $(INCLDIR) -I $(LIBDIR) -o $(TESTTARGET)
	$(TESTTARGET)

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
