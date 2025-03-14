#include <stdio.h>//For standard input/output functions.
#include <stdlib.h>//For exit() function.
#include <string.h>//For string functions.
#include <ctype.h>//For character handling functions.
#include <windows.h>//For Windows API functions.
#include <conio.h>//For _getch() function.
#include <time.h>//For time functions.

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

volatile int timeout_happened = 0;//Flag to check if timeout happened.
// volatile is used to prevent compiler optimization.
HANDLE hConsole;//Handle to the console window.

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
void clear_screen();

int main() {
    srand(time(NULL));//Seeds the random number generator with the current time.
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//Retrieves a handle to the console window.
    //This allows changing text color using SetConsoleTextAttribute()
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
    int lifeline[] = {1, 1}; // 50-50 and Skip Question

    for (int i = 0; i < no_of_questions; i++) {//Loops through all available questions one by one.
        clear_screen();  // ✅ Clears screen before each question
        print_formatted_question(questions[i]);//Calls print_formatted_question() to display the question and options.

        timeout_happened = 0;
        HANDLE hThread = CreateThread(NULL, 0, timeout_thread, &questions[i].timeout, 0, NULL);
        //Creates a new thread (timeout_thread()) to handle the countdown timer.
        //If the user does not answer in time, timeout_happened = 1.

        printf("\nYour answer: ");
        fflush(stdout);//ensures the text is immediately displayed.

        //Check for timeout
        char ch = '\0';
        while (!_kbhit()) { //_kbhit() checks if a key is pressed.
            if (timeout_happened) {
                TerminateThread(hThread, 0);
                CloseHandle(hThread);

                set_console_color(12);
                printf("\n\nTime Out!!!!!\n");
                set_console_color(7);

                set_console_color(9);
                printf("\n\nGame Over! Your total winnings are: Rs %d\n", money_won);
                set_console_color(7);
                return;
            }
        }
        //If timeout occurs, it ends the thread, displays "Time Out!", and terminates the game.

        ch = _getch();
        TerminateThread(hThread, 0);
        CloseHandle(hThread);
        //Reads the user's key press.
        //Stops the countdown timer by terminating the thread.

        if (timeout_happened) {
            set_console_color(9);
            printf("\n\nGame Over! Your total winnings are: Rs %d\n", money_won);
            set_console_color(7);
            return;
        }

        printf("%c\n", ch);
        ch = toupper(ch);//Converts the character to uppercase.

        if (ch == 'L') {
            int value = use_lifeline(&questions[i], lifeline);

            if (value != 2) {
                timeout_happened = 0;
                hThread = CreateThread(NULL, 0, timeout_thread, &questions[i].timeout, 0, NULL);
                i--;
            }
            continue;
        }

        if (ch == questions[i].correct_option) {
            set_console_color(10);
            printf("\nCorrect!\n");
            money_won = questions[i].prize_money;
            set_console_color(9);
            printf("\nYou have won: Rs %d\n", money_won);
        } else {
            set_console_color(12);
            printf("\nWrong! Correct answer is %c.\n", questions[i].correct_option);
            break;
        }
        set_console_color(7);
    }

    set_console_color(9);
    printf("\n\nGame Over! Your total winnings are: Rs %d\n", money_won);
    set_console_color(7);
}



DWORD WINAPI timeout_thread(LPVOID lpParam) {
    int timeout = *(int*)lpParam;
    //lpParam is a pointer to an integer, which stores the timeout duration (in seconds).
    //*(int*)lpParam converts it back to an int

    for (int i = timeout; i > 0; i--) {
        printf("\rTime Remaining: %d seconds  ", i);  // Overwrite the same line
        fflush(stdout);
        Sleep(1000);

        if (timeout_happened) {  // Stop countdown if answer is given
            return 0;
        }
    }

    timeout_happened = 1;
    printf("\rTime Out!!!!!                    \n");  // ✅ Overwrites remaining time
    return 0;
}



int use_lifeline(Question* question, int* lifeline) {
    set_console_color(13);
    printf("\n\nAvailable Lifelines:\n");
    if (lifeline[0]) printf("1. Fifty-Fifty (50/50)\n");
    if (lifeline[1]) printf("2. Skip the Question\n");
    printf("Choose a lifeline or 0 to return: ");
    set_console_color(7);

    char ch = _getch();
    printf("%c\n", ch);

    switch (ch) {
    case '1': // 50-50 Lifeline
        if (lifeline[0]) {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2) {
                int num = rand() % 4;
                if ((num + 'A') != question->correct_option &&
                    question->options[num][0] != '\0') {
                    question->options[num][0] = '\0';//Replaces the first character with '\0', effectively hiding the option.
                    removed++;
                }
            }
            clear_screen();  // ✅ Clears screen before re-asking the question
            return 1;
        }
        break;
    case '2': // Skip Question Lifeline
        if (lifeline[1]) {
            lifeline[1] = 0;
            return 2;  // ✅ Moves to the next question without clearing
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
    
    //Count the Number of Lines
    while (fgets(str, MAX_QUES_LEN, file)) {
        no_of_lines++;
    }//Loops through the file until MAX_QUESTIONS are read or the file ends.
     //Reads one question at a time into questions[count].question
    
     //Calculate the Number of Questions
    int no_of_questions = no_of_lines / 8;
    *questions = (Question*)malloc(no_of_questions * sizeof(Question));
    
    //Read Questions into Memory
    rewind(file);
    for (int i = 0; i < no_of_questions; i++) {
        fgets((*questions)[i].text, MAX_QUES_LEN, file);
        for (int j = 0; j < 4; j++) {
            fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);
        }

        // Read Correct Answer
        char option[10];
        fgets(option, 10, file);
        (*questions)[i].correct_option = option[0];

        // Read Timeout 
        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        // Read Prize Money
        char prize_money[10];
        fgets(prize_money, 10, file);
        (*questions)[i].prize_money = atoi(prize_money);
    }
    
    //Close the File and Return the Number of Questions
    fclose(file);
    return no_of_questions;
}

void set_console_color(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void clear_screen() {
    system("cls");  // ✅ Clears the console screen on Windows
}
