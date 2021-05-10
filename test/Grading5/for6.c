
int putchar(int c);

void myput(int x)
{
  putchar(65+x);
  putchar(10);
}

int main()
{
  int i;
  i = 8;
  for ( i=5 ; i ; ) {
    myput(i);
    i = 0;
  } 
  return 0;
}
