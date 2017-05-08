int main() {
  int z[20];
  int a = 1, b = 2;
  int c = a + b;
  int d = a - b;
  int e = c * d;
  a = e + e;
  a = z[11] + 1;
  z[11] = 2;
  z[2] = 5;
  a = z[11] + z[2];
  a = z[11] + 1;
  d = a * c;
  if (a && b) {
    ;
  }
  return 0;
}