#pragma once
#include "Item.h"
#include "Effect.h"
#include "Enchantment.h"
#include "nlohmann/json.hpp"

class Consumable :
    public Item
{
public:
    float magnitude = 0.0f;
	std::vector<std::shared_ptr<Effect>> effects;

	Consumable() = default;
	Consumable(std::string name, std::string description, 
		float magnitude, float weight, float quantity, float value);
	virtual ~Consumable() = default;

	virtual void use(std::shared_ptr<Character> consumer) = 0;
};

