
struct pair {
  int x, y;
};

void func1()
{
  struct triple {
    struct pair p;
    int z;
  };

  struct pair P;
  struct triple T;

  P;
  T;
}

struct pair { int x, y; };    // Error

void func2()
{
  struct pair P;
  struct triple T;    // Error

  P;
  T;
}

