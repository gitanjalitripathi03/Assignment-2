/* simple_lane_game_upgraded.c
   Features added:
   1) High score saved to "highscore.txt" and displayed on menu / game over
   2) Multiple Levels: Easy / Medium / Hard (affects speed)
   3) Lives system: player has 3 lives (configurable) and loses 1 on collision
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define LANES 3
#define ROWS 10
#define HIGHSCORE_FILE "highscore.txt"

void hideCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);
}

int loadHighScore() {
    FILE *f = fopen(HIGHSCORE_FILE, "r");
    if (!f) return 0;
    int hs = 0;
    fscanf(f, "%d", &hs);
    fclose(f);
    return hs;
}

void saveHighScore(int hs) {
    FILE *f = fopen(HIGHSCORE_FILE, "w");
    if (!f) return;
    fprintf(f, "%d\n", hs);
    fclose(f);
}

void printFrame(int step, int obstaclePos, int playerLane, int score, int lives, int highScore) {
    system("cls");
    printf("=== SIMPLE LANE GAME ===\n");
    printf("Score: %d    Lives: %d    High Score: %d\n", score, lives, highScore);
    printf("+-----------+\n");
    for (int i = 0; i < ROWS; ++i) {
        if (i == step) {
            if (obstaclePos == 0) {
                printf("| %c         |\n", 1); // obstacle left
            } else if (obstaclePos == 1) {
                printf("|     %c     |\n", 1); // obstacle middle
            } else {
                printf("|        %c  |\n", 1); // obstacle right
            }
        } else {
            printf("|           |\n");
        }
    }
    // player row (bottom)
    if (playerLane == 0) {
        printf("| %c         |\n", 6);
    } else if (playerLane == 1) {
        printf("|     %c     |\n", 6);
    } else {
        printf("|        %c  |\n", 6);
    }
    printf("+-----------+\n");
    printf("Controls: ← Left   → Right   P Pause\n");
}

void pauseScreen() {
    printf("Game paused. Press any key to resume...\n");
    getch();
}

void playGame(int startSpeed, int initialLives, int *globalHighScore) {
    srand((unsigned int)time(NULL));
    int playerLane = 1; // start center
    int step = 0;
    int obstaclePos = rand() % LANES;
    int score = 0;
    int speed = startSpeed;
    int lives = initialLives;
    int highScore = *globalHighScore;

    hideCursor();

    while (1) {
        // Input handling (robust for arrow keys)
        if (_kbhit()) {
            int ch = getch();
            if (ch == 0 || ch == 224) { // special key prefix
                ch = getch();
                if (ch == 75 && playerLane > 0) { // left arrow
                    playerLane--;
                } else if (ch == 77 && playerLane < LANES - 1) { // right arrow
                    playerLane++;
                }
            } else if (ch == 'p' || ch == 'P') {
                pauseScreen();
            }
        }

        printFrame(step, obstaclePos, playerLane, score, lives, highScore);

        // If obstacle reaches bottom (step == ROWS - 1), check collision
        if (step == ROWS - 1) {
            if (playerLane == obstaclePos) {
                // collision
                lives--;
                printf("\nOops! You hit an obstacle. Lives left: %d\n", lives);
                Sleep(600);
                if (lives <= 0) {
                    system("cls");
                    printf("\nGAME OVER!\n");
                    printf("Your Score: %d\n", score);
                    if (score > highScore) {
                        printf("New High Score! (old: %d -> new: %d)\n", highScore, score);
                        highScore = score;
                        saveHighScore(highScore);
                        *globalHighScore = highScore;
                    } else {
                        printf("High Score: %d\n", highScore);
                    }
                    printf("Press any key to return to menu...\n");
                    getch();
                    break;
                }
            } else {
                // passed obstacle successfully
                score++;
                if (score > highScore) {
                    // update but don't necessarily save until game ends (optional)
                    highScore = score;
                }
            }

            // reset for next obstacle
            step = 0;
            obstaclePos = rand() % LANES;

            // Increase difficulty slightly over time (optional)
            if (score % 5 == 0 && speed > 30) {
                speed -= 5; // increase game speed
            }
            continue; // print next frame after reset
        }

        Sleep(speed);
        step++;
    }
}

int main() {
    int choice;
    int highScore = loadHighScore();
    while (1) {
        system("cls");
        printf("=================================\n");
        printf("     SIMPLE LANE GAME - MENU     \n");
        printf("=================================\n");
        printf("High Score: %d\n\n", highScore);
        printf("1. Play - Easy (Slow)\n");
        printf("2. Play - Medium\n");
        printf("3. Play - Hard (Fast)\n");
        printf("4. Reset High Score\n");
        printf("5. Exit\n");
        printf("\nSelect option (1-5): ");

        if (scanf("%d", &choice) != 1) {
            // clear invalid input
            while (getchar() != '\n');
            continue;
        }
        // clean newline leftover for subsequent getch() calls
        while (getchar() != '\n');

        if (choice == 1) {
            // Easy
            int easySpeed = 200;   // bigger Sleep -> slower obstacle
            int lives = 3;
            playGame(easySpeed, lives, &highScore);
        } else if (choice == 2) {
            // Medium
            int mediumSpeed = 120;
            int lives = 3;
            playGame(mediumSpeed, lives, &highScore);
        } else if (choice == 3) {
            // Hard
            int hardSpeed = 70;
            int lives = 3;
            playGame(hardSpeed, lives, &highScore);
        } else if (choice == 4) {
            // Reset high score
            highScore = 0;
            saveHighScore(highScore);
            printf("High score reset to 0. Press any key to continue...\n");
            getch();
        } else if (choice == 5) {
            printf("Thanks for playing! Goodbye.\n");
            break;
        } else {
            printf("Invalid option. Press any key to continue...\n");
            getch();
        }
    }
    return 0;
}