#include "Item.h"
#include <iostream>

Item::Item(ItemType itemType, int value)
	: mType(itemType)
	, mValue(value)
	, mCount(1)
{
	SetNameFromType();
}

void Item::SetNameFromType()
{
	switch (mType)
	{
	case ItemType::SmallHealth:
		mName = "Small Health";
		break;
	case ItemType::MedHealth:
		mName = "Medium Health";
		break;
	case ItemType::LightningSpell:
		mName = "Lightning Spell";
		break;
	case ItemType::Grenade:
		mName = "Grenade";
		break;
	case ItemType::Sword:
		mName = "Sword";
		break;
	case ItemType::Shield:
		mName = "Shield";
		break;
	case ItemType::Armor:
		mName = "Armor";
		break;
	case ItemType::Potion:
		mName = "Potion";
		break;
	case ItemType::Scroll:
		mName = "Scroll";
		break;
	case ItemType::Key:
		mName = "Key";
		break;
	}
}

void Item::ConsumeItem()
{
	if (mCount > 0)
	{
		--mCount;
		std::cout << "Consumed " << mName << " (Value: ";
		if (mValue >= 0)
			std::cout << "+" << mValue;
		else
			std::cout << mValue;
		std::cout << ")\n";
	}
	else
	{
		std::cout << "Item " << mName << " does not have any to consume\n";
	}
}

void Item::AddItem()
{
	++mCount;
	std::cout << "Added " << mName << " - Current count: " << mCount << "\n";
}