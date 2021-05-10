
int putchar(int c);

int put(int c, int a)
{
  putchar(c);
  return a;
}

void show(int b)
{
  putchar(102 + 14*b);
  putchar(10);
}

int main()
{
  show( put(65, 0) && put(66, 1) );
  show( put(67, 1) && put(68, 1) );
  show( put(69, 0) || put(70, 0) );
  show( put(71, 1) || put(72, 1) );

  return 0;
}
