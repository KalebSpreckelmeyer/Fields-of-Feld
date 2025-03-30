#include "Weapon.h"
#include <string>
#include "Human.h"
#include <algorithm>
#include <iostream>
#include "IDManager.h"
#include "HelperFunctions.h"

Weapon::Weapon(bool specialDamage, std::string name, std::string description, float stability, float reach, 
	float attackSpeed, float weight, float value, bool twohanded, bool needsAmmo, 
	WeaponType weaponType, EquipSlots slot) : Item(name, description, value, weight, 1.0f, slot), id(IDManager::getNextId()),
		specialDamage(specialDamage), reach(reach), 
		attackSpeed(attackSpeed), twoHanded(twohanded), needsAmmo(needsAmmo),
	weaponType(weaponType), stability(stability)
{
}

Weapon::Weapon() : Item() {
	id = IDManager::getNextId();
}
nlohmann::json Weapon::toJson() const {
	nlohmann::json j;

	j["type"] = "Weapon";
	j["id"] = id;
	j["name"] = name;
	j["description"] = description;
	j["value"] = value;
	j["weight"] = weight;
	j["quantity"] = quantity;
	j["slot"] = equipSlotToString(slot);
	j["specialDamage"] = specialDamage;
	j["stability"] = stability;
	j["reach"] = reach;
	j["attackSpeed"] = attackSpeed;
	j["twoHanded"] = twoHanded;
	j["needsAmmo"] = needsAmmo;
	j["weaponType"] = weaponTypeToString(weaponType);

	// Damage and resistances
	nlohmann::json dmg, def, scale, reqs;
	for (const auto& [type, val] : damageTypes) dmg[damageTypesToString(type)] = val;
	for (const auto& [type, val] : defenseTypes) def[defenseToString(type)] = val;
	for (const auto& [type, val] : scalingStats) scale[statScalingToString(type)] = val;
	for (const auto& [type, val] : statRequirements) reqs[statScalingToString(type)] = val;

	j["damageTypes"] = dmg;
	j["defenseTypes"] = def;
	j["scalingStats"] = scale;
	j["statRequirements"] = reqs;

	// Enchantments
	j["enchantments"] = nlohmann::json::array();
	for (const auto& ench : enchantments) {
		j["enchantments"].push_back(ench->toJson());
	}

	return j;
}



std::shared_ptr<Item> Weapon::fromJson(const nlohmann::json& j) {
	std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>();

	if (j.contains("id")) weapon->id = j["id"];
	if (j.contains("name")) weapon->name = j["name"];
	if (j.contains("description")) weapon->description = j["description"];
	if (j.contains("value")) weapon->value = j["value"];
	if (j.contains("weight")) weapon->weight = j["weight"];
	if (j.contains("quantity")) weapon->quantity = j["quantity"];
	if (j.contains("slot")) weapon->slot = stringToEquipSlot(j["slot"]);

	if (j.contains("specialDamage")) weapon->specialDamage = j["specialDamage"];
	if (j.contains("stability")) weapon->stability = j["stability"];
	if (j.contains("reach")) weapon->reach = j["reach"];
	if (j.contains("attackSpeed")) weapon->attackSpeed = j["attackSpeed"];
	if (j.contains("twoHanded")) weapon->twoHanded = j["twoHanded"];
	if (j.contains("needsAmmo")) weapon->needsAmmo = j["needsAmmo"];
	if (j.contains("weaponType")) weapon->weaponType = stringToWeaponType(j["weaponType"]);

	if (j.contains("damageTypes") && j["damageTypes"].is_object()) {
		for (auto& [key, value] : j["damageTypes"].items()) {
			weapon->damageTypes[stringToDamageTypes(key)] = value;
		}
	}
	if (j.contains("defenseTypes") && j["defenseTypes"].is_object()) {
		for (auto& [key, value] : j["defenseTypes"].items()) {
			weapon->defenseTypes[stringToDefense(key)] = value;
		}
	}
	if (j.contains("scalingStats") && j["scalingStats"].is_object()) {
		for (auto& [key, value] : j["scalingStats"].items()) {
			weapon->scalingStats[stringToStatScaling(key)] = value;
		}
	}
	if (j.contains("statRequirements") && j["statRequirements"].is_object()) {
		for (auto& [key, value] : j["statRequirements"].items()) {
			weapon->statRequirements[stringToStatScaling(key)] = value;
		}
	}

	if (j.contains("enchantments") && j["enchantments"].is_array()) {
		for (const auto& enchantJson : j["enchantments"]) {
			weapon->enchantments.push_back(Enchantment::fromJson(enchantJson));
		}
	}

	return weapon;
}

