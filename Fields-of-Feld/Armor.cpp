#include "Armor.h"
#include <vector>
#include <string>
#include "Item.h"
#include "HelperFunctions.h"
#include <iostream>
#include "nlohmann/json.hpp"
Armor::Armor() {
}
Armor::Armor(std::string name, std::string description, float weight, float value, bool isHead, bool isChest, bool isArms, bool isLegs, bool isLight,
	bool isMedium, bool isHeavy, ArmorDescriptor armorDescriptor, Item::EquipSlots slot) :
	Item(name, description, value, weight, 1.0f, slot),
	isHead(isHead), isChest(isChest), isArms(isArms), isLegs(isLegs), isLight(isLight), isMedium(isMedium), isHeavy(isHeavy), armorDescriptor(armorDescriptor), id(IDManager::getNextId())
{
	//sets physical resistances to the map to default values
	for (Defense type : {Defense::BLUNT, Defense::PIERCE,
		Defense::SLASH, Defense::CHOP})
	{
		defenses[type] = 0.0f;
	}
	//sets magic resistances to the map to default values
	for (Defense type : { Defense::MAGIC, Defense::FIRE, Defense::FROST,
		Defense::SHOCK, Defense::WIND, Defense::POISON, Defense::BLEED,
		Defense::SLEEP, Defense::DARK, Defense::HOLY})
	{
		defenses[type] = 0.0f;
	}
}

Armor::~Armor() {
	id = IDManager::getNextId();
}

nlohmann::json Armor::toJson() const
{
	nlohmann::json j;
	j["id"] = id;
	j["type"] = "Armor";
	j["name"] = name;
	j["description"] = description;
	j["value"] = value;
	j["weight"] = weight;
	j["quantity"] = quantity;
	j["slot"] = equipSlotToString(slot);
	j["isHead"] = isHead;
	j["isChest"] = isChest;
	j["isArms"] = isArms;
	j["isLegs"] = isLegs;
	j["isLight"] = isLight;
	j["isMedium"] = isMedium;
	j["isHeavy"] = isHeavy;
	j["armorDescriptor"] = armorDescriptorToString(armorDescriptor);

	//Serialize unordered_maps
	nlohmann::json defense;
	for (const auto& [type, val] : defenses) defense[defenseToString(type)] = val;

	j["defenses"] = defense;
	//Serialize Enchantments
	j["enchantments"] = nlohmann::json::array();
	for (const auto& ench : enchantments) {
		j["enchantments"].push_back(ench->toJson());
	};
	return j;
}

std::shared_ptr<Item> Armor::fromJson(const nlohmann::json& j)
{
	auto armor = std::make_shared<Armor>();

	try {
		if (j.contains("id"))              armor->id = j["id"];
		if (j.contains("name"))            armor->name = j["name"];
		if (j.contains("description"))     armor->description = j["description"];
		if (j.contains("value"))           armor->value = j["value"];
		if (j.contains("weight"))          armor->weight = j["weight"];
		if (j.contains("quantity"))        armor->quantity = j["quantity"];
		if (j.contains("slot"))            armor->slot = stringToEquipSlot(j["slot"]);
		if (j.contains("isHead"))          armor->isHead = j["isHead"];
		if (j.contains("isChest"))         armor->isChest = j["isChest"];
		if (j.contains("isArms"))          armor->isArms = j["isArms"];
		if (j.contains("isLegs"))          armor->isLegs = j["isLegs"];
		if (j.contains("isLight"))         armor->isLight = j["isLight"];
		if (j.contains("isMedium"))        armor->isMedium = j["isMedium"];
		if (j.contains("isHeavy"))         armor->isHeavy = j["isHeavy"];
		if (j.contains("armorDescriptor")) armor->armorDescriptor = stringToArmorDescriptor(j["armorDescriptor"]);

		// Load defenses
		if (j.contains("defenses") && j["defenses"].is_object()) {
			for (const auto& [key, value] : j["defenses"].items()) {
				armor->defenses[stringToDefense(key)] = value;
			}
		}

		// Load enchantments
		if (j.contains("enchantments") && j["enchantments"].is_array()) {
			for (const auto& ench : j["enchantments"]) {
				armor->enchantments.push_back(Enchantment::fromJson(ench));
			}
		}

	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "[ERROR] Failed to load Armor from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return armor;
}


void Armor::setDefenses(Defense physType, float physResistance)
{
	defenses[physType] = physResistance;
}

//void Armor::setMagicResistance(Defense magType, float magResistance)
//{
//	defenses[magType] = magResistance;
//}

float Armor::getDefenses(Defense physType)
{
	auto it = defenses.find(physType);
	return (it != defenses.end()) ? it->second : 0.0f;
}

float Armor::getArmorDefenseBase(std::shared_ptr<Armor> armor)
{
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

	return (cumulativeSlashResist + cumulativePierceResist + cumulativeBluntResist + cumulativeChopResist + cumulativeMagicResist + cumulativeFireResist
		+ cumulativeIceResist + cumulativeShockResist + cumulativeWindResist + cumulativePoisonResist + cumulativeBleedResist + cumulativeBleedResist +
		cumulativeSleepResist + cumulativeDarkResist + cumulativeHolyResist) / 10;
}
float Armor::getArmorDefenses(std::shared_ptr<Character> target, std::shared_ptr<Armor> armor)
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

		return cumulativeSlashResist + cumulativePierceResist + cumulativeBluntResist + cumulativeChopResist + cumulativeMagicResist + cumulativeFireResist 
			+ cumulativeIceResist + cumulativeShockResist + cumulativeWindResist + cumulativePoisonResist+ cumulativeBleedResist + cumulativeBleedResist +
			cumulativeSleepResist + cumulativeDarkResist+ cumulativeHolyResist;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}
//float Armor::Armor::getMagicResistance(Defense magType)
//{
//	auto it = defenses.find(magType);
//	return (it != defenses.end()) ? it->second : 0.0f;
//}