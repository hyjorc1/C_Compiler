
int putchar(int c);

int put(int c, int a)
{
  putchar(c);
  return a;
}

int main()
{
  if ( put(65, 0) || put(66,1) || put(67,1) )
  {
    putchar(116);
  }
  putchar(10);

  if ( put(69, 0) || put(70,0) || put(71,1) )
  {
    putchar(116);
  }
  putchar(10);

  if ( put(73, 0) || put(74,0) || put(75,0) )
  {
    putchar(116);
  }
  putchar(10);

  if ( put(77, 0) || !put(78,1) || put(79,1) )
  {
    putchar(116);
  }
  putchar(10);

  return 0;
}
