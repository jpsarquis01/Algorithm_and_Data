// Week2Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>

std::chrono::steady_clock::time_point gStartTime;

void StartAlgorithm()
{
    gStartTime = std::chrono::high_resolution_clock::now();
}
void PrintDuration()
{
    std::chrono::steady_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - gStartTime).count();
    std::cout << "Duration: " << duration << "\n";
}

// Example 1 Screen Stack
// add screen to the top of the stack
void GoToScreen(const std::string& screenName, std::array<std::string, 10>& screens)
{
    for (int i = 0; i < screens.size(); ++i)
    {
        if (screens[i].empty())
        {
            screens[i] = screenName;
            break;
        }
    }
    std::cout << "(array) Go to Screen " << screenName << "\n";
}
// add screen to the top of the stack
void GoToScreen(const std::string& screenName, std::vector<std::string>& screens)
{
    screens.push_back(screenName);
    std::cout << "(vector) Go to Screen " << screenName << "\n";
}
// add screen to the top of the stack
void GoToScreen(const std::string& screenName, std::stack<std::string>& screens)
{
    screens.push(screenName);
    std::cout << "(stack) Go to Screen " << screenName << "\n";
}
void GoBack(std::array<std::string, 10>& screens)
{
    // find the last added screen, remove it
    for (int i = screens.size() - 1; i >= 0; --i)
    {
        if (!screens[i].empty())
        {
            std::cout << "(array) Go Back From " << screens[i] << "\n";
            screens[i] = "";
            break;
        }
    }
    // find the next last added screen and that is the screen you are on
    for (int i = screens.size() - 1; i >= 0; --i)
    {
        if (!screens[i].empty())
        {
            std::cout << "(array) Is On Screen " << screens[i] << "\n";
            break;
        }
    }
}
// leave top of the screen and go to previous screen
// what screen was left
// what screen you are on
void GoBack(std::vector<std::string>& screens)
{
    std::cout << "(vector) Go Back From " << screens.back() << "\n";
    screens.pop_back();
    std::cout << "(vector) Is On Screen " << screens.back() << "\n";
}
void GoBack(std::stack<std::string>& screens)
{
    std::cout << "(stack) Go Back From " << screens.top() << "\n";
    screens.pop();
    std::cout << "(stack) Is On Screen " << screens.top() << "\n";
}
void Example1ScreenStack()
{
    // Simple Screen Flow​
    // Create three containers​
    // Array​
    // Vector​
    // Stack​
    // Create functions for each of them to : ​
    // Go to a screen with an std::string screen​
    // Go Back​
    // For each : ​
    //  Go To Main Menu​
    //  Go To Level Setup​
    //  Go To Game​
    //  Go To Game Over​
    //  Return To Main Menu by going back​
    //  Print the time to process each type
    std::array<std::string, 10> screensArray;
    std::vector<std::string> screensVector;
    std::stack<std::string> screensStack;

    // Array Stack
    StartAlgorithm();
    std::cout << "Array:\n";
    GoToScreen("MainMenu", screensArray);
    GoToScreen("LevelSelect", screensArray);
    GoToScreen("GamePlay", screensArray);
    GoToScreen("GameOver", screensArray);
    GoBack(screensArray);
    GoBack(screensArray);
    GoBack(screensArray);
    PrintDuration();

    // Vector Stack
    StartAlgorithm();
    std::cout << "Vector:\n";
    GoToScreen("MainMenu", screensVector);
    GoToScreen("LevelSelect", screensVector);
    GoToScreen("GamePlay", screensVector);
    GoToScreen("GameOver", screensVector);
    GoBack(screensVector);
    GoBack(screensVector);
    GoBack(screensVector);
    PrintDuration();

    // Stack
    StartAlgorithm();
    std::cout << "Stack:\n";
    GoToScreen("MainMenu", screensStack);
    GoToScreen("LevelSelect", screensStack);
    GoToScreen("GamePlay", screensStack);
    GoToScreen("GameOver", screensStack);
    GoBack(screensStack);
    GoBack(screensStack);
    GoBack(screensStack);
    PrintDuration();
}

