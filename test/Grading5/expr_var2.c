
/// ASSEMBLY write

void write(int a, int b)
{
  putchar(a); /** write
                  iload_0,putchar
              **/
  putchar(b); /** write
                  iload_1,putchar
              **/
}

int main()
{
  write(72, 101);
  write(108, 108);
  write(111, 10);
  return 0;
}
