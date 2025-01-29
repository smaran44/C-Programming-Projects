#include<stdio.h>
#include<time.h>//time.h is a header file in the C standard library for the C programming language that contains time and date function declarations to provide standardized access to time/date manipulation and formatting.

void displayTime12Hour();

void displayTime24Hour();

int main () {

    int choice;

    printf("choose the time format : \n"); 
    printf("1. 24 Hour format\n");
    printf("2. 12 Hour format\n");
    printf("Make a choice (1 or 2) : ");
    scanf("%d",&choice);

    if(choice == 1){
        displayTime24Hour();
    }

     if(choice == 2){
        displayTime12Hour();
    }


   return 0;
}

void displayTime12Hour(){
    time_t raw_time;
    struct tm *current_time;
    // Here we used a pointer because the localtime function returns a pointer to a tm structure
    char buffer[100];
    
    time(&raw_time);
    current_time = localtime(&raw_time);
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

}

void displayTime24Hour(){

    time_t raw_time;
    struct tm *current_time;
    // Here we used a pointer because the localtime function returns a pointer to a tm structure
    char buffer[100];
    
    time(&raw_time);
    current_time = localtime(&raw_time);
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

  strftime(buffer, sizeof(buffer), "Current Time : %H:%M:%S", current_time);

  printf("%s\n", buffer);

   strftime(buffer, sizeof(buffer), "Date : %B %d %Y", current_time);

    printf("%s\n", buffer);

   strftime(buffer, sizeof(buffer), "Day : %A", current_time);

    printf("%s\n", buffer);

}

