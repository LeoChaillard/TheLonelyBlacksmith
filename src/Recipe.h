#ifndef RECIPE_H
#define RECIPE_H

#include <list>
#include "Material.h"
#include "Tool.h"

struct RequiredMaterial
{
	Material material;
	int iQuantity;
};

class Recipe
{
public:
protected:
private:
	int iTurnsToCraft;
	int iScoreOnCraft;
	std::list<RequiredMaterial> requiredMaterials;
	Tool prerequisiteTool;

public:
	Recipe() = default;
	Recipe(int _iTurnsToCraft, int _iScoreOnCraft, std::tuple<int, int, int> _requiredMaterials);
	~Recipe() = default;
	
	const std::list<RequiredMaterial>& GetRecquiredMaterials();
	void AddRequiredMaterial(const RequiredMaterial& _requiredMaterial);
	void AddPrerequisiteTool(Tool _tool);
	int GetTurnsToCraft() const;
	int GetScoreOnCraft() const;
	Tool GetPrerequisiteTool() const;
protected:
private:
};

#endif // RECIPE_H

