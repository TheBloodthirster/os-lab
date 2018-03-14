#include <iostream>
#include "dllist.h"
#include <ctime>
#include <cstdlib>

#define H_DLLIST_INCLUDED
#define RANDOM_RANGE 256

using namespace std;

void genRandomNode(IN DLList *list, IN int n)
{
    int *item, key;
    // generating new rand() seed for each iteration
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        item = new int;
        *item = rand() % RANDOM_RANGE;
        key = RANDOM_RANGE / 2 - rand() % RANDOM_RANGE;
        cout << "[*] key = " << key << endl
             << "[*] item = " << *item << endl;
        list->SortedInsert((void *)item, key);
    }
}

void delHdrNode(IN DLList *list, IN int n)
{
    int *item;
    // TODO: complete the func
}
