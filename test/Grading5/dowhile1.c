
/// ASSEMBLY main

int getchar();
int putchar(int c);

int main()
{
  int c;
  c = getchar() - 47;
  do {
    c = c - 1;
    putchar(35);
  } while (c); /** main
    LA:,iload_0,iconst_1,isub,?dup,istore_0,?iload_0,?pop,35,putchar,?pop,iload_0,ifne LA
  **/
  putchar(10);
  return 0;
}
