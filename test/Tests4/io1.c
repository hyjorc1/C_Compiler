
int getchar();
int putchar(int c);

int main()
{
  int c;
  c = getchar();
  putchar(10);  /* newline */
  putchar(c);
  putchar(10);
  return c;
}
