#include "kmer.h"
//Kmer structure maxium size is 32 bytes
#define KMER_LENGTH      32

kmer *  s;

// An array with all the possible four standard nucleotides
static int kmer_digits[4] =
  {
    'A', 'C', 'G', 'T'
  };


// insert into table values ("ACGTA")
static inline kmer* str_to_kmer(const char* str)
{

    int i, j, n = strlen(str);
    int size = n; 
    char dna[32];
    bool found;
// Verify that the value is not null or bigger than 32 bytes
  if( n == 0 || n > KMER_LENGTH )
  {
    ereport(ERROR,
			(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value \"%s\" is out of range for type kmer",str)));
  }
   
   n = sscanf(str, "%s", dna); //We need to get the dna string
  // Verify that the dna has only values A, C, G, T
  for (i=0; i<size; i++ ){ //Using variable size as the length of the dna string
    found = false;
    
    for (j = 0; j < 4; j++) {
            if (dna[i] == kmer_digits[j]) { // Compare the value of the dna string vs the kmer allowed permit
                found = true;
                break;
            }
  }
  // If one value is not allowed, then show an error
  if (found == false){
      elog(ERROR, "value '%c' is not a valid digit for type kmer ('A','C','G','T').", dna[i]);       
  }
  }

  
    kmer* k = (kmer *)palloc(sizeof(kmer)); 
    strcpy(k->dna, dna);
    
return k;
}


// From structure KMER to Str
static inline const char* kmer_to_str(const kmer* k)
{
    char * result = psprintf("%s", k->dna);
    return result;

}

// Inpout from the user 
PG_FUNCTION_INFO_V1(kmer_in);
Datum kmer_in(PG_FUNCTION_ARGS)
{

    const char *str = PG_GETARG_CSTRING(0);
    PG_RETURN_POINTER(str_to_kmer(str));


}

/* Output for the user */
PG_FUNCTION_INFO_V1(kmer_out);
Datum kmer_out(PG_FUNCTION_ARGS)
{
    const kmer* s = (kmer *)PG_GETARG_POINTER(0);
    PG_RETURN_CSTRING(kmer_to_str(s));
}


