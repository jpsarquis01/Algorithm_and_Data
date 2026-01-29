#pragma once
#include <string>

enum class ItemType
{
	SmallHealth,
	MedHealth,
	LightningSpell,
	Grenade,
	Sword,
	Shield,
	Armor,
	Potion,
	Scroll,
	Key
};

class Item
{
public:
	Item() : mType(ItemType::SmallHealth), mValue(0), mCount(0), mName("Unknown") {}
	Item(ItemType itemType, int value);

	void ConsumeItem();
	void AddItem();

	const std::string& GetName() const { return mName; }
	int GetValue() const { return mValue; }
	int GetCount() const { return mCount; }

	// Comparison operator for PriorityQueue (higher count = higher priority)
	bool operator>(const Item& other) const { return mCount > other.mCount; }
	bool operator<(const Item& other) const { return mCount < other.mCount; }

private:
	ItemType mType;
	std::string mName;
	int mValue;
	int mCount;

	void SetNameFromType();
};