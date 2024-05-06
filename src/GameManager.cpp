#include <iostream>
#include "GameManager.h"
#include "CraftManager.h"
#include "UserInterface.h"

namespace constants
{
	const int iMaxTurns = 100;
}

GameManager::GameManager() 
	: iTurns(constants::iMaxTurns),
	iScore(0),
	player()
{
}

GameManager* GameManager::GetInstance()
{
	static GameManager* spInstance = nullptr;
	if (spInstance == nullptr)
	{
		spInstance = new GameManager();
	}
	return spInstance;
}

void GameManager::Init()
{
	// retrieve iTurns limit
	// resource manager init to load recipes??
	CraftManager::GetInstance()->InitCrafts();
}

void GameManager::Run()
{
	GameManager::GetInstance()->Init();
	UserInterface::GetInstance()->DisplayWelcome();
	while (true)
	{
		if (iTurns <= 0)
		{
			return;
		}
		std::cout << "Displaying Menu..." << std::endl;
		UserInterface::GetInstance()->HandleDisplay();
	}
}

Player& GameManager::GetPlayer()
{
	return player;
}

void GameManager::RemoveTurns(int _turns)
{
	iTurns -= _turns;
}

void GameManager::AddScore(int _iScore)
{
	iScore += _iScore;
}
