
int getchar();

int A[10];

int main()
{
  A[0] = 0;
  A[1] = 1;
  A[2] = 2*2;
  A[3] = 3*3;
  A[4] = 4*4;
  A[5] = 5*5;
  A[6] = 6*6;
  A[7] = 7*7;
  A[8] = 8*8;
  A[9] = 9*9;

  return A[getchar() - 48];
}
