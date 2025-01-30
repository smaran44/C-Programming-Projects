#include <stdio.h>

// Function prototype
void print_bar(int task_number, int progress);

int main() {
    
    // Display progress bars for five tasks
    print_bar(1, 25);
    print_bar(2, 50);
    print_bar(3, 75);
    print_bar(4, 90);
    print_bar(5, 100);
    
    return 0;
}

// Function to print a progress bar for a given task
void print_bar(int task_number, int progress) {
    const int max_bar_length = 50; // Maximum length of the progress bar
    
    int bars_to_show = (progress * max_bar_length) / 100; // Calculate filled portion of the bar

    printf("Task %d: [", task_number);

    // Print the progress bar
    for (int i = 0; i < max_bar_length; i++) {
        if (i < bars_to_show) {
            printf("="); // Filled portion
        } else {
            printf(" "); // Unfilled portion
        }
    }

    printf("] %d%%\n", progress); // Display percentage progress
}