// Example 2 Movie Tickets
void EnterLine(const std::string& name, std::array<std::string, 10>& people)
{
    for (int i = 0; i < people.size(); ++i)
    {
        if (people[i].empty())
        {
            people[i] = name;
            break;
        }
    }

    std::cout << "(array) " << name << " is in line for a ticket\n";
}
void EnterLine(const std::string& name, std::vector<std::string>& people)
{
    people.push_back(name);
    std::cout << "(vector) " << name << " is in line for a ticket\n";
}
void EnterLine(const std::string& name, std::queue<std::string>& people)
{
    people.push(name);
    std::cout << "(queue) " << name << " is in line for a ticket\n";
}
void PurchaseTicket(std::array<std::string, 10>& people)
{
    // get first in the list
    std::cout << "(array) " << people[0] << " paid for ticket\n";
    // remove and move everyone up
    for (int i = 0; i < people.size() - 1; ++i)
    {
        people[i] = people[i + 1];
    }
}
void PurchaseTicket(std::vector<std::string>& people)
{
    // get first in the list
    std::cout << "(vector) " << people.front() << " paid for ticket\n";
    // remove and move everyone up
    people.erase(people.begin());
}
void PurchaseTicket(std::queue<std::string>& people)
{
    // get first in the list
    std::cout << "(queue) " << people.front() << " paid for ticket\n";
    // remove from the front
    people.pop();
}
void Example2MovieTickets()
{
    // Movie Tickets​
    // Create three containers​
    // Array​
    // Vector​
    // Queue​
    // Create functions for each of them to : ​
    // Enter Line with a std::string name​
    // Pay For Ticket​
    // For each : ​
    //  Add a few names to the container​
    //  Remove a couple names​
    //  Add a few more ​
    //  Process the remaining names in the containers
    std::array<std::string, 10> peopleArray;
    std::vector<std::string> peopleVector;
    std::queue<std::string> peopleQueue;

    // Array Queue
    StartAlgorithm();
    std::cout << "Array:\n";
    EnterLine("Joe", peopleArray);
    EnterLine("Ryan", peopleArray);
    EnterLine("Daisy", peopleArray);
    EnterLine("Elle", peopleArray);
    PurchaseTicket(peopleArray);
    PurchaseTicket(peopleArray);
    EnterLine("Bruce", peopleArray);
    EnterLine("Selina", peopleArray);
    EnterLine("Harvey", peopleArray);
    while (!peopleArray[0].empty())
    {
        PurchaseTicket(peopleArray);
    }
    PrintDuration();

    // Vector Queue
    StartAlgorithm();
    std::cout << "\nVector:\n";
    EnterLine("Joe", peopleVector);
    EnterLine("Ryan", peopleVector);
    EnterLine("Daisy", peopleVector);
    EnterLine("Elle", peopleVector);
    PurchaseTicket(peopleVector);
    PurchaseTicket(peopleVector);
    EnterLine("Bruce", peopleVector);
    EnterLine("Selina", peopleVector);
    EnterLine("Harvey", peopleVector);
    while (!peopleVector.empty())
    {
        PurchaseTicket(peopleVector);
    }
    PrintDuration();

    // Queue
    StartAlgorithm();
    std::cout << "\Queue:\n";
    EnterLine("Joe", peopleQueue);
    EnterLine("Ryan", peopleQueue);
    EnterLine("Daisy", peopleQueue);
    EnterLine("Elle", peopleQueue);
    PurchaseTicket(peopleQueue);
    PurchaseTicket(peopleQueue);
    EnterLine("Bruce", peopleQueue);
    EnterLine("Selina", peopleQueue);
    EnterLine("Harvey", peopleQueue);
    while (!peopleQueue.empty())
    {
        PurchaseTicket(peopleQueue);
    }
    PrintDuration();
}

// Exercise 3 Priority Queue Numbers
void Example3PriorityQueue()
{
    //Part 1​
    //    Create a priority_queue​
    //    Add random numbers to the priority_queue from 1 - 200​
    //    Add 10 numbers​
    //    Print out the order of the numbers in the priority_queue
    // Max Heap (default)
    std::priority_queue<int> myPriorityQueue;
    // Min Heap
    // std::priority_queue<int, std::vector<int>, std::greater<int>> myPriorityQueue;
    int maxNumbers = 10;
    int minRange = 1;
    int maxRange = 200;
    std::cout << "Adding Numbers\n";
    for (int i = 0; i < maxNumbers; ++i)
    {
        int value = minRange + (rand() % maxRange);
        std::cout << value << ", ";
        myPriorityQueue.push(value);
    }
    std::cout << "\n";
    while (!myPriorityQueue.empty())
    {
        std::cout << myPriorityQueue.top() << ", ";
        myPriorityQueue.pop();
    }
}