float Weapon::getWeaponDamageBase(std::shared_ptr<Weapon> weapon)
{
	//damage = damage - (damage * (resistance / 500)) - max won't let it go below 0
	float cumulativeSlashDamage = weapon->getDamage(DamageTypes::SLASH);
	cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
	float cumulativePierceDamage = weapon->getDamage(DamageTypes::PIERCE);
	cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
	float cumulativeBluntDamage = weapon->getDamage(DamageTypes::BLUNT);
	cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
	float cumulativeChopDamage = weapon->getDamage(DamageTypes::CHOP);
	cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

	float cumulativeMagicDamage = weapon->getDamage(DamageTypes::MAGIC);
	cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
	float cumulativeFireDamage = weapon->getDamage(DamageTypes::FIRE);
	cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
	float cumulativeIceDamage = weapon->getDamage(DamageTypes::FROST);
	cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
	float cumulativeShockDamage = weapon->getDamage(DamageTypes::SHOCK);
	cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
	float cumulativePoisonDamage = weapon->getDamage(DamageTypes::POISON);
	cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
	float cumulativeBleedDamage = weapon->getDamage(DamageTypes::BLEED);
	cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
	float cumulativeSleepDamage = weapon->getDamage(DamageTypes::SLEEP);
	cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
	float cumulativeDarkDamage = weapon->getDamage(DamageTypes::DARK);
	cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
	float cumulativeHolyDamage = weapon->getDamage(DamageTypes::HOLY);
	cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
	float cumulativeWindDamage = weapon->getDamage(DamageTypes::WIND);
	cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

	//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
	float weaponDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
		cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
		cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
	weaponDamage = std::max(weaponDamage, 0.0f);

	return weaponDamage;
}

