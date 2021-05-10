
/// ASSEMBLY test

int putchar(int c);

void test(int x)
{
  if (x) {
    putchar(89);  // Y
    putchar(101); // e
    putchar(115); // s
  } else {
    putchar(78);  // N
    putchar(111); // o
  } /** test
    iload_0,ifeq LA,89,putchar,?pop,101,putchar,?pop,115,putchar,?pop,goto LB,LA:,78,putchar,?pop,111,putchar,?pop,LB:
  **/
  return;
}

int main()
{
  test(1);
  putchar(10);
  return 0;
}
