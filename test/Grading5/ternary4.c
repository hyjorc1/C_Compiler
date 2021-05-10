
/// ASSEMBLY yn

int putchar(int c);

int yn(int x)
{
  return 11*(x ? 2 : 1) + 67; /** yn
    11,iload,ifeq LA,2,goto LB,LA:,1,LB:,imul,67,iadd,ireturn
    11,iload,ifne LA,1,goto LB,LA:,2,LB:,imul,67,iadd,ireturn
  **/
}

int main()
{
  putchar(yn(1));
  putchar(yn(0));
  putchar(yn(3));
  putchar(10);
  return 0;
}
