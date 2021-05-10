
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
  x = 0;
  myput(65);
  do {
    myput(66);
    break;
    myput(67);
  } while (x); /** main
    LA:,66,myput,goto LB,67,myput,iload,ifne LA,LB:
  **/
  putchar(10);
  return 0;
}
