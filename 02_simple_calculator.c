#include <stdio.h>

void print_menu() {
    printf("Welcome to Simple Calculator\n");
    printf("\nChoose one of the following options : \n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    printf("7. Exit\n");
}

int main() {
    

    int choice;
    double num1, num2, result; 
    // double is used to store floating point numbers with double precision.
    

    while {
    print_menu();
    
    printf("\nEnter your choice : ");
    scanf("%d\n", &choice);

    if (choice == 7) {
        printf("Thank you for using the calculator\n");
        break;
    }
    printf("Please enter the first numbere : ");
    scanf("%lf", &num1);//lf is used to read double data type.

    printf("Please enter the second number : ");
    scanf("%lf", &num2);//lf is used to read double data type.

    }
}