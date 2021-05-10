
int putchar(int c);

void show(int a, int b)
{
  int x;
  x = a;
  do {
    x = x + 1;
  } while ((putchar(x) < b) && putchar(44));
  putchar(10);
  return;
}

int main()
{
  show(47, 57);
  show(59, 62);
  show(64, 90);
  show(96,122);
  return 0;
}
