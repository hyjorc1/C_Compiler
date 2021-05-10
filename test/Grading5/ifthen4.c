
/// ASSEMBLY test

int putchar(int c);

void test(int b1, int b2)
{
  if (b1) {
    if (b2) {
      putchar(89);
    }
    putchar(101);
  } /** test
    iload_0,ifeq LA,iload_1,ifeq LB,89,putchar,?pop,LB:,101,putchar,?pop,LA:
  **/
}

int main()
{
  test(1, 1);
  putchar(115);
  putchar(10);
  return 0;
}
