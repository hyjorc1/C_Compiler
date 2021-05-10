
/// ASSEMBLY test

int putchar(int c);

void test(int x)
{
  int c;
  c = 89;
  if (x) { c = 78; }  /** test
    iload_0,ifeq LA,78,?dup,istore_1,?iload_1,?pop,LA:
  **/

  putchar(65);
  putchar(c);
  putchar(10);
  return;
}

int main()
{
  test(0);
  return 0;
}
