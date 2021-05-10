
/// ASSEMBLY triangle

int putchar(int c);

void triangle(int x)
{
  int y;
  do {
    putchar(48 + (y = x));
    do {
      putchar(35);
    } while (y = y - 1);
    putchar(10);
  } while (x = x - 1); /** triangle
    LA:,48,iload_0,?dup,istore_1,?iload_1,iadd,putchar,pop,LB:,35,putchar,?pop,iload_1,iconst_1,isub,?dup,istore_1,?iload_1,ifne LB,10,putchar,?pop,iload_0,iconst_1,isub,?dup,istore_0,?iload_0,ifne LA
  **/
  return;
}

int main()
{
  triangle(3);
  triangle(5);
  triangle(7);
  triangle(11);
  return 0;
}
