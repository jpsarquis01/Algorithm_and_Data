#pragma once
#include <string>
#include "Vector.h"
#include "Player.h"
#include "Globals.h"

class Team
{
public:
    Team() {}
    ~Team() {}

    // Initializes the team with numPlayers players
    void Initialize(const std::string& teamName, int numPlayers)
    {
        mName = teamName;
        mPlayers.Resize(numPlayers);
        for (int i = 0; i < numPlayers; ++i)
        {
            mPlayers[i].Initialize(mName + "_Player" + std::to_string(i));
        }
    }

    // Returns the player with the fastest speed that hasn't attacked (AttackCount > 0 and alive)
    Player* GetNextBattlingPlayer()
    {
        Player* fastest = nullptr;
        for (std::size_t i = 0; i < mPlayers.Size(); ++i)
        {
            Player& p = mPlayers[i];
            if (!p.IsAlive() || p.GetStat(Stats::AttackCount) <= 0)
            {
                continue;
            }
            if (fastest == nullptr || p.GetStat(Stats::Speed) > fastest->GetStat(Stats::Speed))
            {
                fastest = &p;
            }
        }
        return fastest;
    }

    // Pass in the attacking player from another team.
    // Uses that player's Attack stat to damage a random living player on this team.
    // 25% chance the attacked player slows down by 10.
    // 10% chance the attacking player speeds up by 5.
    // Attacking player's AttackCount is set to 0 after.
    void DamagePlayer(Player* attacker)
    {
        if (attacker == nullptr)
        {
            return;
        }

        // Collect indices of living players
        Vector<int> livingIndices;
        for (std::size_t i = 0; i < mPlayers.Size(); ++i)
        {
            if (mPlayers[i].IsAlive())
            {
                livingIndices.PushBack(static_cast<int>(i));
            }
        }

        if (livingIndices.Size() == 0)
        {
            // No targets but attacker still used their turn
            attacker->SetStat(Stats::AttackCount, 0);
            return;
        }

        // Pick a random living player to attack
        int randomIndex = livingIndices[rand() % livingIndices.Size()];
        Player& target = mPlayers[randomIndex];

        // Deal damage
        int damage = attacker->GetStat(Stats::Attack);
        int newHealth = target.GetStat(Stats::Health) - damage;
        target.SetStat(Stats::Health, newHealth);

        // 25% chance target slows down by 10
        if ((rand() % 100) < 25)
        {
            int newSpeed = target.GetStat(Stats::Speed) - 10;
            target.SetStat(Stats::Speed, newSpeed);
        }

        // 10% chance attacker speeds up by 5
        if ((rand() % 100) < 10)
        {
            int newSpeed = attacker->GetStat(Stats::Speed) + 5;
            attacker->SetStat(Stats::Speed, newSpeed);
        }

        // Attacking player's AttackCount is set to 0
        attacker->SetStat(Stats::AttackCount, 0);
    }

    // Returns the count of players that have health > 0
    int GetRemainingPlayers() const
    {
        int count = 0;
        for (std::size_t i = 0; i < mPlayers.Size(); ++i)
        {
            if (mPlayers[i].IsAlive())
            {
                ++count;
            }
        }
        return count;
    }

    // Sorts players by fastest speed using IntroSort.
    // In the sort callback: if a player's AttackCount or Health is 0,
    // treat their speed as 0 (don't actually set it).
    void OrderPlayers()
    {
        auto comp = [](const Player& a, const Player& b) -> bool
            {
                // Effective speed: treat as 0 if dead or already attacked
                int speedA = (a.GetStat(Stats::AttackCount) <= 0 || !a.IsAlive()) ? 0 : a.GetStat(Stats::Speed);
                int speedB = (b.GetStat(Stats::AttackCount) <= 0 || !b.IsAlive()) ? 0 : b.GetStat(Stats::Speed);
                // Sort descending (fastest first): b < a
                return speedB < speedA;
            };

        Globals::IntroSort(mPlayers.Begin(), mPlayers.End(), comp);
    }

    // Resets all living players' AttackCount to 1, then orders them
    void StartTurn()
    {
        for (std::size_t i = 0; i < mPlayers.Size(); ++i)
        {
            if (mPlayers[i].IsAlive())
            {
                mPlayers[i].SetStat(Stats::AttackCount, 1);
            }
        }
        OrderPlayers();
    }

    const std::string& GetName() const { return mName; }
    Vector<Player>& GetPlayers() { return mPlayers; }

private:
    std::string mName;
    Vector<Player> mPlayers;
};