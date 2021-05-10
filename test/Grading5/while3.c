
/// ASSEMBLY revprint

int putchar(int c);

void show_ones(int x)
{
  putchar(48 + x % 10);
  return;
}

void revprint(int x)
{
  show_ones(x);
  while (x) {         /** revprint
    LA:,iload_0,ifeq LB,iload_0,10,idiv,?dup,istore_0,?iload_0,show_ones,goto LA,LB:
  **/
    show_ones(x = x / 10);
  }
  putchar(10);
  return;
}

int main()
{
  revprint(123);
  revprint(54321);
  return 0;
}