// Exercise 4 Class Priority Queue
class Student
{
public:
    Student() : mAge(0), mMark(0) {}
    void SetFirstName(const std::string& name) { mFirstName = name; }
    void SetLastName(const std::string& name) { mLastName = name; }
    void SetAge(int age) { mAge = age; }
    void SetMark(int mark) { mMark = mark; }
    void Print()
    {
        std::cout << mLastName << ", " << mFirstName << " Age (" << mAge << ") Mark (" << mMark << ")\n";
    }
    // override less than operator
    bool operator<(const Student& rhs) const
    {
        if (rhs.mMark == mMark)
        {
            return rhs.mLastName < mLastName;
        }
        return rhs.mMark < mMark;
    }
    int GetAge() const { return mAge; }
    int GetMark() const { return mMark; }
private:
    std::string mFirstName;
    std::string mLastName;
    int mAge;
    int mMark;
};
struct CompareAgeAscending
{
    bool operator()(const Student& lhs, const Student& rhs) const
    {
        return rhs.GetAge() < lhs.GetAge();
    }
};
struct CompareAgeDescending
{
    bool operator()(const Student& lhs, const Student& rhs) const
    {
        return lhs.GetAge() < rhs.GetAge();
    }
};
Student AddStudent(const std::string& firstName, const std::string& lastName, int age, int mark)
{
    Student newStudent;
    newStudent.SetFirstName(firstName);
    newStudent.SetLastName(lastName);
    newStudent.SetAge(age);
    newStudent.SetMark(mark);
    std::cout << "Added Student: ";
    newStudent.Print();
    std::cout << "\n";

    return newStudent;
}
void Exercise4PriorityQueueStudents()
{
    //Part 2​
    //    Create a class Student​
    //    std::string mFirstName;
    //    std::string mLastName;
    //    int mAge;
    //    int mMark;​
    //    Add an operator< to sort the student by "mLastName"​
    //    Create a priority_queue of students​
    //    Add 20 students​
    //    Any names, first and last​
    //    Random age 21 - 35​
    //    Random mark from 60 - 100​
    //    Print out all the students from the list​
    //    Change the operator< to sort by "mMark" and run again with marks highest to
    //    lowest(std::greater<Student>)
    // (default) use the Student < operator
    //std::priority_queue<Student> students;

    // use custom sorting functors
    //std::priority_queue<Student, std::vector<Student>, CompareAgeAscending> students;
    std::priority_queue<Student, std::vector<Student>, CompareAgeDescending> students;
    students.push(AddStudent("Bruce", "Wayne", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Salina", "Kyle", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Harvey", "Dent", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("John", "Waine", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Emma", "Frost", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Clark", "Kent", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Peter", "Parker", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Gwen", "Stacy", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Harry", "Potter", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Hermoine", "Granger", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Ron", "Weisley", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Sonic", "The Hedghog", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Super", "Mario", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("King", "Boo", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Buckey", "Barns", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Steve", "Rogers", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Nick", "Wylde", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Judy", "Hops", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Eric", "Cartman", rand() % 14 + 25, rand() % 40 + 60));
    students.push(AddStudent("Stan", "Marsh", rand() % 14 + 25, rand() % 40 + 60));

    std::cout << "\n\n";
    while (!students.empty())
    {
        Student topStudent = students.top();
        topStudent.Print();
        students.pop();
    }
}

// indexing vs iterators
void Exercise5Iterators()
{
    std::vector<int> myVector;
    for (int i = 0; i < 20; ++i)
    {
        myVector.push_back(rand() % 40 + 1);
    }
    // step through by index
    std::cout << "Vector by index:\n";
    for (int i = 0; i < myVector.size(); ++i)
    {
        std::cout << myVector[i] << " ";
    }
    std::cout << "\n\n";
    // step through by iteration
    for (std::vector<int>::const_iterator it = myVector.begin(); it != myVector.end(); ++it)
    {
        std::cout << (*it) << " ";
    }
    std::cout << "\n\n";
}

// Recursion
unsigned int GetFactorial(unsigned long value)
{
    if (value <= 1)
    {
        return 1;
    }
    return value * GetFactorial(value - 1);
}
void Exercise6Recursion()
{
    // Part 1:​
    //     Ask the user to input a number​
    //     Create a function that gives the factorial value of the number ​
    //     Eg : 4!= 4 * 3 * 2 * 1 = 24​
    //     Print the time it took to solve this problem​
    //     Solve this with a recursive function​
    //     Print the time to resolve this problem​
    //     Try using really big numbers

    std::cout << "Enter a number above 0:\n";
    unsigned long input;
    std::cin >> input;
    StartAlgorithm();
    std::cout << "Factorial: " << GetFactorial(input) << "\n";
    PrintDuration();
    std::cout << "\n\n";
    StartAlgorithm();
    unsigned long total = input;
    for (unsigned long i = input - 1; i > 0; --i)
    {
        total *= i;
    }
    std::cout << "Factorial: " << total << "\n";
    PrintDuration();
}

// Dice Example
void DicePermutations(int numDice, int maxRoll)
{
    if (numDice <= 0)
    {
        std::cout << "\n";
        return;
    }

    std::cout << maxRoll << " ";
    DicePermutations(numDice - 1, maxRoll);
}
void Exercise7DiceRollsRecursive()
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

    StartAlgorithm();
    DicePermutations(2, 6);
    PrintDuration();
}

int main()
{
    std::cout << "Hello World!\n";
}