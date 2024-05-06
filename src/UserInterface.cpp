#include <iostream>
#include <algorithm>
#include "UserInterface.h"
#include "GameManager.h"
#include "CraftManager.h"
#include "Resource.h"

UserInterface::UserInterface()
{
}

UserInterface* UserInterface::GetInstance()
{
	static UserInterface* spInstance = nullptr;
	if (spInstance == nullptr)
	{
		spInstance = new UserInterface();
	}
	return spInstance;
}

void UserInterface::HandleDisplay()
{
	DisplayMainMenu();
}

void UserInterface::DisplayWelcome()
{
	std::cout << "**********Welcome to The Lonely Blacksmith game!**********" << std::endl;
}

void UserInterface::DisplayMainMenu()
{
	std::cout << "1. Collect resources" << std::endl;
	std::cout << "2. Craft tool" << std::endl;
	std::cout << "3. Display resources" << std::endl;

	std::string strInput;
	do
	{
		std::cin >> strInput;
	} while (!IsValidInt(strInput));

	int iChoice = std::stoi(strInput);
	std::cout << std::endl;

	switch (iChoice)
	{
	case 1:
		DisplayCollectMenu();
		break;
	case 2:
		DisplayCraftMenu();
		break;
	case 3: 
		DisplayResourcesMenu();
		break;
	default:
		// wrong input
		break;
	}
}

void UserInterface::DisplayCollectMenu()
{
	std::cout << "1. Collect wood - 1 turn" << std::endl;
	std::cout << "2. Collect stone - 1 turn" << std::endl;
	std::cout << "3. Collect iron - 1 turn - pickaxe required" << std::endl;
	std::cout << "4. Return to main menu" << std::endl;

	int iChoice = 0;
	while (iChoice != 4)
	{
		std::string strInput;
		do
		{
			std::cin >> strInput;
		} while (!IsValidInt(strInput));

		iChoice = std::stoi(strInput);

		switch (iChoice)
		{
		case 1:
			GameManager::GetInstance()->GetPlayer().Collect(Material::WOOD);
			break;
		case 2:
			GameManager::GetInstance()->GetPlayer().Collect(Material::STONE);
			break;
		case 3:
			GameManager::GetInstance()->GetPlayer().Collect(Material::IRON);
			break;
		case 4:
			std::cout << "Returning to menu..." << std::endl;
			break;
		default:
			// wrong input
			break;
		}
	}
}

void UserInterface::DisplayCraftMenu()
{
	int iChoice = 0;
	while(iChoice != 3)
	{
		std::cout << "1. Craft a wood pickaxe - 1 turn - 2 Wood - 10 points" << std::endl; // TODO: display currently highest craftable tool
		std::cout << "2. Craft... (see available recipes)" << std::endl;
		std::cout << "3. Return to main menu" << std::endl;

		std::string strInput;
		do
		{
			std::cin >> strInput;
		} while (!IsValidInt(strInput));

		iChoice = std::stoi(strInput);
		std::cout << std::endl;

		switch (iChoice)
		{
		case 1:
		{
			// display currently highest craftable object
			Tool tool(ToolType::PICKAXE, Material::WOOD);
			GameManager::GetInstance()->GetPlayer().Craft(tool);
			break;
		}
		case 2:
		{
			std::multimap<Tool, Recipe> crafts = CraftManager::GetInstance()->GetCrafts();
			std::cout << "*****RECIPES*****" << std::endl << std::endl;
			int iCraftCounter = 0;

			for (auto& element : crafts)
			{
				++iCraftCounter;

				// Tool
				std::cout << iCraftCounter << ". " << element.first.GetMaterial().ToString();
				element.first.GetMaterial() == Material::UNSPECIFIED ? std::cout << "" : std::cout << " ";
				std::cout << element.first.GetToolType().ToString() << " - ";
				
				// Craft infos
				std::cout << element.second.GetTurnsToCraft() << " turn(s) - ";
				for (auto& resource : element.second.GetRecquiredMaterials())
				{
					std::cout << resource.iQuantity << " " << resource.material.ToString() << " - ";
				}

				std::cout << element.second.GetScoreOnCraft() << " points";
				if (element.second.GetPrerequisiteTool().GetToolType() != ToolType::UNSPECIFIED)
				{
					std::cout << " (" << element.second.GetPrerequisiteTool().GetMaterial().ToString()
						<< " " << element.second.GetPrerequisiteTool().GetToolType().ToString() << " required)";
				} 
				std::cout << std::endl;
			}			

			std::string strInput;
			do
			{
				std::cin >> strInput;
			} while (!IsValidInt(strInput));

			int iCraftChoice = std::stoi(strInput);
			std::cout << std::endl;

			iCraftCounter = 0;
			for (std::multimap<Tool, Recipe>::iterator it = crafts.begin(); it != crafts.end(); ++it)
			{
				++iCraftCounter;

				if (iCraftChoice == iCraftCounter)
				{
					GameManager::GetInstance()->GetPlayer().Craft(it->first);
					break;
				}
			}

			break;
		}
		case 3:
			std::cout << "Returning to menu..." << std::endl;
			break;
		default:
			// wrong input
			break;
		}
	}
	std::cout << "Back to menu..." << std::endl;
}

void UserInterface::DisplayResourcesMenu()
{
	Inventory& inventory = GameManager::GetInstance()->GetPlayer().GetInventory();
	std::cout << "1. You currently have " << inventory.GetMaterialQuantity(Material::WOOD) << " wood, "
		<< inventory.GetMaterialQuantity(Material::STONE) << " stone, "
		<< inventory.GetMaterialQuantity(Material::IRON) << " iron" << std::endl;
	std::cout << "2. Return to main menu" << std::endl;

	int iChoice = 0;
	while (iChoice != 2)
	{
		std::string strInput;
		do
		{
			std::cin >> strInput;
		} while (!IsValidInt(strInput));

		iChoice = std::stoi(strInput);
		std::cout << std::endl;
	}
}

bool UserInterface::IsValidInt(const std::string& strValue)
{
	return std::all_of(std::begin(strValue), std::end(strValue), [](unsigned char c) { return std::isdigit(c); });
}

