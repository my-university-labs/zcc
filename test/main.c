int main()
{
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    b = b + c;
    c = c + d;
    while (a < 10) {
        c = c + 1;
        a = a + 1;
    }
    if (a > b) {
        b = a;
    } else if (a < b) {
        a = b;
    } else {
        a = b + 1;
    }
    for (c = 2; c < 10; c = c + 1) {
        b = b + 3;
    }
    return 0;
}