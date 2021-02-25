
#define A a E
#define B b b
#define C c B
#define D d C
#define E e D

A

#undef B
#undef A

"restarting"

#define A a B
#define B b

A

#undef B

"restarting with a loop"

#define B b E

A

