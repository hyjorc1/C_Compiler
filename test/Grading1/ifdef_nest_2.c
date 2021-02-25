
GOOD1

#ifndef A  
  GOOD2
  #ifndef B
    GOOD3
    #ifndef C
      GOOD4
    #else
      bad1
    #endif
    GOOD5
  #else
    bad2
    #ifdef C
      bad3
    #else
      bad4
    #else 
      bad5
    #endif
    bad6
  #endif
#endif
