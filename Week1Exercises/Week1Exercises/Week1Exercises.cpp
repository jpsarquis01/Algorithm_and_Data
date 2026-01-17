// Week1Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <vector>
#include <chrono>

std::chrono::steady_clock::time_point gStartTime;

void StartAlgorithm()
{
    std::cout << "Algorithm Started\n";
    gStartTime = std::chrono::high_resolution_clock::now();
}
void PrintDuration()
{
    std::chrono::steady_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - gStartTime).count();
    std::cout << "Duration: " << duration << "\n";
}

// [0][][][][][][][][][][]
void PrintRandomValues(int* intArray, int maxSize, int maxValues)
{
    for (int i = 0; i < maxValues; ++i)
    {
        int randIndex = i;// rand() % maxSize;
        int value = intArray[randIndex];
        std::cout << "Value at index: " << randIndex << " is: " << value << "\n";
    }
}
void ConstantTimeComplexity()
{
    // Create:​
    // 2 Arrays​
    // Add 100 items indexed by "i" to one array​
    // Add 10000 items indexed by "i" to the other array​
    // Print​
    // The value of 20 random elements in each array​
    // The time it took to get each value
    // Summary: the more items that get processed, the time does not change

    std::array<int, 100> intArrayA;
    std::array<int, 10000> intArrayB;
    for (int i = 0; i < 100; ++i)
    {
        intArrayA[i] = i;
    }
    for (int i = 0; i < 10000; ++i)
    {
        intArrayB[i] = i;
    }

    StartAlgorithm();
    std::cout << "Printing ArrayA:\n";
    PrintRandomValues(intArrayA.data(), 100, 20);
    PrintDuration();

    std::cout << "\n";

    StartAlgorithm();
    std::cout << "Printing ArrayB:\n";
    PrintRandomValues(intArrayB.data(), 10000, 20);
    PrintDuration();
}

int GetNumberOfRepeats(const std::vector<int>& vec, int value)
{
    int count = 0;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == value)
        {
            ++count;
        }
    }
    return count;
}
void LinearTimeComplexity()
{
    // Create:​
    // 2 Vectors​
    // Add 100 items with random numbers between 1 - 50​
    // Add 10000 items with random numbers between 1 - 50​
    // Ask for a number input​
    // Print : ​
    // The number of times that number repeats​
    // The time it took to get each value​
    // Summary: the more items being processed, the time increases proportionally

    std::vector<int> intVectorA;
    std::vector<int> intVectorB;
    intVectorA.resize(100);
    for (int i = 0; i < intVectorA.size(); ++i)
    {
        intVectorA[i] = (rand() % 50) + 1;
    }
    intVectorB.resize(100000);
    for (int i = 0; i < intVectorB.size(); ++i)
    {
        intVectorB[i] = (rand() % 50) + 1;
    }

    int inputNumber = 0;
    std::cout << "Enter a number between 1-50:\n";
    std::cin >> inputNumber;

    int count = 0;
    StartAlgorithm();
    count = GetNumberOfRepeats(intVectorA, inputNumber);
    std::cout << "Vector A repeats (" << inputNumber << "): " << count << " times\n";
    PrintDuration();

    std::cout << "\n";

    StartAlgorithm();
    count = GetNumberOfRepeats(intVectorB, inputNumber);
    std::cout << "Vector B repeats (" << inputNumber << "): " << count << " times\n";
    PrintDuration();
}

void PrintAtIntervals(const std::vector<int>& vec, int interval)
{
    for (int i = 0; i < vec.size(); i += interval)
    {
        std::cout << "(" << i << " : " << vec[i] << ") ";
    }
    std::cout << "\n";
}
void PrintAtIntervalsWithCopy(std::vector<int> vec, int interval)
{
    for (int i = 0; i < vec.size(); i += interval)
    {
        std::cout << "(" << i << " : " << vec[i] << ") ";
    }
    std::cout << "\n";
}

