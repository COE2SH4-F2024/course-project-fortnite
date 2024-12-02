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

    while(exitFlag == false)  
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
    gameMechanics->setInput(MacUILib_getChar());
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
    MacUILib_clearScreen();    

    // Draw the board

    for (int y = 0; y < BOARD_Y; y++)
    {
        for (int x = 0; x < BOARD_X; x++)
        {
            if (y == 0 || y == BOARD_Y - 1 || x == 0 || x == BOARD_X - 1)
            {
                MacUILib_printf("#"); // Board boundary
            }
            else
            {
                bool isFood = false;

                // Check if there's food at this position
                objPosArrayList* foodList = food->getFood();
                for (int i = 0; i < foodList->getSize(); i++)
                {
                    objPos foodPos = foodList->getElement(i);
                    if (foodPos.pos->x == x && foodPos.pos->y == y)
                    {
                        MacUILib_printf("%c", foodPos.getSymbol());
                        isFood = true;
                        break;
                    }
                }

                if (!isFood)
                {
                    // Check if the snake occupies this position
                    objPosArrayList* playerList = player->getPlayerPosList();
                    bool isSnake = false;

                    for (int i = 0; i < playerList->getSize(); i++)
                    {
                        objPos snakePart = playerList->getElement(i);
                        if (snakePart.pos->x == x && snakePart.pos->y == y)
                        {
                            MacUILib_printf("*");
                            isSnake = true;
                            break;
                        }
                    }

                    if (!isSnake)
                    {
                        MacUILib_printf(" "); // Empty space
                    }
                }
            }
        }
        MacUILib_printf("\n");
    }

    // Display Game Info
    MacUILib_printf("Score: %d\n", gameMechanics->getScore());
    
    
    MacUILib_printf("Press 'ESC' to exit.\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   


    if (gameMechanics->getLoseFlagStatus()) 
    {
        MacUILib_printf("Game Over! You lost. Your final score is: %d", gameMechanics->getScore());
    } 

    else 
    {
        MacUILib_printf("Congratulations! You ended the game. Your final score is: %d",gameMechanics->getScore());
    }

    delete player;
    delete food;
    delete gameMechanics;

    

    MacUILib_uninit();
}
