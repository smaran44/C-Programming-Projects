#include <stdio.h>
#include <string.h>
#include <conio.h> // For getch() in Windows

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

void masked_password(char *password, int max_length);

typedef struct {
    char name[50];
    int acc_no;
    float balance;
    char password[20];
}Account;

int main() {

    int choice;

    while (1) {

        printf("\n***Bank Management System***\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");

        printf("Enter your choice : ");
        scanf("%d" , &choice);

        while (getchar() != '\n'); // Flush input buffer
     //without this Enter Username : Enter password:  these types of errors will come
    
        

    switch (choice) {

        case 1:
        create_account();
        break;
        
        case 2:
        deposit_money();
        break;

        case 3:
        withdraw_money();
        break;

        case 4:
        check_balance();
        break;

        case 5:
        printf("Closing the Bank, Thanks for your visit.\n");
        return 0; //exit program
        break;

        default:
        printf("Invalid Choice. Please try again.\n");
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

int authenticate(int acc_no, char *input_password) {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) return 0;
    Account acc;
    while (fscanf(file, "%s %d %f %s", acc.name, &acc.acc_no, &acc.balance, acc.password) != EOF) {
        if (acc.acc_no == acc_no && strcmp(acc.password, input_password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
/*return 1;
If the account number and password match, it means authentication was successful.
The function returns 1 to indicate the user is authorized.
After finding a match, the function closes the file and exits immediately, skipping further checks.

return 0;
If no matching record is found, it means authentication failed.
The function reaches the end of the file without finding a match, so it returns 0, indicating the user is not authorized.*/


void create_account(){

   //Declare a user struct and open a file
    Account acc;
    char confirm_password[50]; // For password confirmation
    FILE *file = fopen("accounts.txt", "a+");
    //"a+" allows appending new users while also enabling reading of existing users.

    //check if the file opened successfully
    if (file == NULL) {
    printf("Error creating account!\n");
    return;
    }

    //Get the username from the user
    printf("Enter Username : ");
    fgets(acc.name, sizeof(acc.name), stdin);
    //fgets() is used to read a string from the user (up to 50 characters).
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline
    //strcspn(acc.name, "\n") finds the index of the newline character (\n) in the string.
    //acc.name[strcspn(acc.name, "\n")] = 0; replaces the newline with \0 (null terminator) to remove unwanted newlines.

    printf("Enter your account number : ");
    scanf("%d", &acc.acc_no);
    // account number is just an integer so we can use scanf

     //Check if the Username Already Exists
    Account existing_acc;
    rewind(file); 
    // Move file pointer to the beginning so we can read existing user data

     while (fscanf(file, "%s %d %f %s", existing_acc.name, &existing_acc.acc_no, &existing_acc.balance, existing_acc.password) != EOF) {
        if (existing_acc.acc_no == acc.acc_no) {
            printf("Account number already exists! Try again.\n");
            fclose(file);
            return;
        }
    }


// Loop until the user enters matching passwords
    while (1) {
        printf("Enter password: ");
        masked_password(acc.password, sizeof(acc.password));

        printf("Confirm password: ");
        masked_password(confirm_password, sizeof(confirm_password));

        if (strcmp(acc.password, confirm_password) == 0) {
            break; // Passwords match, exit loop
        } else {
            printf("Passwords do not match! Please try again.\n");
        }
    }


    acc.balance = 0;

    //Store the Credentials in the File
     fprintf(file, "%s %d %.2f %s\n", acc.name, acc.acc_no, acc.balance, acc.password);


   //Close the File and Confirm Registration
   fclose(file);
   printf("Account created successfully!\n");

    
}

void deposit_money(){

/*No, the deposit_money() function cannot be done using "a+" (append mode) effectively. Here’s why:

Why "a+" (append mode) won’t work?
Appending adds data, not modifying existing data

"a+" mode allows reading and appending new data at the end of the file.*/

 FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("Error accessing account data!\n");
        return;
    }
    int acc_no, found = 0;
    float amount;
    char input_password[20];
    Account acc;

    FILE *temp = fopen("temp.txt", "w");
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    while (getchar() != '\n');

    printf("Enter your password: ");
    masked_password(input_password, sizeof(input_password));

     if (authenticate(acc_no, input_password) == 0) {
        printf("Invalid account number or password!\n");
        fclose(file);
        fclose(temp);
        return;
    }
 /*return exits the function immediately, preventing further execution.
  It ensures the function stops running when authentication fails.*/

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

     
    while (fscanf(file, "%s %d %f %s", acc.name, &acc.acc_no, &acc.balance, acc.password) != EOF) {
        if (acc.acc_no == acc_no) {
            acc.balance += amount;
            found = 1;
        }
        fprintf(temp, "%s %d %.2f %s\n", acc.name, acc.acc_no, acc.balance, acc.password);
    }

    fclose(file);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    if (found)
        printf("Amount deposited successfully!\n");
    else
        printf("Account not found!\n");

}

void withdraw_money(){
     FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("Error accessing account data!\n");
        return;
    }
    int acc_no, found = 0;
    float amount;
    char input_password[20];
    Account acc;
    FILE *temp = fopen("temp.txt", "w");
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    while (getchar() != '\n');

    printf("Enter your password: ");
    masked_password(input_password, sizeof(input_password));

     if (authenticate(acc_no, input_password) == 0) {
        printf("Invalid account number or password!\n");
        fclose(file);
        fclose(temp);
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    while (fscanf(file, "%s %d %f %s", acc.name, &acc.acc_no, &acc.balance, acc.password) != EOF) {
        if (acc.acc_no == acc_no) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                found = 1;
            } else {
                printf("Insufficient balance!\n");
                found = -1;
            }
        }
        fprintf(temp, "%s %d %.2f %s\n", acc.name, acc.acc_no, acc.balance, acc.password);
    }
    fclose(file);
    fclose(temp);
    if (found > 0) {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        printf("Amount withdrawn successfully!\n");
    } else if (found == 0) {
        printf("Account not found!\n");
    } 

}

void check_balance(){

 FILE *file = fopen("accounts.txt", "r");
     // we use read because just we are reading the balance of the account number

     //check if the file opened successfully
    if (file == NULL) {
    printf("Error checking balance!\n");
    return;
    }

    int acc_no, found = 0;
    float amount;
    char input_password[20];
    Account acc;

    printf("Enter your account number : ");
    scanf("%d", &acc_no);

    printf("Enter your password: ");
    masked_password(input_password, sizeof(input_password));

     if (authenticate(acc_no, input_password) == 0) {
        printf("Invalid account number or password!\n");
        fclose(file);
        return;
    }


     //Search for Matching Credentials
     while (fscanf(file, "%s %d %f %s", acc.name, &acc.acc_no, &acc.balance, acc.password) != EOF) {
        if (acc.acc_no == acc_no) {
    /*acc.acc_no refers to the account number stored in the Account structure while reading from the file.
acc_no is the account number entered by the user when performing a transaction (deposit, withdraw, or checking balance).*/
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    
    fclose(file);

    if (!found){
        printf("Account No: %d not found!\n", acc_no);
    }

}