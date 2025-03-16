#include "Weapon.h"
#include <string>

Weapon::Weapon()
{
}

Weapon::Weapon(bool specialDamage, std::string name, std::string description, float damage, float defense, float reach, float attackSpeed, float weight, float value,
	bool twohanded, bool needsAmmo, WeaponType weaponType, PhysicalDamageType physicalDamageType)
	: specialDamage(specialDamage), damage(damage), defense(defense), reach(reach), attackSpeed(attackSpeed), twoHanded(twohanded), needsAmmo(needsAmmo),
	weaponType(weaponType), physicalDamageType(physicalDamageType), Item(true, name, description, value, weight, 1.0f, EquipSlots::BACKPACK)
{
}

Weapon::~Weapon()
{
}