
int putchar(int c);

int main()
{
  (putchar(65) >= 66) && (67 <= putchar(68));

  (70 >= putchar(69)) || (putchar(71) <= 72);

  putchar(10);
  return 0;
}
