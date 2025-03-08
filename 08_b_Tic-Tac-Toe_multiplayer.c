#include <stdio.h>
#include <stdlib.h> // for system("cls") or system("clear")
#include <time.h> // for srand() and rand()

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
    int playerX;
    int playerO;
    int draw;
} Score;

Score score = {0, 0, 0};

void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main() {
    srand(time(0));
    printf("\nWelcome to Multiplayer Tic-Tac-Toe!\n\n");

    int choice;
    do {
        play_game();
        printf("Do you want to play again? (1: Yes, 0: No): ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("\nThanks for playing!\n");
    return 0;
}

void clear_screen() {
    system("cls");
    // system("clear");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    clear_screen();
    printf("\nScore - Player X: %d, Player O: %d, Draws: %d\n", score.playerX, score.playerO, score.draw);
    printf("Tic-Tac-Toe\n\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        if (i < BOARD_SIZE - 1) {
            printf("\n---+---+---");
        }
    }
    printf("\n\n");
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player) return 1;
    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char current_player = X;
    print_board(board);

    while (1) {
        player_move(board, current_player);
        print_board(board);

        if (check_win(board, current_player)) {
            if (current_player == X) score.playerX++;
            else score.playerO++;
            print_board(board);
            printf("Player %c wins!\n", current_player);
            break;
        }
        if (check_draw(board)) {
            score.draw++;
            print_board(board);
            printf("It's a draw!\n");
            break;
        }

        current_player = (current_player == X) ? O : X;
    }
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    int row, col;
    do {
        printf("Player %c's turn.\n", player);
        printf("Enter row and column (1-3) separated by space: ");
        scanf("%d %d", &row, &col);
        row--; col--;
    } while (!is_valid_move(board, row, col));
    board[row][col] = player;
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) return 0;
    if (board[row][col] != ' ') return 0;
    return 1;
}