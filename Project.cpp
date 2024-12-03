#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define BOARD_X 40
#define BOARD_Y 20

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* gameMechanics;
Player* player;
Food* food;



int main(void)
{

    Initialize();

    while(!exitFlag && !gameMechanics->getLoseFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    gameMechanics = new GameMechs(BOARD_X, BOARD_Y); // Board size
    food = new Food();
    player = new Player(gameMechanics, food);

    // Generate initial food on the board
    food->generateFood(player->getPlayerPosList());
}

void GetInput(void)
{
    if (MacUILib_hasChar()) 
    {
        gameMechanics->setInput(MacUILib_getChar());
    } 

    else 
    {
        gameMechanics->clearInput(); // Clear input when no key is pressed
    }
}

void RunLogic(void)
{
    player->updatePlayerDir();

    // Move the player (snake) and handle game logic
    player->movePlayer();

    // Update game state (e.g., speed, delay, etc.)
    player->updatePlayerSpeed();
    player->updatePlayerDelay();

    // Check if the game has ended
    exitFlag = gameMechanics->getExitFlagStatus();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // Clear the screen for redrawing

    for (int y = 0; y < BOARD_Y; y++) 
    {
        for (int x = 0; x < BOARD_X; x++) 
        {
            if (y == 0 || y == BOARD_Y - 1 || x == 0 || x == BOARD_X - 1) 
            {
                MacUILib_printf("#"); // Draw border for the gameboard
            } 

            else 
            {
                bool isRendered = false;

                // Check if the position contains food
                objPosArrayList* foodList = food->getFood();
                for (int i = 0; i < foodList->getSize(); i++) 
                {
                    objPos foodPos = foodList->getElement(i);
                    if (foodPos.pos->x == x && foodPos.pos->y == y)
                    {
                        MacUILib_printf("%c", foodPos.getSymbol()); // Spawn food
                        isRendered = true;
                        break;
                    }
                }

                // If no food, check if the position contains part of the snake
                if (!isRendered) 
                {
                    objPosArrayList* playerList = player->getPlayerPosList();
                    for (int i = 0; i < playerList->getSize(); i++) 
                    {
                        objPos snakePart = playerList->getElement(i);
                        if (snakePart.pos->x == x && snakePart.pos->y == y) 
                        {
                            MacUILib_printf("*"); // Render snake segment
                            isRendered = true;
                            break;
                        }
                    }
                }

                // If neither food nor snake print empty space
                if (!isRendered) 
                {
                    MacUILib_printf(" ");
                }
            }
        }

        MacUILib_printf("\n");
    }

    // Display game info
    MacUILib_printf("Score: %d\n", gameMechanics->getScore());
    MacUILib_printf("Apple, Banana, Grape, & Super Fruit(20%% chance)\n");
    MacUILib_printf("Press 'ESC' to exit.\n");
}



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   


    if (gameMechanics->getLoseFlagStatus()) // game over screen if you lose or quit on purpose
    {
        MacUILib_printf("Game Over! You lost. Your final score is: %d", gameMechanics->getScore());
    } 

    else 
    {
        MacUILib_printf("Congratulations! You ended the game. Your final score is: %d",gameMechanics->getScore());
    }

    delete player; // frees memory
    player = nullptr;

    delete food; // frees memory
    food = nullptr;

    delete gameMechanics; // frees memory
    gameMechanics = nullptr;

    

    MacUILib_uninit();
}
