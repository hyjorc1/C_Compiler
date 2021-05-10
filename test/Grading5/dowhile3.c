
/// ASSEMBLY main

int getchar();
int putchar(int c);

int main()
{
  int c, d;
  c = 32;
  do {
    d = c;
  } while ( (c=getchar()) > 32); /** main
    LA:,iload_0,?dup,istore_1,?iload_1,?pop,getchar,?dup,istore_0,?iload_0,32,if_icmpgt LA
    LA:,iload_1,?dup,istore_0,?iload_0,?pop,getchar,?dup,istore_1,?iload_1,32,if_icmpgt LA
  **/
  putchar(d);
  putchar(10);
  return 0;
}
