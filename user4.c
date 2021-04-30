

int main() {
    int i = 0 ? 2 : (0 ? 3 : 4); // 4
    int j = 1 ? (1 ? 2 : 0) : 3; // 2
    putchar(i + j + 48); // 6
    putchar(10);
    return 0;
}


