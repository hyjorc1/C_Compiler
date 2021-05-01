

int main() {
    int i;
    for (i = 3; i; i--) {
        continue;
        i = 2;
    }
    putchar(i + 48); // 0
    putchar(10);
    return 0;
}




