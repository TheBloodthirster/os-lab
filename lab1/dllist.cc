#include <iostream>
#include "dllist.h"

using namespace std;

// initialize a list element
DLLElement::DLLElement(IN void *itemPtr, IN int sortKey)
{
    key = sortKey;  // priority, for a sorted list
    item = itemPtr; // pointer to item on the list
    next = NULL;    // next element on list
                    // NULL if this is the last
    prev = NULL;    // previous element on list
                    // NULL if this is the first
}

// initialize the list
DLList::DLList()
{
    first = NULL; // head of the list, NULL if empty
    last = NULL;  // last element of the list, NULL if empty
}

// de-allocate the list
DLList::~DLList()
{
    DLLElement *currElem = first; // current element in the DLList
    DLLElement *nextElem = NULL;  // next element in the DLList
    while (currElem != NULL)
    { // delete all the element in the DLList from head to the tail
        nextElem = currElem->next;
        delete currElem;
        currElem = nextElem;
    }
}


// DLList::Append(void *item) {}