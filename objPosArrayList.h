#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        ~objPosArrayList();

        objPosArrayList(const objPosArrayList& copy);
        objPosArrayList& operator=(const objPosArrayList& copy);

        //added move constructor and assingment operator
        objPosArrayList(objPosArrayList&& other) noexcept;
        objPosArrayList& operator=(objPosArrayList&& other) noexcept; 

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif