
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
  x=0;
  myput(x);
  do {
    z = x / 5;
    if (z) break;
    x = x + 1;
    myput(x);
  } while (x); /** main
    LA:,iload,5,idiv,?dup,istore,?iload,?pop,?iload,ifeq LB,goto LC,LB:,iload,1,iadd,?dup,istore,?iload,?pop,?iload,myput,iload,ifne LA,LC:
    LA:,iload,5,idiv,?dup,istore,?iload,?pop,?iload,ifne LC,iload,1,iadd,?dup,istore,?iload,?pop,?iload,myput,iload,ifne LA,LC:
  **/
  putchar(10);
  return 0;
}
