#pragma once

#include <string>
#include "Array.h"

enum class Stats
{
    Health,
    Attack,
    Speed,
    AttackCount,
    Count  // used to get the number of stats for Array size
};

class Player
{
public:
    Player() {}
    ~Player() {}

    // Initializes the player with default values
    // Health = 100, AttackCount = 1, rest are random 5-20
    void Initialize(const std::string& name)
    {
        mName = name;

        mStats[static_cast<std::size_t>(Stats::Health)] = 100;
        mStats[static_cast<std::size_t>(Stats::Attack)] = 5 + (rand() % 16); // random 5-20
        mStats[static_cast<std::size_t>(Stats::Speed)] = 5 + (rand() % 16); // random 5-20
        mStats[static_cast<std::size_t>(Stats::AttackCount)] = 1;
    }

    // Returns the value for the stated stat
    int GetStat(Stats stat) const
    {
        return mStats[static_cast<std::size_t>(stat)];
    }

    // Updates a stat
    void SetStat(Stats stat, int value)
    {
        mStats[static_cast<std::size_t>(stat)] = value;
    }

    // Returns true if health > 0
    bool IsAlive() const
    {
        return mStats[static_cast<std::size_t>(Stats::Health)] > 0;
    }

    // Returns the player's name
    const std::string& GetName() const
    {
        return mName;
    }

    // Performs an attack — reduces AttackCount by 1; returns false if can't attack
    bool Attack()
    {
        int attackCount = GetStat(Stats::AttackCount);
        if (attackCount <= 0)
        {
            return false;
        }
        SetStat(Stats::AttackCount, attackCount - 1);
        return true;
    }

private:
    std::string mName;
    // Array sized by the number of stats in the enum (excludes Count sentinel)
    Array<int, static_cast<std::size_t>(Stats::Count)> mStats;
};