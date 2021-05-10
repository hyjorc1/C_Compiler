
int putchar(int c);

int main()
{

  (putchar(65) < 100) && (putchar(66) < 50) && (putchar(67) < 20);
  putchar(10);

  (putchar(68) > 100) || (putchar(69) > 50) || (putchar(70) > 20);
  putchar(10);

  return 0;
}
