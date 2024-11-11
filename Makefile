EXTENSION   = kmer 
MODULES     = kmer
DATA        = kmer--1.0.sql kmer.control        

LDFLAGS=-lrt

PG_CONFIG ?= pg_config
PGXS = $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)