
int putchar(int c);

int main()
{
  int x;

  x = 66;

  (x != putchar(65)) || (putchar(66) < x);

  (x < putchar(67)) && (x != putchar(68));

  putchar(10);
  return 0;
}
