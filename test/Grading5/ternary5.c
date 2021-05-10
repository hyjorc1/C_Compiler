
/// ASSEMBLY yn

int putchar(int c);

int yn(int x, int u)
{
  return ( x ? 89 : 78 ) + ( u ? 0 : 32 ); /** yn
    iload_0,ifeq LA,89,goto LB,LA:,78,LB:,iload_1,ifeq LC,0,goto LD,LC:,32,LD:,iadd
    iload_0,ifne LA,78,goto LB,LA:,89,LB:,iload_1,ifne LC,32,goto LD,LC:,0,LD:,iadd
  **/
}

int main()
{
  putchar(yn(1, 1));
  putchar(yn(0, 1));
  putchar(yn(3, 1));
  putchar(10);
  putchar(yn(1, 0));
  putchar(yn(0, 0));
  putchar(yn(3, 0));
  putchar(10);
  return 0;
}
