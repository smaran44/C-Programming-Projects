#include <stdio.h>   // Standard Input/Output functions
#include <stdlib.h>  // For rand(), srand(), exit()
#include <conio.h>   // For _kbhit() and _getch() (handles keyboard input without Enter)
#include <windows.h> // For Windows-specific console functions like Sleep(), SetConsoleCursorPosition()
#include <time.h>    // For time() to seed random number generator

// Define the size of the game board
#define HEIGHT 15
#define WIDTH 40

// Enumeration to represent possible movement directions
//enum (short for enumeration) is a user-defined data type in C that consists of named integer constants. 
//It helps in defining a set of related constants with meaningful names, improving code readability and maintainability.
enum Direction {
    STOP = 0, LEFT, RIGHT, UP, DOWN
};

// Global variables
enum Direction dir; // Stores the current movement direction
int score;          // Stores the current score
int fruit_x, fruit_y; // Stores fruit coordinates
int head_x, head_y; // Stores the snake's head position
int tail_length;    // Stores the snake's tail length
int tail_x[100], tail_y[100]; // Arrays to store tail coordinates

HANDLE console;  // Handle to console for cursor positioning
// A handle is an integer value that identifies a resource such as a file, a window, or a console.
COORD cursor_position; // Stores the cursor position
// The COORD structure defines the coordinates of a character cell in a console screen buffer.

int speed = 100; // Initial speed in milliseconds (100 ms = 0.1 seconds)

// Function Declarations
void setup();
void draw();
void input();
void game_play();
void goto_xy(int x, int y);
void hide_cursor();
void sleep_ms(int milliseconds);

// Main function
int main() {
    srand(time(NULL));  // Seed the random number generator
    console = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle
    hide_cursor(); // Hide cursor to make rendering smooth
    setup(); // Initialize game variables

    // Infinite game loop
    while (1) {
        draw();   // Render the game
        input();  // Handle user input
        game_play(); // Update game logic
        sleep_ms(speed); // Control game speed (100 ms delay)
    }
}

// Initializes game variables
void setup() {
    head_x = WIDTH / 2;  // Start snake in the middle
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH; // Place fruit at random position
    fruit_y = rand() % HEIGHT;
    /*% WIDTH ensures the fruit is placed within horizontal boundaries (0 to 39).
      % HEIGHT ensures the fruit is placed within vertical boundaries (0 to 14)*/
    dir = STOP; // Snake does not move initially
    //The snake remains stationary until the player presses a key (w, a, s, d).
    score = 0;
    tail_length = 0; // Start with no tail
    speed = 100; // Reset speed when game starts
}

// Function to render the game
void draw() {
    // Move the cursor to the top-left (0,0) to redraw the screen smoothly.
    // This prevents flickering and makes the game look smoother.
    goto_xy(0, 0);
    
    // Print the title of the game at the top of the screen
    printf("\t\tSnake Game\n");
    printf("Controls: W (Up), A (Left), S (Down), D (Right), X (Exit)\n");

    // Draw the top border of the game area using '#' characters
    for (int i = 0; i < WIDTH + 2; i++) { 
        printf("#");  // Print border character
    }
    printf("\n"); // Move to the next line

    // Loop through each row inside the game area (excluding top and bottom borders)
    for (int i = 0; i < HEIGHT; i++) {
        printf("#");  // Print the left border of the game area

        // Loop through each column inside the game area
        for (int j = 0; j < WIDTH; j++) {
            
            // Check if the current position (i, j) is the snake's head
            if (i == head_y && j == head_x) { 
                printf("O");  // Print 'O' for the snake's head
            }
            // Check if the current position (i, j) is the fruit
            else if (i == fruit_y && j == fruit_x) { 
                printf("F");  // Print 'F' for the fruit
            }
            else {
                // Variable to track if the current position is occupied by the snake's tail
                int tail_found = 0;

                // Loop through all tail segments to check if one is at the current position (i, j)
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) { // If tail segment found
                        printf("o");  // Print 'o' for the tail segment
                        tail_found = 1; // Mark as found
                        break; // Exit the loop since we found a tail segment
                    }
                }

                // If the position is not occupied by the head, tail, or fruit, print empty space
                if (!tail_found) { 
                    printf(" ");
                }
            }
        }

        printf("#");  // Print the right border of the game area and move to the next row
        printf("\n");
    }

    // Draw the bottom border of the game area using '#' characters
    for (int i = 0; i < WIDTH + 2; i++) { 
        printf("#");  // Print border character
    }
    printf("\n"); // Move to the next line

    // Display the current score below the game area
    printf("Score: %d\n", score);
}

