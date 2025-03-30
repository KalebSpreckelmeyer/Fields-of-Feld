#include "Ammunition.h"
#include <iostream>
#include "PhysicalDamageType.h"
#include "DamageTypes.h"
#include "Human.h"
#include "HelperFunctions.h"

Ammunition::Ammunition(bool specialDamage, std::string name, std::string description, float value, float weight,
	float quantity, EquipSlots slot, float range, AmmoType ammoType)
	: Item(name, description, value, weight, quantity, slot), specialDamage(specialDamage), 
	range(range), ammoType(ammoType), id(IDManager::getNextId())
{
}

nlohmann::json Ammunition::toJson() const
{
	json j;
	j["id"] = id;
	j["type"] = "Ammunition";
	j["name"] = name;
	j["description"] = description;
	j["value"] = value;
	j["weight"] = weight;
	j["quantity"] = quantity;
	j["slot"] = equipSlotToString(slot);
	j["specialDamage"] = specialDamage;
	j["range"] = range;
	j["ammoType"] = ammoTypeToString(ammoType);

	// Convert physicalDamage
	json dmgJson;
	for (const auto& [type, val] : damageTypes) {
		dmgJson[damageTypesToString(type)] = val;
	}
	j["damageTypes"] = dmgJson;

	// Enchantments
	j["enchantments"] = json::array();
	for (const auto& ench : enchantments) {
		j["enchantments"].push_back(ench->toJson());
	}

	return j;

}

std::shared_ptr<Ammunition> Ammunition::fromJson(const nlohmann::json& j)
{
	auto ammo = std::make_shared<Ammunition>();

	try {
		// Basic fields
		if (j.contains("id"))            ammo->id = j["id"];
		if (j.contains("name"))          ammo->name = j["name"];
		if (j.contains("description"))   ammo->description = j["description"];
		if (j.contains("value"))         ammo->value = j["value"];
		if (j.contains("weight"))        ammo->weight = j["weight"];
		if (j.contains("quantity"))      ammo->quantity = j["quantity"];
		if (j.contains("slot"))          ammo->slot = stringToEquipSlot(j["slot"]);
		if (j.contains("specialDamage")) ammo->specialDamage = j["specialDamage"];
		if (j.contains("range"))         ammo->range = j["range"];
		if (j.contains("ammoType"))      ammo->ammoType = stringToAmmoType(j["ammoType"]);

		// Physical Damage Map
		if (j.contains("damageTypes") && j["damageTypes"].is_object()) {
			for (const auto& [key, value] : j["damageTypes"].items()) {
				ammo->damageTypes[stringToDamageTypes(key)] = value;
			}
		}

		// Enchantments
		if (j.contains("enchantments") && j["enchantments"].is_array()) {
			for (const auto& enchantJson : j["enchantments"]) {
				ammo->enchantments.push_back(Enchantment::fromJson(enchantJson));
			}
		}
	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "[ERROR] Failed to load Ammunition from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return ammo;
}

void Ammunition::setDamage(DamageTypes damageType, float damageValue)
{
	damageTypes[damageType] = damageValue;
}

float Ammunition::getDamage(DamageTypes damageType)
{
	return damageTypes[damageType];
}


float Ammunition::getAmmoDamage(std::shared_ptr<Character> target, std::shared_ptr<Ammunition> ammo)
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
			auto armor = std::dynamic_pointer_cast<Armor>(item);
			if (!armor) continue;
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
		float cumulativeSlashDamage = ammo->getDamage(DamageTypes::SLASH) - (ammo->getDamage(DamageTypes::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = ammo->getDamage(DamageTypes::PIERCE) - (ammo->getDamage(DamageTypes::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = ammo->getDamage(DamageTypes::BLUNT) - (ammo->getDamage(DamageTypes::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = ammo->getDamage(DamageTypes::CHOP) - (ammo->getDamage(DamageTypes::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = ammo->getDamage(DamageTypes::MAGIC) - (ammo->getDamage(DamageTypes::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = ammo->getDamage(DamageTypes::FIRE) - (ammo->getDamage(DamageTypes::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = ammo->getDamage(DamageTypes::FROST) - (ammo->getDamage(DamageTypes::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = ammo->getDamage(DamageTypes::SHOCK) - (ammo->getDamage(DamageTypes::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = ammo->getDamage(DamageTypes::POISON) - (ammo->getDamage(DamageTypes::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = ammo->getDamage(DamageTypes::BLEED) - (ammo->getDamage(DamageTypes::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = ammo->getDamage(DamageTypes::SLEEP) - (ammo->getDamage(DamageTypes::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = ammo->getDamage(DamageTypes::DARK) - (ammo->getDamage(DamageTypes::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = ammo->getDamage(DamageTypes::HOLY) - (ammo->getDamage(DamageTypes::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = ammo->getDamage(DamageTypes::WIND) - (ammo->getDamage(DamageTypes::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float ammoDamage = cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage;

		return ammoDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}