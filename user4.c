
/// USER whatever
/// whatever types (CCCIIFFF)F
/// whatever stack 1
/// whatever locals 18
float whatever(char a, char b, char c, int d, int e, float f, float g, float h)
{
  int i, j, k;
  char l, m, n, o;
  float p, q, r;

  return f;
}

/// USER max
/// max types (FFFI)F
/// max stack 3
/// max locals 4
float max(float a, float b, float c, int n)
{
  return a+b+c;
}


/// USER deep
/// deep types ()V
/// deep stack 17
/// deep locals 0
void deep()
{
  whatever('a', 'b', 'c', 4, 5, 6.0, 7.0, 
    max(8.0, 9.0, 
      whatever('j', 'k', 'l', 13, 14, 15.0, 16.1, 17.1), 18
    )
  );
}

