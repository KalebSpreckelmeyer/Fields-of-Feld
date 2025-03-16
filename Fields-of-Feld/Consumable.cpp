#include "Consumable.h"
#include <string>

Consumable::Consumable()
{
}

Consumable::Consumable(Effect effect, ConsumableType consumableType, PotionType potionType, std::string name, std::string description, float magnitude,
	float weight, float quantity, float value)
	: Item(hasBeenInitialized, name, description, value, weight, quantity, slot), effect(effect), consumableType(consumableType), potionType(potionType), magnitude(magnitude)
{
}

Consumable::~Consumable()
{
}
