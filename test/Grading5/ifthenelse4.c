
/// ASSEMBLY test

int putchar(int c);

void test(int x)
{
  if (x) {
    putchar(89);  // Y
  } else {
    putchar(78);  // N
  } /** test
    iload_0,ifeq LA,89,putchar,?pop,goto LB,LA:,78,putchar,?pop,LB:
    iload_0,ifne LA,78,putchar,?pop,goto LB,LA:,89,putchar,?pop,LB:
    iload_0,ifne LA,goto LB,LA:,89,putchar,?pop.goto LC,LB:,78.putchar,?pop,LC:
  **/

  if (x) {
    putchar(101); // e
  } else {
    putchar(111); // o
  } /** test
    iload_0,ifeq LA,101,putchar,?pop,goto LB,LA:,111,putchar,?pop,LB:
    iload_0,ifne LA,111,putchar,?pop,goto LB,LA:,101,putchar,?pop,LB:
    iload_0,ifne LA,goto LB,LA:,101,putchar,?pop.goto LC,LB:,111.putchar,?pop,LC:
  **/

  if (x) {
    putchar(115); // s
  } /** test
    iload_0,ifeq LA,115,putchar,?pop,LA:
    iload_0,iconst_0,if_icmpne LA,115,putchar,?pop,LA:
    iconst_0,iload_0,if_icmpne LA,115,putchar,?pop,LA:
  **/

  return;
}

int main()
{
  test(1);
  putchar(10);
  return 0;
}
