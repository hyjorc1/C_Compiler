// File: ifdefs2.c

#define F 1

#ifndef F
#define G
#endif

#ifdef G
  8
#else
  9
#endif

#ifdef ERROR
  X
#else
  Y
#else
  Z
#endif
