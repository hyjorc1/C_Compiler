
int putchar(int c);

int put(int c, int a)
{
  putchar(c);
  return a;
}

int main()
{
  put(65, 1) && put(66,0) && put(67,1);
  putchar(10);

  put(69, 1) && put(70,1) && put(71,0);
  putchar(10);

  put(73, 1) && put(74,1) && put(75,1);
  putchar(10);

  put(77, 1) && !put(78,0) && put(79,1);
  putchar(10);
  return 0;
}
