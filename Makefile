EXTENSION    = geqo_extension
EXTVERSION   = $(shell grep default_version $(EXTENSION).control | \
               sed -e "s/default_version[[:space:]]*=[[:space:]]*'\([^']*\)'/\1/")

DOCS         = $(wildcard doc/*.md)
TESTS        = $(wildcard test/sql/*.sql)
REGRESS      = $(patsubst test/sql/%.sql,%,$(TESTS))
REGRESS_OPTS = --inputdir=test
PG_CONFIG    = pg_config

#EXTRA_CLEAN = src/saio_probes.h

MODULE_big = geqo_extension
OBJS =	src/geqo.o src/geqo_copy.o src/geqo_eval.o src/geqo_main.o src/geqo_misc.o \
	src/geqo_mutation.o src/geqo_pool.o src/geqo_random.o src/geqo_recombination.o \
	src/geqo_selection.o \
	src/geqo_erx.o src/geqo_pmx.o src/geqo_cx.o src/geqo_px.o src/geqo_ox1.o src/geqo_ox2.o

# make sure
all: all-lib


coverage:
	lcov -d . -c -o lcov.info
	genhtml --show-details --legend --output-directory=coverage --title=PostgreSQL --num-spaces=4 --prefix=./src/ `find . -name lcov.info -print`


PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
