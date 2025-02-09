# Snake Game in C++

This is a simple Snake Game implemented in C++ using the Windows console. The game features a snake that moves around the screen, grows when it eats a fruit, and ends when it collides with itself or the walls. It is a fun and engaging way to practice C++ programming and understand game development fundamentals.

## Features
- **Classic Snake Mechanics**: The snake moves in four directions and grows as it eats.
- **Randomized Fruit Placement**: Fruits appear at random locations on the grid.
- **Score Tracking**: Keep track of your score as you eat more fruits.
- **Game Over Conditions**: The game ends when the snake collides with itself or the walls.
- **Colored Console Output**: The snake and fruit are visually distinct using ANSI escape codes.
- **Game Restart Option**: Restart the game after losing instead of restarting the application.
- **Beep Sound for Game Over**: A sound effect plays when the game ends.

## How to Play
- **Controls:**
  - `W` - Move Up
  - `A` - Move Left
  - `S` - Move Down
  - `D` - Move Right
  - `X` - Quit the game
- The goal is to navigate the snake around the screen and eat the red fruit (`F`) to grow and increase your score.
- Avoid hitting the walls or yourself, as this will end the game.
- The game continuously loops until the player chooses to quit.

## Requirements
- **Operating System**: Windows (due to the use of `windows.h` and console manipulation functions)
- **Compiler**: C++ compiler (such as MinGW g++ or MSVC)
- **Terminal**: Command Prompt or any compatible terminal that supports ANSI escape codes.

## Compilation and Execution
To compile the game, use the following command in your terminal:

```sh
 g++ snake_game.cpp -o snake_game.exe
```

Then run the game with:

```sh
 ./snake_game.exe
```

## Code Structure and Explanation
The game is implemented using a `SnakeGame` class that encapsulates the entire game logic and rendering. Below is an overview of the key components:

### 1. **Class Definition (`SnakeGame`)**
   - Manages game state variables such as snake position, fruit position, score, and game-over status.
   - Handles user input, game logic, and rendering.

### 2. **Functions in `SnakeGame` Class**
   - `SnakeGame(int w, int h)`: Constructor initializes game dimensions and starts a new game.
   - `StartNewGame()`: Resets game variables to start a fresh game.
   - `hideCursor()`: Hides the blinking console cursor for a cleaner UI.
   - `gotoXY(int x, int y)`: Moves the console cursor to a specific position for smooth rendering.
   - `Draw()`: Renders the game field, snake, and fruit using ASCII characters and ANSI colors.
   - `Input()`: Captures user keystrokes and updates the snake’s movement direction.
   - `Logic()`: Updates the snake’s position, checks for collisions, handles fruit consumption, and extends the snake’s body.
   - `spawnFruit()`: Randomly places a new fruit ensuring it does not spawn inside the snake’s body.
   - `isGameOver()`: Returns whether the game has ended.
   - `PlayGameOverSound()`: Plays a beep sound when the game ends.
   - `ShowGameOverScreen()`: Displays the game-over message and final score.

### 3. **Main Game Loop (`main()`)**
   - Creates an instance of `SnakeGame`.
   - Runs a loop to repeatedly call `Draw()`, `Input()`, and `Logic()` until the game ends.
   - After a game-over event, prompts the user to restart or exit.

## Future Improvements
- **Increasing Difficulty**: Gradual increase in speed as the score rises.
- **Pause Functionality**: Ability to pause and resume the game.
- **Customizable Game Settings**: Change grid size and speed before starting.
- **Cross-Platform Compatibility**: Replace `windows.h` dependencies for broader support.
- **High Score Tracking**: Save and display the highest score achieved.
- **Multiplayer Mode**: Introduce a two-player mode for added fun.
- **Graphical Interface**: Replace console-based rendering with a GUI for better visuals.
