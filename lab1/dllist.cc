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

// return true if list is empty
bool DLList::IsEmpty()
{
    // when first == NULL and last == NULL
    // list is empty
    if (!first && !last)
    {
        return true;
    }

    // list is not empty
    return false;
}

// add to head of list (set key = min_key-1)
void DLList::Prepend(IN void *item)
{
    if (IsEmpty())
    {
        // list is empty
        DLLElement *newNode = new DLLElement(item, 0);
        first = newNode;
    }
    else
    {
        // list is not empty
        DLLElement *newNode = new DLLElement(item, first->key - 1);
        first->prev = newNode;
        newNode->next = first;
        first = newNode;
    }
}

// add to tail of list (set key = max_key+1)
void DLList::Append(IN void *item)
{
    if (IsEmpty())
    {
        // list is empty
        DLLElement *newNode = new DLLElement(item, 0);
        first = newNode;
    }
    else
    {
        // list is not empty
        DLLElement *newNode = new DLLElement(item, last->key - 1);
        last->prev = newNode;
        newNode->next = last;
        last = newNode;
    }
}

// remove from head of list
// set *keyPtr to key of the removed item
// return item (or NULL if list is empty)
void* DLList::Remove(OUT int *keyPtr)
{
    void* temp;
    if (IsEmpty())
    {
        // list is empty
        return NULL;
    }
    else
    {
        // list is not empty
        // first != NULL
        first = first->next;
        *keyPtr = first->prev->key;
        temp = first->prev->item;
        delete first->prev;
        first->prev = NULL;
        return temp;
    }
}
