# Lab 1 The Trouble with Concurrent Programming

## 实验内容

本实验包含两部分内容. 

* 在第一部分, 你将编写, 编译并最终运行一个简单的C++程序, 以此来创建, 添加, 移除按优先级排序的双向链表中的元素. 
* 在第二部分, 你要使用这个程序来熟悉`Nachos`以及它的(并不完整)线程系统工作代码. 

在随后的实验中, 你将会使用到这个线程系统, 但就现在, 你就好好利用现有的代码来享受并发编程的乐趣吧!

## 按优先级排序的双向链表(20分)

基于以下定义, 编写一个C++程序实现双向链表:

``` c++
class DLLElement {
public:
    DLLElement(void* itemPtr, int sortKey); // initialize a list element
    DLLElement* next; // next element on list
    // NULL if this is the last
    DLLElement* prev; // previous element on list
    // NULL if this is the first
    int key; // priority, for a sorted list
    void* item; // pointer to item on the list
};
class DLList {
public:
    DLList(); // initialize the list
    ~DLList(); // de-allocate the list
    void Prepend(void* item); // add to head of list (set key = min_key-1)
    void Append(void* item); // add to tail of list (set key = max_key+1)
    void* Remove(int* keyPtr); // remove from head of list
    // set *keyPtr to key of the removed item
    // return item (or NULL if list is empty)
    bool IsEmpty(); // return true if list has elements
    // routines to put/get items on/off list in order (sorted by key)
    void SortedInsert(void* item, int sortKey);
    void* SortedRemove(int sortKey); // remove first item with key==sortKey
    // return NULL if no such item exists
private:
    DLLElement* first; // head of the list, NULL if empty
    DLLElement* last; // last element of the list, NULL if empty
};
```

双向链表应保证各结点按照`int`类型的`key`值进行排序.(当插入操作没有取`key`作参数时, 也应该为该操作分配`key`值). 你的代码应包含在如下三个文件中: `dllist.h`, `dllist.cc`, `dllist-driver.cc`. 前两个文件应该提供上述代码中两个`class`的定义以及实现, 第三个文件应该包含两个函数: 

* 一个函数生成`N`个结点, 每个结点的`key`值随机(或是为了方便调试, 你可以手动输入合适的key值), 并将这些结点插入到双向链表中 
* 另一个函数则从链表头开始移除`N`个结点, 并将移除的结点打印在控制台上
* 两个函数都应该取`int`类型的`N`以及一个指向链表的指针作为参数

为了验证你是否正确实现了`class`和驱动函数, 请单独创建一个文件(比如`main.cpp`), 文件中包含`main`函数. 

1. 在函数中, 首先申请链表, 然后调用上述的驱动程序, 并给参数传递一个合适的值. 
2. 你需要给我们演示, 你在按排序顺序插入了一个结点后, 又准确地删除了该结点. 
3. 你也可以做其他的测试样例来验证说, 你确实实现了一个双向链表

建议你在`Linux/x86`平台上, 使用`gcc`编译, 以确保你的程序可以在实验的第二部分内容里与`Nachos`进行交互
