int x[10];

int main() {
    x[0] = 0;
    x[1] = 1;
    x[0] = ++x[1]; // [2, 2];
    return x[0] + x[1];  // 4
}
