
int putchar(int c);

void triangle(int x)
{
  int y;
  y = x;
  while (x && y && putchar(35) ) {
    y = y - 1;
    if (!y) {
      putchar(10);
      x = x - 1;
      y = x;
    }
  }
  return;
}

int main()
{
  triangle(3);
  triangle(7);
  return 0;
}
