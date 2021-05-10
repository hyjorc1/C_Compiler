
int putchar(int c);

int put(int c, int a)
{
  putchar(c);
  return a;
}

int main()
{
  if ( put(65, 1) || put(66,0) )
  {
    putchar(116);
    putchar(10);
  }
  else
  {
    putchar(102);
    putchar(10);
  }
  
  if ( put(68, 0) || put(69,0) )
  {
    putchar(116);
    putchar(10);
  }
  else
  {
    putchar(102);
    putchar(10);
  }
  return 0;
}
