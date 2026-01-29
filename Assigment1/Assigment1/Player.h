#pragma once

#include "Vector.h"
#include "PlayerStats.h"
#include "Array.h"
#include <string>
#include <cstdlib>
#include <ctime>

class Player
{
public:

	Player(const std::string& playerName)
		: mPlayerName(playerName)
	{
		InitializeStats();
	}

	Player()
		: mPlayerName("Unknown")
	{
		InitializeStats();
	}

	~Player()
	{

	}

	void InitializeStats()
	{
		static bool seeded = false;

		if (!seeded)
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			seeded = true;
		}
		
		// std::size_t is used because the Array class has that type for indexing
		mPlayerStats[(std::size_t)Stats::Health] = 100;

		for (std::size_t i = 0; i < mPlayerStats.Size(); ++i)
		{
			// fix value so skips setting health again
			if (i == (std::size_t)Stats::Health)
			{
				continue;
			}

			mPlayerStats[i] = std::rand() % 5 + 1; // random value between 1 and 5
		}
	}

	int GetStat(Stats stat) const
	{
		// Gets player stats
		//	Health,		// 0
		//	Attack,		// 1
		//	Defense,	// 2
		//	Stamina,	// 3
		//	Speed,		// 4
		//	Count		// 5
		return mPlayerStats[(std::size_t)stat];
	}

	std::string GetName() const
	{
		return mPlayerName;
	}

	void PrintStats() const
	{
		std::cout << "Player: " << mPlayerName << "\n";
		std::cout << "HP: " << GetStat(Stats::Health) << "\n";
		std::cout << "Atk: " << GetStat(Stats::Attack) << "\n";
		std::cout << "Dfs: " << GetStat(Stats::Defense) << "\n";
		std::cout << "Stamina: " << GetStat(Stats::Stamina) << "\n";
		std::cout << "Speed: " << GetStat(Stats::Speed) << "\n";
	}

private:
	std::string mPlayerName;
	// Array to hold player stats
	// int is the type of data stored (number 1-5 random)
	// and (std::size_t)Stats::Count is the number of elements in the array (5)
	// Count is used to always have the correct number of stats even if more are added later
	// Count does not store a stat itself
	Array<int, (std::size_t)Stats::Count> mPlayerStats;
};