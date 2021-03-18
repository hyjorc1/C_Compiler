
const float pi = 3.1415926535897932384626433832795028841971; /* approximately */

void zero(int A[], const int N)
{
  int i = 0;

  N;
  N+1;
  i >= N;
  N > 3;

  for (;;) {
    A[i] = 0;
    i++;
    if (i>=N) break;
  }
}

void OK()
{
  int primes[100];
  int size = 100;
  zero(primes, size); 
}

void illegal()
{
  const int i;
  const int j = 4;

  i = 7;  /* nope */
  j++;    /* nope */

  pi /= 2.0;  /* nope */
}
