
/// ASSEMBLY test

int putchar(int c);

void test(int n, int x, int y, int z)
{
  if (x) {
    putchar(89);  // Y
    if (y) {
      putchar(101);  // e
    } /** test
      iload_1,ifeq LA,89,putchar,?pop,iload_2,ifeq LB,101,putchar,?pop,LB:
    **/
    if (z) {
      putchar(115); // s
      if (n) {
        putchar(111);
      }
    }
    if (n) {
      putchar(111);
    }
  }
  if (n) {
    putchar(111);
  }
  putchar(10);
}

int main()
{
  test(0, 1, 1, 1);
  return 0;
}
