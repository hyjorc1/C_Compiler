
struct expr {
  char optor;  // u, +, *, -, /, or # for number
  struct expr* left;
  struct expr* right;
  long number;
};

/*
  Build a pointer to a new expression struct
  containing the number n.
*/
struct expr* makeNumber(long n);

/*
  Build a pointer to a new expression struct
  for the given binary operation
*/
struct expr* makeBinary(struct expr* left, char op, struct expr* right);

/*
  Save the root to a global variable
*/
void saveRoot(struct expr* t);

/*
  Get the global root variable
*/
struct expr* getRoot();
