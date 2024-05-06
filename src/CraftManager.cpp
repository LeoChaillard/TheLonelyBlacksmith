#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include "CraftManager.h"
#include "GameManager.h"

namespace constants
{
	const char* strRecipeFileName = "recipes.txt";
}

CraftManager::CraftManager()
{
}

void CraftManager::InitCrafts()
{
	// Temporary recipe list
	std::vector<Recipe> recipesList;
	std::vector<int> recipesValues;

	// Input file
	std::string strFileName(constants::strRecipeFileName);

	// Lines
	int iLines = 0, iLineElements = 5;
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
				recipesValues.push_back(std::stoi(strLine));
			}
			recipesList.push_back(Recipe(recipesValues.at(0), recipesValues.at(1), std::make_tuple(recipesValues.at(2), recipesValues.at(3), recipesValues.at(4))));
			recipesValues.clear();
		}
	}

	crafts.insert({ Tool(ToolType::PICKAXE, Material::WOOD), recipesList.at(0)});
	crafts.insert({ Tool(ToolType::AXE, Material::WOOD), recipesList.at(1) });
	crafts.insert({ Tool(ToolType::HAMMER, Material::BASIC), recipesList.at(2) });
	crafts.insert({ Tool(ToolType::PICKAXE, Material::STONE), recipesList.at(3) });
	crafts.insert({ Tool(ToolType::AXE, Material::STONE), recipesList.at(4) });

	recipesList.at(5).AddPrerequisiteTool(Tool(ToolType::HAMMER, Material::BASIC));
	crafts.insert({ Tool(ToolType::HAMMER, Material::STONE), recipesList.at(5) }); // basic hammer required

	crafts.insert({ Tool(ToolType::PICKAXE, Material::IRON), recipesList.at(6) });
	crafts.insert({ Tool(ToolType::AXE, Material::IRON), recipesList.at(7) });

	recipesList.at(8).AddPrerequisiteTool(Tool(ToolType::HAMMER, Material::STONE));
	crafts.insert({ Tool(ToolType::HAMMER, Material::IRON), recipesList.at(8) }); // stone hammer required

	recipesList.at(9).AddPrerequisiteTool(Tool(ToolType::HAMMER, Material::IRON));
	crafts.insert({ Tool(ToolType::FORGE, Material::UNSPECIFIED), recipesList.at(9) }); // iron hammer required
}

CraftManager* CraftManager::GetInstance()
{
	static CraftManager* spInstance = nullptr;
	if (spInstance == nullptr)
	{
		spInstance = new CraftManager();
	}
	return spInstance;
}

bool CraftManager::CheckAndMakeCraft(Inventory& _inventory, Tool& _tool)
{
	std::map<Tool, Recipe>::iterator it = crafts.find(_tool);
	if (it == crafts.end())
	{
		return false;
	}

	// Checking prequisite
	if (it->second.GetPrerequisiteTool().GetToolType() != ToolType::UNSPECIFIED)
	{
		if (!_inventory.HasTool(it->second.GetPrerequisiteTool()))
		{
			std::cout << it->second.GetPrerequisiteTool().GetMaterial().ToString() << " " 
					  << it->second.GetPrerequisiteTool().GetToolType().ToString() << " required!" << std::endl;
			return false;
		}
	}

	// Checking resources
	std::list<RequiredMaterial> requiredMaterials = it->second.GetRecquiredMaterials();
	for (const RequiredMaterial& requiredMaterial : requiredMaterials)
	{
		if (_inventory.GetMaterialQuantity(requiredMaterial.material) < requiredMaterial.iQuantity)
		{
			std::cout << "Not craftable" << std::endl;
			return false;
		}
	}

	// Removing resources from inventory
	for (const RequiredMaterial& requiredMaterial : requiredMaterials)
	{
		_inventory.RemoveMaterial(requiredMaterial.material, requiredMaterial.iQuantity);
	}

	// Updating turns and scores
	GameManager::GetInstance()->RemoveTurns(it->second.GetTurnsToCraft());
	GameManager::GetInstance()->AddScore(it->second.GetScoreOnCraft());

	return true;
}

Recipe& CraftManager::GetRecipe(Tool& _tool)
{
	return crafts.find(_tool)->second;
}

std::multimap<Tool, Recipe> CraftManager::GetCrafts()
{
	return crafts;
}
