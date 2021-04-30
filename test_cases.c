
void if_stmt() {
    int i = 1;
    if (i) {
        i = 2;
    }
    putchar(i + 48); // 2
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
    putchar(i + 48); // 4
    putchar(10);
}

void while_stmt() {
    int i = 3, j = 0;
    while (i) {
        i--;
        j++;
    }
    putchar(j + 48); // 3
    putchar(10);
}

void do_stmt() {
    int i = 3, j = 0;
    do {
        i--;
        j++;
    } while (i);
    putchar(j + 48); // 3
    putchar(10);
}

void for_stmt() {
    int i, j = 0;
    for (i = 3; i; i--) {
        j++;
    }
    
    putchar(j + 48); // 3
    putchar(10);
}

