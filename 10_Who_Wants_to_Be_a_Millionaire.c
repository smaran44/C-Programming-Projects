#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

volatile int timeout_happened = 0;
HANDLE hConsole;

typedef struct {
    char text[MAX_QUES_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

int read_questions(char* file_name, Question** questions);
void print_formatted_question(Question question);
void play_game(Question* questions, int no_of_questions);
int use_lifeline(Question* question, int* lifeline);
DWORD WINAPI timeout_thread(LPVOID lpParam);
void set_console_color(int color);

int main() {
    srand(time(NULL));
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    set_console_color(13); // Pink
    printf("\t\tLet’s play Who Wants to Be a Millionaire!!!\n");
    set_console_color(7);  // Reset to default
    
    Question* questions;
    int no_of_questions = read_questions("question_bank.txt", &questions);
    play_game(questions, no_of_questions);
    
    free(questions);
    return 0;
}

void play_game(Question* questions, int no_of_questions) {
    int money_won = 0;
    int lifeline[] = {1, 1};

    for (int i = 0; i < no_of_questions; i++) {
        print_formatted_question(questions[i]);

        timeout_happened = 0;
        HANDLE hThread = CreateThread(NULL, 0, timeout_thread, &questions[i].timeout, 0, NULL);

        printf("\nYour answer: "); 
        fflush(stdout); // Ensure output is properly flushed

        char ch = _getch();  // Waits for user input
        TerminateThread(hThread, 0);
        CloseHandle(hThread);

        printf("\rYour answer: %c\n", ch);  // Correctly overwrites the line

        ch = toupper(ch);

        if (timeout_happened) {
            set_console_color(12); // Red
            printf("\nTime out!!!!! Press Any Key...\n");
            set_console_color(7);
            break;
        }

        if (ch == 'L') {
            int value = use_lifeline(&questions[i], lifeline);
            if (value != 2) {
                i--;  // Repeat the question if a lifeline is used
            }
            continue;
        }

        if (ch == questions[i].correct_option) {
            set_console_color(10); // Green
            printf("\nCorrect!\n");
            money_won = questions[i].prize_money;
            set_console_color(9); // Blue
            printf("\nYou have won: Rs %d\n", money_won);
        } else {
            set_console_color(12); // Red
            printf("\nWrong! Correct answer is %c.\n", questions[i].correct_option);
            break;
        }
        set_console_color(7);
    }
    set_console_color(9); // Blue
    printf("\n\nGame Over! Your total winnings are: Rs %d\n", money_won);
    set_console_color(7);
}



DWORD WINAPI timeout_thread(LPVOID lpParam) {
    int timeout = *(int*)lpParam;
    
    for (int i = timeout; i > 0; i--) {
        Sleep(1000);
        if (timeout_happened) return 0;

        printf("\rTime Remaining: %d seconds   ", i); // Overwrite the line
        fflush(stdout);
    }

    timeout_happened = 1;
    return 0;
}




int use_lifeline(Question* question, int* lifeline) {
    set_console_color(13); // Pink
    printf("\n\nAvailable Lifelines:\n");
    if (lifeline[0]) printf("1. Fifty-Fifty (50/50)\n");
    if (lifeline[1]) printf("2. Skip the Question\n");
    printf("Choose a lifeline or 0 to return: ");
    set_console_color(7);
    
    char ch = _getch();
    printf("%c\n", ch);

    switch (ch) {
    case '1':
        if (lifeline[0]) {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2) {
                int num = rand() % 4;
                if ((num + 'A') != question->correct_option &&
                    question->options[num][0] != '\0') {
                    question->options[num][0] = '\0';
                    removed++;
                }
            }
            return 1;
        }
        break;
    case '2':
        if (lifeline[1]) {
            lifeline[1] = 0;
            return 2;
        }
        break;
    default:
        set_console_color(13);
        printf("\nReturning to the Question.\n");
        set_console_color(7);
        break;
    }
    return 0;
}

void print_formatted_question(Question question) {
    set_console_color(14); // Yellow
    printf("\n\n%s\n", question.text);

    set_console_color(11); // Aqua
    for (int i = 0; i < 4; i++) {
        if (question.options[i][0] != '\0') {
            printf("%c. %s\n", ('A' + i), question.options[i]);
        }
    }

    set_console_color(10); // Green
    printf("\nEnter your answer (A, B, C, or D) or L for lifeline:\n");  // Ensure input is below timer
    set_console_color(7);
}


int read_questions(char* file_name, Question** questions) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("\nUnable to open the questions bank.");
        exit(0);
    }
    
    char str[MAX_QUES_LEN];
    int no_of_lines = 0;
    
    while (fgets(str, MAX_QUES_LEN, file)) {
        no_of_lines++;
    }
    
    int no_of_questions = no_of_lines / 8;
    *questions = (Question*)malloc(no_of_questions * sizeof(Question));
    
    rewind(file);
    for (int i = 0; i < no_of_questions; i++) {
        fgets((*questions)[i].text, MAX_QUES_LEN, file);
        for (int j = 0; j < 4; j++) {
            fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);
        }
        char option[10];
        fgets(option, 10, file);
        (*questions)[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        (*questions)[i].prize_money = atoi(prize_money);
    }
    
    fclose(file);
    return no_of_questions;
}

void set_console_color(int color) {
    SetConsoleTextAttribute(hConsole, color);
}
