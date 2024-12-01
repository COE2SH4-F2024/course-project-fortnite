#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "stdlib.h"
#include "time.h"

#define BOARD_X 40
#define BOARD_Y 20
#define FOOD_NUMBER 1

class Food 
{
private:
    objPosArrayList *foodBin;
    char foodSymbols[3] = {'A', 'B', 'G'};
    bool isSpecialFood; // Flag to indicate if special food is active


public:
    Food(); // Constructor
    ~Food(); // Destructor (if needed)
    // Food(const Food& other);             // Copy Constructor
    // Food& operator=(const Food& other);  // Copy Assignment Operator

    void generateFood(const objPosArrayList *blockOff);
    objPosArrayList* getFood() const;
};

#endif