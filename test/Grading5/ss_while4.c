
int putchar(int c);

int main()
{
  int i, j;

  i = 42;
  j = 96;

  do {
    i = i + 1;
    j = j + 1;
  } while ((putchar(j) < 102) || (putchar(i) < 57));
  putchar(10);
  return 0;
}
