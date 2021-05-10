
/// ASSEMBLY test

void test(int a)
{
  int b;
  b = a;  /** test
              iload_0,?dup,istore_1
          **/

  putchar(b);
}

int main()
{
  test(79);
  test(75);
  test(10);
  return 0;
}
