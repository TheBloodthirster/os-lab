#include <iostream>
#include "dllist.h"
#include <ctime>
#include <cstdlib>

#define H_DLLIST_INCLUDED
#define RANDOM_RANGE 256

// using namespace std;

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
        std::cout << "[*] key = " << key << std::endl
             << "[*] item = " << *item << std::endl;
        // list->SortedInsert((void *)item, key);
    }
}

void delHdrNode(IN DLList *list, IN int n)
{
    int *item;
    // TODO: complete the func
}

int main() {
    int n;
    DLList *list = new DLList();

    std::cout << "[+] Created a DLList named list" << std::endl;
    std::cout << "[+] Just Create 1 node in the list" << std::endl;
    genRandomNode(list, 1);
    return 0;
}



