
/// ASSEMBLY test

int putchar(int c);

void test(int x, int y)
{
  int c;
  if (x) {
    c = 88;
  } else if (y) {
    c = 89;
  } else {
    c = 90;
  } /** test
    iload_0,ifeq LA,88,?dup,istore_2,?iload_2,?pop,goto LB,LA:,iload_1,ifeq LC,89,?dup,istore_2,?iload_2,?pop,goto LB,LC:,90,?dup,istore_2,?iload_2,?pop,LB:
  **/
  putchar(c);
  putchar(10);
}

int main()
{
  test(0,0);
  test(0,1);
  test(1,0);
  test(1,1);
  return 0;
}
