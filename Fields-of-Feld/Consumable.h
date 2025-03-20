#pragma once
#include "Item.h"
#include "Effect.h"
#include "Enchantment.h"

class Consumable :
    public Item
{
public:
	std::vector<Effect*> effects;
	enum class ConsumableType { DEFAULT, POTION, FOOD, DRINK, SCROLL, GEM };
	ConsumableType consumableType = ConsumableType::DEFAULT;
	enum class PotionType { NOTPOTION, HEALING, FATIGUE };
	PotionType potionType = PotionType::NOTPOTION;
    float magnitude = 0.0f;

	Consumable();
	Consumable(ConsumableType consumableType, PotionType potionType, std::string name, std::string description, 
		float magnitude, float weight, float quantity, float value);
	~Consumable();
};

