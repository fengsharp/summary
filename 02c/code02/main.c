// int sub(int a, int b)
// {
//     return a-b;
// }

// int main()
// {
//     int ret = sub(3, 2);
//     return 0;
// }

void change(int a, int b)
{
    int c = a;
    a = b;
    b = c;
}

int main()
{
    int a = 3;
    int b = 2;
    change(a, b);
    return 0;
}