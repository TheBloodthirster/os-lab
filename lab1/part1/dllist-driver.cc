#include "dllist-driver.h"

// generate N node with random key value
void genRandomNode(IN DLList *list, IN int n)
{
    int *item, key;
    // generating new rand() seed for each iteration
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        item = new int;
        *item = rand() % RANDOM_RANGE;
        key = rand() % RANDOM_RANGE;
        std::cout << "[*] generated node key = " << key << " item = " << *(int *)item << std::endl;
        list->SortedInsert((void *)item, key);
    }
}

// delete N node from head to tail
void delHdrNode(IN DLList *list, IN int n)
{
    void *item;
    int *key = new int;

    for (int i = 0; i < n; i++)
    {
        if (list->IsEmpty())
        {
            // list is empty NOW!
            std::cout << "[x] list is empty" << std::endl;
            return;
        }
        else
        {
            // list is not empty
            item = list->Remove(key);
            if (item != NULL)
            {
                std::cout << "[*] removed node key = " << *key << " item = " << *(int *)item << std::endl;
            }
            else
            {
                std::cout << "[*] removed node key = " << *key << " item = NULL" << std::endl;
            }
        }
    }
}

void dllistDriverTest()
{
    int n;
    int item1,item2;
    void *i1,*i2;
    std::cout << "[+] Created a DLList named list" << std::endl;
    DLList *list = new DLList();

    std::cout << "[*] Please input the value of n" << std::endl;
    std::cin >> n;
    std::cout << "[+] Just Create n node in the list" << std::endl;
    genRandomNode(list, n);
    std::cin >> item1;
    i1 = &item1;
    list->Prepend(i1);
    std::cin >> item2;
    i2 = &item2;
    list->Append(i2);
    std::cout << "[*] How many node you want to remove?" << std::endl;
    std::cin >> n;
    delHdrNode(list, n);
}
