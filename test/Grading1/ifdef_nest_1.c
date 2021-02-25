
#ifdef FOO
  bad1
#else
  GOOD1
#endif

#ifdef FOO
  bad2
  #ifdef BAR
    bad3
  #else
    bad4
  #endif
  bad5
#else
  GOOD2
  #ifdef BAR
    bad6
  #else
    GOOD3
  #endif
  GOOD4
#endif
GOOD5
