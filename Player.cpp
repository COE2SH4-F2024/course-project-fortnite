#include "Player.h"
#include "objPosArrayList.h"


Player::Player(GameMechs* thisGMRef, Food *foodRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = foodRef;

    // more actions to be included

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(20, 10, '*')); // Starting Position in the middle of the board
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    playerPosList = nullptr;

}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList->getHeadElement();
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput(); // Get input from game mechanisms

    if (input == 27) { // ASCII code for Escape key
        mainGameMechsRef->setExitTrue(); // Ends the game
    }

    switch (input) //FSM for the snake movement
    {
        case 'w': case 'W':
            if (myDir != DOWN) myDir = UP;
            break;

        case 's': case 'S':
            if (myDir != UP) myDir = DOWN;
            break;

        case 'a': case 'A':
            if (myDir != RIGHT) myDir = LEFT;
            break;

        case 'd': case 'D':
            if (myDir != LEFT) myDir = RIGHT;
            break;

        default:
            break; // Ignore invalid inputs
    }
    mainGameMechsRef->clearInput(); // Clear input after processing          
}

void Player::movePlayer()
{
    if (myDir == STOP) return; // Do nothing if direction is STOP

    objPos newHead = playerPosList->getHeadElement(); // Get current head position

    // Update head position based on direction
    switch (myDir) 
    {
        case UP:    newHead.pos->y--; break;
        case DOWN:  newHead.pos->y++; break;
        case LEFT:  newHead.pos->x--; break;
        case RIGHT: newHead.pos->x++; break;
        default:    break;
    }

    // Handles wraparound
    if (newHead.pos->x < 1) 
    {
        newHead.pos->x = BOARD_X - 2;
    }

    else if (newHead.pos->x > BOARD_X - 2) 
    {
        newHead.pos->x = 1;
    }

    if (newHead.pos->y < 1) 
    {
        newHead.pos->y = BOARD_Y - 2;
    }

    else if (newHead.pos->y > BOARD_Y - 2)
    {
        newHead.pos->y = 1;
    }

    // Add the new head to the front of the snake
    playerPosList->insertHead(newHead);

    // Remove the tail only if the snake is not growing
    if (!isGrowing) 
    {
        playerPosList->removeTail();
    } 

    else 
    {
        isGrowing = false; // Reset the growth flag
    }

    moveCount++; // Increment move count

    // Check for food and self-collision
    foodCollisionCheck(*food);
    selfCollisionCheck();
}


// More methods to be added

// Check for collision with food
void Player::foodCollisionCheck(const Food& foodRef) 
{
    objPosArrayList* foodList = food->getFood();
    objPos head = playerPosList->getHeadElement();

    for (int i = 0; i < foodList->getSize(); ++i)
    {
        objPos foodPos = foodList->getElement(i);
        if (head.isPosEqual(&foodPos)) 
        {
            if (foodPos.getSymbol() == 'S') // Special food detected
            { 
                mainGameMechsRef->incrementScore(5); // Bonus points (5)

                // Reset the snake to only the head
                while (playerPosList->getSize() > 1) 
                {
                    playerPosList->removeTail();
                }
            } 

            else  // Normal food
            {
                mainGameMechsRef->incrementScore(1); // Normal food score (1)
                isGrowing = true;  // Allow the snake to grow
            }

            food->generateFood(playerPosList);  // Generate new food
            return;
        }
    }
}






// Check for self-collision
void Player::selfCollisionCheck()
{
    objPos head = playerPosList->getHeadElement(); // Get the head of the snake

    // Start checking from the second element because the head is already at index 0
    for (int i = 1; i < playerPosList->getSize(); ++i) 
    {
        objPos bodyElement = playerPosList->getElement(i); // Get each body segment

        if (head.isPosEqual(&bodyElement)) 
        {
            // If the head collides with any body segment, game over
            mainGameMechsRef->setLoseFlag(); // Set the lose flag in GameMechs
            return;
        }
    }
}



// Update player's speed
void Player::updatePlayerSpeed()
{
    int currentSpeed = mainGameMechsRef->getSpeed();
    mainGameMechsRef->setSpeed(currentSpeed + 1);
}

// Update player's delay
void Player::updatePlayerDelay()
{
    int currentDelay = mainGameMechsRef->getDelay();
    mainGameMechsRef->setDelay(currentDelay - 5000);    //reduces delay, increasing game speed
}

objPosArrayList* Player::getPlayerPosList() const {
    return playerPosList;
}

int Player::getMoveCount() const {
    return moveCount;
}

Player::Dir Player::getDirection() const {
    return myDir;
}




