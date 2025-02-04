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
int is_solved(int puzzle[9][9]);

int main() {
    int row, column, value;

    // Print the initial puzzle
    print_puzzle(puzzle);

    // Game loop continues until the puzzle is solved
    while (!is_solved(puzzle)) {
        // Ask user for input
        printf("\nEnter row (1-9): ");
        scanf("%d", &row);
        printf("Enter column (1-9): ");
        scanf("%d", &column);
        printf("Enter value (1-9): ");
        scanf("%d", &value);

        // Convert to 0-based indexing
        row -= 1;
        column -= 1;

        // Check if the move is valid
        if (valid_move(puzzle, row, column, value)) {
            printf("\nValid move!\n");
            puzzle[row][column] = value; // Place the value in the puzzle
        } else {
            printf("\nInvalid move! Try again.\n");
        }

        // Print the updated puzzle
        print_puzzle(puzzle);
    }

    printf("\nCongratulations! The Sudoku puzzle is solved!\n");

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
//This loop goes through all the cells in the same row (row) and checks if the value the user wants to place (value) already exists in that row.
        }
    }

    // Check if the value exists in the column
    for (int i = 0; i < 9; i++) {
        if (puzzle[i][column] == value) {
            return 0;
// This loop checks if the value exists in the same column (column). It goes through all rows (i) of the given column to see if the value is already there.
        }
    }

    // Find the starting index of the 3x3 subgrid
    int start_row = row - row % 3;
    /*If row = 4, row % 3 = 1, so subtracting this from row gives start_row = 4 - 1 = 3. The subgrid starts from row 3 (index 3, which is the first row of the subgrid).
      If row = 7, row % 3 = 1, so start_row = 7 - 1 = 6. The subgrid starts from row 6 (index 6).*/
    int start_col = column - column % 3;
    /*If column = 5, column % 3 = 2, so subtracting this from column gives start_col = 5 - 2 = 3. The subgrid starts from column 3 (index 3, which is the first column of the subgrid).
      If column = 8, column % 3 = 2, so start_col = 8 - 2 = 6. The subgrid starts from column 6 (index 6).*/

    // Check if the value exists in the 3x3 subgrid
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[start_row + i][start_col + j] == value) {
                return 0;
            }
        }
    }
    /*hese two nested loops (i and j) iterate over the 3x3 subgrid to check if the value already exists within that subgrid.

 Outer loop (i):
 Loops through the rows of the 3x3 subgrid, starting from start_row (which is the top-left corner of the subgrid).

 Inner loop (j):
 Loops through the columns of the 3x3 subgrid, starting from start_col.*/

    return 1; // Move is valid
}

// Function to check if the Sudoku puzzle is solved
int is_solved(int puzzle[9][9]) {
    // Check if all cells are filled and no violations exist
    for (int row = 0; row < 9; row++) {
        for (int column = 0; column < 9; column++) {
            if (puzzle[row][column] == 0) {
                return 0; // Puzzle is not solved if there's an empty cell
            }
        }
    }
    return 1; // Puzzle is solved
}