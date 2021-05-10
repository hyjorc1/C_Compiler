
/// ASSEMBLY main

int putchar(int c);

int main()
{
  int x;
  x = 0;
  if (x)    /** main
                iload_0,ifeq LA,78,putchar,?pop,111,putchar,?pop,LA:
            **/
  {
    putchar(78);  // N
    putchar(111); // o
  }
  x = 1;
  if (x)   
  {
    putchar(89);  // Y
    putchar(101); // e
    putchar(115); // s
  }
  putchar(10);
  return 0;
}
