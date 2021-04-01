
void foo();
void bar();

void test()
{
  /* These are all bad */

  foo() + bar();
  foo() - bar();
  foo() * bar();
  foo() / bar();
  foo() % bar();
  foo() & bar();
  foo() | bar();
}

