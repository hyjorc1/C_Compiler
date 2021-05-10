
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
  for (x=10; x; x=x-1) {
    myput(x);
    continue;
    myput(x);
  } /** main
    iload,myput,goto LC,iload,myput,LC:,iload,1,isub
  **/
  putchar(10);
  return 0;
}
