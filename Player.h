#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food *foodRef);
        ~Player();

        objPos getPlayerPos() const; // Upgrade this in iteration 3. (Upgraded)       
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        int getMoveCount() const;             
        Dir getDirection() const;

        objPosArrayList* getPlayerPosList() const;

        void foodCollisionCheck(const Food& foodRef); // checks if the food is eaten
        void selfCollisionCheck();    // checks if the snake hits itself
        void updatePlayerSpeed();  
        void updatePlayerDelay();  

    private:
        objPosArrayList* playerPosList; // // Upgrade this in iteration 3. (Upgraded)         
        enum Dir myDir;

        // Reference to the main game mechanisms
        GameMechs* mainGameMechsRef;
        Food* food;

        int moveCount = 0;
        int snakeLength = 5; // (new) Fixed length for the snake
        bool isGrowing = false; //  (new)Flag to indicate whether the snake is growing after eating food

};

#endif