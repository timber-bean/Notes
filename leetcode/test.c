#include <stdio.h>

union Da
{
    /* data */
    long long int a;
    float b;
}x;


int main(void) {
    x.a = 4,503,599,621,079,039;
    printf("%f\n",x.b);
    printf("%d\n",x.a);
    int j = 536870911;
    printf("%f\n",j);
    return 0;
}