
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
  do {
    x = x - 1;
    z = x / 5;
    if (z) continue;
    myput(x);
  } while (x); /** main
    iload_1,ifeq LB,goto LC,LB:,iload_0,myput,LC:,iload_0,ifne LA  
    iload_0,ifeq LB,goto LC,LB:,iload_1,myput,LC:,iload_1,ifne LA  
    iload_1,ifne LC,iload_0,myput,LC:,iload_0,ifne LA  
    iload_0,ifne LC,iload_1,myput,LC:,iload_1,ifne LA  
  **/
  putchar(10);
  return 0;
}
