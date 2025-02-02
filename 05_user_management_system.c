#include <stdio.h>
#include <string.h>
#include <conio.h> // For getch() in Windows

typedef struct {
  // data
  char username[50];
  char password[50];

} User;

void masked_password(char *password, int max_length);
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

// Function to take password input while masking it with '*'
void masked_password(char *password, int max_length) {
    int i = 0;  // Index to track the length of the password
    char ch;    // Variable to store user input character

    while (1) {
        ch = getch(); // Get character input without displaying it on the screen

        // If the user presses 'Enter' (ASCII 13), terminate input
        if (ch == 13) { 
            password[i] = '\0'; // Null-terminate the password string
            break; 
        }
        // if this is not there when we press enter it will also go into password

        // If the user presses 'Backspace' (ASCII 8), handle deletion
        else if (ch == 8) { 
            if (i > 0) {  // Ensure there are characters to delete
                i--;  
                printf("\b \b"); // Move cursor back, erase character, move back again
            }
        }
        // if this is not there when we press backspace it will also go into password

        // If the user types a valid character (within max length), store it
        else if (i < max_length - 1) { 
            password[i++] = ch;  // Store the character
            printf("*");  // Print '*' to mask the input
        }
    }
    printf("\n"); // Move to a new line after input completion
}

void register_user() {
    
    //Declare a user struct and open a file
    User newuser;
    char confirm_password[50]; // For password confirmation
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
    // Loop until the user enters matching passwords
    while (1) {
        printf("Enter password: ");
        masked_password(newuser.password, 49);

        printf("Confirm password: ");
        masked_password(confirm_password, 49);

        if (strcmp(newuser.password, confirm_password) == 0) {
            break; // Passwords match, exit loop
        } else {
            printf("Passwords do not match! Please try again.\n");
        }
    }


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
    masked_password(password, 49); // Masked password input


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