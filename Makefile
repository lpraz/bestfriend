#
# Variables
#

# Compiler options
CC = gcc
CFLAGS = -std=c99

# Directories
SRCDIR = src
INCLDIR = include
BUILDDIR = build

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
	$(CC) $^ -o $(TARGET)

# Build objects from source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -I $(INCLDIR) -c -o $@ $<

# Clean objects
.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o
