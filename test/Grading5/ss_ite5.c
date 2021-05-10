
int putchar(int c);

int main()
{

  putchar(
    (putchar(65) < 100) && (putchar(66) < 50) && (putchar(67) < 20)
    ?  116 : 102
  );
  putchar(10);

  putchar(
    (putchar(68) > 100) || (putchar(69) > 50) || (putchar(70) > 20)
    ?  116 : 102
  );
  putchar(10);

  return 0;
}
