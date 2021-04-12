
int fn(int x, char y, char arr[]) {
    return x + y + arr[2]; // 148
}

int main() {
  return fn(1, '0', "abc"); // 1 + 48 + [97, 98, 99]
}
