#include "Food.h"

Food::Food()
{
    foodBin = new objPosArrayList(); //food storage list
}

Food::~Food()   //memory clean up
{
    delete foodBin;
    foodBin = nullptr;
}

void Food::generateFood(const objPosArrayList* blockOff) { //checks where to spawn food
    int xCoord, yCoord;
    bool validCoords;

    // Clear the existing food list
    while (foodBin->getSize() > 0) 
    {
        foodBin->removeTail();
    }

    // Generate 3 food items
    for (int i = 0; i < FOOD_NUMBER; i++) 
    {
        validCoords = false;

        // Decide if this is a special food (20% chance for one special food)
        bool isSpecialFood = (i == 0 && rand() % 5 == 0);

        // Keep trying until valid coordinates are found
        while (!validCoords) 
        {
            validCoords = true;
            xCoord = rand() % (BOARD_X - 2) + 1; // Within board bounds
            yCoord = rand() % (BOARD_Y - 2) + 1;

            // Check against blocked positions (snake body)
            for (int j = 0; j < blockOff->getSize(); j++) 
            {
                if (xCoord == blockOff->getElement(j).pos->x && yCoord == blockOff->getElement(j).pos->y) 
                {
                    validCoords = false;
                    break;
                }
            }

            // Check against existing food positions
            for (int j = 0; j < foodBin->getSize(); j++) 
            {
                if (xCoord == foodBin->getElement(j).pos->x && yCoord == foodBin->getElement(j).pos->y) 
                {
                    validCoords = false;
                    break;
                }
            }
        }

        // Add the new food to the food list
        char foodSymbol = isSpecialFood ? specialFoodSymbol : foodSymbols[i % 3];
        foodBin->insertTail(objPos(xCoord, yCoord, foodSymbol));
    }
}

objPosArrayList* Food::getFood() const
{
    return foodBin;
}
