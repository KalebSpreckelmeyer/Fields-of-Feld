#pragma once
#include "Item.h"
#include "PhysicalDamageType.h"
#include "MagicDamageType.h"
#include "Enchantment.h"
#include <vector>
#include <unordered_map>

class Weapon :
    public Item
{
public:

	std::unordered_map<PhysicalDamageType, float>physicalDamages;
	std::unordered_map<MagicDamageType, float> magicDamages;

	std::unordered_map<PhysicalDamageType, float> physicalResistance;
	std::unordered_map<MagicDamageType, float> magicResistance;

	bool specialDamage = false;
	float reach = 0.0f;
	float attackSpeed = 0.0f;
	bool twoHanded = 0.0f;
	bool needsAmmo = 0.0f;
	float stability = 0.0f;
	enum class WeaponType {
		DAGGER, STRAIGHTSWORD, GREATSWORD, FIST, MACE, GREATMACE,
		HATCHET, AXE, GREATAXE, THRUSTINGSWORD, SPEAR, GREATSPEAR, HALBERD, POLEHAMMER,
		PARRYSHIELD, MEDIUMSHIELD, GREATSHIELD,
		LONGBOW, COMPOUNDBOW, GREATBOW, MINICROSSBOW, CROSSBOW, BALLISTA,
		TALISMAN, CHIME, TOME, WAND, STAFF, ORB
	};
	WeaponType weaponType = WeaponType::DAGGER;

	float getWeaponDamage(Character* target, Weapon weapon);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getWeaponDefense(Character* target);

	void setPhysicalDefense(PhysicalDamageType physType, float physDefense);

	void setMagicDefense(MagicDamageType magType, float magDefense);

	float getPhysicalDefense(PhysicalDamageType physType);

	float getMagicDefense(MagicDamageType magType);

	//ENCHANTMENTS
	std::vector<Enchantment*> enchantments;
	
	Weapon();

	Weapon(bool specialDamage, std::string name, std::string description, float stability, float reach, float attackSpeed, float weight, float value,
		bool twohanded, bool needsAmmo, WeaponType weaponType, PhysicalDamageType physAttack, MagicDamageType magAttack,
		PhysicalDamageType physDefense, MagicDamageType magDefense, EquipSlots slot);

	~Weapon();
};

