#include "Ammunition.h"
#include <iostream>

Ammunition::Ammunition()
{
}

Ammunition::Ammunition(bool specialDamage, bool hasBeenInitialized, std::string name, std::string description, float value, float weight, 
	float quantity, EquipSlots slot, float damage, float range, AmmoType ammoType, AmmoDamageType ammoDamageType)
	: Item(hasBeenInitialized, name, description, value, weight, quantity, slot), specialDamage(specialDamage), damage(damage), range(range), 
	ammoType(ammoType), ammoDamageType(ammoDamageType)
{
}

Ammunition::~Ammunition()
{
}
