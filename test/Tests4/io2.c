
int getchar();
int putchar(int c);

int main()
{
  int c, d;
  d = c = getchar();
  putchar(10);  /* newline */
  putchar(65);
  putchar(83);
  putchar(67);
  putchar(putchar(73));
  putchar(58);
  putchar(32);

  putchar(48 + d/100);
  d = d % 100;
  putchar(48 + d/10);
  d = d % 10;
  putchar(48 + d);

  putchar(10);
  return c;
}
