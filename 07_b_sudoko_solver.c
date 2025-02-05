#include <stdio.h>

// Define a 9x9 Sudoku puzzle with some prefilled values and 0s as empty spaces
void input_puzzle(int puzzle[9][9]);
// Function prototypes
void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int column, int value);
int solve_puzzle(int puzzle[9][9], int row, int column);

int main(){

     int puzzle[9][9];
    printf("\nWelcome to the Sudoku Solver!\n\n");
    printf("Enter your Sudoku puzzle row by row (use 0 for empty cells):\n");
    input_puzzle(puzzle);

    printf("Original puzzle : \n");

    print_puzzle(puzzle);
    printf("\n");

    if(solve_puzzle(puzzle, 0, 0)){
        printf("The solved puzzle is : \n");
        print_puzzle(puzzle);
    } else {
        printf("This puzzle is not solvable");
    }
    
      return 0;
}

// Function to take user input for the Sudoku puzzle
void input_puzzle(int puzzle[9][9]) {
    for (int row = 0; row < 9; row++) {
        printf("Enter 9 numbers for row %d (separated by spaces): ", row + 1);
        for (int column = 0; column < 9; column++) {
            scanf("%d", &puzzle[row][column]);
        }
    }
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

int solve_puzzle(int puzzle[9][9], int row, int column) {
    if (row == 9) {
        return 1;
    }
    /*If row == 9, it means we have successfully placed numbers in all rows (0 to 8) and moved beyond the last row.
    This indicates that the puzzle has been completely solved.
    Return 1 (true) to signal success*/

    if (column == 9) {
        return solve_puzzle(puzzle, row + 1, 0);
    }
    /*If column == 9, it means we have reached the end of a row (because columns are indexed 0 to 8).
     Move to the next row (row + 1) and start at column 0.
     Call solve_puzzle recursively for the next row.*/

    if (puzzle[row][column] != 0) {
        return solve_puzzle(puzzle, row, column + 1);
    }
    /*If the current cell (puzzle[row][column]) is already filled (not 0), it means we shouldn't change it.
     We move to the next column (column + 1) and continue solving.*/

    for (int i = 1; i <= 9; i++) {
        if (valid_move(puzzle, row, column, i)) {
            puzzle[row][column] = i;
            if (solve_puzzle(puzzle, row, column + 1)) {
                return 1;
                /*If valid, place i in the cell.
                 Then, recursively call solve_puzzle to solve the next cell (column + 1).
                If the recursive call returns 1 (solved), return 1 immediately.*/
            }
            puzzle[row][column] = 0; // Backtrack
            /*If placing i does not lead to a solution, undo the move (set back to 0).
              This is backtracking, meaning we return to the previous state and try the next number.*/
        }
    }

    return 0;
    //If none of the numbers (1-9) work, return 0 to signal failure.
}