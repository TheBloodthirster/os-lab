# Lab 1 The Trouble with Concurrent Programming

## 实验内容

本实验包含两部分内容. 

* 在第一部分, 你将编写, 编译并最终运行一个简单的C++程序, 以此来创建, 添加, 移除按优先级排序的双向链表中的元素. 
* 在第二部分, 你要使用这个程序来熟悉`Nachos`以及它的(并不完整)线程系统工作代码. 

在随后的实验中, 你将会使用到这个线程系统, 但就现在, 你就好好利用现有的代码来享受并发编程的乐趣吧!

## 编译Nachos

鉴于`Nachos`是32位操作系统, 因为`Ubuntu`的64位C/C++库存在一定兼容问题, 且我个人在MakeFile里的编译选项中加入`-m32`后依旧出现大量问题后, 我就直接抛弃使用64位的Linux系统. 我使用如下办法成功编译好了`Nachos`

1. 在VMware里安装了一个32位的Ubuntu 14.04.5
2. 在32位ubuntu里, 修改source.list后apt更新, 安装vim和g++
3. 使用命令`tar -zxvf code-linux.tar_2.gz`解压
4. 进入到文件夹`/nachos-3.4/code`里
5. 使用`vim`修改`Makefile`, 将里面的`gmake`更改为`make`
6. 使用命令`make`编译`Nachos`
7. 进入`threads`文件夹, 发现里面有许多`.o`文件以及`nachos`可执行文件, 说明编译成功

## 按优先级排序的双向链表 (20 分)

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

## 实验代码

