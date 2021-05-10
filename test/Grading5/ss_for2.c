
int putchar(int c);

void show(int a, int b)
{
  int x;
  for (x=a; (putchar(x) != b) && putchar(44); x=b) {
    putchar(32);
  }
  putchar(10);
  return;
}

int main()
{
  show(72, 101);
  show(108, 108);
  show(111, 32);
  show(119, 111);
  show(114, 108);
  show(100, 33);
  return 0;
}
