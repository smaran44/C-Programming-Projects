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

    while (getchar() != '\n'); // Flush input buffer
    //without this Enter Username : Enter password:  these types of errors will come
    
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
    FILE *file = fopen("users.txt", "a+");
    //"a+" allows appending new users while also enabling reading of existing users.

    //check if the file opened successfully
    if (file == NULL) {
    printf("Error registering data!\n");
    return;
    }

    //Get the username from the user
    printf("Enter Username : ");
    fgets(newuser.username, 50, stdin);
    //fgets() is used to read a string from the user (up to 50 characters).
    newuser.username[strcspn(newuser.username, "\n")] = 0; // Remove newline
    //strcspn(newUser.username, "\n") finds the index of the newline character (\n) in the string.
    //newuser.username[strcspn(newuser.username, "\n")] = 0; replaces the newline with \0 (null terminator) to remove unwanted newlines.

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
   fprintf(file, "%s %s\n", newuser.username, newuser.password);


   //Close the File and Confirm Registration
   fclose(file);
   printf("Registration successful!\n");


}

void login_user() {
    
     //Declare variables
     char username[50], password[50];
     //username and password arrays are declared to store the user input for login.
     User storedUser;
     //storedUser is a User structure to store the username and password read from the file.
     FILE *file = fopen("users.txt", "r");
     //The file users.txt is opened in read (r) mode

     //Check if the File Opened Successfully
     if (file == NULL) {
    printf("No registered users found. Please register first.\n");
    return;
    }

    //Get the Username and Password from the User
    printf("Enter username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline


   //Search for Matching Credentials
   int found = 0;
//A variable found is initialized to 0, which will indicate whether the username and password match.
   while (fscanf(file, "%s %s", storedUser.username, storedUser.password) != EOF) {
    if (strcmp(username, storedUser.username) == 0 && strcmp(password, storedUser.password) == 0) {
        found = 1;
        break;
    }
 }

 //Close the File
     fclose(file);


     //Check If the Credentials Were Found
     if (found) {
    printf("Login successful! Welcome, %s\n", username);
 } else {
    printf("Invalid username or password. Please try again.\n");
 }

}