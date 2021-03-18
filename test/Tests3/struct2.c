
struct pair {
  int x, y;
};

struct triple {
  struct pair p;
  int z;
};

void test()
{
  struct triple T;
  T;
  T.p;
  T.z;
  T.p.x;
  T.p.y;
  T.nope;     // Error
  T.p.nope;   // Error
  T.p.x.nope; // Error
}
