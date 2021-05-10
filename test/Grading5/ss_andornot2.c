
int putchar(int c);

int put(int c, int a)
{
  putchar(c);
  return a;
}

int main()
{
  put(65, 1) || put(66,0);
  putchar(10);
  
  put(68, 0) || put(69,0);
  putchar(10);
  return 0;
}