void LogarithmicTimeComplexity()
{
    // Create:​
    // 2 Vectors​
    // Add 100 items with random numbers between 1 - 100​
    // Add 10000 items with random numbers between 1 - 100​
    // Ask for a number between 1 and 10​
    // Print​
    // The value at each interval​
    // for (int i = 0; i < count; i += inputValue)​
    //     print(vector[i])​
    //     The time it took print the values for each vector​
    // Summary: as items are added, the time increases, but at a scaled down rate

    std::vector<int> intVectorA;
    std::vector<int> intVectorB;
    intVectorA.resize(100);
    intVectorB.resize(1000);
    for (int i = 0; i < intVectorA.size(); ++i)
    {
        intVectorA[i] = (rand() % 100) + 1;
    }
    for (int i = 0; i < intVectorB.size(); ++i)
    {
        intVectorB[i] = (rand() % 100) + 1;
    }

    int interval = 0;
    std::cout << "Enter a number between 1-10:\n";
    std::cin >> interval;

    StartAlgorithm();
    std::cout << "Vector A intervals\n";
    PrintAtIntervals(intVectorA, interval);
    PrintDuration();
    std::cout << "\n";
    // NOTE: this is to show the time requirements to allocate, copy, and deallocate data in a function
    StartAlgorithm();
    std::cout << "Vector A with copy\n";
    PrintAtIntervalsWithCopy(intVectorA, interval);
    PrintDuration();

    std::cout << "\n\n";

    StartAlgorithm();
    std::cout << "Vector B intervals\n";
    PrintAtIntervals(intVectorB, interval);
    PrintDuration();
    std::cout << "\n";
    // NOTE: this is to show the time requirements to allocate, copy, and deallocate data in a function
    StartAlgorithm();
    std::cout << "Vector B with copy\n";
    PrintAtIntervalsWithCopy(intVectorB, interval);
    PrintDuration();
}

void PrintNextPairIndices(const std::vector<int>& vec)
{
    // to speed up options:
    //  - when adding to the list, sort
    //      - trade off is longer initialization, but faster pairing check
    //  - could iterate through the min/max (1-50) and find all the indices for each index
    //      - trade off is slower for smaller list of items, but more benefits for large lists
    //  - could cache the pairs and reuse
    //      - trade off is more memory use, but faster comparision
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < vec.size(); ++j)
        {
            if (vec[i] == vec[j])
            {
                std::cout << "Value (" << vec[i] << ") repeats at (" << i << ", " << j << ");\n";
            }
        }
    }
}
void QuadraticTimeComplexity()
{
    // Create:​
    // 2 Vectors​
    // Add 100 items with random numbers between 1 - 50​
    // Add 10000 items with random numbers between 1 - 50​
    // Print​
    // The every number that repeats index of its first duplicate​
    // Eg : if vector[2] = 10 and vector[7] = 10​
    // Print "Value 10 has a pair at index 2 and 7​
    // The time it took to get the results for each vector
    // Summary: As the input size increase, time complexity increases exponentially
    std::vector<int> intVectorA;
    std::vector<int> intVectorB;
    intVectorA.resize(10);
    intVectorB.resize(50);
    for (int i = 0; i < intVectorA.size(); ++i)
    {
        intVectorA[i] = (rand() % 50) + 1;
    }
    for (int i = 0; i < intVectorB.size(); ++i)
    {
        intVectorB[i] = (rand() % 50) + 1;
    }

    StartAlgorithm();
    std::cout << "Vec A Pairs: \n";
    PrintNextPairIndices(intVectorA);
    PrintDuration();

    std::cout << "\n";
    StartAlgorithm();
    std::cout << "Vec B Pairs: \n";
    PrintNextPairIndices(intVectorB);
    PrintDuration();

}

int main()
{
    // Scenario:​
    // You are playing a board game and you are given dice(D6) to roll​
    // You can get more dice as you play​
    // Print : ​
    //  All the permutations of potential dice rolls if you had 2 Dice​
    //  Print the time it took to calculate​
    //  All the permutations of potential dice rolls if you had 6 Dice​
    //  Print the time it took to calculate​
    //  All the permutations if the dice were swapped to D8​
    //      2 Dice as well as 6 Dice permutations​
    //      Print the time it took to calculate each​

    std::cout << "Week 1 Exercises!\n";
}
