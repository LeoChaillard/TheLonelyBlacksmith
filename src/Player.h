#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Tool.h"
#include <tuple>

class Player
{
public:
protected:
private:
	Inventory inventory;
	std::multimap<Tool, std::tuple<int, int>> woodCollectionIntervals;
	std::multimap<Tool, std::tuple<int, int>> stoneCollectionIntervals;
	std::multimap<Tool, std::tuple<int, int>> ironCollectionIntervals;

public:
	Player();
	~Player() = default;

	bool Collect(Material _material);
	bool Craft(Tool _tool);
	Inventory& GetInventory();
	int GetRandomQuantity(Material _material);
protected:
private:
};

#endif // PLAYER_H

