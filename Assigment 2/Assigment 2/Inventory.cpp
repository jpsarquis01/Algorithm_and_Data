#include "Inventory.h"
#include <iostream>

Inventory::Inventory()
{
}

void Inventory::Initialize()
{
	// Add at least 10 items to the inventory
	mItems.PushBack(Item(ItemType::SmallHealth, 25));
	mItems.PushBack(Item(ItemType::MedHealth, 50));
	mItems.PushBack(Item(ItemType::LightningSpell, -30));
	mItems.PushBack(Item(ItemType::Grenade, -40));
	mItems.PushBack(Item(ItemType::Sword, -25));
	mItems.PushBack(Item(ItemType::Shield, 15));
	mItems.PushBack(Item(ItemType::Armor, 35));
	mItems.PushBack(Item(ItemType::Potion, 20));
	mItems.PushBack(Item(ItemType::Scroll, 10));
	mItems.PushBack(Item(ItemType::Key, 0));

	std::cout << "Inventory initialized with " << mItems.Size() << " item types.\n\n";
}

void Inventory::AddItem(ItemType itemType)
{
	// Check if item already exists in inventory
	for (std::size_t i = 0; i < mItems.Size(); ++i)
	{
		if (mItems[i].GetName() == Item(itemType, 0).GetName())
		{
			mItems[i].AddItem();
			return;
		}
	}

	// If item doesn't exist, create a new one with default value
	int defaultValue = 0;
	switch (itemType)
	{
	case ItemType::SmallHealth: defaultValue = 25; break;
	case ItemType::MedHealth: defaultValue = 50; break;
	case ItemType::LightningSpell: defaultValue = -30; break;
	case ItemType::Grenade: defaultValue = -40; break;
	case ItemType::Sword: defaultValue = -25; break;
	case ItemType::Shield: defaultValue = 15; break;
	case ItemType::Armor: defaultValue = 35; break;
	case ItemType::Potion: defaultValue = 20; break;
	case ItemType::Scroll: defaultValue = 10; break;
	case ItemType::Key: defaultValue = 0; break;
	}

	mItems.PushBack(Item(itemType, defaultValue));
}

void Inventory::DisplayInventory()
{
	std::cout << "\n=== Displaying Inventory ===\n";

	// Create a PriorityQueue
	PriorityQueue<Item> pq;

	// Add everything from the inventory Vector to the PriorityQueue
	for (std::size_t i = 0; i < mItems.Size(); ++i)
	{
		pq.Push(mItems[i]);
	}

	// Print the PriorityQueue in order of highest count
	std::cout << "Items sorted by count (highest first):\n";
	while (!pq.Empty())
	{
		Item item = pq.Top();
		pq.Pop();

		std::cout << item.GetName() << " - Count: " << item.GetCount()
			<< " - Value: ";
		if (item.GetValue() >= 0)
			std::cout << "+";
		std::cout << item.GetValue() << "\n";
	}
	std::cout << "\n";
}