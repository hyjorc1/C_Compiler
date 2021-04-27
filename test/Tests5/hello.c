
int putchar(int c);

void prints(char A[])
{
  int i;
  for (i=0; A[i]; i++) {
    putchar((int)A[i]);
  }
}

int main()
{
  prints("Hello, world!\n");
  return 0;
}
