
int getchar();
int putchar(int c);

int main()
{
  int d;
  int last;
  last = 0;
  for (d = getchar() ; (10!=d) && (13!=d) && putchar(44); d=getchar()) {
    for ( ; (9==d) || (32==d) ; d=getchar() ) 
    {
      if (last) {
        putchar(10);
        last = 0;
      }
    }
    last = putchar(d);
  }
  putchar(10);
  return 0;
}
