
/// ASSEMBLY main

int getchar();
int putchar(int c);

int main()
{
  int c;
  c = getchar();
  if (c > 32) {
    c = c - 32;
    do {
      putchar( (c = c - 1) + 32);
    } while (c); /** main
      LA:,iload_0,iconst_1,isub,?dup,istore_0,?iload_0,32,iadd,putchar,?pop,iload_0,ifne LA
    **/
  }
  putchar(10);
  return 0;
}
