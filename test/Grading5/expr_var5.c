
/// ASSEMBLY test

void test(int a, int b, int c)
{
  int d;

  d = a;    /** test
                iload_0,?dup,istore_3
            **/

  b = d;    /** test
                iload_3,?dup,istore_1
            **/

  c = b;    /** test
                iload_1,?dup,istore_2
            **/

  d = c;    /** test
                iload_2,?dup,istore_3
            **/

  putchar(d);
}

int main()
{
  test(79, 1, 2);
  test(75, 4, 5);
  test(10, 9, 8);
  return 0;
}
