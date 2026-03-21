
#include <iostream>
#include <string>
#include "Array.h"
#include "Vector.h"
#include "ContainerIterator.h"
#include "PriorityQueue.h"
#include "Vector2.h"
#include "Map.h"
#include "Graph.h"
#include "Globals.h"
#include "Player.h"
#include "Team.h"
#include "KDTree.h"
#include "MSTGraph.h"
#include "MSTGraphK.h"
#include "UnorderedMap.h"
#include "WeightedGraph.h"


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

void Assigment4()
{
    class Texture
    {
    public:
        Texture(const std::string& path)
            : filePath(path)
        {
        }
        Texture()
            : filePath("default_texture.png")
        {
        }
        void Print()
        {
            std::cout << "Rendering: " << filePath << "\n";
        }
    private:
        std::string filePath;
    };

    class TextureManager
    {
    public:
        static TextureManager* Get()
        {
            static TextureManager instance;
            return &instance;
        }
        std::size_t LoadTexture(const std::string& filePath)
        {
            auto uniqueKey = Globals::HashFunction(filePath);
            mTextures.Insert(uniqueKey, Texture(filePath));
            return uniqueKey;
        }
        Texture* GetTexture(std::size_t key)
        {
            return &mTextures[key];
        }
    private:
        UnorderedMap<std::size_t, Texture> mTextures;
    };

    class Entity
    {
    public:
        void Initialize(const std::string& textureFilePath)
        {
            mTextureId = TextureManager::Get()->LoadTexture(textureFilePath);
            mPosition = Vector2(0.0f, 0.0f);
        }
        void Update()
        {
            int dx = rand() % 20;
            int dy = rand() % 20;
            mPosition = Vector2(dx, dy);
        }
        Vector2 GetPosition() const
        {
            return mPosition;
        }
        void Render()
        {
            // Get the texture from the texture manager using our stored ID
            Texture* texture = TextureManager::Get()->GetTexture(mTextureId);
            if (texture)
            {
                texture->Print();
            }

            // Print the entity's position
            std::cout << "Position: (" << mPosition.x << ", " << mPosition.y << ")\n";
        }
    private:
        std::size_t mTextureId;
        Vector2 mPosition;
    };

    // main code
    srand(time(0));
    Vector<Entity> myEntities;
    Entity playerOne;
    Entity playerTwo;
    std::string enemyTexturePath = "enemy1234";
    playerOne.Initialize("player1");
    myEntities.PushBack(playerOne);
    playerTwo.Initialize("player2");
    myEntities.PushBack(playerTwo);

    for (int i = 0; i < 20; ++i)
    {
        Entity enemy;
        enemy.Initialize(enemyTexturePath);
        myEntities.PushBack(enemy);
    }

    for (std::size_t i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    // Sort by closest to origin
    std::function<bool(const Entity&, const Entity&)> sortByDistance = [](const Entity& a, const Entity& b)
        {
            Vector2 posA = a.GetPosition();
            Vector2 posB = b.GetPosition();
            float distA = (posA.x * posA.x) + (posA.y * posA.y);
            float distB = (posB.x * posB.x) + (posB.y * posB.y);
            return distA > distB;
        };

    Globals::BubbleSort(myEntities, sortByDistance);

    for (std::size_t i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Render();
        std::cout << "\n";
    }

    for (int i = 0; i < 20; ++i)
    {
        Entity enemy;
        enemy.Initialize(enemyTexturePath);
        myEntities.PushBack(enemy);
    }

    for (std::size_t i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    // Sort by closest to origin
    std::function<bool(const Entity&, const Entity&)> sortByDistance2 = [](const Entity& a, const Entity& b)
        {
            Vector2 posA = a.GetPosition();
            Vector2 posB = b.GetPosition();
            float distA = (posA.x * posA.x) + (posA.y * posA.y);
            float distB = (posB.x * posB.x) + (posB.y * posB.y);
            return distA > distB;
        };

    Globals::BubbleSort(myEntities, sortByDistance2);

    for (int i = 0; i < 20; ++i)
    {
        Entity enemy;
        enemy.Initialize(enemyTexturePath);
        myEntities.PushBack(enemy);
    }

    for (std::size_t i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    // Sort by closest to origin
    std::function<bool(const Entity&, const Entity&)> sortByDistance3 = [](const Entity& a, const Entity& b)
        {
            Vector2 posA = a.GetPosition();
            Vector2 posB = b.GetPosition();
            float distA = (posA.x * posA.x) + (posA.y * posA.y);
            float distB = (posB.x * posB.x) + (posB.y * posB.y);
            return distA > distB;
        };

    Globals::BubbleSort(myEntities, sortByDistance3);

    for (int i = 0; i < 20; ++i)
    {
        Entity enemy;
        enemy.Initialize(enemyTexturePath);
        myEntities.PushBack(enemy);
    }

    for (std::size_t i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Update();
    }

    // Sort by closest to origin
    std::function<bool(const Entity&, const Entity&)> sortByDistance4 = [](const Entity& a, const Entity& b)
        {
            Vector2 posA = a.GetPosition();
            Vector2 posB = b.GetPosition();
            float distA = (posA.x * posA.x) + (posA.y * posA.y);
            float distB = (posB.x * posB.x) + (posB.y * posB.y);
            return distA > distB;
        };

    Globals::BubbleSort(myEntities, sortByDistance4);

    for (std::size_t i = 0; i < myEntities.Size(); ++i)
    {
        myEntities[i].Render();
        std::cout << "\n";
    }

}

void Assigment5()
{
    class KeyItem
    {
    public:
        void Add(int amount)
        {
            mCount += amount;
        }
        void Consume(int amount)
        {
            mCount -= amount;
        }
        int GetCount() const
        {
            return mCount;
        }
        void Print() const
        {
            std::cout << mName << ": " << mCount << "\n";
        }
    private:
        std::string mName;
        int mCount = 0;
    };

    class Inventory
    {
    public:
        Inventory* Get()
        {
            static Inventory instance;
            return &instance;
        }
        void PickupKey(const std::string& keyName, int amount)
        {
            if (mKeys.Has(keyName))
            {
                std::cout << "This key already exists, adding " << amount << " to it.\n";
                mKeys[keyName].Add(amount);
            }
            else
            {
                KeyItem newKey;
                newKey.Add(amount);
                mKeys.Insert(keyName, newKey);
            }
        }
        void UseKey(const std::string& keyName, int amount)
        {
            if (mKeys.Has(keyName))
            {
                mKeys[keyName].Consume(amount);  // Decrease the count

                // Removes if counter gets to 0
                if (mKeys[keyName].GetCount() <= 0)  
                {
                    mKeys.Remove(keyName);
                }
            }
        }
        void ObtainKeys(Vector<std::string>& outKeys)
        {
            mKeys.ObtainKeys(outKeys);
        }

        int GetKeyCount(const std::string& keyName)
        {
            if (mKeys.Has(keyName))
            {
                return mKeys[keyName].GetCount();
            }
            return 0;
        }

        bool Has(const std::string& keyName)
        {
            return mKeys.Has(keyName);
        }
    private:
        Map<std::string, KeyItem> mKeys;
    };

    // Main Flow

    srand(time(0));
    Inventory inventory;
    Vector<std::string> mKeyNames;
    for (int i = 0; i < 20; ++i)
    {
        mKeyNames.PushBack("Key" + std::to_string(i));
    }

    // Add 100 random keys using names from the vector
    for (int i = 0; i < 100; i++)
    {
        int randomIndex = rand() % mKeyNames.Size(); // pick a random index
        std::string randomKey = mKeyNames[randomIndex]; // get the name from the vector
        inventory.PickupKey(randomKey, 1); // PickupKey handles creating the KeyItem internally
    }

    // Obtain all keys and print their names and counts
    Vector<std::string> ownedKeys;
    inventory.ObtainKeys(ownedKeys);

    for (int i = 0; i < ownedKeys.Size(); i++)
    {
        std::string keyName = ownedKeys[i];
        int count = inventory.GetKeyCount(keyName);
        std::cout << "Key: " << keyName << " | Count: " << count << "\n";
    }

    int doorsUnlocked = 0;
    int failedAttempts = 0;

    int choice = 0;
    while (true)
    {
        std::cout << "\n--- Adventure Menu ---\n";
        std::cout << "1. Open a door\n";
        std::cout << "2. Pick up a key\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            // Pick a random door that needs a random key
            int randomIndex = rand() % mKeyNames.Size();
            std::string requiredKey = mKeyNames[randomIndex];

            std::cout << "You arrive at a door and need a " << requiredKey << "\n";

            if (inventory.Has(requiredKey))
            {
                std::cout << "You have the " << requiredKey << " and have unlocked the door!\n";
                inventory.UseKey(requiredKey, 1);
                doorsUnlocked++;
            }
            else
            {
                std::cout << "You do not have the " << requiredKey << ", the door will remain locked.\n";
                failedAttempts++;
            }
        }
        else if (choice == 2)
        {
            int randomIndex = rand() % mKeyNames.Size();
            std::string randomKey = mKeyNames[randomIndex];
            inventory.PickupKey(randomKey, 1);

            std::cout << "You picked up a " << randomKey << "!\n";
            std::cout << "Total count of " << randomKey << ": " << inventory.GetKeyCount(randomKey) << "\n";
        }
        else if (choice == 3)
        {
            std::cout << "\n--- Game Over ---\n";

            // Print all owned keys and counts
            Vector<std::string> ownedKeys;
            inventory.ObtainKeys(ownedKeys);

            if (ownedKeys.Size() == 0)
            {
                std::cout << "You have no keys remaining.\n";
            }
            else
            {
                std::cout << "Keys remaining in inventory:\n";
                for (int i = 0; i < ownedKeys.Size(); i++)
                {
                    std::string keyName = ownedKeys[i];
                    std::cout << "  " << keyName << " | Count: " << inventory.GetKeyCount(keyName) << "\n";
                }
            }

            std::cout << "Doors unlocked: " << doorsUnlocked << "\n";
            std::cout << "Failed unlock attempts: " << failedAttempts << "\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice, please enter 1, 2, or 3.\n";
        }
    }
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

void Assigment6()
{
    srand(42);

    // Create two teams with 10 players each
    Team teamA;
    Team teamB;
    teamA.Initialize("Team Alpha", 10);
    teamB.Initialize("Team Beta", 10);

    std::cout << "=== BATTLE START ===\n\n";

    int turnNumber = 0;

    // Repeat until one team is eliminated
    while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
    {
        ++turnNumber;
        std::cout << "--- Turn " << turnNumber << " ---\n";
        std::cout << teamA.GetName() << " remaining: " << teamA.GetRemainingPlayers()
            << " | " << teamB.GetName() << " remaining: " << teamB.GetRemainingPlayers() << "\n";

        // StartTurn for both teams
        teamA.StartTurn();
        teamB.StartTurn();

        // Repeat c-e until all players have attacked
        bool anyoneCanAttack = true;
        while (anyoneCanAttack && teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
        {
            // Get next battling player for both teams
            Player* playerA = teamA.GetNextBattlingPlayer();
            Player* playerB = teamB.GetNextBattlingPlayer();

            anyoneCanAttack = (playerA != nullptr || playerB != nullptr);
            if (!anyoneCanAttack)
            {
                break;
            }

            // Fastest player attacks the other team
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
                std::cout << "[" << teamA.GetName() << "] " << playerA->GetName() << " (SPD:" << playerA->GetStat(Stats::Speed) << " ATK:" << playerA->GetStat(Stats::Attack) << ") attacks " << teamB.GetName() << "!\n";

                teamB.DamagePlayer(playerA);

                int remainingAfter = teamB.GetRemainingPlayers();
                if (remainingAfter < remainingBefore)
                {
                    std::cout << "  >> A " << teamB.GetName() << " player was eliminated! (" << remainingAfter << " remaining)\n";
                }  
                else
                {
                    std::cout << "  >> Hit! " << teamB.GetName() << " still has " << remainingAfter << " players standing.\n";
                }   
            }
            else if (!aGoesFirst && playerB != nullptr)
            {
                int remainingBefore = teamA.GetRemainingPlayers();
                std::cout << "[" << teamB.GetName() << "] " << playerB->GetName()<< " (SPD:" << playerB->GetStat(Stats::Speed) << " ATK:" << playerB->GetStat(Stats::Attack) << ") attacks " << teamA.GetName() << "!\n";

                teamA.DamagePlayer(playerB);

                int remainingAfter = teamA.GetRemainingPlayers();
                if (remainingAfter < remainingBefore)
                {
                    std::cout << "  >> A " << teamA.GetName() << " player was eliminated! (" << remainingAfter << " remaining)\n";
                }
                else
                {
                    std::cout << "  >> Hit! " << teamA.GetName() << " still has " << remainingAfter << " players standing.\n";
                }
            }

            // OrderPlayers for both teams
            teamA.OrderPlayers();
            teamB.OrderPlayers();
        }

        std::cout << "\n";
    }

    // Print Winner
    std::cout << "=== BATTLE OVER ===\n";
    if (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() <= 0)
        std::cout << teamA.GetName() << " WINS with " << teamA.GetRemainingPlayers() << " players remaining!\n";
    else if (teamB.GetRemainingPlayers() > 0 && teamA.GetRemainingPlayers() <= 0)
        std::cout << teamB.GetName() << " WINS with " << teamB.GetRemainingPlayers() << " players remaining!\n";
    else
		std::cout << "It's a DRAW! Both teams have been eliminated." << "\n";
}

void Class10()
{
    // Test MST

}

void Assigment7()
{
    class House
    {
    public:
        House(const std::string& name, const Vector2& pos)
            : mName(name), mPosition(pos)
        {

        }
        House()
        {

        }
        std::string GetName() const
        {
            return mName;
        }
        Vector2 GetPosition() const
        {
            return mPosition;
        }
    private:
        std::string mName;
        Vector2 mPosition;
    };

    class City
    {
    public:
        void AddHouse(const std::string& name, const Vector2& pos)
        {
            // goes through mHouses and see if the house is already taken or not
            for (std::size_t i = 0; i < mHouses.Size(); ++i)
            {
                if (name == mHouses[i].GetName() || pos == mHouses[i].GetPosition())
                {
                    std::cout << "This house is already taken.\n";
                    return;
                }
            }
            // push back the new houses
            House newHouse(name, pos);
            mHouses.PushBack(newHouse);
        }

        void ConnectAllHouses()
        {
            // go through all the houses and add them as a node of mHouseGraph using .AddItem
            for (std::size_t i = 0; i < mHouses.Size(); ++i)
            {
                mHousesGraph.AddItem(&mHouses[i]);
            }

            // go through all the houses and add a i and j value and also get the distance between them and use it as the weight
            for (std::size_t i = 0; i < mHouses.Size(); ++i)
            {
                for (std::size_t j = i + 1; j < mHouses.Size(); ++j)
                {
                    float distance = mHouses[i].GetPosition().Distance(mHouses[j].GetPosition());
                    mHouseEdgesGraph.AddEdge(i, j, distance);
                    mHousesGraph.AddEdge(i, j, distance, true);
                }
            }
        }

        float GetTotalRoadDistancePrim()
        {
            // return the MST from mHousesGraph using Prim's algorithm
            mHousesGraph.GenerateMST(0);
            const auto& mstEdges = mHousesGraph.GetMST();

            // sum up the weights for the total road dinstance 
            float totalDistance = 0.0f;
            for (std::size_t i = 0; i < mstEdges.Size(); ++i)
            {
                totalDistance += mstEdges[i].weight;
            }

            // finally return the total distance calculated
            return totalDistance;
        }

        float GetToalRoadDistanceKruskal()
        {
            // same code as before but this time we use MSTGraphK functions instead of MSTGraph
            mHouseEdgesGraph.GenerateMST();
            const auto& mstEdges = mHouseEdgesGraph.GetMST();

            float totalDistance = 0.0f;
            for (std::size_t i = 0; i < mstEdges.Size(); ++i)
            {
                totalDistance += mstEdges[i].weight;
            }

            // Returns the total distance calculated
            return totalDistance;
        }

        void PrintMST()
        {
            std::cout << "=== Prim's Connections ===\n";
            const auto& primEdges = mHousesGraph.GetMST();
            for (std::size_t i = 0; i < primEdges.Size(); ++i)
            {
                std::cout << mHouses[primEdges[i].fromIndex].GetName() << " -> " << mHouses[primEdges[i].fromIndex].GetName() << " | Distance: " << primEdges[i].weight << "m\n";
            }
        }
    private:
        Vector<House> mHouses;
        MSTGraph<House, float> mHousesGraph;
        MSTGraphK<float> mHouseEdgesGraph;
    };

    // Main Flow

    City city;

    // Populate with the houses from the diagram
    city.AddHouse("A", Vector2(20.0f, 40.0f));
    city.AddHouse("B", Vector2(50.0f, 20.0f));
    city.AddHouse("C", Vector2(90.0f, 40.0f));
    city.AddHouse("D", Vector2(60.0f, 80.0f));
    city.AddHouse("E", Vector2(30.0f, 120.0f));
    city.AddHouse("F", Vector2(100.0f, 110.0f));
    city.AddHouse("G", Vector2(150.0f, 130.0f));
    city.AddHouse("H", Vector2(160.0f, 90.0f));
    city.AddHouse("I", Vector2(140.0f, 60.0f));
    city.AddHouse("J", Vector2(180.0f, 30.0f));
    city.AddHouse("K", Vector2(200.0f, 120.0f));
    city.AddHouse("L", Vector2(220.0f, 70.0f));
    city.AddHouse("M", Vector2(240.0f, 50.0f));

    // Connect all houses
    city.ConnectAllHouses();

    // Print MST connections for both
    city.PrintMST();

    // Print total cost for both (should be the same)
    float primDistance = city.GetTotalRoadDistancePrim();
    std::cout << "\n=== Prim's ===\n";
    std::cout << "Total distance: " << primDistance << " meters\n";
    std::cout << "Total cost: $" << primDistance * 10.0f << "\n";

    float kruskalDistance = city.GetToalRoadDistanceKruskal();
    std::cout << "\n=== Kruskal's ===\n";
    std::cout << "Total distance: " << kruskalDistance << " meters\n";
    std::cout << "Total cost: $" << kruskalDistance * 10.0f << "\n";

    std::cout << "\nBoth methods match: " << (primDistance == kruskalDistance ? "YES" : "NO") << "\n";

}

void Assigment8()
{
    class City
    {
    public:
        City(std::string name, Vector2 positon)
            :mName(name), mPosition(positon)
        {

        }

        City()
        {

        }

        std::string GetName() const
        {
            return mName;
        }

        Vector2 GetPosition() const
        {
            return mPosition;
        }
    private:
        std::string mName;
        Vector2 mPosition;
    };

    class GPS
    {
    public:
        ~GPS()
        {
            for (std::size_t i = 0; i < mCities.Size(); ++i)
            {
                delete mCities[i];
            }
            mCities.Clear();
        }

        void AddCity(const std::string& name, const Vector2& pos)
        {
            for (std::size_t i = 0; i < mCities.Size(); ++i)
            {
                if (name == mCities[i]->GetName() || pos == mCities[i]->GetPosition())
                {
                    std::cout << "This city already exists\n";
                    return;
                }
            }
            City* newCity = new City(name, pos);
            mCities.PushBack(newCity);
            mCityGraph.AddItem(mCities[mCities.Size() - 1]);
        }

        void ConnectCities(const City* a, const City* b)
        {
            std::size_t cityA = 0;
            std::size_t cityB = 0;
            bool foundA = false;
            bool foundB = false;
            for (std::size_t i = 0; i < mCities.Size(); ++i)
            {
                if (a->GetPosition() == mCities[i]->GetPosition())
                {
                    cityA = i;
                    foundA = true;
                }
                if (b->GetPosition() == mCities[i]->GetPosition())
                {
                    cityB = i;
                    foundB = true;
                }
            }
            if (!foundA || !foundB)
            {
                std::cout << "Invalid cities\n";
                return;
            }
            float weight = a->GetPosition().Distance(b->GetPosition());
            mCityGraph.AddEdge((int)cityA, (int)cityB, weight);
        }

        float FindPath(const City* from, const City* to, Vector<const City*>& pathOutput)
        {
            int startIndex = -1;
            int endIndex = -1;
            for (int i = 0; i < (int)mCities.Size(); ++i)
            {
                if (mCities[i]->GetPosition() == from->GetPosition())
                {
                    startIndex = i;
                }
                if (mCities[i]->GetPosition() == to->GetPosition())
                {
                    endIndex = i;
                }
            }
            if (startIndex == -1 || endIndex == -1)
            {
                return -1.0f;
            }

            return mCityGraph.GetPath(startIndex, endIndex, pathOutput);
        }

        const City* GetCity(const std::string& name) const
        {
            for (std::size_t i = 0; i < mCities.Size(); ++i)
            {
                if (mCities[i]->GetName() == name)
                {
                    return mCities[i];
                }
            }
            return nullptr;
        }

    private:
        Vector<City*> mCities;
        WeightedGraph<City, float> mCityGraph;
    };

    // Run GPS demo inside the function (removed nested main which is invalid)
    GPS gps;

    // Populate cities
    gps.AddCity("Powel River", { 420, 605 });
    gps.AddCity("Vancouver", { 475, 635 });
    gps.AddCity("Abbotsford", { 505, 650 });
    gps.AddCity("Penticton", { 600, 615 });
    gps.AddCity("Kelowna", { 603, 593 });
    gps.AddCity("Kamloops", { 570, 555 });
    gps.AddCity("Nelson", { 685, 608 });
    gps.AddCity("Creston", { 715, 625 });
    gps.AddCity("Cranbrook", { 740, 598 });
    gps.AddCity("Revelstoke", { 642, 526 });
    gps.AddCity("Lillooet", { 512, 556 });
    gps.AddCity("Prince George", { 447, 376 });
    gps.AddCity("Burns Lake", { 375, 362 });
    gps.AddCity("Smithers", { 330, 330 });
    gps.AddCity("Terrace", { 285, 345 });
    gps.AddCity("Prince Rupert", { 227, 352 });
    gps.AddCity("Dawson Creek", { 550, 268 });
    gps.AddCity("Fort St. John", { 530, 243 });
    gps.AddCity("Fort Nelson", { 470, 102 });
    gps.AddCity("Dease Lake", { 250, 120 });
    gps.AddCity("Williams Lake", { 500, 475 });
    gps.AddCity("Quesnel", { 485, 430 });

    // Connect cities (edges based on geographic proximity/roads)
    gps.ConnectCities(gps.GetCity("Vancouver"), gps.GetCity("Abbotsford"));
    gps.ConnectCities(gps.GetCity("Vancouver"), gps.GetCity("Powel River"));
    gps.ConnectCities(gps.GetCity("Vancouver"), gps.GetCity("Kamloops"));
    gps.ConnectCities(gps.GetCity("Abbotsford"), gps.GetCity("Penticton"));
    gps.ConnectCities(gps.GetCity("Penticton"), gps.GetCity("Kelowna"));
    gps.ConnectCities(gps.GetCity("Penticton"), gps.GetCity("Creston"));
    gps.ConnectCities(gps.GetCity("Kelowna"), gps.GetCity("Kamloops"));
    gps.ConnectCities(gps.GetCity("Kelowna"), gps.GetCity("Revelstoke"));
    gps.ConnectCities(gps.GetCity("Kamloops"), gps.GetCity("Lillooet"));
    gps.ConnectCities(gps.GetCity("Kamloops"), gps.GetCity("Revelstoke"));
    gps.ConnectCities(gps.GetCity("Kamloops"), gps.GetCity("Williams Lake"));
    gps.ConnectCities(gps.GetCity("Revelstoke"), gps.GetCity("Cranbrook"));
    gps.ConnectCities(gps.GetCity("Revelstoke"), gps.GetCity("Nelson"));
    gps.ConnectCities(gps.GetCity("Nelson"), gps.GetCity("Creston"));
    gps.ConnectCities(gps.GetCity("Nelson"), gps.GetCity("Cranbrook"));
    gps.ConnectCities(gps.GetCity("Creston"), gps.GetCity("Cranbrook"));
    gps.ConnectCities(gps.GetCity("Lillooet"), gps.GetCity("Powel River"));
    gps.ConnectCities(gps.GetCity("Lillooet"), gps.GetCity("Williams Lake"));
    gps.ConnectCities(gps.GetCity("Williams Lake"), gps.GetCity("Quesnel"));
    gps.ConnectCities(gps.GetCity("Williams Lake"), gps.GetCity("Prince George"));
    gps.ConnectCities(gps.GetCity("Quesnel"), gps.GetCity("Prince George"));
    gps.ConnectCities(gps.GetCity("Prince George"), gps.GetCity("Burns Lake"));
    gps.ConnectCities(gps.GetCity("Prince George"), gps.GetCity("Dawson Creek"));
    gps.ConnectCities(gps.GetCity("Burns Lake"), gps.GetCity("Smithers"));
    gps.ConnectCities(gps.GetCity("Smithers"), gps.GetCity("Terrace"));
    gps.ConnectCities(gps.GetCity("Smithers"), gps.GetCity("Dease Lake"));
    gps.ConnectCities(gps.GetCity("Terrace"), gps.GetCity("Prince Rupert"));
    gps.ConnectCities(gps.GetCity("Dease Lake"), gps.GetCity("Fort Nelson"));
    gps.ConnectCities(gps.GetCity("Dawson Creek"), gps.GetCity("Fort St. John"));
    gps.ConnectCities(gps.GetCity("Fort St. John"), gps.GetCity("Fort Nelson"));

    // Find and print paths
    const float speed = 80.0f;

    auto PrintPath = [&](const std::string& fromName, const std::string& toName)
        {
            Vector<const City*> path;
            const City* fromCity = gps.GetCity(fromName);
            const City* toCity = gps.GetCity(toName);
            if (!fromCity || !toCity)
            {
                std::cout << "Invalid city name(s): " << fromName << " or " << toName << "\n";
                return;
            }

            float distance = gps.FindPath(fromCity, toCity, path);
            if (distance < 0.0f || path.Size() == 0)
            {
                std::cout << "\nRoute: " << fromName << " -> " << toName << "\n";
                std::cout << "No path found.\n";
                return;
            }

            std::cout << "\nRoute: " << fromName << " -> " << toName << "\n";
            std::cout << "Path: ";
            for (int i = (int)path.Size() - 1; i >= 0; --i)
            {
                std::cout << path[i]->GetName();
                if (i > 0) std::cout << " -> ";
            }
            std::cout << "\n";
            std::cout << "Total Distance: " << distance << " km\n";

            // Print estimated travel time
            float hours = distance / speed;
            int h = (int)hours;
            int m = (int)((hours - h) * 60);
            std::cout << "Estimated Duration: " << h << "h " << m << "m\n";
        };

    PrintPath("Vancouver", "Cranbrook");   // #1
    PrintPath("Prince Rupert", "Kelowna"); // #2
    PrintPath("Fort Nelson", "Creston");   // #3
}

int main()
{
    Assigment8();
	return 0;
}

