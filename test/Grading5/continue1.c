
/// ASSEMBLY main

int putchar(int c);

void myput(int x)
{
  putchar(65+x);
  return;
}

int main()
{
  int x;
  x=10;
  do {
    x = x - 1;
    myput(x);
    continue;
    myput(x);
  } while (x); /** main
    myput,goto LB,iload,myput,LB:,iload,ifne LA
  **/
  putchar(10);
  return 0;
}
