int main() {
  int i;
  for (i = 0; i < 10; ++i) {
    int j;
    for (j = i; j < 10; ++j) {
      break;
    }
  }
  return 0;
}