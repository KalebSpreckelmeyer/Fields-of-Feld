#pragma once
#include "Item.h"
#include "PhysicalDamageType.h"
#include "MagicDamageType.h"
#include "Enchantment.h"
#include <vector>
#include <unordered_map>
#include "StatScaling.h"	

class Weapon :
    public Item
{
public:

	//Physical and Magical Damage of the Weapon
	std::unordered_map<PhysicalDamageType, float>physicalDamages;
	std::unordered_map<MagicDamageType, float> magicDamages;

	PhysicalDamageType physDmgType = PhysicalDamageType::BLUNT;
	MagicDamageType magDmgType = MagicDamageType::NONE;

	//Physical and Magical Defense of the Weapon
	std::unordered_map<PhysicalDamageType, float> physicalResistance;
	std::unordered_map<MagicDamageType, float> magicResistance;

	PhysicalDamageType physDefType = PhysicalDamageType::BLUNT;
	MagicDamageType magDefType = MagicDamageType::NONE;

	//Weapon Scaling Stats
	std::unordered_map<StatScaling, float> scalingStats;
	StatScaling scalingStat = StatScaling::NONE;

	//Weapon Requirements
	std::unordered_map<StatScaling, float> statRequirements;
	StatScaling statRequirement = StatScaling::NONE;

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


	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);


	float getWeaponDamage(std::shared_ptr<Character> target, Weapon weapon);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getWeaponDefense(std::shared_ptr<Character> target);

	void setPhysicalDefense(PhysicalDamageType physType, float physDefense);

	void setMagicDefense(MagicDamageType magType, float magDefense);

	float getPhysicalDefense(PhysicalDamageType physType);

	float getMagicDefense(MagicDamageType magType);

	float getWeaponScalingValue(StatScaling);

	float getWeaponRequirementValue(StatScaling);

	void setWeaponScalingValue(StatScaling, float scalingValue);

	void setWeaponRequirementValue(StatScaling, float requirementValue);
	//ENCHANTMENTS
	std::vector<std::shared_ptr<Enchantment>> enchantments;
	
	Weapon() = default;

	Weapon(bool specialDamage, std::string name, std::string description, float stability, float reach, float attackSpeed, float weight, float value,
		bool twohanded, bool needsAmmo, WeaponType weaponType, EquipSlots slot);

	~Weapon() = default;
};

