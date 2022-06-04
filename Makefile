# This Makefile is the output of a template Makefile that was
# processed by the m4 macro preprocessor. It is not intended
# to be human readable.

CC=cc
PREFIX=/usr/local
# CFLAGS=-ansi -Wall -Wextra -Wshadow -Wdouble-promotion -fpic -Wno-unused-variable -Wno-unused-function -Wno-sign-compare
TESTS=tests/array_test.out tests/var_addr.out tests/struct_values.out tests/stress_test.out tests/stack_lookup.out tests/stack_init.out tests/stack_free.out tests/stack_delete.out tests/stack_contains.out tests/stack_assign.out tests/lookup_bucket.out tests/lookup.out tests/iter.out tests/is_full.out tests/init.out tests/free.out tests/delete.out tests/contains.out tests/assign.out 
DOCS=./doc/chash_lookup_bucket.cware ./doc/chash_lookup.cware ./doc/chash_iter.cware ./doc/chash_is_full.cware ./doc/chash_init_stack.cware ./doc/chash_init.cware ./doc/chash_free.cware ./doc/chash_delete.cware ./doc/chash_contains.cware ./doc/chash_assign.cware ./doc/chash.cware 
MANNAMES=chash_lookup_bucket.cware chash_lookup.cware chash_iter.cware chash_is_full.cware chash_init_stack.cware chash_init.cware chash_free.cware chash_delete.cware chash_contains.cware chash_assign.cware chash.cware 
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
