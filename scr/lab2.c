#include <stdio.h>
#include <stdlib.h>
#include <../include/lab2.h>
#include <../include/add.h>

void lab2()
{
    float s;
    float a;
    float x;
    float b;
    float eps;
    float c;
    int sign;
    int i;
    printf("eps=");
    scanf("%f", &eps);
    printf("x=");
    scanf("%f", &x);
    s=0;
    sign=1;
    i=0;
    c=x;
    b=1;
    a=c/b;
    while(a>eps) {
        s=s+a*sign;
        sign=-sign;
        c=c*x;
        b=b+1;
        a=c/b;
        i=i+1;
    }
    printf("n=%d, s=%f\n", i, s);
    return 0;
}
