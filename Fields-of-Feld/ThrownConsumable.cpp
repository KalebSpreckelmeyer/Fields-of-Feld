#include "ThrownConsumable.h"
#include "Item.h"
ThrownConsumable::ThrownConsumable()
{
}

ThrownConsumable::ThrownConsumable(bool specialDamage, std::string name, std::string description, float damage, float reach, 
	float attackSpeed, float weight, float quantity, float value)
	: Item(hasBeenInitialized, name, description, value, weight, quantity, slot), specialDamage(specialDamage), damage(damage), reach(reach), attackSpeed(attackSpeed)
{
}

ThrownConsumable::~ThrownConsumable()
{
}

