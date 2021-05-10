
/// ASSEMBLY main

int putchar(int c);

int main()
{
  int x;
  x = 0;
  putchar(66);
  while (x) {
    putchar(65);
  } /** main
    LA:,iload_0,ifeq LB,?65,?putchar,?pop,goto LA,LB:
  **/
  putchar(10);
  return 0;
}
