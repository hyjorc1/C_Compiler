
/// ASSEMBLY main

int putchar(int c);

void myput(int x)
{
  putchar(x);
  return;
}

int main()
{
  int x;
  x = 5;
  myput(65);
  while (x) {
    myput(66);
    break;
    myput(67);
    x = x - 1;
  } /** main
    LA:,iload,ifeq LB,66,myput,goto LB,67,myput,?iload,?iconst,?isub,?dup,?istore,?iload,?pop,goto LA,LB:
  **/
  putchar(10);
  return 0;
}
