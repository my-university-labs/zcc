int main() {
  int b = 1;
  int a = 10;
  while (a--) {
    if (a && b) {
      break;
    } else {
      continue;
    }
    while (1) {
      break;
    }
  }
  do {
    while (1)
      continue;
  } while (1);
  return 0;
}