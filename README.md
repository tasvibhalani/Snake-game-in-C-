# Snake Game in C++

## Description
This is a simple console-based Snake Game implemented in C++ using Windows-specific console manipulation functions. The game features:
- Movement using arrow keys (`←`, `→`, `↑`, `↓`) or `WASD` keys
- A fruit spawning mechanism that ensures fruits do not appear on the snake's body
- A real-time display without clearing the console screen
- A high score tracking system
- A game-over screen with sound effects

## Features
- **Real-time keyboard input detection** using `_kbhit()` and `_getch()`
- **Dynamic snake growth** when it eats the fruit
- **Border collision detection** for game over conditions
- **Self-collision detection**
- **Game restart option**
- **Game-over sound effect** using `Beep()`
- **Cursor movement** using `SetConsoleCursorPosition()`

## How to Play
1. Run the program.
2. Use the arrow keys (`←`, `→`, `↑`, `↓`) or `WASD` keys to control the snake's movement.
3. Eat the fruit (`F`) to grow and increase your score.
4. Avoid crashing into the walls or yourself.
5. When the game ends, you will see your final score and high score.
6. Choose whether to restart (`y/Y`) or exit (`n/N`).

## Code Breakdown
### 1. **Class `SnakeGame`**
This class contains all the game logic and UI rendering.

#### Private Members:
- `gameOver`: A boolean to track if the game has ended.
- `width`, `height`: Dimensions of the game board.
- `x`, `y`: Snake's head position.
- `fruitX`, `fruitY`: Position of the fruit.
- `score`, `highScore`: Tracks the score and highest score.
- `snake`: A vector storing the snake's body coordinates.
- `Direction`: Enum for snake movement direction.
- `hConsole`, `cursorPos`: Used for cursor movement in the console.

#### Key Methods:
- `StartNewGame()`: 
  - Resets all game-related variables.
  - Places the snake at the center of the board.
  - Randomly places the fruit in a valid position.
  - Initializes the score to zero.

- `hideCursor()`: 
  - Uses `CONSOLE_CURSOR_INFO` to make the console cursor invisible.
  - Prevents visual distractions by removing the blinking cursor.

- `gotoXY(int x, int y)`: 
  - Moves the console cursor to a specific (x, y) coordinate.
  - Uses `SetConsoleCursorPosition()` to efficiently update screen output without flickering.

- `Draw()`: 
  - Uses `gotoXY(0,0)` to prevent unnecessary screen clearing.
  - Draws the game board, snake, and fruit.
  - Utilizes ANSI escape codes to color the snake and fruit.
  - Displays the current score and high score.

- `Input()`: 
  - Uses `_kbhit()` to detect if a key is pressed.
  - Uses `_getch()` to capture the keypress without requiring Enter.
  - Updates the snake's direction, preventing instant reversal.
  - Allows the player to exit by pressing 'X'.

- `Logic()`: 
  - Moves the snake in the current direction.
  - Shifts each segment of the snake forward to simulate movement.
  - Checks for collisions with walls or itself and ends the game if necessary.
  - Detects if the snake eats the fruit, increasing score and growing the snake.
  - Calls `spawnFruit()` to generate a new fruit if needed.

- `spawnFruit()`: 
  - Randomly places a fruit in a location that does not overlap with the snake.
  - Uses a loop to ensure a valid fruit placement before breaking.

- `isGameOver()`: 
  - Returns the `gameOver` boolean to indicate whether the game has ended.

- `PlayGameOverSound()`: 
  - Uses `Beep()` to play a series of tones when the game ends.
  - Creates an audio cue to enhance user experience.

- `ShowGameOverScreen()`: 
  - Updates the high score if the current score is greater.
  - Displays the final score and high score to the player.
  - Calls `PlayGameOverSound()` to play a sound.

### 2. **Main Function**
- Initializes `srand(time(0))` for random fruit placement.
- Creates an instance of `SnakeGame`.
- Runs the game loop, checking `isGameOver()`.
- After a game over, prompts the player to restart or exit.

## Dependencies
This program uses:
- `<iostream>`: For input and output operations.
- `<conio.h>`: For `_kbhit()` and `_getch()` functions (Windows-specific).
- `<windows.h>`: For `Sleep()`, `Beep()`, and console handling.
- `<vector>`: To store the snake's body.
- `<cstdlib>`: For `rand()` to generate fruit positions.
- `<ctime>`: To seed `rand()` with `srand(time(0))`.

## Compilation and Execution
### Windows
1. Open Command Prompt.
2. Navigate to the directory containing `snake_game.cpp`.
3. Compile using:
   ```sh
   g++ snake_game.cpp -o snake_game.exe
   ```
4. Run the game:
   ```sh
   snake_game.exe
   ```

## Potential Enhancements
- Adding **difficulty levels** (faster snake speed as the score increases).
- Implementing a **pause feature**.
- Adding **multiplayer mode**.

## Acknowledgments
This game is inspired by the classic Snake game and is designed for educational purposes.

---
**Enjoy playing Snake! 🐍**

