
/// USER funcA
/// funcA types (C)V
/// funcA stack 1
/// funcA locals 2
void funcA(char c)
{
  int a;
  c = 'c';
  a = 2;
}

/// USER funcB
/// funcB types (FII)V
/// funcB stack 1
/// funcB locals 3
void funcB(float a, int b, int c)
{
  b = c;
}

/// USER funcC
/// funcC types ()I
/// funcC stack 1
/// funcC locals 2
int funcC()
{
  int a, b;
  a = 1;
  b = 2;
  return a+b;
}
