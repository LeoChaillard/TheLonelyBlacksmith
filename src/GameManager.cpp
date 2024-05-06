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
			std::cout << "You used all your turns! Your final score is " << iScore << std::endl;
			return;
		}
		UserInterface::GetInstance()->HandleDisplay();
	}
}

Player& GameManager::GetPlayer()
{
	return player;
}

int GameManager::GetRemainingTurns() const
{
	return iTurns;
}

void GameManager::RemoveTurns(int _turns)
{
	iTurns -= _turns;
}

void GameManager::AddScore(int _iScore)
{
	iScore += _iScore;
}
