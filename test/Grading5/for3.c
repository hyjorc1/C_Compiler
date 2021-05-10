
int putchar(int c);

void myput(int x)
{
  putchar(65+x);
  putchar(10);
}

int main()
{
  int i;
  i = 5;
  for ( ; i ; i = i - 1) {
    myput(i);
  } 
  return 0;
}