1. 将本仓库`lab1`目录下的`dllist.h`, `dllist.cc`和`dllist-driver.cc`放在`Nachos`源码的`/nachos-3.4/code/threads`目录下. 
2. 对`Makefile.common`在`THREAD_H`中添加`../threads/dllist.h\` (可以参照本仓库中的`Makefile.common`文件)
3. 对`Makefile.common`在`THREAD_C`中添加`../threads/dllist.cc\`和`../threads/dllist-driver.cc\` (可以参照本仓库中的`Makefile.common`文件)
4. 使用`make`命令编译即可

由于第一部分的内容, 并不需要和`nachos`联系起来, 所以为了方便测试, 我写了一个单独的`Makefile`专门用于编译`dllist.cc`, `dllist.h`和`dllist-driver.cc`, 同时我还新加了`dllist-driver.h`文件用于编译, 在`main.cpp`内调用`dllist-driver.h`内的函数进行测试, 生成一个名为`test`的可执行文件. 

## 熟悉Nachos并理解其线程系统 (80 分)

在本部分内容中, 你将要理解`Nachos`的线程系统是如何工作的(在后续实验中你还会扩展它的功能). 一般来说, `Nachos`线程原语(primitive)仅在`Nachos`操作系统内核的内部使用, 从未直接用于用户程序. 实际上这些原语跟现实操作系统管理进程时用到的内部原语十分相似. 

为了理解他们到底是如何工作的, 在本实验中(还有`Lab 3`), 我们将直接使用`线程原语`来运行简单的并发程序, 比如`Unix(Solaris)`的应用程序. 如果你为此感到困惑, 请不用担心. 

只需使用`make`命令即可编译`nachos`的可执行程序. 在目录`code`里运行`make`(无需任何参数), 生成的`nachos`可执行程序存放在`threads`子目录里. 如果你现在已经在`threads`子目录下和一个`nachos`可执行程序在一起, 你即可输入命令`nachos`(如果没有生效, 可以尝试`./nachos`)来简单测试`Nachos`. 

如果你有仔细阅读过`threads/main.cc`, 你会发现你正在执行`threadtest.cc`的`ThreadTest`函数. `ThreadTest`是一个简单的并发程序示例. 在本例中, 有两个的独立线程在"同一时刻"控制执行并且在进程中访问相同的数据. 你的首要目标就是程序所使用的线程原语, 然后做些实验来帮助理解程序运行时的多线程到底是如何发生的. 为了理解代码执行路径, 你可以在简单测试示例里跟踪代码. 请阅读`Section 2.2`(看`Tracing and Debugging Nachos Programs`部分)中的相关提示.

接下来的目标, 你有多种方式来展示并发代码, 比如在运行时各线程以不确定的顺序执行.(Your next goal is to show the many ways that concurrent code like this can break given a nondeterministic ordering of thread executions at runtime.). 事先暴露的问题越多, 你之后编写代码会越顺利. 

你的任务是, 创建一个你自己的`ThreadTest`函数, 该函数启动一个`T`线程以访问一个特定共享的数据结构: 你在第一部分里实现的非同步按优先级排序的双向链表. 非同步是指你的`ThreadTest`和你实现的链表, 都不应该使用`信号`, `互斥锁`, `中断禁用`或其他你将在后续学习到的同步机制. 这些机制都是为了解决那些你应当在本次实验中体验到并需要说明的问题. 

你的各个测试用线程, 都需要调用`dllist-driver.cc`中的两个驱动函数(第一个是插入结点, 第二个是移除结点). 注意了, 你应该在启动线程之前, 就在你的`ThreadTest`函数中创建链表出来, `T`和`N`都应当使用命令行设置. 我们"正确的"或说"预期的"结果应该是, 每个插入到链表中的结点在移除对应的原语中返回`1`次, 每一个调用移除函数应当返回`1`个合法结点, 当最后一个线程结束时链表也应当为空.(The "correct" or  expected" behavior is that each item inserted into the list is returned by the remove primitive exactly once, that every remove call returns a valid item, and that the list is empty when the last thread has finished.) 因为链表经过排序, 每个线程也都期望移除的结点也顺序排序. 尽管当`T > 1`时它们也不一定是线程放回链表的相同结点.(even though they won't necessarily be the same items that thread put into the list if T > 1.)

一旦你写好了你的测试程序, 你的任务就是识别并说明在这种简单情形下可能发生的任何不对or不在预期内的结果. 在你们的demo和报告中, 你们应当展示一些在程序运行时, 可能因特定执行发生交错而造成的困难. 你的带选项和输出的用于展示bug行为的双向链表和测试程序是最主要的编程挑战. 为了完成这些, 你需要修改代码来"强制"产生特定的线程交错bug, 并展示程序由于一些交错bug是如何运行失败的. 请阅读`Section 2.3`的笔记(看`Controlling the Order of Execution in Nachos`部分), 里面有关于线程交错和一些控制它们的方法的完整讨论. 

特别指出, 这部分的任务要求你完成以下步骤:

1. 复制你的`dllist.h`, `dllist.cc`和`dllist-driver.cc`文件到`threads`子目录里. 在`nachos`根目录的`Makefile.common`中修改`THREAD_H`和`THREAD_C`的定义以包含这些文件并更新`makefile`依赖关系. 这能确保你的文件被编译链接到`nachos`发行版内.
2. 创建一个类似于文件`threadtest.cc`的驱动程序文件，该文件使用`dllist-driver.cc`中的函数对`DLList`类进行调用. 修改`thread/main.cc`以便执行`nachos`命令时, 执行的是新的驱动程序文件, 而非文件`threadtest.cc`中的函数`ThreadTest`.
3. 修改你的`DLList`类和`ThreadTest`以强制产生线程交错bug, 解释这里产生的虽不正确但十分有趣的行为. 在演示时, 你应当能够枚举和演示每一个情景, 请使用`Section 2.2.3`中所描述的命令行标志(见`Defining New Command-Line Flags for Nachos`), 而不是总是重新编译你的测试程序
4. 认真思考你能演示的bug行为, 并将其分类. 你的报告中应该描述每一种类型的bug, 概述线程交错部分并解释线程交错是如何导致bug行为的. 注意, 如果不同线程之间有着不同的交错行为, 那么你可能会发现更多有趣的行为.

你可以不详尽, 但你必须要彻底解决错误. 请着重于那些最"有趣"的交错, 避免花费时间描述or展示大量相似的工作. 实验的目标是让你明白这些并发行为, 而不是给彼此制造繁琐的工作. 
