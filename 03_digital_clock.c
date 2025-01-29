#include<stdio.h>
#include<time.h>//time.h is a header file in the C standard library for the C programming language that contains time and date function declarations to provide standardized access to time/date manipulation and formatting.

void displayTime12Hour();

void displayTime24Hour();

int main () {

    displayTime12Hour();
    displayTime24Hour();

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

}

