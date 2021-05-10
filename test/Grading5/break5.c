
/// ASSEMBLY main

int putchar(int c);

void myput(int x)
{
  putchar(65+x);
  return;
}

int main()
{
  int x,z;
  for (x=10; x; x=x-1) {
    z = (10-x)/5;
    if (z) break;
    myput(x);
  } /** main
    idiv,?dup,istore_0,?iload_0,?pop,?iload_0,ifeq LA,goto LB,LA:,iload_1,myput
    idiv,?dup,istore_1,?iload_1,?pop,?iload_1,ifeq LA,goto LB,LA:,iload_0,myput
    idiv,?dup,istore_0,?iload_0,?pop,?iload_0,ifne LA,iload_1,myput
    idiv,?dup,istore_1,?iload_1,?pop,?iload_1,ifne LA,iload_0,myput
  **/
  putchar(10);
  return 0;
}
