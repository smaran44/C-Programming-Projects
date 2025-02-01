#include <stdio.h>

typedef struct {
  // data
  char username[50];
  char password[50];

} User;

void register_user();
void login_user();

int main() {

    int option;

    while (1) {

    printf("\nWelcome to User Management\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

    printf("Select an option : ");
    scanf("%d" , &option);

    switch (option) {

        case 1:
        register_user();
        break;

        case 2:
        login_user();
        break;

        case 3:
        printf("Exiting Program\n");
        return 0; // Exits the program
        break;

        default:
        printf("Invalid option. Please try again.\n");
        break;

    }


    }

    return 0;
}

void register_user() {
    printf("hi\n");
}

void login_user() {
    printf("hello\n");
}