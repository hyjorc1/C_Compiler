
/// ASSEMBLY triangle

int putchar(int c);

void triangle(int x)
{
  int y;
  while (x) {           /** triangle
                              LA:,iload_0,ifeq LB
                        **/
    y = x;
    while (y) {         /** triangle
                              LA:,iload_1,ifeq LB
                        **/
      putchar(35);
      y = y - 1;
    }                   
    putchar(10);
    x = x - 1;
  } /** triangle
    goto LA,LB:,10,putchar,?pop,?iload_0,?iconst_1,?isub,?dup,?istore_0,?iload_0,?pop,goto LC
  **/
}

int main()
{
  triangle(3);
  triangle(5);
  triangle(7);
  triangle(11);
  return 0;
}
