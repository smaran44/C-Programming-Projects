#include <stdio.h>

void print_bar(int task_number , int progress);

int main() {

    
   return 0;
}

void print_bar(int task_number , int progress) {

 const int max_bar_length = 50;
   
    int bars_to_show = (progress * max_bar_length) / 100;

    printf("Task %d: [", task_number);

    for (int i = 0; i < max_bar_length; i++) {
        
        if (i< bars_to_show) {
            printf("=");
        } else {
            printf(" ");
        }
    }

    printf("] %d%%\n", progress);//%% → Prints a literal % symbol.

}
