#include <stdio.h>

int main()
{
    int n, i, x;
    long int mult = 1;
    (void)scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        (void)scanf("%d", &x);
        mult *= x;
    }
    printf("%ld", mult);
    return 0;
}