#include <iostream>
#include "dllist.h"
#include <ctime>
#include <cstdlib>

#define H_DLLIST_INCLUDED
#define RANDOM_RANGE 256

#ifndef H_DLLIST_DRIVER_INCLUDED
#define H_DLLIST_DRIVER_INCLUDED

void genRandomNode(IN DLList *list, IN int n);
void delHdrNode(IN DLList *list, IN int n);
void dllistDriverTest();
#endif