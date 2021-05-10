
int putchar(int c);

void show(int a, int b)
{
  int x;
  x = a;
  while ((putchar(x) < b) && putchar(44)) {
    x = x + 1;
  }
  putchar(10);
  return;
}

int main()
{
  show(48, 57);
  show(60, 62);
  show(65, 90);
  show(97,122);
  return 0;
}
