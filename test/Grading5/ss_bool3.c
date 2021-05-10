
int putchar(int c);

void show(int b)
{
  putchar(102 + 14*b);
  putchar(10);
}

int main()
{
  int b;

  b = putchar(65) < 100;
  show(b);

  b = putchar(66) > 100;
  show(b);

  return 0;
}
