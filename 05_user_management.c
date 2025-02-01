#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    //Declare a user struct and open a file
    User newuser;
    File *file = fopen("users.txt", "a+")
    //"a+" allows appending new users while also enabling reading of existing users.

    //check if the file opened successfully
    if (file == NULL) {
    printf("Error registering data!\n");
    return;
    }

    //Get the username from the user
    printf("Enter Username : ");
    fgets("newuser.username, 50, stdin");
    //fgets() is used to read a string from the user (up to 50 characters).
    newuser.username[strcspn(newuser.username, "\n")] = 0; // Remove newline
    //strcspn(newUser.username, "\n") finds the index of the newline character (\n) in the string.
    //newUser.username[strcspn(newUser.username, "\n")] = 0; replaces the newline with \0 (null terminator) to remove unwanted newlines.

    // Get the Password from the User
    printf("Enter password: ");
    fgets(newuser.password, 50, stdin);
    newuser.password[strcspn(newuser.password, "\n")] = 0; // Remove newline

    //Check if the Username Already Exists
    User existinguser;
    rewind(file); 
    // Move file pointer to the beginning so we can read existing user data
    
    //The while loop reads each username and password pair from users.txt
    while (fscanf(file, "%s %s", existinguser.username, existinguser.password) != EOF) {
    if (strcmp(existinguser.username, newuser.username) == 0) {
        printf("Username already exists! Try again.\n");
        fclose(file);
        return;
    }
 }

   //Store the New User's Credentials in the File
    fprintf(file, "%s %s\n", newUser.username, newUser.password);

   //Close the File and Confirm Registration
   fclose(file);
   printf("Registration successful!\n");


}

void login_user() {
    printf("hello\n");
}