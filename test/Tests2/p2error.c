int ok()
{
  /* Empty functions are allowed! */
}

int printf(int n)   // Because we can
{
  int i;
  i = 0;
  for (;;) {
    i++;
    n/=2;
    if (n) continue;
    return i;
  }
}

int too_many_elses(int a, int b)
{
  if (a<b) {
    return 1;
  } else {
    return 2;
  } else {
    return 3;
  }
}

