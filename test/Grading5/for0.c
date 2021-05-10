
/// ASSEMBLY main

int putchar(int c);

void myput(int x)
{
  putchar(x);
  putchar(10);
}

int main()
{
  for ( ; ; ) {
    myput(65);
    return 0;
  } /** main
    LA:,65,myput,0,ireturn,goto LA
  **/
  myput(66);
  return 1;
}
