#include <stdio.h>

// Define a 9x9 Sudoku puzzle with some prefilled values and 0s as empty spaces
int puzzle[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9},
};

// Function prototypes
void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int column, int value);

int main() {
    int row, column, value;

    // Print the initial puzzle
    print_puzzle(puzzle);

    // Ask user for input
    printf("\nEnter row (0-8): ");
    scanf("%d", &row);
    printf("Enter column (0-8): ");
    scanf("%d", &column);
    printf("Enter value (1-9): ");
    scanf("%d", &value);

    // Check if the move is valid
    if (valid_move(puzzle, row, column, value)) {
        printf("\nValid move!\n");
        puzzle[row][column] = value; // Place the value in the puzzle
    } else {
        printf("\nInvalid move! Try again.\n");
    }

    // Print the updated puzzle
    print_puzzle(puzzle);

    return 0;
}

// Function to print the Sudoku puzzle in a structured format
void print_puzzle(int puzzle[9][9]) {
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (int column = 0; column < 9; column++) {
            if (column % 3 == 0) {
                printf("| ");
            }
            if (puzzle[row][column] == 0) {
                printf(". ");
            } else {
                printf("%d ", puzzle[row][column]);
            }
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}

// Function to check if a move is valid in the Sudoku puzzle
int valid_move(int puzzle[9][9], int row, int column, int value) {
    // Check if the cell is already filled
    if (puzzle[row][column] != 0) {
        return 0;
    }

    // Check if the value exists in the row
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == value) {
            return 0;
        }
    }

    // Check if the value exists in the column
    for (int i = 0; i < 9; i++) {
        if (puzzle[i][column] == value) {
            return 0;
        }
    }

    // Find the starting index of the 3x3 subgrid
    int start_row = row - row % 3;
    int start_col = column - column % 3;

    // Check if the value exists in the 3x3 subgrid
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[start_row + i][start_col + j] == value) {
                return 0;
            }
        }
    }

    return 1; // Move is valid
}
