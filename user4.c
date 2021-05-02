
int putchar(int c);

int N;

void print(int x)
{
  if (x<0) {
    putchar((int)'-');
    return;
  }
  if (x>9) {
    print(x/10);
  }
  putchar(48+x%10);
}

void print_row(int A[], int n)
{
  int i;
  for (i=0; i<n; i++) {
    print(A[i]);
    putchar(32);
  }
  putchar(10);
}

int main()
{
  int i,j,prev,next;
  int A[10];
  N=9;

  A[0] = 1;
  for (i=1; i<=N; i++) {
    A[i] = 0;
  }
  print_row(A, 1);
  for (i=1; i<N; i++) {
    prev = 0;
    for (j=0; j<=i; j++) {
      next = A[j] + prev;
      prev = A[j];
      A[j] = next;
    }
    print_row(A, i+1);
  }

  return 0;
}
