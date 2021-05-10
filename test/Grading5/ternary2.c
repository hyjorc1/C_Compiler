
/// ASSEMBLY putyn

int putchar(int c);

void putyn(int x)
{
  putchar( x ? 89 : 78 ); /** putyn
    iload,ifeq LA,89,goto LB,LA:,78,LB:,putchar
    iload,ifne LA,78,goto LB,LA:,89,LB:,putchar
  **/
  putchar(10);
  return;
}

int main()
{
  putyn(1);
  putyn(0);
  putyn(3);
  return 0;
}
