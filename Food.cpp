#include "Food.h"

Food::Food()
{
    foodBin = new objPosArrayList();
}

Food::~Food()
{
    delete foodBin;
    foodBin = nullptr;

}

// // Copy Constructor
// Food::Food(const Food& other)
// {
//     // Perform deep copy
//     foodBin = new objPosArrayList(*other.foodBin);
// }

// // Copy Assignment Operator
// Food& Food::operator=(const Food& other)
// {
//     if (this == &other) {
//         return *this; 
//     }

//     delete foodBin;

//     foodBin = new objPosArrayList(*other.foodBin);

//     return *this;
// }

void Food::generateFood(const objPosArrayList* blockOff) {
    int xCoord, yCoord;
    bool validCoords = false;

    // Clear the existing food list
    while (foodBin->getSize() > 0) {
        foodBin->removeTail();
    }

    // Toggle between normal and special food
    isSpecialFood = (rand() % 5 == 0); // 20% chance for special food

    static int fruitIndex = 0; // Keeps track of which fruit to spawn next
    fruitIndex = (fruitIndex + 1) % 3; // Cycle through normal fruits

    char foodSymbol = isSpecialFood ? 'S' : foodSymbols[fruitIndex];

    while (!validCoords) {
        validCoords = true;
        xCoord = rand() % (BOARD_X - 2) + 1; // Ensure within board bounds
        yCoord = rand() % (BOARD_Y - 2) + 1;

        // Check against blocked positions (snake body)
        for (int j = 0; j < blockOff->getSize(); j++) {
            if (xCoord == blockOff->getElement(j).pos->x && yCoord == blockOff->getElement(j).pos->y) {
                validCoords = false;
                break;
            }
        }
    }

    // Add the new food
    foodBin->insertTail(objPos(xCoord, yCoord, foodSymbol));
}



objPosArrayList *Food::getFood() const
{
    return foodBin;
}