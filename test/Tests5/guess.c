
int getchar();
int putchar(int c);

void put4(char c1, char c2, char c3, char c4)
{
  putchar((int) c1);
  putchar((int) c2);
  putchar((int) c3);
  putchar((int) c4);
}

void put8(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8)
{
  put4(c1, c2, c3, c4);
  put4(c5, c6, c7, c8);
}

void putint(int x)
{
  if (x>9) {
    putint(x/10);
  }
  putchar(48 + x%10);
}

int getyn()
{
  int k;
  for (;;) {
    k = getchar();
    if (k<0) return 0;        // prevent infinite loop on EOF
    if (89 == k) return 1;
    if (121 == k) return 1;
    if (78 == k) return 0;
    if (110 == k) return 0;
  }
  return 0; // keep compiler happy
}

int main()
{
  int low, high, mid;

  put8('C', 'h', 'o', 'o', 's', 'e', ' ', 'a');
  put8(' ', 'n', 'u', 'm', 'b', 'e', 'r', ' ');
  put8('b', 'e', 't', 'w', 'e', 'e', 'n', ' ');
  put8('0', ' ', 'a', 'n', 'd', ' ', '9', '9');
  put4('9', '.', ' ', '\n');

  low = 0;
  high = 1000;

  while (low+1 < high) {
    mid = (low+high)/2;
    put8('I', 's', ' ', 'y', 'o', 'u', 'r', ' ');
    put8('n', 'u', 'm', 'b', 'e', 'r', ' ', 'l');
    put8('e', 's', 's', ' ', 't', 'h', 'a', 'n');
    putchar(32);
    putint(mid);
    putchar((int)'?');
    putchar(10);

    if (getyn()) {
      high = mid;
    } else {
      low = mid;
    }
  }
  put8('Y', 'o', 'u', 'r', ' ', 'n', 'u', 'm');
  put8('b', 'e', 'r', ' ', 'i', 's', ':', ' ');
  putint(low);
  putchar(10);

  return 0;
}
