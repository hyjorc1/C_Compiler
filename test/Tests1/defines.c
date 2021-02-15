// File: defines.c

/* Not too fancy substitution */

#define PI 3.14159
#define N 100

PI + N;

#undef M
// There is no M to undefine.  This is OK but a warning is also OK.
M;
#define M 6
M;
#define M 7
// Should give a warning because we're redefining M
M;

/* Recursive substitution */

#define TWOPI (2.0 * PI)
#define NP1 (N + 1)
#define NP1SQ  NP1 * NP1

TWOPI + NP1SQ;

#undef N

NP1SQ;  // Still ok, but uses N instead of 100

/* Substitution cycle */

#define BAD hi THING
#define THING hi BAD

BAD;
