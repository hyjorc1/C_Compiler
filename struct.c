void foo1() {
    struct A { };
}

struct B { };

void foo2() {
    struct A a; // error at a
    struct B b;
}

void foo3(struct A aa, struct B bb) { // error at aa
    
}

struct A aaa; // error at aaa
struct B bbb;
