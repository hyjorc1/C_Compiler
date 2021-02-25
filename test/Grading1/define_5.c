
#define A 4
#define B A+1
#define C B+1

A;
B;
C;

#undef B

A;
B;
C;

#undef A

A;
B;
C;

