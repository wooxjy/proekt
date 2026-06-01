#include <stdio.h>
#include "include/lab1.h"
#include "include/lab2.h"
#include "include/lab3.h"
#include "include/lab4.h"
#include "include/lab5.h"
#include "include/lab6.h"

void show_menu(){
printf("\n-----labs-----\n");
printf("1. lab 1\n");
printf("2. lab 2\n");
printf("3. lab 3\n");
printf("4. lab 3 (add)\n");
printf("5. lab 4\n");
printf("6. lab 4 (add)\n");
printf("7. lab 5\n");
printf("8. lab 5 (add)\n");
printf("9. lab 6\n");
printf("0. exit\n");
printf("choose number: ");
}
int main() {
   int choice;
    do {
    show_menu();
    scanf("%d", &choice);
    while (getchar() != '\n');
    switch(choice){
    case 1: lab1(); break;
    case 2: lab2(); break;
    case 3: lab3(); break;
    case 4: lab3_add(); break;
    case 5: lab4(); break;
    case 6: lab4_add(); break;
    case 7: lab5(); break;
    case 8: lab5_add(); break;
    case 9: lab6(); break;
    case 0: printf ("exit\n"); break;
    default: printf("error\n");
    }
   } while (choice != 0);
return 0;
}
