📘 Simple Lane Game – Upgraded Version
(C Console Game Project – README)
📌 Overview

Simple Lane Game is a console-based C game where the player moves left or right to avoid obstacles falling from the top of the screen.
The upgraded version adds multiple modern features including:

High Score system (stored permanently in a file)

Multiple difficulty levels

Lives system (player gets 3 lives)

Smooth movement, cleaner UI

Pause support

Increasing difficulty

This game is fully portable and runs on any Windows system with a C compiler.

🎮 Gameplay Instructions
▶ Controls
Key	Action
←	Move Left
→	Move Right
P	Pause Game
Any Key	Resume after pause
🎯 Objective

Avoid obstacles (☺ ASCII character)

Survive as long as you can

Each obstacle you dodge gives you +1 score

Lose 1 life on collision

Game ends when all lives are lost

⭐ Features Added in the Upgraded Version
✔ 1. High Score Support

Game saves the highest score permanently in a file named highscore.txt

High score is displayed:

On the menu

During gameplay

On game over

If the player sets a new high score, it updates automatically

✔ 2. Multiple Difficulty Levels

Menu offers 3 levels:

Level	Speed	Difficulty
Easy	Slow	Best for beginners
Medium	Normal	Balanced gameplay
Hard	Fast	Challenging
✔ 3. Lives System

Player starts with 3 lives

On collision:

Life decreases by 1

Game continues until lives reach 0

On game over:

Score displayed

High score checked and updated

✔ 4. Dynamic Speed Increase

Every 5 points, game speed increases slightly

Creates a progressive difficulty curve

✔ 5. Improved Input Handling

Supports special keys (Arrow keys) using _kbhit() and getch()

More responsive player movement

Prevents input bugs from previous versions

✔ 6. Pause Feature

Press P anytime to pause the game

Press any key to resume

✔ 7. Clean & Structured Code

Modular functions:

playGame()

printFrame()

pauseScreen()

loadHighScore()

saveHighScore()

Clear ASCII-based user interface

Consistent formatting

🧱 Game Layout (ASCII Grid)
+-----------+
|           |
|     ☺     | ← Falling obstacle
|           |
|           |
|     ♠     | ← Player
+-----------+


Symbols:

Symbol	Meaning
☺ (ASCII 1)	Obstacle
♠ (ASCII 6)	Player
$	Powerup (if added later)
🗂 Project Files
1. simple_lane_game_upgraded.c

Main game source file containing all logic.

2. highscore.txt

Stores the highest score permanently.
Automatically created if not present.

📦 How to Compile & Run
Compile:
gcc simple_lane_game_upgraded.c -o lane_game.exe

Run:
lane_game.exe


Requires Windows because it uses:

<conio.h>

<windows.h>

_kbhit() and Sleep()

🧩 Future Upgrade Ideas

(If you want to extend in future)

Multiple obstacles at the same time

Powerups (Shield, Slow Motion)

Sound effects

Colors in console

Animated obstacle movement

Leaderboard (top 5 scores)

🏁 Conclusion

This upgraded version transforms the basic lane game into a more polished and engaging console project with file handling, player state management, difficulty levels, and smooth controls.
Perfect for college assignments and learning intermediate-level C programming
