#include "Armor.h"
#include <vector>
#include <string>
#include "Item.h"

Armor::Armor() {
}
Armor::Armor(std::string name, std::string description, float weight, float value, bool isLight, bool isMedium,
	bool isHeavy, ArmorDescriptor armorDescriptor, PhysicalDamageType physType, MagicDamageType magType) : 
	Item(true, name, description, physType, magType, value, weight, 1.0f, EquipSlots::BACKPACK),
	isLight(isLight), isMedium(isMedium), isHeavy(isHeavy)
{ 
	//sets physical resistances to the map to default values
	for (PhysicalDamageType type : {PhysicalDamageType::BLUNT, PhysicalDamageType::PIERCE,
		PhysicalDamageType::SLASH, PhysicalDamageType::CHOP})
	{
		physicalResistance[type] = 0.0f;
	}
	//sets magic resistances to the map to default values
	for (MagicDamageType type : { MagicDamageType::MAGIC, MagicDamageType::FIRE, MagicDamageType::FROST, 
		MagicDamageType::SHOCK, MagicDamageType::WIND, MagicDamageType::POISON, MagicDamageType::BLEED, 
		MagicDamageType::SLEEP, MagicDamageType::DARK, MagicDamageType::HOLY})
	{
		magicResistance[type] = 0.0f;
	}
}

Armor::~Armor() {
}

void Armor::setPhysicalResistance(PhysicalDamageType physType, float physResistance)
{
	physicalResistance[physType] = physResistance;
}

void Armor::setMagicResistance(MagicDamageType magType, float magResistance)
{
	magicResistance[magType] = magResistance;
}

float Armor::getPhysicalResistance(PhysicalDamageType physType)
{
	auto it = physicalResistance.find(physType);
	return (it != physicalResistance.end()) ? it->second : 0.0f;
}

float Armor::Armor::getMagicResistance(MagicDamageType magType)
{
	auto it = magicResistance.find(magType);
	return (it != magicResistance.end()) ? it->second : 0.0f;
}