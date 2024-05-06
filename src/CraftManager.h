#ifndef CRAFTMANAGER_H
#define CRAFTMANAGER_H

#include "Inventory.h"
#include "Tool.h"
#include "Recipe.h"

class CraftManager
{
public:
protected:
private:
	std::multimap<Tool, Recipe> crafts;

public:
	CraftManager() = default;
	~CraftManager() = default;

	static CraftManager* GetInstance();

	void InitCrafts();
	bool CheckAndMakeCraft(Inventory& _inventory, Tool& _tool);
	Recipe& GetRecipe(Tool& _tool);
	std::multimap<Tool, Recipe>& GetCrafts();
protected:
private:
};

#endif // CRAFTMANAGER_H

