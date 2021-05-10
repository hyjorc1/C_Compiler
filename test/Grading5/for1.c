
int putchar(int c);

void myput(int x)
{
  putchar(65+x);
  putchar(10);
}

int main()
{
  int i;
  i = 0;
  for ( ; ; i = i + 1 ) {
    myput(i);
    if (i) {
      return 0;
    }
  } 
  myput(66);
  return 1;
}
