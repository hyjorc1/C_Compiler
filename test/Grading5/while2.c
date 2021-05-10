
/// ASSEMBLY main

int putchar(int c);

int main()
{
  int x;
  x = 1;
  while (x) {
    x = 65 - putchar(65);
  } /** main
    LA:,iload_0,ifeq LB,?65,?65,?putchar,?isub,?dup,?istore_0,?pop,goto LA,LB:
  **/
  putchar(10);
  return 0;
}
