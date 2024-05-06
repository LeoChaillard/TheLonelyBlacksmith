#include <algorithm>
#include <iostream>
#include "Inventory.h"

Inventory::Inventory()
	: materialQuantities(),
	toolQuantities(),
	currentBestPickaxe(),
	currentBestAxe()
{

}

Inventory::Inventory(const Inventory& _inventory)
	: materialQuantities(_inventory.materialQuantities),
	toolQuantities(_inventory.toolQuantities),
	currentBestPickaxe(_inventory.currentBestPickaxe),
	currentBestAxe(_inventory.currentBestAxe)
{
}

int Inventory::GetMaterialQuantity(Material _material)
{
	if (materialQuantities.empty() || !HasMaterial(_material))
	{
		return 0;
	}
	return materialQuantities[_material];
}

Tool& Inventory::GetCurrentBestPickaxe()
{
	return currentBestPickaxe;
}

Tool& Inventory::GetCurrentBestAxe()
{
	return currentBestAxe;
}

void Inventory::AddMaterial(Material _material, int _iQuantity/* = 1 */)
{
	std::map<Material, int>::iterator it = materialQuantities.find(_material);
	if (it != materialQuantities.end())
	{
		it->second += _iQuantity;
	}
	else
	{
		materialQuantities.insert({ _material, _iQuantity });
	}
}

void Inventory::RemoveMaterial(Material _material, int _iQuantity/* = 1 */)
{
	std::map<Material, int>::iterator it = materialQuantities.find(_material);
	if (it != materialQuantities.end())
	{
		it->second -= _iQuantity;
		if (it->second <= 0)
		{
			materialQuantities.erase(_material);
		}
	}
}

void Inventory::AddTool(Tool& _tool)
{
	std::map<Tool, int>::iterator it = toolQuantities.find(_tool);
	if (it != toolQuantities.end())
	{
		it->second++;
	}
	else
	{
		toolQuantities.insert({ _tool, 1 });
		if (_tool.GetToolType() == ToolType::PICKAXE && currentBestPickaxe.GetToolType() == ToolType::UNSPECIFIED)
		{
			currentBestPickaxe = _tool;
		}
		else if (_tool.GetToolType() == ToolType::AXE && currentBestAxe < _tool)
		{
			currentBestAxe = _tool;
		}
	}
}

bool Inventory::HasMaterial(const Material& _material)
{
	return materialQuantities.find(_material) != materialQuantities.end();
}

bool Inventory::HasTool(const Tool& _tool)
{
	return toolQuantities.find(_tool) != toolQuantities.end();
}

