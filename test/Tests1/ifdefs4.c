// File: ifdefs1.c

#define A
#define B
#define C

#ifdef D
1
#ifdef B
2
#ifdef C
3
#else
4
#endif
5
#else
6
#endif
7
#else
8
#ifdef A
9
#else
10
#ifdef B
11
#else
12
#endif
13
#endif
14
#endif