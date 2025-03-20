#include "Consumable.h"
#include <string>

Consumable::Consumable()
{
}

Consumable::Consumable(ConsumableType consumableType, PotionType potionType, std::string name, std::string description,
	float magnitude, float weight, float quantity, float value)
	: Item(hasBeenInitialized, name, description, value, weight, quantity, slot), 
	consumableType(consumableType), potionType(potionType), magnitude(magnitude)
{
}

Consumable::~Consumable()
{
}
