#pragma once
#include "Item.h"
#include "Effect.h"

class Consumable :
    public Item
{
public:
	Effect effect;
	enum class ConsumableType { DEFAULT, POTION, FOOD, DRINK, SCROLL, GEM };
	ConsumableType consumableType = ConsumableType::DEFAULT;
	enum class PotionType { NOTPOTION, HEALING, FATIGUE };
	PotionType potionType = PotionType::NOTPOTION;
    float magnitude = 0.0f;

	Consumable();
	Consumable(Effect effect, ConsumableType consumableType, PotionType potionType, std::string name, std::string description,
		PhysicalDamageType physType, MagicDamageType magType, float magnitude, float weight, float quantity, float value);
	~Consumable();
};

