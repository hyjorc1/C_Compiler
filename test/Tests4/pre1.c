int x = 1;

int main() {
    int y = 0;
    y -= ++x; // y = -2, x = 2
    y += --x; // y = -1, x = 1

    return y -= x + ++y; // -2
}
