#include<stdio.h>
#include<stdlib.h>//for system("cls") or system("clear")
#include<time.h>//for srand() and rand()

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
    int player;
    int computer;
    int draw;
} Score;

Score score = {.player=0,.computer=0,.draw=0};// or we can use Score score={0,0,0};

int difficulty;

void input_diffficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
//we use int instead of void because we want to return the value of the winner

void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main(){

srand(time(0));//seed the random number generator
//time(0) returns the current time of the system in seconds
//this will generate random number

printf("\nWelcome to the Tic-Tac-Toe Game!\n\n");

input_diffficulty();

int choice;
do{
    play_game();
    printf("Do you want to play again? (1:Yes, 0:No) : ");
    scanf("%d",&choice);
}while (choice == 1);

printf("\nThanks for playing");

}

void input_diffficulty(){
    do{
        printf("Select difficulty level\n");
        printf("1.Fair Play Mode\n");
        printf("2.Unbeatable Mode\n");
        
        printf("Enter your choice : ");
        scanf("%d",&difficulty);
        
        if(difficulty!=1 && difficulty!=2){
        printf("Invalid choice! Please enter again\n\n");
        }
        
        }while(difficulty!=1 && difficulty!=2);
}        

void clear_screen(){
    system("cls");
    //system("clear");
}

// Function to display the Tic-Tac-Toe board
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Clears the console screen before printing the updated board
    clear_screen();
    printf("\n");

    // Display the current score of the game
    printf("Score - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);
    printf("\nTic-Tac-Toe\n\n");

    if(difficulty==1){
        printf("Difficulty Level: Fair Play Mode\n");
    }else{
        printf("Difficulty Level: Unbeatable Mode\n");
    }

    // Loop through each row of the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\n"); // Move to a new line before printing each row

        // Loop through each column of the current row
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]); // Print the board cell value (X, O, or empty space)

            // Print a vertical separator ('|') between columns except for the last column
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }

        // Print a horizontal separator line after each row except for the last row
        if (i < BOARD_SIZE - 1) {
            printf("\n---+---+---");
        }
    }
    printf("\n\n"); // Move to a new line for better readability
}

// Function to check if the given player has won the game
// Returns 1 if the player wins, otherwise returns 0
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // Check all rows for a win
    for (int i = 0; i < BOARD_SIZE; i++) {
        // If all three positions in the same row contain the player's symbol
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1; // Return 1 to indicate a win
        }
    }

    // Check all columns for a win
    for (int i = 0; i < BOARD_SIZE; i++) {
        // If all three positions in the same column contain the player's symbol
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1; // Return 1 to indicate a win
        }
    }

    // Check the first diagonal (top-left to bottom-right)
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1; // Return 1 if the player has won diagonally
    }

    // Check the second diagonal (bottom-left to top-right)
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player) {
        return 1; // Return 1 if the player has won diagonally
    }

    // If none of the winning conditions are met, return 0 (no win)
    return 0;
}

// Function to check if the game is a draw
// Returns 1 if the board is full and no player has won, otherwise returns 0
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Loop through every cell in the board
    for (int i = 0; i < BOARD_SIZE; i++) {  // Iterate over rows
        for (int j = 0; j < BOARD_SIZE; j++) {  // Iterate over columns
            // If any cell is still empty (' '), the game is not a draw
            if (board[i][j] == ' ') {
                return 0;  // Return 0 because there are still moves left
            }
        }
    }

    // If no empty cells are found, it means the board is full
    // Since this function is called after checking for a win,
    // If we reach here, it means no player has won and the game is a draw
    return 1;
}

