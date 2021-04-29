

int main() {
    int i = 0;
    if (i) {
        if (i - 1) {
            i = 2;
        } else {
            i = 4;
        }
    }
    putchar(i + 48);
    putchar(10);
    return i;
}

void if_stmt() {
    int i = 1;
    if (i) {
        i = 2;
    }
    putchar(i + 48);
    putchar(10);
}

void if_else_stmt() {
    int i = 1;
    if (i) {
        if (i - 1) {
            i = 2;
        } else {
            i = 4;
        }
    } else {
        i = 3;
    }
    putchar(i + 48);
    putchar(10);
}
