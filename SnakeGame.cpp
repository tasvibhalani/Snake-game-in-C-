#include <iostream>
#include <conio.h>   // For _kbhit() and _getch()
#include <windows.h> // For Sleep(), Beep(), and console manipulation
#include <vector>
#include <cstdlib> //Required for rand()
// rand() - used to randomly generate the position of the fruit 
#include <ctime> // Used for srand(time(0)) 

using namespace std;

class SnakeGame {
private:
    bool gameOver;
    int width, height;
    int x, y, fruitX, fruitY, score;
    int highScore;  // Added variable to track the high score
    vector<pair<int, int>> snake;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//user defined datatype used to check direction
    Direction dir, lastDir;
    HANDLE hConsole; //a Windows-specific data type used to reference system resources also known as 'opaque pointer'
    COORD cursorPos; //a simple struct that represents a coordinate (X, Y) in the console screen buffer. It is used to move the cursor in the console window.

public:
    SnakeGame(int w, int h) {
        width = w;
        height = h;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // stores the handle to the console output. It is used for setting the position of the cursor
        // STD_OUTPUT_HANDLE - Retrieves the handle for standard output (console screen).
        hideCursor();
        highScore = 0;  // Initialize high score to 0
        StartNewGame();
    }

    void StartNewGame() {
        gameOver = false;
        dir = STOP;
        lastDir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        snake.clear();//used to reset the snake's body by removing all elements from the vector that stores the snake's position.
        snake.push_back({x, y}); // gives the starting position to the snake 
    }

    void hideCursor() { //Calls function to hide the blinking cursor.
        CONSOLE_CURSOR_INFO cursorInfo; // a structure used in Windows console applications to manage the appearance and visibility of the console cursor.
        cursorInfo.dwSize = 10;// sets the size of the console cursor (percentage of the cell height that the cursor occupies)
        //for dwsize - To control the cursor appearance in text-based applications.(makes the cursor less distracting)
        cursorInfo.bVisible = FALSE;// removes the visibility of the cursor 
        SetConsoleCursorInfo(hConsole, &cursorInfo); // It allows you to set the cursor's size and whether it should be visible or hidden.
    }

    void gotoXY(int x, int y) {// X and Y are already defined in the default struct of COORD
        cursorPos.X = x;
        cursorPos.Y = y;
        SetConsoleCursorPosition(hConsole, cursorPos);  // use to give a specific position to the cursor in a console screen buffer
        // console screen buffer is a special area in memory where the console (Command Prompt) stores what is displayed on the screen.
    }

    void Draw() {
        gotoXY(0, 0); // Move cursor to top-left without clearing the screen

        // Draw the top border
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        // Draw game area
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "#";

                bool isSnake = false;
                for (auto s : snake) {
                    if (s.first == j && s.second == i) {
                        isSnake = true;
                        break;
                    }
                }

                if (isSnake)
                    cout << "\033[32mO\033[0m";  // Green snake - makes the required cell of green colour then resets the default colour
                else if (j == fruitX && i == fruitY)
                    cout << "\033[31mF\033[0m";  // Red fruit (similar to above)
                else
                    cout << " ";

                if (j == width - 1) cout << "#";
            }
            cout << endl;
        }

        // Draw the bottom border
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        // Display current score and high score
        cout << "Score: " << score << "  High Score: " << highScore << endl;
    }

    void Input() {
        if (_kbhit()) {// _kbit() - checks wheather the key has been pressed or not on the keyboard.It does not wait for input, meaning it allows continuous program execution.
            switch (_getch()) {// _getch() - it reads the single char from the keyboard without pressing enter. No need to display the pressed key on the console.
                case 75: if (lastDir != RIGHT) dir = LEFT; break;
                case 'a': if (lastDir != RIGHT) dir = LEFT; break;
                case 77: if (lastDir != LEFT) dir = RIGHT; break;
                case 'd': if (lastDir != LEFT) dir = RIGHT; break;
                case 72: if (lastDir != DOWN) dir = UP; break;
                case 'w': if (lastDir != DOWN) dir = UP; break;
                case 80: if (lastDir != UP) dir = DOWN; break;
                case 's': if (lastDir != UP) dir = DOWN; break;
                case 'x': gameOver = true; break;
            }
        }
    }

    void Logic() {
        pair<int, int> prev = snake[0], prev2;// updates the snake's body position as it moves. It shifts each segment forward, ensuring the tail follows the head.
        snake[0] = { x, y };
        for (size_t i = 1; i < snake.size(); i++) {
            prev2 = snake[i];//stores the current segment
            snake[i] = prev; // moves previous segment forward
            prev = prev2; // update 'prev' for the next segment
        }

        switch (dir) { // for the motion of the snake
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
            default: break;
        }
        // **Game Over condition: Snake touches any border**
        if (x >= width || x < 0 || y >= height || y < 0 ) { 
            gameOver = true;
            return; // Exit early
        }
        // **Game Over condition: Snake touches itself**
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[i].first == x && snake[i].second == y) {
                gameOver = true;
                return;
            }
        }
        // Check if fruit is eaten
        if (x == fruitX && y == fruitY) {
            score += 10;
            spawnFruit();
            snake.push_back(snake.back()); // Add new segment
        }
        lastDir = dir; // Prevent instant reversal
    }

    void spawnFruit() { //generates a fruit position that does not overlap with the snake's body.
        bool valid; // checks wheather the new position of the fruit does not overlap with the position of the snake 
        do {
            valid = true; //assumes that it's valid
            fruitX = rand() % width; //Random X coordinate within the game area 
            fruitY = rand() % height;// Random Y coordinate within the game area 
            for (const auto& segment : snake) { //Check if Fruit Overlaps with the Snake                
                if (segment.first == fruitX && segment.second == fruitY) {
                    valid = false; // Fruit is inside the snake, try again
                    break;
                }
            }
        } while (!valid); //If valid == false, the function repeats the process until a safe fruit position is found.
        // If valid == true, the fruit placement is successful, and the loop exits.[]
    }

    bool isGameOver() {
        return gameOver;
    }
    void PlayGameOverSound() {
        Beep(523, 500);
        Beep(494, 500);
        Beep(440, 500);
    }
    void ShowGameOverScreen() {
        // Update the high score if current score is higher
        if (score > highScore) {
            highScore = score;
        }

        gotoXY(0, height + 3);  // Move cursor to avoid overlapping text
        cout << "\033[31mGame Over!\033[0m" << endl;
        cout << "Final Score: " << score << endl;
        cout << "High Score: " << highScore << endl;
        PlayGameOverSound();
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    SnakeGame game(30, 20);

    while (true) {
        while (!game.isGameOver()) {
            game.Draw();
            game.Input();
            game.Logic();
            Sleep(100);
        }

        game.ShowGameOverScreen();

        cout << "Do you want to play again? (y/n): ";
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
                game.StartNewGame();
            }
        else {
            break;
        }
        
    }
}
