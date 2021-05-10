
int getchar();
int putchar(int c);

/// ASSEMBLY writeint readint

void writeint(int x)
{
  do {
    putchar(x % 10 + 48);
    x = x / 10;
  } while (x);  /** writeint
    LA:,iload_0,10,irem,48,iadd,putchar,pop,iload_0,10,idiv,?dup,istore_0,?iload_0,?pop,iload_0,ifne LA
    LA:,iload_0,10,irem,48,iadd,putchar,pop,iload_0,10,idiv,istore_0,iload_0,ifne LA
  **/
  putchar(10);
  return;
}

int readint()
{
  int digit;
  int number;
  int power;
  number = 0;
  power = 1;
  do {
    digit = getchar();
    if (10 == digit) {
      digit = 0;
    } else {
      number = number + (digit - 48) * power;
      power = power * 10;
    }
  } while (digit);  /** readint
    LA:,getchar,?dup,istore,?iload,?pop,10,iload,if_icmpne LB,0,?dup,istore,?iload,?pop,goto LC,LB:
    LA:,getchar,istore,10,iload,if_icmpne LB,0,istore,goto LC,LB:
  **/
  return number;
}

int main()
{
  int a, b;

  a = readint();
  b = readint();
  writeint(a+b);
  return 0;
}
