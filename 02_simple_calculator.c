#include <stdio.h>
#include <math.h> // Required for pow()
//math.h is a header file in the standard library of the C programming language designed for basic mathematical operations.

void print_menu() {
    printf("\nWelcome to Simple Calculator\n");
    printf("\nChoose one of the following options : \n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");//Modulus operator returns the remainder of the division of two numbers.
    printf("6. Power\n");
    printf("7. Exit\n");
}

int main() {
    

    int choice;
    double num1, num2, result; 
    // double is used to store floating point numbers with double precision.
    

    while(1) { // (1) is always true, so the loop runs indefinitely until a break statement is encountered


    // in guess the game the loop is do while loop because it should not stop upto guess is equal to generated
    // here we use while loop because we have to run the program until the user wants to exit

    print_menu();
    
    printf("\nEnter your choice : ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7) { // Check if the choice is valid
    printf("Invalid choice! Please select a number between 1 and 7.\n");
    continue; // Skip the rest of the loop and show the menu again
    }

    if (choice == 7) {
        printf("Thank you for using the calculator\n");
        break;
    }
    printf("Please enter the first numbere : ");
    scanf("%lf", &num1);//lf is used to read double data type.

    printf("Please enter the second number : ");
    scanf("%lf", &num2);//lf is used to read double data type.

     switch (choice) {
    
        case 1: //Addition
            result = num1 + num2;
            printf("The sum of %.2lf and %.2lf is %.2lf\n", num1, num2, result);
            break;
        case 2: //Subtraction
            result = num1 - num2;
            printf("The difference of %.2lf and %.2lf is %.2lf\n", num1, num2, result);
            break;
        case 3: //Multiplication
            result = num1 * num2;
            printf("The product of %.2lf and %.2lf is %.2lf\n", num1, num2, result);
            break;
        case 4: //Division
            if (num2 != 0) {
                result = num1 / num2;
                printf("The division of %.2lf by %.2lf is %.2lf\n", num1, num2, result);
            } else {
                printf("Error: Division by zero is not allowed\n");
            }
            break;
        case 5: //Modulus
            if (num2 != 0) {
                result = (int)num1 % (int)num2;
                printf("The remainder of %d divided by %d is %d\n", (int)num1, (int)num2, (int)result);
                // modulus operator can only be used with integers
                // so we have to typecast the numbers to integers
                // if we enter 15.23 as num1 it will be converted to 15
                // if we enter 4.56 as num2 it will be converted to 4
            } else {
                printf("Error: Modulus by zero is not allowed\n");
            }
            break;
        case 6: //Power
            result = pow(num1, num2);
            if (num1 < 0 && num2 != (int)num2) {
                // Negative base with non-integer exponent is not supported
               printf("Error: Negative base with non-integer exponent is not supported.\n");
         } else { 
              result = pow(num1, num2);
               printf("%.2lf raised to the power of %.2lf is %.2lf\n", num1, num2, result);
    }

            break;
        default:
            printf("Invalid choice\n");

            //here we use default because if the user enters the choice other than 1 to 7 then it will print invalid choice
            //but it will print it after entering the two numbers
            // so we have to done it before entering the numbers
            // so we done if and continue after entering choice

    }
    
    }

    return 0;
}