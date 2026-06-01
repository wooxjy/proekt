#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <../include/lab1.h>
#include <../include/add.h>

void lab1()
{
    setlocale(LC_ALL, "Russian");
    float a;
    float b;
    float c;
    float dis;
    float x1;
    float x2;
    float x;
    printf("a=");
    scanf("%f", &a);
    printf("b=");
    scanf("%f", &b);
    printf("c=");
    scanf("%f", &c);
    dis=b*b-4*a*c;
    if (dis>0) {
        x1=(-b+sqrt(dis))/(2*a);
        x2=(-b-sqrt(dis))/(2*a);
        printf("x1=%.2f, x2=%.2f", x1, x2);
    }
    if (dis==0) {
        x=-b/(2*a);
        printf("x=%.2f", x);
    }
    if (dis<0) {
        printf("Корней нет");
    }
    return 0;
}
