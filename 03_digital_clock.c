#include<stdio.h>
#include<time.h>//time.h is a header file in the C standard library for the C programming language that contains time and date function declarations to provide standardized access to time/date manipulation and formatting.
#include <unistd.h> // For sleep() function
#include <stdlib.h> // For system()

void displayTime12Hour();

void displayTime24Hour();

int main () {

    int choice;

    printf("choose the time format : \n"); 
    printf("1. 12 Hour format\n");
    printf("2. 24 Hour format\n");
    printf("Make a choice (1 or 2) : ");
    scanf("%d",&choice);

    if (choice == 1) {
        displayTime12Hour();
    } else if (choice == 2) {
        displayTime24Hour();
    } else {
        printf("Invalid choice. Exiting program.\n");
    }

   return 0;
}

void displayTime12Hour(){

    while (1) { // Infinite loop to keep the clock running

    time_t raw_time;
    struct tm *current_time;
    // Here we used a pointer because the localtime function returns a pointer to a tm structure
    char buffer[100];
    
    time(&raw_time);
    current_time = localtime(&raw_time);

    // Clear the screen before printing the updated time
    system("cls");
    //system("clear"); // For Linux/macOS

    //localtime is a function from library time.h
    // Convert the raw time to local time structure

    // Format time into a human-readable string
    // %A - Full weekday name
    // %B - Full month name
    // %d - Day of the month (01-31)
    // %Y - Year
    // %H - Hour (01-24)
    // %I - Hour (01-12)
    // %M - Minutes (00-59)
    // %S - seconds (00-59)
    // %p - AM/PM notation
    strftime(buffer, sizeof(buffer), "Current Time : %I:%M:%S %p", current_time);

    printf("%s\n", buffer);

    strftime(buffer, sizeof(buffer), "Date : %B %d %Y", current_time);

    printf("%s\n", buffer);

    strftime(buffer, sizeof(buffer), "Day : %A", current_time);

    printf("%s\n", buffer);

    fflush(stdout);
    //fflush(stdout) is used to manually flush the output buffer, ensuring that any buffered output is printed immediately to the screen.
    
    sleep(1); // Pause for 1 second

}

}

void displayTime24Hour(){

    while (1) { // Infinite loop to keep the clock running

    time_t raw_time;
    struct tm *current_time;
    // Here we used a pointer because the localtime function returns a pointer to a tm structure
    char buffer[100];
    
    time(&raw_time);
    current_time = localtime(&raw_time);

    // Clear the screen before printing the updated time
    system("cls");
    //system("clear"); // For Linux/macOS

    // Format time into a human-readable string
    // %A - Full weekday name
    // %B - Full month name
    // %d - Day of the month (01-31)
    // %Y - Year
    // %H - Hour (01-24)
    // %I - Hour (01-12)
    // %M - Minutes (00-59)
    // %S - seconds (00-59)
    // %p - AM/PM notation
  strftime(buffer, sizeof(buffer), "Current Time : %H:%M:%S", current_time);

  printf("%s\n", buffer);

   strftime(buffer, sizeof(buffer), "Date : %B %d %Y", current_time);

    printf("%s\n", buffer);

   strftime(buffer, sizeof(buffer), "Day : %A", current_time);

    printf("%s\n", buffer);

    fflush(stdout);

        sleep(1); // Pause for 1 second

}

}

