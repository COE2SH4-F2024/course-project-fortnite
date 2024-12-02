#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

// Constructor: Initialize the list with default capacity
objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;   // Set maximum capacity
    listSize = 0;                    // Initialize list size to 0
    aList = new objPos[arrayCapacity]; // Allocate memory for the array
}

// Destructor: Clean up allocated memory
objPosArrayList::~objPosArrayList()
{
    delete[] aList; // Free the dynamically allocated memory
}

// Copy Constructor: Create a deep copy of another objPosArrayList
objPosArrayList::objPosArrayList(const objPosArrayList& copy)
{
    listSize = copy.listSize;
    arrayCapacity = copy.arrayCapacity;

    // Allocate new memory for the copied elements
    aList = new objPos[arrayCapacity];
    for (int i = 0; i < listSize; i++)
    {
        aList[i] = copy.aList[i];
    }
}

// Copy Assignment Operator: Assign values from another objPosArrayList
objPosArrayList& objPosArrayList::operator=(const objPosArrayList& copy)
{
    if (this == &copy) // Check for self-assignment
    {
        return *this;
    }

    // Clean up existing resources
    delete[] aList;

    // Copy new values
    listSize = copy.listSize;
    arrayCapacity = copy.arrayCapacity;

    // Allocate new memory and copy elements
    aList = new objPos[arrayCapacity];
    for (int i = 0; i < listSize; i++)
    {
        aList[i] = copy.aList[i];
    }

    return *this;
}

// Get the current size of the list
int objPosArrayList::getSize() const
{
    return listSize;
}

// Insert an element at the head of the list
void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity)
    {
        return; // Do nothing if capacity is exceeded
    }

    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;
    listSize++;
}

// Insert an element at the tail of the list
void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity)
    {
        return; // Do nothing if capacity is exceeded
    }

    aList[listSize] = thisPos;
    listSize++;
}

// Remove the head element of the list
void objPosArrayList::removeHead()
{
    if (listSize == 0)
    {
        return; // Do nothing if the list is empty
    }

    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

// Remove the tail element of the list
void objPosArrayList::removeTail()
{
    if (listSize == 0)
    {
        return; // Do nothing if the list is empty
    }

    listSize--;
}

// Get the head element of the list
objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0)
    {
        return objPos(); // Return a default objPos if the list is empty
    }

    return aList[0];
}

// Get the tail element of the list
objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0)
    {
        return objPos(); // Return a default objPos if the list is empty
    }

    return aList[listSize - 1];
}

// Get an element at a specific index
objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize)
    {
        return objPos(); // Return a default objPos for invalid indices
    }

    return aList[index];
}