/*Coordinates of the Walls in the Game Grid
Width = 40
Height = 15
 Wall Placement in the Grid
Top Border → All (x, y) where y = 0
Bottom Border → All (x, y) where y = HEIGHT + 1 = 16
Left Border → All (x, y) where x = 0
Right Border → All (x, y) where x = WIDTH + 1 = 41*/

//In this game, the origin is at the top-left corner of the grid

/*The playable area is inside the borders:

The x-coordinates range from 0 to 39 (total 40 columns).
The y-coordinates range from 0 to 14 (total 15 rows).
So, even though the border contains 42 # characters, the snake's movement is within 0 to 39 (for x) and 0 to 14 (for y).

*/

// Handles user input for controlling the snake
void input() {
    // Check if a key has been pressed
    if (_kbhit()) { //_kbhit() (from <conio.h>) checks if a key has been pressed
        // Get the pressed key without waiting for Enter (real-time input)
        switch (_getch()) { //_getch() (also from <conio.h>) reads the character without waiting for Enter.
            case 'a': 
                if (dir != RIGHT) dir = LEFT;  // Move left (only if not moving right)
                break;
            case 'd': 
                if (dir != LEFT) dir = RIGHT;  // Move right (only if not moving left)
                break;
            case 'w': 
                if (dir != DOWN) dir = UP;  // Move up (only if not moving down)
                break;
            case 's': 
                if (dir != UP) dir = DOWN;  // Move down (only if not moving up)
                break;
            case 'x': 
                exit(0);  // Exit the game when 'x' is pressed
        }
    }
}
// enum dir stores the current direction of the snake (LEFT, RIGHT, UP, DOWN, or STOP).


// Updates the game state and snake movement
void game_play() {
    // Move tail - shift each tail segment to the position of the previous one
    for (int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }

    // Update the first tail segment to follow the previous head position
    if (tail_length > 0) {
        tail_x[0] = head_x;
        tail_y[0] = head_y;
    }

    // Move the head in the direction set by `dir`
    switch (dir) {
        case LEFT:  head_x--; break;  // Move left
        case RIGHT: head_x++; break;  // Move right
        case UP:    head_y--; break;  // Move up
        case DOWN:  head_y++; break;  // Move down
        default:    return;  // If STOP, do nothing
    }

    // Wrap-around behavior when hitting walls (Snake reappears on the other side)
    if (head_x < 0) head_x = WIDTH - 1;      // Left wall → Appear on right
    else if (head_x >= WIDTH) head_x = 0;    // Right wall → Appear on left
    if (head_y < 0) head_y = HEIGHT - 1;     // Top wall → Appear at bottom
    else if (head_y >= HEIGHT) head_y = 0;   // Bottom wall → Appear at top

    // Check if snake collides with its tail
    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == head_x && tail_y[i] == head_y) {
            printf("\nYou hit your tail. GAME OVER!\n");
            exit(0); // End the game if snake collides with its own body
        }
    }

    // Check if snake eats the fruit
    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;   // Increase score
        tail_length++;  // Increase tail length
        fruit_x = rand() % WIDTH;  // Generate new fruit position (random x)
        fruit_y = rand() % HEIGHT; // Generate new fruit position (random y)
        if (speed > 30) speed -= 3; // Increase speed after eating fruit
        //The speed variable represents the delay in milliseconds, so decreasing it makes the game run faster.
    }
}


// Moves the console cursor to a specific position
void goto_xy(int x, int y) {
    cursor_position.X = x;
    cursor_position.Y = y;
    SetConsoleCursorPosition(console, cursor_position);
}

// Hides the console cursor to improve visual smoothness
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 100;
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursor_info);
}

// Implements a sleep function for better control over game speed
void sleep_ms(int milliseconds) {
    Sleep(milliseconds); // Windows-specific sleep function
}
