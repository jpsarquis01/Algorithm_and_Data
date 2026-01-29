#include <iostream>
#include "Vector.h"
#include "Array.h"
#include "Player.h"

// simple pool of names to pick from
static const char* gNames[] =
{
	"Link","Mario","Zelda","Samus","Kratos","MasterChief","LaraCroft","Geralt",
	"SolidSnake","Sonic","Cloud","Sephiroth","ArthurMorgan","Joel","Ellie","Ezio",
	"Dante","MegaMan","Pikachu","Kirby","Bowser","Yoshi","DonkeyKong","FoxMcCloud",
	"LeonKennedy","JillValentine","Ryu","Ken","SubZero","Scorpion"
};

// get number of names in pool
static int GetNameCount()
{
	return (int)(sizeof(gNames) / sizeof(gNames[0]));
}

// make a random player from the name pool
static Player MakeRandomPlayer()
{
	int idx = std::rand() % GetNameCount();
	return Player(gNames[idx]);
}

// add X random players to the vector
static void AddRandomPlayers(Vector<Player>& players, int count)
{
	for (int i = 0; i < count; ++i)
	{
		players.PushBack(MakeRandomPlayer());
	}
}

// remove X players from the end of the vector
static void RemovePlayers(Vector<Player>& players, int howMany)
{
	for (int i = 0; i < howMany; ++i)
	{
		if (players.Size() > 0)
		{
			players.PopBack();
		}
	}
}

// print all players in the vector
static void PrintAllPlayers(const Vector<Player>& players)
{
	for (int i = 0; i < players.Size(); ++i)
	{
		std::cout << i + 1 << ". ";
		players[i].PrintStats();
		std::cout << "-----------------------\n";
	}
}

// PlayerA(Attack * Stamina) - PlayerB(Defense * Speed) / PlayerB(Health)
static int HitValue(const Player& attacker, const Player& defender)
{
	int atk = attacker.GetStat(Stats::Attack);
	int sta = attacker.GetStat(Stats::Stamina);

	int def = defender.GetStat(Stats::Defense);
	int spd = defender.GetStat(Stats::Speed);
	int hp = defender.GetStat(Stats::Health);

	return (atk * sta) - ((def * spd) / hp);
}

static void Fight(const Player& player1, const Player& player2)
{
	// Player1 hits Player2
	int damageToPlayer2 = HitValue(player1, player2);

	// Player2 hits Player1 (reverse calc)
	int damageToPlayer1 = HitValue(player2, player1);

	// keep it simple: negative damage = 0
	int realDamageToP1 = (damageToPlayer1 > 0) ? damageToPlayer1 : 0;
	int realDamageToP2 = (damageToPlayer2 > 0) ? damageToPlayer2 : 0;

	int p1Health = player1.GetStat(Stats::Health);
	int p2Health = player2.GetStat(Stats::Health);

	int remainingP1 = p1Health - realDamageToP1;
	int remainingP2 = p2Health - realDamageToP2;

	if (remainingP2 > remainingP1)
	{
		std::cout << "--------------------------------\n";
		std::cout << "Winner:\n";
		std::cout << "--------------------------------\n";
		player1.PrintStats();
	}
	else if (remainingP1 > remainingP2)
	{
		std::cout << "--------------------------------\n";
		std::cout << "Winner:\n";
		std::cout << "--------------------------------\n";
		player2.PrintStats();
	}
	else
	{
		std::cout << "It's a Tie!\n";
		std::cout << "Flipping a coin to determine the winner...\n";
		int coinFlip = std::rand() % 2; // 0 or 1

		std::cout << "--------------------------------\n";
		std::cout << "Winner:\n";
		std::cout << "--------------------------------\n";

		if (coinFlip == 0)
			player1.PrintStats();
		else
			player2.PrintStats();
	}
}

int main()
{
	std::srand(std::time(nullptr));

	Vector<Player> playersVector;
	playersVector.Reserve(10);

	// add 10 players
	AddRandomPlayers(playersVector, 10);

	std::cout << "Add 10 players: \n";
	std::cout << "--------------------------------\n";
	PrintAllPlayers(playersVector);

	// remove last 6
	RemovePlayers(playersVector, 6);

	std::cout << "\nRemove 6: \n";
	std::cout << "--------------------------------\n";
	PrintAllPlayers(playersVector);

	std::cout << "\ncapacity: " << playersVector.Capacity() << "\n";

	// fill up to 20 total, then print ONLY the new ones
	int startNewPlayers = playersVector.Size();

	while (playersVector.Size() < 20)
	{
		playersVector.PushBack(MakeRandomPlayer());
	}

	std::cout << "\nFill up and print only the NEW ones\n";
	std::cout << "--------------------------------\n";
	for (int i = startNewPlayers; i < playersVector.Size(); ++i)
	{
		std::cout << i + 1 << ". ";
		playersVector[i].PrintStats();
		std::cout << "-----------------------\n";
	}

	std::cout << "\nNew capacity: " << playersVector.Capacity() << "\n";

	// Random battle selection
	int randomPlayer1 = std::rand() % playersVector.Size();
	int randomPlayer2 = std::rand() % playersVector.Size();

	while (randomPlayer1 == randomPlayer2)
	{
		randomPlayer2 = std::rand() % playersVector.Size();
	}

	std::cout << "\nRandomly Selected Players for Battle: \n";
	std::cout << "--------------------------------\n";
	playersVector[randomPlayer1].PrintStats();
	std::cout << "---------------VS---------------\n";
	playersVector[randomPlayer2].PrintStats();

	Fight(playersVector[randomPlayer1], playersVector[randomPlayer2]);

	return 0;
}