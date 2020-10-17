#include <stdio.h>

double potencia(double a, int n)
{
    double ret = a;

    for (int i = n; i > 1; i/=2)
    {
        ret *= ret;
    }

    if (n % 2 != 0)
    {
        ret *= a;
    }

    return ret;
    
}

int main(void)
{
    double a, result;
    int n;

    scanf(" %lf %d", &a, &n);
    result = potencia(a, n);

    printf("%lf\n", result);
    
    return 0;
}
