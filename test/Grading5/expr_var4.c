
/// ASSEMBLY write

int write(int a)
{
  int b;

  a = 79;   /** write
                79,?dup,istore_0
            **/

  b = 75;   /** write
                75,?dup,istore_1
            **/

  putchar(a);
  return putchar(b);
}

int main()
{
  write(5);
  write(6);
  return putchar(10);
}
