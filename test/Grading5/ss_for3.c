
int putchar(int c);

void triangle(int x)
{
  int y;
  putchar(45);
  for (y=x; x && y && putchar(35); putchar(45)) {
    y = y - 1;
    if (!y) {
      putchar(10);
      x = x - 1;
      y = x;
    }
  }
  putchar(10);
  return;
}

int main()
{
  triangle(3);
  triangle(7);
  return 0;
}
