int i1 = 1, i2 = 2;
char c1 = 'a', c2 = 'b';
float f1 = 2.1, f2 = 2.2;

int main() {
    int li1 = 1, li2 = 2;
    char lc1 = 'a', lc2 = 'b';
    float lf1 = 2.1, lf2 = 2.2;

    int s1 = i1 + (int) c1 + (int) f1; // 1 + 97 + 2 = 100
    int s2 = li1 + (int) lc1 + (int) lf1;
    int s3 = li1 + (int) c1 + (int) lf1;

    s1 = 10 / 2 - 10 % 5 + 3 * 3; // 14
    s2 = 1 * 2 + 4 / 2; // 4

    return s1 + s2; // 18
}