#include <iostream>
#include <conio.h>   // For _kbhit() and _getch()
#include <windows.h> // For Sleep(), Beep(), and console manipulation
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class SnakeGame {
private:
    bool gameOver;
    int width, height;
    int x, y, fruitX, fruitY, score;
    vector<pair<int, int>> snake;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir, lastDir;
    HANDLE hConsole;
    COORD cursorPos;

public:
    SnakeGame(int w, int h) {
        width = w;
        height = h;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        hideCursor();
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
        snake.clear();
        snake.push_back({x, y});
    }

    void hideCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 10;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    void gotoXY(int x, int y) {
        cursorPos.X = x;
        cursorPos.Y = y;
        SetConsoleCursorPosition(hConsole, cursorPos);
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
                    cout << "\033[32mO\033[0m";  // Green snake
                else if (j == fruitX && i == fruitY)
                    cout << "\033[31mF\033[0m";  // Red fruit
                else
                    cout << " ";

                if (j == width - 1) cout << "#";
            }
            cout << endl;
        }

        // Draw the bottom border
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        cout << "Score: " << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': if (lastDir != RIGHT) dir = LEFT; break;
                case 'd': if (lastDir != LEFT) dir = RIGHT; break;
                case 'w': if (lastDir != DOWN) dir = UP; break;
                case 's': if (lastDir != UP) dir = DOWN; break;
                case 'x': gameOver = true; break;
            }
        }
    }
    void Logic() {
        pair<int, int> prev = snake[0], prev2;
        snake[0] = { x, y };
        for (size_t i = 1; i < snake.size(); i++) {
            prev2 = snake[i];
            snake[i] = prev;
            prev = prev2;
        }
    
        switch (dir) {
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
            snake.push_back({ -1, -1 }); // Add new segment
        }
    
        lastDir = dir; // Prevent instant reversal
    }
    

    void spawnFruit() {
        bool valid;
        do {
            valid = true;
            fruitX = rand() % width;
            fruitY = rand() % height;
            for (const auto& segment : snake) {
                if (segment.first == fruitX && segment.second == fruitY) {
                    valid = false; // Fruit is inside the snake, try again
                    break;
                }
            }
        } while (!valid);
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
        gotoXY(0, height + 3);  // Move cursor to avoid overlapping text
        cout << "\033[31mGame Over!\033[0m" << endl;
        cout << "Final Score: " << score << endl;
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
