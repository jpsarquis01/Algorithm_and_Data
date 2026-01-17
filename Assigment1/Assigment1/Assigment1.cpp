#include <iostream>
#include "Vector.h"
#include "Array.h"
#include "Player.h"

void Fight(const Player& player1, const Player& player2)
{
	// PlayerA calculations
	int player1Atk = player1.GetStat(Stats::Attack);
	int player1Sta = player1.GetStat(Stats::Stamina);
	int player2Def = player2.GetStat(Stats::Defense);
	int player2Spd = player2.GetStat(Stats::Speed);
	int player2Health = player2.GetStat(Stats::Health);
	int damageToPlayer2 = (player1Atk * player1Sta) - (player2Def + player2Spd / player2Health);

	// PlayerB calculations
	int player2Atk = player2.GetStat(Stats::Attack);
	int player2Sta = player2.GetStat(Stats::Stamina);
	int player1Def = player1.GetStat(Stats::Defense);
	int player1Spd = player1.GetStat(Stats::Speed);
	int player1Health = player1.GetStat(Stats::Health);
	int damageToPlayer1 = (player2Atk * player2Sta) - (player1Def + player1Spd / player1Health);

	if (damageToPlayer2 > damageToPlayer1)
	{
		std::cout << "--------------------------------\n";
		std::cout << "Winner:\n";
		std::cout << "--------------------------------\n";
		player1.PrintStats();
	}
	else if (damageToPlayer1 > damageToPlayer2)
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
		if (coinFlip == 0)
		{
			std::cout << "--------------------------------\n";
			std::cout << "Winner:\n";
			std::cout << "--------------------------------\n";
			player1.PrintStats();
		}
		else
		{
			std::cout << "--------------------------------\n";
			std::cout << "Winner:\n";
			std::cout << "--------------------------------\n";
			player2.PrintStats();
		}
	}
}

int main()
{
	std::srand(std::time(nullptr));

	Vector<Player> playersVector;
	playersVector.Reserve(10);

	Player Player1("Greivin");
	Player Player2("Alfredo");
	Player Player3("Santiago");
	Player Player4("Darren");
	Player Player5("Arthur");
	Player Player6("Ayush");
	Player Player7("Thomas");
	Player Player8("Juan");
	Player Player9("Alfredo");
	Player Player10("Tavin");

	playersVector.PushBack(Player1);
	playersVector.PushBack(Player2);
	playersVector.PushBack(Player3);
	playersVector.PushBack(Player4);
	playersVector.PushBack(Player5);
	playersVector.PushBack(Player6);
	playersVector.PushBack(Player7);
	playersVector.PushBack(Player8);
	playersVector.PushBack(Player9);
	playersVector.PushBack(Player10);

	std::cout << "Part 1: \n";
	std::cout << "--------------------------------\n";
	for (int i = 0; i < playersVector.Size(); ++i)
	{
		std::cout << i + 1 << ". ";
		playersVector[i].PrintStats();
		std::cout << "-----------------------\n";
	}

	// removes last 6 players from the vector. 0-5 indexes
	for (int i = 0; i < 6; ++i)
	{
		playersVector.PopBack();
	}

	std::cout << "\nPart 2: \n";
	std::cout << "--------------------------------\n";
	for (int i = 0; i < playersVector.Size(); ++i)
	{
		std::cout << i + 1 << ". ";
		playersVector[i].PrintStats();
		std::cout << "-----------------------\n";
	}

	std::cout << "\ncapacity: " << playersVector.Capacity() << "\n";

	// add 16 more players max it out at 20
	// Player1 - Player4 left 

	Player Player11("Liam");
	Player Player12("Noah");
	Player Player13("Oliver");
	Player Player14("Elijah");
	Player Player15("James");
	Player Player16("William");
	Player Player17("Jac");
	Player Player18("Jose");
	Player Player19("Alex");
	Player Player20("Will");
	Player Player21("Smithers");
	Player Player22("Homer");
	Player Player23("Mario");
	Player Player24("Ronaldo");
	Player Player25("Speed");
	Player Player26("Holoa");

	playersVector.PushBack(Player11);
	playersVector.PushBack(Player12);
	playersVector.PushBack(Player13);
	playersVector.PushBack(Player14);
	playersVector.PushBack(Player15);
	playersVector.PushBack(Player16);
	playersVector.PushBack(Player17);
	playersVector.PushBack(Player18);
	playersVector.PushBack(Player19);
	playersVector.PushBack(Player20);
	playersVector.PushBack(Player21);
	playersVector.PushBack(Player22);
	playersVector.PushBack(Player23);
	playersVector.PushBack(Player24);
	playersVector.PushBack(Player25);
	playersVector.PushBack(Player26);

	std::cout << "\nPart 3: (New Players)\n";
	std::cout << "--------------------------------\n";
	for (int i = 4; i < playersVector.Size(); ++i)
	{
		std::cout << i + 1 << ". ";
		playersVector[i].PrintStats();
		std::cout << "-----------------------\n";
	}

	std::cout << "\nNew capacity: " << playersVector.Capacity() << "\n";

	int randomPlayer1 = std::rand() % 20;
	int randomPlayer2 = std::rand() % 20; // to get a random player between 1 and 20

	while (randomPlayer1 == randomPlayer2)
	{
		randomPlayer2 = std::rand() % 20;
	}

	std::cout << "\nRandomly Selected Players for Battle: \n";
	std::cout << "--------------------------------\n";
	playersVector[randomPlayer1].PrintStats();
	std::cout << "---------------\033[31mvs\033[0m---------------\n";
	playersVector[randomPlayer2].PrintStats();

	Fight(playersVector[randomPlayer1], playersVector[randomPlayer2]);

	return 0;
}

