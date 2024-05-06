#include "Recipe.h"

Recipe::Recipe(int _iTurnsToCraft, int _iScoreOnCraft, std::tuple<int, int, int> _requiredMaterials)
	: iTurnsToCraft(_iTurnsToCraft),
	iScoreOnCraft(_iScoreOnCraft),
	requiredMaterials(),
	prerequisiteTool()
{
	AddRequiredMaterial({ Material::WOOD, std::get<0>(_requiredMaterials) });
	AddRequiredMaterial({ Material::STONE, std::get<1>(_requiredMaterials) });
	AddRequiredMaterial({ Material::IRON, std::get<2>(_requiredMaterials) });
}

const std::list<RequiredMaterial>& Recipe::GetRecquiredMaterials()
{
	return requiredMaterials;
}

void Recipe::AddRequiredMaterial(const RequiredMaterial& _requiredResource)
{
	requiredMaterials.push_back(_requiredResource);
}

void Recipe::AddPrerequisiteTool(Tool _tool)
{
	prerequisiteTool = _tool;
}

int Recipe::GetTurnsToCraft() const
{
	return iTurnsToCraft;
}

int Recipe::GetScoreOnCraft() const
{
	return iScoreOnCraft;
}

Tool& Recipe::GetPrerequisiteTool()
{
	return prerequisiteTool;
}
