
/// ASSEMBLY comp

int putchar(int c);

void comp(float x)
{
  putchar(62);
  if (x > 42.0) {
    putchar(89);
  } else {
    putchar(78);
  } /** comp
    fload_0,42,fcmp.,ifle LA,89,putchar,?pop,goto LB,LA:,78,putchar,?pop,LB:
    fload_0,42,fcmp.,ifgt LA,goto LB,LA:,89,putchar,?pop,goto LC,LB:,78,putchar,?pop,LC:
    fload_0,42,fcmp.,ifgt LA,78,putchar,?pop,goto LB,LA:,89,putchar,?pop,LB:
  **/
  putchar(10);
  return;
}

int main()
{
  comp(40.0);
  comp(41.0);
  comp(42.0);
  comp(43.0);
  comp(44.0);
  return 0;
}
