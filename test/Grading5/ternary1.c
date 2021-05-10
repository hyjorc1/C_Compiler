
/// ASSEMBLY putyn

int putchar(int c);

void putyn(int x)
{
  int c;
  c = x ? 89 : 78;  /** putyn
    iload,ifeq LA,89,goto LB,LA:,78,LB:,?dup,istore
    iload,ifne LA,78,goto LB,LA:,89,LB:,?dup,istore
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
