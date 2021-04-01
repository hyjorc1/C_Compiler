
int foo();

void bar();

int cruft(int a)
{
  foo();
  bar();
  foo(a); /* error */
}
