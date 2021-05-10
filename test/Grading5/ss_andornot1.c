
int putchar(int c);

int put(int c, int a)
{
  putchar(c);
  return a;
}

int main()
{
  put(65, 0) && put(66,0);
  putchar(10);

  put(68, 1) && put(69,1);
  putchar(10);

  return 0;
}
