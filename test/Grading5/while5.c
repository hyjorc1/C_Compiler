
/// ASSEMBLY readint

int getchar();
int putchar(int c);

int update(int n, int c)
{
  return n * 10 + c - 48;
}

int readint()
{
  int c;
  int n;
  n = 0;
  while (1) {
    c = getchar();
    if (10 == c) return n;  
    n = update(n, c);
  } /** readint
    LA:,?iconst_1,?ifeq LB,getchar,?dup,?istore_0,?iload_0,?pop,?10,?iload_0,if.* LC,iload_1,ireturn,LC:,?iload_1,?iload_0,update,?dup,istore_1,?iload_1,?pop,goto LA
  **/
  return 0;
}

void writeint(int x)
{
  if (x < 0) {
    putchar(45);
    return writeint(-x);
  }
  if (x > 9) {
    writeint(x/10);
  }
  putchar(48 + x % 10);
}

int main()
{
  int x, y, z;
  x = readint();
  y = readint();
  z = x + y;
  writeint(z);
  putchar(10);
  return 0;
}
