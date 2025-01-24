// GUESS THE NUMBER
// This program is a simple guess the number where the player attempts to guess a randomly generated number between 1 and 100.
// The game provides feedback on whether the player's guess is too high, too low, or correct.
// The player can continue guessing until they find the correct number, and the program keeps track of the number of attempts.
// The game ends with a congratulatory message and displays the total number of guesses taken.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){

int generated,guess;
int no_of_guesses = 0;

srand(time(0)); //this will generate random number

//The line generated = rand() % 101; generates a number between 0 and 100, inclusive. However, your prompt suggests the range should be between 1 and 100. To fix this:
generated = (rand() % 100) + 1; //this will generate random number between 1 to 100

printf("Welcome to Guess the Number\n");

//here we use do while loop 
//For Loop	When you know the exact number of iterations beforehand.	Before each iteration.
//While Loop	When the number of iterations depends on a runtime condition.	Before each iteration.
//Do-While Loop	When you need the loop body to execute at least once, even if the condition is false initially.	After each iteration.

do {
    printf("Enter the number between (1 to 100) : ");
    scanf("%d", &guess);
    no_of_guesses++;


    if  (guess < generated) {
        printf("Your guess is too low.\n");
    } else if (guess > generated) {
        printf("Your guess is too high.\n");
    } else {
        printf("Congratulations you guessed the right number in %d attempts.\n", no_of_guesses);
    }


} while (guess != generated); //the loop should not stop upto guess is equal to generated

   
   printf("Thanks for playing\nDeveloped by Smaran Yanapu");

       return 0;
}