float Weapon::getWeaponDamage(std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon)
{
	//Target is human
	if (std::dynamic_pointer_cast<Human>(target))
	{
		std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(target);
		//GET ARMOR RESISTANCES
		float cumulativeSlashResist = 0;
		float cumulativePierceResist = 0;
		float cumulativeBluntResist = 0;
		float cumulativeChopResist = 0;

		float cumulativeMagicResist = 0;
		float cumulativeFireResist = 0;
		float cumulativeIceResist = 0;
		float cumulativeShockResist = 0;
		float cumulativePoisonResist = 0;
		float cumulativeBleedResist = 0;
		float cumulativeSleepResist = 0;
		float cumulativeDarkResist = 0;
		float cumulativeHolyResist = 0;
		float cumulativeWindResist = 0;

		for (std::shared_ptr<Item> item : target->inventory.equippedItems)
		{
			if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item))
			{
				cumulativeSlashResist += armor->getDefenses(Defense::SLASH);
				cumulativePierceResist += armor->getDefenses(Defense::PIERCE);
				cumulativeBluntResist += armor->getDefenses(Defense::BLUNT);
				cumulativeChopResist += armor->getDefenses(Defense::CHOP);
				cumulativeMagicResist += armor->getDefenses(Defense::MAGIC);
				cumulativeFireResist += armor->getDefenses(Defense::FIRE);
				cumulativeIceResist += armor->getDefenses(Defense::FROST);
				cumulativeShockResist += armor->getDefenses(Defense::SHOCK);
				cumulativeWindResist += armor->getDefenses(Defense::WIND);
				cumulativePoisonResist += armor->getDefenses(Defense::POISON);
				cumulativeBleedResist += armor->getDefenses(Defense::BLEED);
				cumulativeSleepResist += armor->getDefenses(Defense::SLEEP);
				cumulativeDarkResist += armor->getDefenses(Defense::DARK);
				cumulativeHolyResist += armor->getDefenses(Defense::HOLY);
			}
		}

		cumulativeSlashResist = std::max(cumulativeSlashResist, 0.0f);
		cumulativePierceResist = std::max(cumulativePierceResist, 0.0f);
		cumulativeBluntResist = std::max(cumulativeBluntResist, 0.0f);
		cumulativeChopResist = std::max(cumulativeChopResist, 0.0f);

		cumulativeMagicResist = std::max(cumulativeMagicResist, 0.0f);
		cumulativeFireResist = std::max(cumulativeFireResist, 0.0f);
		cumulativeIceResist = std::max(cumulativeIceResist, 0.0f);
		cumulativeShockResist = std::max(cumulativeShockResist, 0.0f);
		cumulativePoisonResist = std::max(cumulativePoisonResist, 0.0f);
		cumulativeBleedResist = std::max(cumulativeBleedResist, 0.0f);
		cumulativeSleepResist = std::max(cumulativeSleepResist, 0.0f);
		cumulativeDarkResist = std::max(cumulativeDarkResist, 0.0f);
		cumulativeHolyResist = std::max(cumulativeHolyResist, 0.0f);
		cumulativeWindResist = std::max(cumulativeWindResist, 0.0f);

		//damage = damage - (damage * (resistance / 500)) - max won't let it go below 0
		float cumulativeSlashDamage = weapon->getDamage(DamageTypes::SLASH) - (weapon->getDamage(DamageTypes::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = weapon->getDamage(DamageTypes::PIERCE) - (weapon->getDamage(DamageTypes::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = weapon->getDamage(DamageTypes::BLUNT) - (weapon->getDamage(DamageTypes::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = weapon->getDamage(DamageTypes::CHOP) - (weapon->getDamage(DamageTypes::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = weapon->getDamage(DamageTypes::MAGIC) - (weapon->getDamage(DamageTypes::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = weapon->getDamage(DamageTypes::FIRE) - (weapon->getDamage(DamageTypes::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = weapon->getDamage(DamageTypes::FROST) - (weapon->getDamage(DamageTypes::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = weapon->getDamage(DamageTypes::SHOCK) - (weapon->getDamage(DamageTypes::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = weapon->getDamage(DamageTypes::POISON) - (weapon->getDamage(DamageTypes::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = weapon->getDamage(DamageTypes::BLEED) - (weapon->getDamage(DamageTypes::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = weapon->getDamage(DamageTypes::SLEEP) - (weapon->getDamage(DamageTypes::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = weapon->getDamage(DamageTypes::DARK) - (weapon->getDamage(DamageTypes::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = weapon->getDamage(DamageTypes::HOLY) - (weapon->getDamage(DamageTypes::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = weapon->getDamage(DamageTypes::WIND) - (weapon->getDamage(DamageTypes::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float weaponDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
		weaponDamage = std::max(weaponDamage, 0.0f);

		return weaponDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}

//Not sure why this exists but I'm too scared to delete it

//float Weapon::getDefense(std::shared_ptr<Character> target)
//{
//	//Target is human
//	if (std::dynamic_pointer_cast<Human>(target))
//	{
//		std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(target);
//		//GET ARMOR RESISTANCES
//		float cumulativeSlashResist = 0;
//		float cumulativePierceResist = 0;
//		float cumulativeBluntResist = 0;
//		float cumulativeChopResist = 0;
//
//		float cumulativeMagicResist = 0;
//		float cumulativeFireResist = 0;
//		float cumulativeIceResist = 0;
//		float cumulativeShockResist = 0;
//		float cumulativePoisonResist = 0;
//		float cumulativeBleedResist = 0;
//		float cumulativeSleepResist = 0;
//		float cumulativeDarkResist = 0;
//		float cumulativeHolyResist = 0;
//		float cumulativeWindResist = 0;
//
//		for (std::shared_ptr<Item> item : target->inventory.equippedItems)
//		{
//			if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item))
//			{
//				cumulativeSlashResist += armor->getDefenses(Defense::SLASH);
//				cumulativePierceResist += armor->getDefenses(Defense::PIERCE);
//				cumulativeBluntResist += armor->getDefenses(Defense::BLUNT);
//				cumulativeChopResist += armor->getDefenses(Defense::CHOP);
//				cumulativeMagicResist += armor->getDefenses(Defense::MAGIC);
//				cumulativeFireResist += armor->getDefenses(Defense::FIRE);
//				cumulativeIceResist += armor->getDefenses(Defense::FROST);
//				cumulativeShockResist += armor->getDefenses(Defense::SHOCK);
//				cumulativeWindResist += armor->getDefenses(Defense::WIND);
//				cumulativePoisonResist += armor->getDefenses(Defense::POISON);
//				cumulativeBleedResist += armor->getDefenses(Defense::BLEED);
//				cumulativeSleepResist += armor->getDefenses(Defense::SLEEP);
//				cumulativeDarkResist += armor->getDefenses(Defense::DARK);
//				cumulativeHolyResist += armor->getDefenses(Defense::HOLY);
//			}
//		}
//		return 0;
//	}
//	//Target is creature
//	else
//	{
//		//TODO
//		return 0;
//	}
//}
void Weapon::setDamage(DamageTypes damType, float damValue)
{
	damageTypes[damType] = damValue;
}

float Weapon::getDamage(DamageTypes damType)
{
	auto it = damageTypes.find(damType);
	return (it != damageTypes.end()) ? it->second : 0.0f;
}

void Weapon::setDefense(Defense defenseType, float defenseValue)
{
	defenseTypes[defenseType] = defenseValue;
}

float Weapon::getDefense(Defense defenseType)
{
	auto it = defenseTypes.find(defenseType);
	return (it != defenseTypes.end()) ? it->second : 0.0f;
}

float Weapon::getWeaponScalingValue(StatScaling scalingStat)
{
	auto it = scalingStats.find(scalingStat);
	return (it != scalingStats.end()) ? it->second : 0.0f;
}

float Weapon::getWeaponRequirementValue(StatScaling statRequirement)
{
	auto it = statRequirements.find(statRequirement);
	return (it != statRequirements.end()) ? it->second : 0.0f;
}

void Weapon::setWeaponScalingValue(StatScaling scalingStat, float scalingValue)
{
	scalingStats[scalingStat] = scalingValue;
}

void Weapon::setWeaponRequirementValue(StatScaling statRequirement, float requirementValue)
{
	statRequirements[statRequirement] = requirementValue;
}