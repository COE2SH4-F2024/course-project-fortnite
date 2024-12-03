#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "stdlib.h"
#include "time.h"

#define BOARD_X 40
#define BOARD_Y 20
#define FOOD_NUMBER 3

class Food 
{
private:
    objPosArrayList *foodBin;
    char foodSymbols[3] = {'A', 'B', 'G'};
    char specialFoodSymbol = 'S'; // Special food symbol

public:
    Food(); // Constructor
    ~Food(); // Destructor

    void generateFood(const objPosArrayList *blockOff);
    objPosArrayList* getFood() const;
};

#endif
