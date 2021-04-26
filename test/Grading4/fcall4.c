
int putchar(int c);

void evil(int a)
{
  putchar(putchar(a));
  // No return statement; but this should be fine
}

int main()
{
  putchar(72);
  putchar(101);
  evil(108);
  putchar(111);
  putchar(10);
  return 33;
}
