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
		: mPlayerName("NoName")
	{
		InitializeStats();
	}

	~Player()
	{

	}

	void InitializeStats()
	{
		// initialize seed for random number generation only once
		static bool seeded = false;
		if (!seeded)
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			seeded = true;
		}

		// health always is 100 
		// this is the structure of our custom array class
		// we always use std::size_t, because the Array class uses that type for indexing
		mPlayerStats[(std::size_t)Stats::Health] = 100;

		for (std::size_t i = 0; i < mPlayerStats.Size(); ++i)
		{
			// skip setting up health since it is a fixed value
			if (i == (std::size_t)Stats::Health)
			{
				continue;
			}

			mPlayerStats[i] = std::rand() % 5 + 1; // random value between 1 and 5
		}
	}

	int GetStat(Stats stat) const
	{
		//	Health,		// 0
		//	Attack,		// 1
		//	Defense,	// 2
		//	Stamina,	// 3
		//	Speed,		// 4
		//	Count		// 5
		return mPlayerStats[(std::size_t)stat];
	}

	void PrintStats() const
	{
		std::cout << "Player: " << mPlayerName << "\n";
		std::cout << "Health: " << GetStat(Stats::Health) << "\n";
		std::cout << "Attack: " << GetStat(Stats::Attack) << "\n";
		std::cout << "Defense: " << GetStat(Stats::Defense) << "\n";
		std::cout << "Stamina: " << GetStat(Stats::Stamina) << "\n";
		std::cout << "Speed: " << GetStat(Stats::Speed) << "\n";
	}

	std::string GetName() const
	{
		return mPlayerName;
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