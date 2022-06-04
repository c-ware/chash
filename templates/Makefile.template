# This Makefile is the output of a template Makefile that was
# processed by the m4 macro preprocessor. It is not intended
# to be human readable.

CC=cc
PREFIX=/usr/local
# CFLAGS=-ansi -Wall -Wextra -Wshadow -Wdouble-promotion -fpic -Wno-unused-variable -Wno-unused-function -Wno-sign-compare
TESTS=syscmd(`find tests/ -type f -name "*.c" | tr "\n" " " | sed "s/\.c/.out/g"')
DOCS=syscmd(`find . -type f -name "*.cware" | tr "\n" " "')
MANNAMES=syscmd(`for src in $(find . -type f -name "*.cware"); do echo $src | xargs basename; done | tr "\n" " "')
DEBUGGER=

.PHONY: all clean check install
.SUFFIXES: .c .out

all: $(TESTS) $(DOCS)

clean:
	rm -f $(TESTS)

check:
	./scripts/check.sh $(DEBUGGER)

install:
	install -d -m 755 $(PREFIX)/include/cware
	install -m 755 src/chash.h $(PREFIX)/include/cware
	install -d -m 755 $(PREFIX)/share/man/mancware
	for manual in $(MANNAMES); do \
		install -m 755 doc/$$manual $(PREFIX)/share/man/mancware; \
	done


uninstall:
	rm -f $(PREFIX)/include/cware/chash.h
	for manual in $(MANNAMES); do  \
		rm -f $(PREFIX)/share/man/mancware/$$manual; \
	done
	rmdir $(PREFIX)/share/man/mancware
	rmdir $(PREFIX)/include/cware

.c.out:
	$(CC) $< $(OBJS) $(CFLAGS) -o $@
