
#include "parse.h"

int yyparse();

struct expr* theroot;

int main()
{
  int code = yyparse();
  struct expr* T = getRoot();
  // Do stuff with T here
  return 0;
}
