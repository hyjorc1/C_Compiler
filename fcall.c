
/*
  Function call tests.

  Comment out the bad ones to get past the syntax errors.
*/

int good()
{
  foo();
  foo(1);
  foo(1, 2);
  foo(1, 2, 3);
  foo(1, 2, 3, 4);
}

int bad1()
{
  foo(, 1);
}

int bad2()
{
  foo(1 ,);
}

int bad3()
{
  foo(1, , 2);
}
