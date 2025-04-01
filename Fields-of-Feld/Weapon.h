#pragma once
#include "Item.h"
#include "PhysicalDamageType.h"
#include "DamageTypes.h"
#include "Enchantment.h"
#include <vector>
#include <unordered_map>
#include "StatScaling.h"	
#include "Defense.h"
#include "WeaponArt.h"

class Weapon :
    public Item
{
public:
	int id;
	//Physical and Magical Damage of the Weapon
	std::unordered_map<DamageTypes, float> damageTypes;

	//Physical and Magical Defense of the Weapon
	std::unordered_map<Defense, float> defenseTypes;

	//Weapon Scaling Stats
	std::unordered_map<StatScaling, float> scalingStats;
	//StatScaling scalingStat = StatScaling::NONE;

	//Weapon Requirements
	std::unordered_map<StatScaling, float> statRequirements;
	//StatScaling statRequirement = StatScaling::NONE;

	//Weapon Arts
	std::vector<std::shared_ptr<WeaponArt>> weaponArts;

	bool specialDamage = false;
	float reach = 0.0f;
	float attackSpeed = 0.0f;
	bool twoHanded = 0.0f;
	bool needsAmmo = 0.0f;
	float stability = 0.0f;
	float magicAdjust = 0.0f;
	float distanceTraveled = 0.0f;
	enum class WeaponType {
		DAGGER, STRAIGHTSWORD, GREATSWORD, FIST, MACE, GREATMACE,
		HATCHET, AXE, GREATAXE, THRUSTINGSWORD, SPEAR, GREATSPEAR, HALBERD, POLEHAMMER,
		PARRYSHIELD, MEDIUMSHIELD, GREATSHIELD,
		LONGBOW, COMPOUNDBOW, GREATBOW, MINICROSSBOW, CROSSBOW, BALLISTA,
		WAND, STAFF, INSTRUMENT
	};
	WeaponType weaponType = WeaponType::DAGGER;


	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	float getWeaponDamageBase(std::shared_ptr<Weapon> weapon);

	float getWeaponDamage(std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon);

	void setDamage(DamageTypes damType, float damValue);

	float getDamage(DamageTypes damValue);

	float getDefense(Defense defenseType);

	void setDefense(Defense defenseType, float defenseValue);

	float getWeaponScalingValue(StatScaling scalingStat);

	float getWeaponRequirementValue(StatScaling statRequirement);

	void setWeaponScalingValue(StatScaling scalingStat, float scalingValue);

	void setWeaponRequirementValue(StatScaling statRequirement, float requirementValue);

	float getWeaponRange();

	//ENCHANTMENTS
	std::vector<std::shared_ptr<Enchantment>> enchantments;
	
	Weapon();

	Weapon(bool specialDamage, std::string name, std::string description, float stability, float reach, float attackSpeed, float weight, float value,
		bool twohanded, bool needsAmmo, float magicAdjust, float distanceTraveled, WeaponType weaponType, EquipSlots slot);

	~Weapon() = default;
};

