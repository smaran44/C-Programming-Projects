#include <stdio.h>


int main() {
    

    int choice;
    double num1, num2, result; 
    // double is a data type that can store decimal numbers with precision.
    

    do {
    printf("Welcome to Simple Calculator\n");
    printf("\nChoose one of the following options : \n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    printf("7. Exit\n");
    
    printf("\nEnter your choice : ");
    scanf("%d", &choice);
    } while (choice != 7);
}
