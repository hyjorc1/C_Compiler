
int putchar(int c);

int main()
{

  if ( (putchar(65) < 100) && (putchar(66) < 50) && (putchar(67) < 20) ) {
    putchar(68);
  }
  putchar(10);

  if ( (putchar(69) > 100) || (putchar(70) > 50) || (putchar(71) > 20) ) {
    putchar(72);
  }
  putchar(10);

  return 0;
}
