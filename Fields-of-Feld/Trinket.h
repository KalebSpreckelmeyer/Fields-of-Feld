#pragma once
#include "Item.h"
#include "Effect.h"
class Trinket :
    public Item
{
public:
	Effect effect;
	enum class TrinketType { AMULET, RING, MISC};
	TrinketType trinketType = TrinketType::MISC;

	Trinket();
	Trinket(Effect effect, TrinketType trinketType, PhysicalDamageType physType, MagicDamageType magType);
	~Trinket();
};

