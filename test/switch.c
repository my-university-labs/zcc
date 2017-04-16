int main() {
  int a = 10;
  switch (a) {
  case 1:
    break;
  case 2:
    a = 10;
  case 3:
  case 4:
  case 5:
  default:
    a = a + 5;
  }
  return 0;
}