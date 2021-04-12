int x = 1;

int main() {
    int y = 0;
    int z = y++ + --x; // 0, 1, 0
    return x + y + z; // 1
}
