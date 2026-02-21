
#include <iostream>
#include <string>
#include "Array.h"
#include "Vector.h"
#include "PriorityQueue.h"
#include "Vector2.h"


//int GetValue(int* data, int size, int index)
//{
//    if (index < size)
//    {
//        return data[index];
//    }
//
//    return 0;
//}

void Assigment1()
{
    std::cout << "Custom Containers\n";

    Array<int, 5> myInts(0);
    for (std::size_t i = 0; i < myInts.Size(); ++i)
    {
        myInts[i] = i + 1;
    }

    for (std::size_t i = 0; i < myInts.Size(); ++i)
    {
        std::cout << "Value at " << i << " is " << myInts[i] << "\n";
    }

    Vector<int> myVector;
    myVector.Reserve(10);
    for (std::size_t i = 0; i < myInts.Size(); ++i)
    {
        myVector.PushBack(i + 1);
        std::cout << "Value at " << i << " is " << myInts[i] << "\n";
    }
    std::cout << "Vector\n";
    std::cout << "Vector size: " << myVector.Size() << "\n";
    std::cout << "Vector capacity: " << myVector.Capacity() << "\n";

}

void ClassWork()
{
    Array<int, 10> myInts;
    for (int i = 0; i < myInts.Size(); ++i)
    {
        myInts[i] = rand() % 100;
    }

    for (Array<int, 10>::Iterator iter = myInts.Begin(); iter != myInts.End(); ++iter)
    {
        std::cout << "Array Value: " << *iter << "\n";
    }

    std::sort(myInts.Begin(), myInts.End());
    std::cout << "\nmyInts Sorted: \n";
    for (Array<int, 10>::Iterator iter = myInts.Begin(); iter != myInts.End(); ++iter)
    {
        std::cout << "Array Value: " << *iter << "\n";
    }
}

void Class4()
{
    PriorityQueue<int> priorityQueue;
    for (int i = 0; i < 20; ++i)
    {
        int value = rand() % 100;
        priorityQueue.Push(value);
        std::cout << value << " ";
    }
    std::cout << "\n\n";
    while (!priorityQueue.Empty())
    {
        std::cout << priorityQueue.Top() << " ";
        priorityQueue.Pop();
    }
}

struct Item
{
    std::string name;
    Vector2 position;
};

int main()
{
    Vector<Item> items;
    KDTree<float, 2> itemLocations;
    int maxItems = 100;
    items.Resize(maxItems);
    for (int i = 0; i < maxItems; ++1)
    {
        items[i].name = "ItemName" + std::to_string(i);
        items[i].position = { (float)(rand() % 501), (float)(rand() % 501) };
        
        itemLocations.AddItem(&items[i].position.x, &items[i]);
    }

    itemLocations.BuilsTree();

    Vector2 minRange = { 200.0f, 200.0f };
    Vector2 maxRange = { 300.0f, 300.0f };
}

