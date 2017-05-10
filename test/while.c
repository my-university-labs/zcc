int main() {
  int b = 1;
  int a = 10;
  while (a > b && b < a) {
    a = a + b;
    while (a < b) {
      b = a + b;
    }
    if (a > b)
      a = 2;
  }

  return 0;
}