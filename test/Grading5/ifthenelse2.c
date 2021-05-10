
/// ASSEMBLY test

int putchar(int c);

void test(int x)
{
  if (x) {
    putchar(89);
  } else {
    putchar(78);
  } /** test
    iload_0,ifeq LA,89,putchar,?pop,goto LB,LA:,78,putchar,?pop,LB:
    iload_0,ifne LA,78,putchar,?pop,goto LB,LA:,89,putchar,?pop,LB:
    iload_0,ifne LA,goto LB,LA:,89,putchar,?pop.goto LC,LB:,78.putchar,?pop,LC:
  **/
  putchar(10);
  return;
}

int main()
{
  test(1);
  return 0;
}
