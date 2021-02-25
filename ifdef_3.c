
#define GOOD_ON

#ifdef GOOD_ON
#define GOOD_A
#define GOOD_B
#endif

GOOD1

#ifdef GOOD_A
  GOOD2
#else
  bad1
  "#endif"
  bad2
#endif

GOOD3

#ifndef GOOD_B
  bad2
#else
  GOOD4
#endif

GOOD5

"#ifdef NOPE"

GOOD6

