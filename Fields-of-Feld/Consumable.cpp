#include "Consumable.h"
#include <string>

Consumable::Consumable()
{
}

Consumable::Consumable(Effect effect, ConsumableType consumableType, PotionType potionType, std::string name, std::string description,
	PhysicalDamageType physType, MagicDamageType magType, float magnitude, float weight, float quantity, float value)
	: Item(hasBeenInitialized, name, description, physType, magType, value, weight, quantity, slot), effect(effect), consumableType(consumableType), potionType(potionType), magnitude(magnitude)
{
}

Consumable::~Consumable()
{
}
