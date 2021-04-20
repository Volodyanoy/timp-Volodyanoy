#include <stdio.h>

int main()
{
    int n, x, count = 0, i;
    (void)scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        (void)scanf("%d", &x);
        if (x >= 0)
            count++;
    }
    printf("%d", count);
    return 0;
}