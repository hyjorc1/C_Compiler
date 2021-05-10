
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
  int b;

  b = put(65, 0) || put(66, 0);
  show(b);

  b = put(67, 1) || put(68, 1);
  show(b);

  return 0;
}
