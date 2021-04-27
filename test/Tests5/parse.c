
/*
  Parser from week 1 of class, written
  in our subset of C

  BECAUSE WE CAN.

*/

int next;

int getchar();
int putchar(int c);

void yyerror(char exp)
{
  putchar(10);
  putchar(10);
  putchar(69);  putchar(114);  putchar(114);  putchar(111);  putchar(114);
  putchar(58);  putchar(32);
  putchar(101); putchar(120); putchar(112); putchar(101); putchar(99);
  putchar(116); putchar(101); putchar(100); putchar(32);

  if ('#' == exp) {
    putchar(100); putchar(105); putchar(103); putchar(105); putchar(116);
  } else {
    putchar(43); putchar(32); putchar(111); putchar(114); 
    putchar(32); putchar(42);
  }

  putchar(44); putchar(32); putchar(103); putchar(111); putchar(116);
  putchar(58); putchar(32);
  putchar(next);
  putchar(10);
}

void init_lexer()
{
  next = getchar();
}

/*
  Skip whitespace,
  return first non-whitespace character or EOF (-1).
*/
void skip_white()
{
  while ( (9==next) || (10==next) || (13==next) || (32==next) )
  {
    next = getchar();
  }
}

int get_number()
{
  skip_white();
  if ((next < 48) || (next > 57)) {
    yyerror('#');
    return 0;
  }
  putchar(next);
  next = getchar();
  while (( next >= 48 ) && ( next <= 57 )) {
    putchar(next);
    next = getchar();
  }
  putchar(32);
  return 1;
}

int get_op()
{
  skip_white();
  if (43 == next) {
    next = getchar();
    return 43;
  }
  if (42 == next) {
    next = getchar();
    return 42;
  }
  if (next < 0) { // EOF
    return 0;
  }
  yyerror('+');
  return 0;
}

int main()
{
  int op, nextop, waiting_plus;

  init_lexer();

  if (! get_number()) return 1;

  op = get_op();
  waiting_plus = 0;

  while (op) {
    if (! get_number()) return 1;

    nextop = get_op();

    if (42 == op) { // *
      putchar(42);  putchar(32);
      if ( (42 != nextop) && waiting_plus ) {
        putchar(43); putchar(32);
        waiting_plus = 0;
      }
    }
    if (43 == op) { // +
      if (42 != nextop) {
        putchar(43); putchar(32);
      } else {
        waiting_plus = 1;
      }
    }

    op = nextop;
  } // while token

  putchar(10);
  return 0;
}
