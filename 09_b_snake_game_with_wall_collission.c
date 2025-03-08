#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 15
#define WIDTH 40

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

enum Direction dir;
int score;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_length;
int tail_x[100], tail_y[100];

HANDLE console;
COORD cursor_position;

int speed = 100;

void setup();
void draw();
void input();
void game_play();
void goto_xy(int x, int y);
void hide_cursor();
void sleep_ms(int milliseconds);

int main() {
    srand(time(NULL));
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    hide_cursor();
    setup();

    while (1) {
        draw();
        input();
        game_play();
        sleep_ms(speed);
    }
}

void setup() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
    score = 0;
    tail_length = 0;
    speed = 100;
}

void draw() {
    goto_xy(0, 0);
    printf("\t\tSnake Game\n");
    printf("Controls: W (Up), A (Left), S (Down), D (Right), X (Exit)\n");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_y && j == head_x) printf("O");
            else if (i == fruit_y && j == fruit_x) printf("F");
            else {
                int tail_found = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found) printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': exit(0);
        }
    }
}

void game_play() {
    for (int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    if (tail_length > 0) {
        tail_x[0] = head_x;
        tail_y[0] = head_y;
    }

    switch (dir) {
        case LEFT:  head_x--; break;
        case RIGHT: head_x++; break;
        case UP:    head_y--; break;
        case DOWN:  head_y++; break;
        default:    return;
    }

    if (head_x < 0 || head_x >= WIDTH || head_y < 0 || head_y >= HEIGHT) {
        printf("\nYou hit the wall. GAME OVER!\n");
        exit(0);
    }

    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == head_x && tail_y[i] == head_y) {
            printf("\nYou hit your tail. GAME OVER!\n");
            exit(0);
        }
    }

    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        tail_length++;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
        if (speed > 30) speed -= 3;
    }
}

void goto_xy(int x, int y) {
    cursor_position.X = x;
    cursor_position.Y = y;
    SetConsoleCursorPosition(console, cursor_position);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 100;
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursor_info);
}

void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}
