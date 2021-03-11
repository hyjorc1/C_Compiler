# Mode 2 Parsing Rules

1.  A C program is a sequence of zero or more (global) variable declarations, function prototypes, and function definitions, appearing in any order.
2.  A variable declaration is a type name, followed by a comma-separated list of one or more identifiers, each identifier optionally followed by a left bracket, an integer constant, and a right bracket. The list is terminated with a semicolon. Note that this restricts arrays to a single dimension.
3.  A type name is one of the simple types: void, char, int, float.
4.  A function prototype is a function declaration followed by a semicolon.
5.  A function declaration is a type name (the return type of the function), followed by an identifier (the name of the function), a left parenthesis, an optional comma-separated list of formal parameters, and a right parenthesis.
6.  A formal parameter is a type name, followed by an identifier, and optionally followed by a left and right bracket.
7.  A function definition is a function declaration followed by a left brace, a sequence of zero or more variable declarations, a sequence of zero or more statements, and a right brace. Note that this definition requires all variable declarations to appear before statements.
8.  A statement block is a left brace, a sequence of zero or more statements, and a right brace.
9.  A statement is one of the following.
    - An empty string followed by a semicolon.
    - An expression followed by a semicolon.
    - Keywords break or continue followed by a semicolon. Note: you do not need to check that these statements are within a loop.
    - Keyword return, followed by an optional expression, and a semicolon.
    - Keyword if, followed by a left parenthesis, an expression, and a right parenthesis, followed by either a statement block or a single statement followed by a semicolon. Then, optionally, the following: keyword else, followed by either a statement block, or a single statement followed by a semicolon.
    - Keyword for, followed by a left parenthesis, an optional expression, a semicolon, an optional expression, a semicolon, an optional expression, a right parenthesis, and then either a statement block, or a single statement followed by a semicolon.
    - Keyword while, followed by a left parenthesis, an expression, and a right parenthesis, and then either a statement block, or a single statement followed by a semicolon.
    - Keyword do, followed by either a statement block or a statement and a semicolon, followed by keyword while, a left parenthesis, an expression, a right parenthesis, and a semicolon.
10. An expression is one of the following.
    - A literal (constant) value.
    - An identifier, left parenthesis, a comma-separated list of zero or more expressions, and a right parenthesis.
    - An l-value.
    - An l-value, an assignment operator, and an expression.
    - An l-value, preceeded by or followed by the increment or decrement operator.
    - A unary operator, and an expression.
    - An expression, a binary operator, and an expression.
    - An expression, a question mark, an expression, a colon, and an expression.
    - A left parenthesis, a type name, a right parenthesis, and an expression.
    - A left parenthesis, an expression, and a right parenthesis.
11. An l-value is an identifier, optionally followed by a left bracket, an expression, and a right bracket. Note that this restricts array access to a single dimension.
12. Unary operators (for any expression) are: -, !, ~
13. Binary operators are: ==, !=, >, >=, <, <=, +, -, \*, /, %, |, &, ||, &&
14. Assignment operators are: =, +=, -=, \*=, /=
