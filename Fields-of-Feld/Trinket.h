#pragma once
#include "Item.h"
#include "Effect.h"
class Trinket :
    public Item
{
public:
	Effect effect;
	enum class TrinketType { AMULET, RING, MISC};
	TrinketType trinketType;

	Trinket();
	Trinket(Effect effect, TrinketType trinketType);
	~Trinket();
};

