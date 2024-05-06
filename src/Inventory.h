#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <list>
#include "Tool.h"

class Inventory
{
public:
protected:
private:
	std::map<Material, int> materialQuantities;
	std::map<Tool, int> toolQuantities;
	Tool currentBestPickaxe;
	Tool currentBestAxe;

public:
	Inventory();
	Inventory(const Inventory& _inventory);
	~Inventory() = default;

	int GetMaterialQuantity(Material _material);
	void AddMaterial(Material _material, int _iQuantity = 1);
	void RemoveMaterial(Material _material, int _iQuantity = 1);
	void AddTool(const Tool& _tool);
	Tool& GetCurrentBestPickaxe();
	Tool& GetCurrentBestAxe();
	bool HasMaterial(const Material& _material);
	bool HasTool(const Tool& _tool);
protected:
private:
};

#endif // INVENTORY_H

