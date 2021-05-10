
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
  while (x) {
    x = x - 1;
    myput(x);
    continue;
    myput(x);
  } /** main
    iload,myput,goto LA,iload,myput,goto LA,LB:
  **/
  putchar(10);
  return 0;
}
