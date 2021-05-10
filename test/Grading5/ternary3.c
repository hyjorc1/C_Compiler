
/// ASSEMBLY putyn

int putchar(int c);

void putyn(int x)
{
  int c;
  c = 70 + (x ? 19 : 8);  /** putyn
    70,iload,ifeq LA,19,goto LB,LA:,8,LB:,iadd
    70,iload,ifne LA,8,goto LB,LA:,19,LB:,iadd
  **/
  putchar(c);
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
