#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"

/*
 * This code has only been tested with PostgreSQL 14.3
 */


#if  (PG_VERSION_NUM / 100) < 14
#error "Unknown or unsupported PostgreSQL version"
#endif
 
PG_MODULE_MAGIC;


typedef struct
{
    char dna[32]; // 1 char -> 1 byte

} kmer;


Datum kmer_in(PG_FUNCTION_ARGS);
Datum kmer_out(PG_FUNCTION_ARGS);

static inline kmer* str_to_kmer(const char*);
static inline const char* kmer_to_str(const kmer*);
