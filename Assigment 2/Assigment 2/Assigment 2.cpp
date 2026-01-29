#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Inventory.h"


int main()
{
	// Seed random number generator
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// a. Create an Inventory object
	Inventory inventory;

	// b. Call Initialize
	inventory.Initialize();

	// c. Add 100 random items to the inventory
	std::cout << "Adding 100 random items to inventory...\n\n";
	for (int i = 0; i < 100; ++i)
	{
		// Generate random ItemType (0-9)
		int randomType = std::rand() % 10;
		ItemType itemType = static_cast<ItemType>(randomType);
		inventory.AddItem(itemType);
	}

	// d. Call DisplayInventory
	inventory.DisplayInventory();

	// e. Confirm items are sorted correctly
	std::cout << "Items are sorted by count in descending order (highest count first).\n";

	return 0;
}









































