int global, A[50];

void print(int x);

int putc(int a);

int f(int a)
{
  a = b;                /* error */
  a + "nope";           /* error */
  a += putc(10+a/2);
  print(42);
  return a+3;   
}

float g(int x, int y)
{
  int z;
  z = f(x) + A[putc(f(y))]; 
  while (print(3)) {    /* error */
    z++;
    return 4.5;
  } 
  if (z < 12) {
    return;             /* error */
  }
  g(x-1, y-1);
  return 7;             /* error */
}

void h()
{
  f('c');               /* error for minimal implementation */
  f(3, 4, 5);           /* error */
  g(6);                 /* error */
  h(7);                 /* error */
  i("not defined");     /* error */
  A[g(1,2)];            /* error */
}
