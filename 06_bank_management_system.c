#include <stdio.h>
#include <string.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

typedef struct {
    char name[50];
    int acc_no;
    float balance;
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

void create_account(){

   //Declare a user struct and open a file
    Account acc;
    FILE *file = fopen("accounts.txt", "a+");
    //"a+" allows appending new users while also enabling reading of existing users.

    //check if the file opened successfully
    if (file == NULL) {
    printf("Error creating account!\n");
    return;
    }

    //Get the username from the user
    printf("\nEnter Username : ");
    fgets(acc.name, sizeof(acc.name), stdin);
    //fgets() is used to read a string from the user (up to 50 characters).
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline
    //strcspn(acc.name, "\n") finds the index of the newline character (\n) in the string.
    //acc.name[strcspn(acc.name, "\n")] = 0; replaces the newline with \0 (null terminator) to remove unwanted newlines.

    printf("Enter your account number : ");
    scanf("%d", &acc.acc_no);
    // account number is just an integer so we can use scanf

    acc.balance = 0;

    //Store the Credentials in the File
    fprintf(file, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);


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
    Account acc;

    FILE *temp = fopen("temp.txt", "w");
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    while (fscanf(file, "%s %d %f", acc.name, &acc.acc_no, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            acc.balance += amount;
            found = 1;
        }
        fprintf(temp, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);
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
    Account acc;
    FILE *temp = fopen("temp.txt", "w");
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    while (fscanf(file, "%s %d %f", acc.name, &acc.acc_no, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                found = 1;
            } else {
                printf("Insufficient balance!\n");
                found = -1;
            }
        }
        fprintf(temp, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);
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

    int acc_no;
    printf("Enter your account number : ");
    scanf("%d", &acc_no);


     //Search for Matching Credentials
   int found = 0;
     while (fscanf(file, "%s %d %f", acc.name, &acc.acc_no, &acc.balance) != EOF) {
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