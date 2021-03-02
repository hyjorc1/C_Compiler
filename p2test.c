int x, y;
float z[50];

int foo(int z)
{
  // Variable a is never declared?  That's OK for now!
  return a;   
}

int bar(int a, int b)
{
  // Local variable hides parameter, OK for now
  int a;
  // Incorrect parameter type is OK for now
  a = foo(4.2);
  for (i=0; i<10; i++) {
    foo(i, 7);
    // Incorrect number of parameters is OK for now
  }
  // Incorrect assignment type is OK for now
  a = z * 2.5;
  // Incorrect return type is OK for now
  return 5.3;
}

int more, global[25], variables;

float proto_only(char x, int y[], float z);

int test(int lots, int more, int useless)
{
  char variables[15], just, to, show;
}

int bar(int a, int b) // duplicate definition for bar?  OK for now!
{
  int d;
  d = 0;
  while ( (d += ++a) < b);
  return d;
}

int main()
{
  float how, this, part, should, work;
  return 7;
}
