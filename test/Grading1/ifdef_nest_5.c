
#define A
#define B
#define C
#define E

#ifdef A
  GOOD1
  #ifdef B
    GOOD2
    #ifdef C
      GOOD3
      #ifdef D
        bad1
        #ifdef E
          bad2
        #else
          bad3
        #endif
        bad4
      #else
        GOOD4
      #endif
      GOOD5
    #else
      bad5
      #ifdef C
        bad6
      #else
        bad7
      #endif
      bad8
    #endif
    GOOD6
  #endif
  GOOD7
#endif
GOOD8