// Function to play a single round of Tic-Tac-Toe
void play_game() {
    // Initialize the Tic-Tac-Toe board with empty spaces
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // Randomly select which player goes first (X or O)
    char current_player = rand() % 2 == 0 ? X : O;

    // Display the initial empty board
    print_board(board);

    // Game loop: continues until there is a winner or the game is a draw
    while (1) {
        // If it's the player's turn (X)
        if (current_player == X) {
            player_move(board);  // Player makes a move
            print_board(board);  // Print updated board

            // Check if the player (X) has won
            if (check_win(board, X)) {
                score.player++;  // Increment player win count
                print_board(board);  // Display the final board
                printf("Congratulations! You have won!!!\n");  // Victory message
                break;  // Exit the game loop
            }

            // Switch turn to the computer (O)
            current_player = O;
        } 
        // If it's the computer's turn (O)
        else {
            computer_move(board);  // Computer makes a move
            print_board(board);  // Print updated board

            // Check if the computer (O) has won
            if (check_win(board, O)) {
                score.computer++;  // Increment computer win count
                print_board(board);  // Display the final board
                printf("I won!!! Better luck next time\n");  // Computer victory message
                break;  // Exit the game loop
            }

            // Switch turn to the player (X)
            current_player = X;
        }

        // Check if the board is full (draw condition)
        if (check_draw(board)) {
            score.draw++;  // Increment draw count
            print_board(board);  // Display the final board
            printf("\nIt's a draw!\n");  // Draw message
            break;  // Exit the game loop
        }
    }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    // Check if the row and column are within valid range (0 to 2)
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return 0; // Return 0 (false) if out of bounds
    }

    // Check if the selected position is already occupied
    if (board[row][col] != ' ') {
        return 0; // Return 0 (false) if the cell is not empty
    }

    // If both conditions are satisfied, it's a valid move
    return 1; // Return 1 (true), meaning the move is valid
}


// Function to handle the player's move
void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    int count = 0, x, y;  // Variables to track the last empty cell
    int row, col;         // Variables to store player's input for row and column

    // Check if only one move is left
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {  // If the cell is empty
                count++;  // Increase the count of empty cells
                x = i;    // Store the row index of the empty cell
                y = j;    // Store the column index of the empty cell
            }
        }
    }

    // If there is only one empty space left, place 'X' automatically
    if (count == 1) {
        board[x][y] = X;
        return;  // Exit the function
    }
    
    // Loop until the player enters a valid move
    do {
        printf("\nPlayer X's turn.");
        printf("\nEnter row and column (1-3) for X using space in between: ");
        scanf("%d", &row);
        scanf("%d", &col);
        row--; col--; // Convert to zero-based indexing (since the user enters 1-3)

    } while (!is_valid_move(board, row, col)); // Keep asking until a valid move is entered

    // Place the player's move on the board
    board[row][col] = X;
}


void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {

    // 1. Check if there's an immediate winning move for the computer
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') { // Check if the cell is empty
                board[i][j] = O; // Temporarily place 'O' to check for a win
                if (check_win(board, O)) { // Check if this move results in a win
                    return; // If so, keep 'O' and return
                }
                board[i][j] = ' '; // Otherwise, revert back to empty
            }
        }
    }

    // 2. Check if there's an immediate winning move for the player (block it)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') { // Check if the cell is empty
                board[i][j] = X; // Temporarily place 'X' to check if the player would win
                if (check_win(board, X)) { // If so, block it
                    board[i][j] = O; // Place 'O' instead to block the player
                    return;
                }
                board[i][j] = ' '; // Otherwise, revert back to empty
            }
        }
    }

    // 3. If in "God Mode" (difficulty 2), apply a stronger strategy
        if (difficulty == 2) {
            // a) Take the center if available
            if (board[1][1] == ' ') {
                board[1][1] = O;
                return;
            }

            // b) Take a corner if available
            int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
            for (int i = 0; i < 4; i++) {
                if (board[corners[i][0]][corners[i][1]] == ' ') {
                    board[corners[i][0]][corners[i][1]] = O;
                    return;
                }
            }
        }

    // 4. If no special move is available, pick the first empty cell
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') { // Find the first available empty space
                board[i][j] = O; // Place 'O' in that position
                return;
            }
        }
    }
}


