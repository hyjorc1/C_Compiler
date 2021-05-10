
int putchar(int c);

void show(int b)
{
  putchar(102 + 14*b);
  putchar(10);
}

int main()
{
  show( ! (putchar(65) < 100) );
  show( ! (putchar(66) > 100) );

  return 0;
}
