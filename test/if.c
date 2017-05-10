int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    if (a > b || c < d) {
        a = b + c;
    } else if (b > d) {
        c = 3;
    } else {
        c = 4;
    }
    a = 2;
    return 0;
}