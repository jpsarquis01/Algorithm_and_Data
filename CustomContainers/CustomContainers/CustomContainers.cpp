
#include <iostream>
#include "Array.h"
#include "Vector.h"

int GetValue(int* data, int size, int index)
{
    if (index < size)
    {
        return data[index];
    }

    return 0;
}


int main()
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

