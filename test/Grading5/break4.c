
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
  x=1;
  myput(x);
  while (x) { 
    z = x / 5;
    if (z) break;
    x = x + 1;
    myput(x);
  } /** main
    LA:,iload,ifeq LB,iload,5,idiv,?dup,istore,?iload,?pop,?iload,ifeq LC,goto LB,LC:,iload,1,iadd,?dup,istore,?iload,?pop,?iload,myput,goto LA,LB:
    LA:,iload,ifeq LB,iload,5,idiv,?dup,istore,?iload,?pop,?iload,ifne LB,iload,1,iadd,?dup,istore,?iload,?pop,?iload,myput,goto LA,LB:
  **/
  putchar(10);
  return 0;
}
