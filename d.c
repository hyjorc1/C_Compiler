// File: d.c
#include "a.h"
int D()
{
  return A + B + C;
}
#include "e.h"
// The above causes an include cycle error, so there is no
// guarantee that the compiler will continue past here.
int BYE;
