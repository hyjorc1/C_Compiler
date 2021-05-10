
/// ASSEMBLY main

int putchar(int c);

int main()
{
  int x;
  x = 1;
  if (x) { putchar(89); }       /** main
                                    iload_0,ifeq LA,89,putchar,?pop,LA:
                                **/

  x = 0;
  if (x) { putchar(78); }       /** main
                                    iload_0,ifeq LA,78,putchar,?pop,LA:
                                **/

  putchar(10);
  return 0;
}
