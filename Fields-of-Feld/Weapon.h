#pragma once
#include "Item.h"
#include "Enchantment.h"
#include <vector>

class Weapon :
    public Item
{
public:
	bool specialDamage = false;
	float damage = 0.0f;
	float defense = 0.0f;
	float reach = 0.0f;
	float attackSpeed = 0.0f;
	bool twoHanded = 0.0f;
	bool needsAmmo = 0.0f;
	enum class WeaponType {
		DAGGER, STRAIGHTSWORD, GREATSWORD, FIST, MACE, GREATMACE,
		HATCHET, AXE, GREATAXE, THRUSTINGSWORD, SPEAR, GREATSPEAR, HALBERD, POLEHAMMER,
		PARRYSHIELD, MEDIUMSHIELD, GREATSHIELD,
		LONGBOW, COMPOUNDBOW, GREATBOW, MINICROSSBOW, CROSSBOW, BALLISTA,
		TALISMAN, CHIME, TOME, WAND, STAFF, ORB
	};
	WeaponType weaponType = WeaponType::DAGGER;
	enum class PhysicalDamageType {
		SLASH, BLUNT, PIERCE
	};
	PhysicalDamageType physicalDamageType = PhysicalDamageType::BLUNT;

	//ENCHANTMENTS
	std::vector<Enchantment*> enchantments;
	
	Weapon();

	Weapon(bool specialDamage, std::string name, std::string description, float damage, float defense, float reach, float attackSpeed, float weight, float value,
		bool twohanded, bool needsAmmo, WeaponType weaponType, PhysicalDamageType physicalDamageType);

	~Weapon();
};

