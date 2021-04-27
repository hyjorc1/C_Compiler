
int putchar(int c);
int getchar();

int read_int()
{
  int c;
  int val;
  val = 0;

  c = getchar();
  while (( c >= 48) && (c <= 57)) {
    val = val * 10 + c - 48;
    c = getchar();
  }
  return val;
}

void write_int(int x)
{
  if (x<0) {
    putchar(111);
    putchar(118);
    putchar(101);
    putchar(114);
    putchar(102);
    putchar(108);
    putchar(111);
    putchar(119);
  } else {
    if (x>9) write_int(x/10);
    putchar(48 + x%10);
  }
}

/*
  Factorial, but check for overflow
*/
int fact(int n)
{
  int f, fn;
  if (n<2) return 1;
  f = fact(n-1);
  if (f<0) return f;
  fn = n * f;
  if (f != fn / n) return -1;
  return fn;
}

int main()
{
  int n;
  putchar(73);
  putchar(110);
  putchar(116);
  putchar(101);
  putchar(103);
  putchar(101);
  putchar(114);
  putchar(63);
  putchar(10);
  n = read_int();
  write_int(n);
  putchar(33);
  putchar(61);
  write_int(fact(n));
  putchar(10);
  return 0;
}
