
#include <iostream>
#include <string>
#include "Array.h"
#include "Vector.h"
#include "PriorityQueue.h"
#include "Vector2.h"
#include "Map.h"
#include "Globals.h"
#include "Player.h"
#include "Team.h"

struct Item
{
    std::string name;
    Vector2 position;
};

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

void Class7()
{
    /* Vector<Item> items;
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
   Vector2 maxRange = { 300.0f, 300.0f };*/

    std::cout << "Custom Map:\n";
    Map<int, int> myMap;
    for (int i = 0; i < 10; ++i)
    {
        int value = rand() % 1000;
        myMap.Insert(i, value);
        std::cout << value << " ";
    }
    std::cout << "\n\n";
    std::cout << "Has key 3 " << myMap.Has(3) << "\n";
    std::cout << "Has key 30" << myMap.Has(30) << "\n";

    Vector<int> allKeys;
    myMap.ObtainKeys(allKeys);
    std::cout << "Obtain all Keys:\n";
    for (std::size_t i = 0; i < allKeys.Size(); ++i)
    {
        std::cout << allKeys[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Value for key 5: " << myMap[7] << "\n";
    myMap.Remove(5);
    allKeys.Clear();
    myMap.ObtainKeys(allKeys);
    std::cout << "Obtain all Keys after removing key 5:\n";
    for (std::size_t i = 0; i < allKeys.Size(); ++i)
    {
        std::cout << allKeys[i] << " ";
    }
    myMap.Clear();
}

void Assigment5()
{

}

void Class8()
{
    std::cout << "Custom Sorting:\n";
    Vector<int> myNumbers;
    int maxNumbers = 20;

    for (int i = 0; i < maxNumbers; ++i)
    {
        int value = 1 + (rand() % 100);
        myNumbers.PushBack(value);
        std::cout << value << " ";
    }
    std::cout << "\n";

    // =========================================================
    //Globals::InsertionSort(myNumbers.Begin(), myNumbers.End());

    //Globals::MergeSort(myNumbers.Begin(), myNumbers.End());

    //Globals::QuickSort(myNumbers.Begin(), myNumbers.End());

    //Globals::BucketSort(myNumbers.Begin(), myNumbers.End());

    //Globals::HeapSort(myNumbers.Begin(), myNumbers.End());

    Globals::IntroSort(myNumbers.Begin(), myNumbers.End());
    for (std::size_t i = 0; i < myNumbers.Size(); ++i)
    {
        std::cout << myNumbers[i] << " ";
    }
    std::cout << "\n";
}

void Assignment6()
{
    srand(42);

    // 4a. Create two teams with 10 players each
    Team teamA;
    Team teamB;
    teamA.Initialize("Team Alpha", 10);
    teamB.Initialize("Team Beta", 10);

    std::cout << "=== BATTLE START ===\n\n";

    int turnNumber = 0;

    // 4g. Repeat until one team is eliminated
    while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
    {
        ++turnNumber;
        std::cout << "--- Turn " << turnNumber << " ---\n";
        std::cout << teamA.GetName() << " remaining: " << teamA.GetRemainingPlayers()
            << " | " << teamB.GetName() << " remaining: " << teamB.GetRemainingPlayers() << "\n";

        // 4b. StartTurn for both teams
        teamA.StartTurn();
        teamB.StartTurn();

        // 4f. Repeat c-e until all players have attacked
        bool anyoneCanAttack = true;
        while (anyoneCanAttack && teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
        {
            // 4c. Get next battling player for both teams
            Player* playerA = teamA.GetNextBattlingPlayer();
            Player* playerB = teamB.GetNextBattlingPlayer();

            anyoneCanAttack = (playerA != nullptr || playerB != nullptr);
            if (!anyoneCanAttack)
            {
                break;
            }

            // 4d. Fastest player attacks the other team
            bool aGoesFirst = false;
            if (playerA != nullptr && playerB != nullptr)
            {
                aGoesFirst = playerA->GetStat(Stats::Speed) >= playerB->GetStat(Stats::Speed);
            }
            else
            {
                aGoesFirst = (playerA != nullptr);
            }

            if (aGoesFirst && playerA != nullptr)
            {
                int remainingBefore = teamB.GetRemainingPlayers();
                std::cout << "[" << teamA.GetName() << "] " << playerA->GetName()
                    << " (SPD:" << playerA->GetStat(Stats::Speed)
                    << " ATK:" << playerA->GetStat(Stats::Attack) << ") attacks "
                    << teamB.GetName() << "!\n";

                teamB.DamagePlayer(playerA);

                int remainingAfter = teamB.GetRemainingPlayers();
                if (remainingAfter < remainingBefore)
                    std::cout << "  >> A " << teamB.GetName() << " player was eliminated! (" << remainingAfter << " remaining)\n";
                else
                    std::cout << "  >> Hit! " << teamB.GetName() << " still has " << remainingAfter << " players standing.\n";
            }
            else if (!aGoesFirst && playerB != nullptr)
            {
                int remainingBefore = teamA.GetRemainingPlayers();
                std::cout << "[" << teamB.GetName() << "] " << playerB->GetName()
                    << " (SPD:" << playerB->GetStat(Stats::Speed)
                    << " ATK:" << playerB->GetStat(Stats::Attack) << ") attacks "
                    << teamA.GetName() << "!\n";

                teamA.DamagePlayer(playerB);

                int remainingAfter = teamA.GetRemainingPlayers();
                if (remainingAfter < remainingBefore)
                    std::cout << "  >> A " << teamA.GetName() << " player was eliminated! (" << remainingAfter << " remaining)\n";
                else
                    std::cout << "  >> Hit! " << teamA.GetName() << " still has " << remainingAfter << " players standing.\n";
            }

            // 4e. OrderPlayers for both teams
            teamA.OrderPlayers();
            teamB.OrderPlayers();
        }

        std::cout << "\n";
    }

    // 4i. Print who wins
    std::cout << "=== BATTLE OVER ===\n";
    if (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() <= 0)
        std::cout << teamA.GetName() << " WINS with " << teamA.GetRemainingPlayers() << " players remaining!\n";
    else if (teamB.GetRemainingPlayers() > 0 && teamA.GetRemainingPlayers() <= 0)
        std::cout << teamB.GetName() << " WINS with " << teamB.GetRemainingPlayers() << " players remaining!\n";
    else
		std::cout << "It's a DRAW! Both teams have been eliminated." << "\n";
}


int main()
{
    Assignment6();
	return 0;
}

