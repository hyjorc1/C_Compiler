
int putchar(int c);

void show(int s, int n, int d)
{
  int i;
  for (i=s; (i<s+n) && (i>s-n) && putchar(44); i=i+d) {
    putchar(i);
  }
  putchar(10);
}

int main()
{
  show(65, 6, 1);
  show(57, 10, -1);
  show(97, 5, 2);
  show(122, 5, -2);
  return 0;
}
