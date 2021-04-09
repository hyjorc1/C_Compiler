int x = 1, y;

// int m1() {
//     return 0;
// }

int main1(int a, char b, float c) {
    // b = 'a';
    // c = (float) 1.0;
    // a = m1();
    // a = getchar();
    // a = putchar(0);
    // x = a;
    // a = x;
    // int d = 10, e = 1;
    // a = d;
    a = (int) c;
    b = (char) a;
    c = (float) a;
    return a;
}

int main() {
    return main1(10, 'a', 1.0);
}

