
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
  x=10;
  while (x) {
    x = x - 1;
    z = x / 5;
    if (z) continue;
    myput(x);
  } /** main
    iload_1,ifeq LC,goto LA,LC:,iload_0,myput,goto LA,LB:
    iload_0,ifeq LC,goto LA,LC:,iload_1,myput,goto LA,LB:
    iload_1,ifne LA,iload_0,myput,goto LA,LB:
    iload_0,ifne LA,iload_1,myput,goto LA,LB:
  **/
  putchar(10);
  return 0;
}
