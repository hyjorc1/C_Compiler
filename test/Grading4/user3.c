
/// USER max
/// max types (IIIIII)I
/// max stack 1
/// max locals 7
int max(int a, int b, int c, int d, int e, int f)
{
  int m;
  m = a;
  // TBD
  return m;
}

/// USER fun
/// fun types (II)I
/// fun stack 11
/// fun locals 2
int fun(int a, int b)
{
  return max(a, b, 3, 4, 5, max(6, 7, 8, 9, 10, 11));
}
