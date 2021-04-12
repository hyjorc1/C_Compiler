
void fn() {}
int zero() { return 0; }

int main() {
    int x;
    x = zero();
    return zero() + zero() + 1; // 1
}
