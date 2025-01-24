// NUMBER GUESSING GAME

#include <stdio.h>



int main(){

int generated, guess,;
int no_of_guesses = 0;

printf("Welcome to the game of guessing numbers\n");

//here we use do while loop 
//For Loop	When you know the exact number of iterations beforehand.	Before each iteration.
//While Loop	When the number of iterations depends on a runtime condition.	Before each iteration.
//Do-While Loop	When you need the loop body to execute at least once, even if the condition is false initially.	After each iteration.

do {
    printf("Enter the number between (1 to 100) : ")
    scanf("%d", &guess)
    no_of_guesses++;


    if  (guess < generated) {
        printf("You guessed smaller number.\n")
    } else if (guess > generated) {
        printf("You guessed larger number.\n")
    } else {
        printf("Congratulations you guessed the right number in %d attempts.\n, no_of_guesses")
    }


} while (guess != generated); //the loop should not stop upto guess is equal to generated

   
   printf("Thanks for playing\nDeveloped by Smaran Yanapu")

        return 0;
}