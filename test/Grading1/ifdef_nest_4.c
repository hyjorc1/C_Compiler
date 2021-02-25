
#define A
#define C

GOOD1

#ifdef A
  GOOD2
  #ifdef B
    bad1 
    #ifdef C
      bad2 
    #endif
    bad3 
  #endif
  GOOD2
#endif
GOOD3
