# Directory structure
SUBDIRS = src

# Compiler flags
AM_CFLAGS = -std=c99 -Wall -Wextra

# Installation directories
libdir = $(prefix)/lib
includedir = $(prefix)/include

# What to install
install-data-local:
	mkdir -p $(DESTDIR)$(libdir) $(DESTDIR)$(includedir)

