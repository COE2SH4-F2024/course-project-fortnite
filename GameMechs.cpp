#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;             
    exitFlag = false;      
    loseFlag = false;      
    score = 0;
    speed = 3;
    delay = 50000;              
    boardSizeX = 40;       
    boardSizeY = 20;       
    food = objPos(0, 0, 'F');    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;             
    exitFlag = false;      
    loseFlag = false;      
    score = 0;    
    speed = 3;
    delay = 50000;          
    boardSizeX = boardX;   
    boardSizeY = boardY;   
    food = objPos(0, 0, 'F');
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //no
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(int increment) {
    score += increment; // Add the increment value to the score
}


int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;    
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

int GameMechs::getSpeed() const
{
    return speed;
}

int GameMechs::getDelay() const
{
    return delay;
}

void GameMechs::setSpeed(int Nspeed)
{
    speed = Nspeed;
}

void GameMechs::setDelay(int Ndelay)
{
    delay = Ndelay;
}