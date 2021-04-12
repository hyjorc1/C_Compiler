
char fn(int x, char y, char arr[]) {
    return (char) ('b' - 'a'); // 1
}

int main() {
  return fn(1, '0', "abc"); // 1 + 48 + [97, 98, 99]
}
