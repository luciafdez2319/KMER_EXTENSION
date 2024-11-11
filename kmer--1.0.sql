-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION kmer" to load this file. \quit

CREATE OR REPLACE FUNCTION kmer_in(cstring)
RETURNS kmer
AS '$libdir/kmer'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION kmer_out(kmer)
RETURNS cstring
AS '$libdir/kmer'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE kmer (
	INPUT          = kmer_in,
	OUTPUT         = kmer_out,
    INTERNALLENGTH = 32
);
COMMENT ON TYPE kmer IS 'kmer contains dna';