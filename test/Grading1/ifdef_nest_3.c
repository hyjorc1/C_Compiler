
#define A
#define B
#define C

GOOD1

#ifdef A
  GOOD2
  #ifdef B
    GOOD3
    #ifdef C
      GOOD4
    #endif
    GOOD5
  #endif
  GOOD6
#endif
GOOD7
#endif
#endif
#endif
