#include <stdio.h>
#include <unistd.h> // For usleep function (delays execution for animation effect)

// Function prototype to print the progress bar
void print_bar(int task_number, int progress);

int main() {
    // Array to track progress of each task, all start at 0%
    int task_progress[5] = {0, 0, 0, 0, 0};
    
    // Different speeds for each task (percentage increment per loop iteration)
    int task_speeds[5] = {8,7,6,4,3}; 
    
    int completed = 0; // Counter for completed tasks
    
    while (completed < 5) { // Continue looping until all tasks reach 100%
        printf("\033[H\033[J"); // Clear the console for smooth animation effect
        completed = 0; // Reset completed counter in each iteration
        
        for (int i = 0; i < 5; i++) {
            // If task is not yet completed, update its progress
            if (task_progress[i] < 100) {
                task_progress[i] += task_speeds[i]; // Increment progress by its speed
                
                // Ensure the progress does not exceed 100%
                if (task_progress[i] > 100) {
                    task_progress[i] = 100;
                }
            } else {
                completed++; // If task reaches 100%, count it as completed
            }
            
            // Print the updated progress bar for the task
            print_bar(i + 1, task_progress[i]);
        }
        
        sleep(1); // Small delay for animation effect (100 milliseconds)
    }
    
    return 0; // Program ends when all tasks are completed
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
