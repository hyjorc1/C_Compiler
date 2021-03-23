
int c, A[50], a = err;

const int B[50];

struct S1 {
    int a, b;
    int a;
};

struct S1 {};

struct S2 {
    int a, b;
    const struct S1 s1;
    const struct S1 s2;
    const struct S1 s3, s4[1];
    const struct S3 s5;
};

void f1(int x, int y);

void f1(int a, int b) {
    const struct S1 s1;
    const struct S1 s2;
    int c[10];

    struct S3 {
        const struct S1 s1;
        const struct S1 s2;
    };

    struct S3 {};

    struct S4 {
        const struct S3 s3;
        struct S4 s2;
    };

    12;
    "hi";
    'j';
    12.3;

    if ("hi") {}
    while ("hi") {}
    do {} while("hi");
    for (;"hit";) {}

    return 1;
}

void f1() {}

void f1(int a, int b) {}

void f1();

int f2() {

    f();
    f1(1, 2, 3);
    f1("str1", "str2");


    f1(1, 2);

    /* test for R1 */
    i1 ? 1 : 2; // error
    1 ? i1 : 2; // error
    1 ? 1 : i1; // error
    "hi" ? 1 : 2; // error
    1 ? "hi" : 2; // error
    1 ? 1 : "hi"; // error

    1 ? "hi" : "hi";

    /* test for R2 */
    ~1;
    ~'a';
    ~"hi"; // error

    /* test for R3 */
    -'a';
    -1;
    -1.1;
    -"hi"; // error

    /* test for R4 */
    !'a';
    !1;
    !1.1;
    !"hi"; // error

    /* test for R5,6,7 */
    (char) 1;
    (char) "hi"; // error
    (int) 1;
    (int) "hi"; // error
    (float) 1;
    (float) "hi"; // error

    /* test for R8 */
    'a' & 1; // int
    "hi" & 1; // error

    /* test for R9 */
    1 + 3; // int
    1.2 / 10; // float
    'a' - 1.2; // float
    'a' * 1; // int
    "hi" + 3; // error

    /* test for R10 */
    1 == 3; // char
    1.2 == 10; // char
    'a' == 1.2; // char
    'a' == 1; // char
    "hi" == 3; // error

    return 'c';
}

void f3() {
    // struct S2 s2;
    // s2.s1.a;
    const int b;
    int a;
    char c;
    float d;
    int arr[10];

    b; 
    b[10]; // error

    arr; // int[]
    arr['a']; // int
    arr[1]; // int
    arr["hi"]; // error

    /* test for r11, 12 */
    ++arr; // error
    ++b; // error
    b--; // error
    arr--; // error
    a++; // int
    c++; // char
    d++; // float
}

void f4() {
    const float a = 1, b = 1.2, c = 'a';
    float d;
    float a1 = "hi", b1 = "hi", c1 = "hi";
    a = 10; // error
    d = 1;
    d = 1.2;
    d = 'a';
}

float f5(int a) {
    a += 'x';
    return a;
}

void f6() {
    f5('a');
    (1>2)?3:4;
}

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




