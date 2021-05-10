
int putchar(int c);

void myput(int x)
{
  putchar(x);
  putchar(10);
}

int main()
{
  int i;
  i=67;
  for ( i=65 ; ; ) {
    myput(i);
    return 0;
  } 
  myput(66);
  return 1;
}
