#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Player.h"
#include "CraftManager.h"
#include "GameManager.h"

namespace constants
{
	const char* strCollectedResourcesFileName = "collectionIntervals.txt";
	const int iInitialWood = 2;
	const int iInitialStone = 1;
	const int iInitialIron = 0;
}

Player::Player()
	: inventory()
{	
	// Temporary tuple list
	std::vector<std::tuple<int, int>> tuplesList;

	// Input file
	std::string strFileName(constants::strCollectedResourcesFileName);

	// Lines
	int iLines = 0, iLineElements = 7;
	std::string strLine;

	std::ifstream intervals(strFileName);
	if (intervals.is_open())
	{
		// Ignoring first line
		std::getline(intervals, strLine);

		while (!intervals.eof())
		{
			for (int i = 0; i < iLineElements; ++i)
			{
				i == iLineElements - 1 ? std::getline(intervals, strLine, '\n') : std::getline(intervals, strLine, ',');
				int iPos = strLine.find("-");
				std::string strLow = strLine.substr(0, iPos);
				std::string strHigh = strLine.substr(iPos + 1);
				tuplesList.push_back(std::make_tuple(std::stoi(strLow), std::stoi(strHigh)));
			}
		}
	}

	// Filling intervals
	woodCollectionIntervals.insert({ Tool(ToolType::UNSPECIFIED, Material::UNSPECIFIED), tuplesList.at(0) });
	woodCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::WOOD), tuplesList.at(1) });
	woodCollectionIntervals.insert({ Tool(ToolType::AXE, Material::WOOD), tuplesList.at(2) });
	woodCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::STONE), tuplesList.at(3) });
	woodCollectionIntervals.insert({ Tool(ToolType::AXE, Material::STONE), tuplesList.at(4) });
	woodCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::IRON), tuplesList.at(5) });
	woodCollectionIntervals.insert({Tool(ToolType::AXE, Material::IRON), tuplesList.at(6) });

	stoneCollectionIntervals.insert({ Tool(ToolType::UNSPECIFIED, Material::UNSPECIFIED), tuplesList.at(7) });
	stoneCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::WOOD), tuplesList.at(8) });
	stoneCollectionIntervals.insert({ Tool(ToolType::AXE, Material::WOOD), tuplesList.at(9) });
	stoneCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::STONE), tuplesList.at(10) });
	stoneCollectionIntervals.insert({ Tool(ToolType::AXE, Material::STONE), tuplesList.at(11) });
	stoneCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::IRON), tuplesList.at(12) });
	stoneCollectionIntervals.insert({ Tool(ToolType::AXE, Material::IRON), tuplesList.at(13) });

	ironCollectionIntervals.insert({ Tool(ToolType::UNSPECIFIED, Material::UNSPECIFIED), tuplesList.at(14) });
	ironCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::WOOD), tuplesList.at(15) });
	ironCollectionIntervals.insert({ Tool(ToolType::AXE, Material::WOOD), tuplesList.at(16) });
	ironCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::STONE), tuplesList.at(17) });
	ironCollectionIntervals.insert({ Tool(ToolType::AXE, Material::STONE), tuplesList.at(18) });
	ironCollectionIntervals.insert({ Tool(ToolType::PICKAXE, Material::IRON), tuplesList.at(19) });
	ironCollectionIntervals.insert({ Tool(ToolType::AXE, Material::IRON), tuplesList.at(20) });

	// Initial resources
	inventory.AddMaterial(Material::WOOD, constants::iInitialWood);
	inventory.AddMaterial(Material::STONE, constants::iInitialStone);
	inventory.AddMaterial(Material::IRON, constants::iInitialIron);
}

bool Player::Collect(Material _material)
{
	if (_material == Material::IRON && inventory.GetCurrentBestPickaxe().GetToolType() == ToolType::UNSPECIFIED)
	{
		std::cout << "Pickaxe is required!" << std::endl;
		return false;
	}

	GameManager::GetInstance()->RemoveTurns(1);
	int iRandomQuantity = GetRandomQuantity(_material);
	std::cout << "Collected " << iRandomQuantity << " " << _material.ToString() << std::endl;

	inventory.AddMaterial(_material, iRandomQuantity);
	return true;
}

bool Player::Craft(Tool _tool)
{
	if (CraftManager::GetInstance()->CheckAndMakeCraft(inventory, _tool))
	{
		std::cout << "Crafted a " << _tool.GetMaterial().ToString() << " " << _tool.GetToolType().ToString() << std::endl;
		inventory.AddTool(_tool);
		return true;
	}
	return false;
}

Inventory& Player::GetInventory()
{
	return inventory;
}

int Player::GetRandomQuantity(Material _material)
{
	int iLow = 1, iHigh = 1;
	std::multimap<Tool, std::tuple<int, int>>::iterator it;
	srand(time(0));

	// Using Axe
	if (_material == Material::WOOD)
	{
		it = woodCollectionIntervals.find(inventory.GetCurrentBestAxe());
	}
	
	// Using Pickaxe
	if (_material == Material::STONE || _material == Material::IRON)
	{
		it =  _material == Material::STONE ? stoneCollectionIntervals.find(inventory.GetCurrentBestPickaxe()) 
									       : ironCollectionIntervals.find(inventory.GetCurrentBestPickaxe());

	}

	std::tuple<int, int> interval = it->second;
	iLow = std::get<0>(interval);
	iHigh = std::get<1>(interval);
	int iResult = iLow + (rand() % iHigh);

	return iResult;
}
