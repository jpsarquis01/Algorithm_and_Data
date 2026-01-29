#pragma once
#include "Item.h"
#include "Vector.h"
#include "PriorityQueue.h"

class Inventory
{
public:
	Inventory();

	void Initialize();
	void AddItem(ItemType itemType);
	void DisplayInventory();

private:
	Vector<Item> mItems;
};