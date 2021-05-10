
/// ASSEMBLY comp

int putchar(int c);

void comp(int x)
{
  putchar(60);
  putchar(61);
  if (x <= 42) {
    putchar(89);
  } else {
    putchar(78);
  } /** comp
    iload_0,42,if_icmpgt LA,89,putchar,?pop,goto LB,LA:,78,putchar,?pop,LB:
    iload_0,42,if_icmple LA,goto LB,LA:,89,putchar,?pop,goto LC,LB:,78,putchar,?pop,LC:
    iload_0,42,if_icmple LA,78,putchar,?pop,goto LB,LA:,89,putchar,?pop,LB:
  **/
  putchar(10);
  return;
}

int main()
{
  comp(40);
  comp(41);
  comp(42);
  comp(43);
  comp(44);
  return 0;
}
