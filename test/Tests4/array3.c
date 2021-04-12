int x[10];

int sum(int x[]) {
    return x[0] + x[1] + x[2];
}

int main() {
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    x[0] *= x[1] += x[2] -= 1; // [0, 2, 1]
    return sum(x); // 3
}
