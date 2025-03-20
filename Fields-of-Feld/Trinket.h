#pragma once
#include "Item.h"
#include "Effect.h"
#include "Enchantment.h"
#include <vector>
class Trinket :
    public Item
{
public:
	std::vector<Enchantment*> enchantments;
	enum class TrinketType { AMULET, RING, MISC};
	TrinketType trinketType = TrinketType::MISC;

	Trinket();
	Trinket(TrinketType trinketType);
	~Trinket();
};

