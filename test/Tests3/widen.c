
int A[100];

float fact(int n)
{
  float f;
  if (n<2) {
    return 1;       // 1 is an int, widened to float here
  } else {
    f = n * fact(n-1);    // n should be widened to float here
    return f;
  }
}

void tests()
{
  char c;
  int i;
  float f;

  c = 'a';
  i = 'b';    // char -> int
  f = i;      // int -> float
  f = 'c';    // char -> float

  fact(c);            // char -> int
  fact(f ? i : c);    // char -> int
  fact(A['4']);       // array index char -> int
}
