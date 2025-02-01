#include <stdio.h>

int main() {

    int option;

    while (1) {

    printf("\nWelcome to User Management");
    printf("\n1. Register");
    printf("\n2. Login");
    printf("\n3. Exit");

    printf("\nSelect an option : ");
    scanf("%d" , &option);

    switch (option) {

        case 1:
        break;

        case 2:
        break;

        case 3:
        printf("\nExiting Program");
        break;

        default:
        printf("\nInvalid option. Please try again.");
        break;

    }


    }

    return 0;
}