
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
    int i = 4, j = 0;
    while (i) {
        i--;
        j++;
    }
    putchar(j + 48); // 4
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
    for (i = 5; i; i--) {
        j++;
    }
    
    putchar(j + 48); // 5
    putchar(10);
}

void ternary_exp() {
    int i = 0 ? 2 : (0 ? 3 : 4); // 4
    int j = 1 ? (1 ? 2 : 0) : 3; // 2
    putchar(i + j + 48); // 6
    putchar(10);
}


void break_stmt1() {
    int i = 3;
    while (i) {
        i--;
        while(i) {
            i--;
            if (1) {
                i = 2;
                if (1) {
                    i = 3;
                    break;
                } else {
                    i = 4;
                    break;
                }
            } else {
                break;
            }
        }
        break;
    }
    putchar(i + 48); // 3
    putchar(10);
}

void break_stmt2() {
    int i = 3;
    do {
        i--;
        break;
    } while(i);
    putchar(i + 48); // 2
    putchar(10);
}

void break_stmt3() {
    int i;
    for (i = 2; i; i--) {
        i++;
        break;
    }
    putchar(i + 48); // 3
    putchar(10);
}

void continue_stmt1() {
    int i = 3;
    while (i) {
        i--;
        continue;
        i = 1;
    }
    putchar(i + 48); // 0
    putchar(10);
}

void continue_stmt2() {
    int i = 3;
    do {
        i--;
        continue;
        i = 1;
    } while (i);
    putchar(i + 48); // 0
    putchar(10);
}

void continue_stmt3() {
    int i;
    for (i = 3; i; i--) {
        continue;
        i = 2;
    }
    putchar(i + 48); // 0
    putchar(10);
    return 0;
}

void cmp_exp1() {
    int i = 0;
    if (i == 0) {
        i = 3;
    }
    putchar(i + 48); // 3
    putchar(10);
}

void cmp_exp2() {
    int i = 0;
    if (i != 0) {
        i = 3;
    }
    putchar(i + 48); // 0
    putchar(10);
}

void cmp_exp3() {
    int i = 1;
    if (i >= 0) {
        i = 3;
    }
    putchar(i + 48); // 3
    putchar(10);
}

void cmp_exp4() {
    int i = 1;
    if (i > 1) {
        i = 3;
    }
    putchar(i + 48); // 0
    putchar(10);
}

void cmp_exp5() {
    int i = 1;
    if (i <= 0) {
        i = 3;
    }
    putchar(i + 48); // 1
    putchar(10);
}

void cmp_exp6() {
    int i = 1;
    if (i < 1) {
        i = 3;
    }
    putchar(i + 48); // 1
    putchar(10);
}

void or_exp() {
    int i = 4;
    if (i <= 2 || i >= 5 || i == 3) {
        i = 0;
    }
    putchar(i + 48); // 4
    putchar(10);
}

void not_exp() {
    int i = 4;
    if (!(i < 2)) {
        i = 0;
    }
    putchar(i + 48); // 0
    putchar(10);
}

void and_exp() {
    int i = 15;
    if (i % 3 == 0 && i % 5 == 0) {
        i = 0;
    }
    putchar(i + 48); // 0
    putchar(10);
}

void short_circuiting() {
    // if
    int i = 1;
    if (i > 0 && (i == 1 || i == 2)) {
        i = 3;
    }
    putchar(i + 48); // 3
    putchar(10);

    // if else
    i = 0;
    if (i > 1 || i) {
        i = 1;
    } else {
        i = 3;
    }
    putchar(i + 48); // 3
    putchar(10);

    // ternary
    i = 3;
    i = (i > 0 && (i == 1 || i == 2)) ? 3 : 4;
    putchar(i + 48); // 4
    putchar(10);

    i = 8;
    if (i == 0 || i != 1 || i > 1 || i >= 4 || i < 5 || i <= 6)
        i = 4;
    putchar(i + 48); // 4
    putchar(10);

    // while
    i = 8;
    while (i > 0 && i < 5) {
        i--;
    }
    putchar(i + 48); // 8
    putchar(10);

    // do while
    i = 8;
    do {
        i--;
    } while (i > 0 && i < 5);
    putchar(i + 48); // 7
    putchar(10);

    // for
    for (i = 2; i >= 2 && i <= 5; i++) {
        putchar(i + 48); // 2345
    }
    putchar(10);
}

int f() {
    int i = 8;
    if (1)
        return 10 - --i;
    return 4;
}

int main() {
    putchar(f() + 48); // 3
    putchar(10);
    return 0;
}


