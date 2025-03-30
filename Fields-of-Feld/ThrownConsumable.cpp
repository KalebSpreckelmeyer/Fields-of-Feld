#include "ThrownConsumable.h"
#include "Item.h"
#include "Human.h"
#include "HelperFunctions.h"

ThrownConsumable::ThrownConsumable(bool specialDamage, std::string name, std::string description, float reach, float attackSpeed, float weight, float quantity, float value)
	: Item(name, description, value, weight, quantity, slot), id(IDManager::getNextId()),
	specialDamage(specialDamage), reach(reach), attackSpeed(attackSpeed)
{
}

ThrownConsumable::ThrownConsumable()
{
	id = IDManager::getNextId();
}
nlohmann::json ThrownConsumable::toJson() const {
	nlohmann::json jsonObj = {
		{"id", id},
		{"type", "ThrownConsumable"},
		{"name", name},
		{"description", description},
		{"value", value},
		{"weight", weight},
		{"quantity", quantity},
		{"specialDamage", specialDamage},
		{"reach", reach},
		{"attackSpeed", attackSpeed},
		{"damage", damageTypesToString(damage)},
		{"scalingStat", statScalingToString(scalingStat)},
		{"statRequirement", statScalingToString(statRequirement)},
		{"enchantments", nlohmann::json::array()}
	};

	nlohmann::json dmg, scalingJson, reqJson;
	for (const auto& [k, v] : damageTypes) dmg[damageTypesToString(k)] = v;
	for (const auto& [k, v] : scalingStats) scalingJson[statScalingToString(k)] = v;
	for (const auto& [k, v] : statRequirements) reqJson[statScalingToString(k)] = v;

	jsonObj["damageTypes"] = dmg;
	jsonObj["scalingStats"] = scalingJson;
	jsonObj["statRequirements"] = reqJson;

	for (const auto& enchant : enchantments)
		jsonObj["enchantments"].push_back(enchant->toJson());

	return jsonObj;
}

std::shared_ptr<Item> ThrownConsumable::fromJson(const nlohmann::json& j) {
	auto thrownConsumable = std::make_shared<ThrownConsumable>();

	if (j.contains("id")) thrownConsumable->id = j["id"];
	if (j.contains("name")) thrownConsumable->name = j["name"];
	if (j.contains("description")) thrownConsumable->description = j["description"];
	if (j.contains("value")) thrownConsumable->value = j["value"];
	if (j.contains("weight")) thrownConsumable->weight = j["weight"];
	if (j.contains("quantity")) thrownConsumable->quantity = j["quantity"];
	if (j.contains("specialDamage")) thrownConsumable->specialDamage = j["specialDamage"];
	if (j.contains("reach")) thrownConsumable->reach = j["reach"];
	if (j.contains("attackSpeed")) thrownConsumable->attackSpeed = j["attackSpeed"];

	if (j.contains("damage") && j["damage"].is_string())
		thrownConsumable->damage = stringToDamageTypes(j["damage"]);

	if (j.contains("scalingStat") && j["scalingStat"].is_string())
		thrownConsumable->scalingStat = stringToStatScaling(j["scalingStat"]);

	if (j.contains("statRequirement") && j["statRequirement"].is_string())
		thrownConsumable->statRequirement = stringToStatScaling(j["statRequirement"]);

	if (j.contains("damageTypes")) {
		for (const auto& [key, val] : j["damageTypes"].items()) {
			thrownConsumable->damageTypes[stringToDamageTypes(key)] = val;
		}
	}
	if (j.contains("scalingStats")) {
		for (const auto& [key, val] : j["scalingStats"].items()) {
			thrownConsumable->scalingStats[stringToStatScaling(key)] = val;
		}
	}
	if (j.contains("statRequirements")) {
		for (const auto& [key, val] : j["statRequirements"].items()) {
			thrownConsumable->statRequirements[stringToStatScaling(key)] = val;
		}
	}

	if (j.contains("enchantments") && j["enchantments"].is_array()) {
		for (const auto& ench : j["enchantments"]) {
			thrownConsumable->enchantments.push_back(Enchantment::fromJson(ench));
		}
	}

	return thrownConsumable;
}


float ThrownConsumable::getThrownConsumableDamage(std::shared_ptr<Character> target, ThrownConsumable consumable)
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
		float cumulativeSlashDamage = consumable.getDamage(DamageTypes::SLASH) - (consumable.getDamage(DamageTypes::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = consumable.getDamage(DamageTypes::PIERCE) - (consumable.getDamage(DamageTypes::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = consumable.getDamage(DamageTypes::BLUNT) - (consumable.getDamage(DamageTypes::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = consumable.getDamage(DamageTypes::CHOP) - (consumable.getDamage(DamageTypes::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = consumable.getDamage(DamageTypes::MAGIC) - (consumable.getDamage(DamageTypes::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = consumable.getDamage(DamageTypes::FIRE) - (consumable.getDamage(DamageTypes::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = consumable.getDamage(DamageTypes::FROST) - (consumable.getDamage(DamageTypes::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = consumable.getDamage(DamageTypes::SHOCK) - (consumable.getDamage(DamageTypes::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = consumable.getDamage(DamageTypes::POISON) - (consumable.getDamage(DamageTypes::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = consumable.getDamage(DamageTypes::BLEED) - (consumable.getDamage(DamageTypes::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = consumable.getDamage(DamageTypes::SLEEP) - (consumable.getDamage(DamageTypes::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = consumable.getDamage(DamageTypes::DARK) - (consumable.getDamage(DamageTypes::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = consumable.getDamage(DamageTypes::HOLY) - (consumable.getDamage(DamageTypes::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = consumable.getDamage(DamageTypes::WIND) - (consumable.getDamage(DamageTypes::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float consumableDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
		consumableDamage = std::max(consumableDamage, 0.0f);

		return consumableDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}

void ThrownConsumable::setDamage(DamageTypes damageType, float damageValue)
{
	damageTypes[damageType] = damageValue;
}

float ThrownConsumable::getDamage(DamageTypes damageType)
{
	auto it = damageTypes.find(damageType);
	return (it != damageTypes.end()) ? it->second : 0.0f;
}

float ThrownConsumable::getThrownConsumableScalingValue(StatScaling)
{
	auto it = scalingStats.find(scalingStat);
	return (it != scalingStats.end()) ? it->second : 0.0f;
}

float ThrownConsumable::getThrownConsumableRequirementValue(StatScaling)
{
	auto it = statRequirements.find(statRequirement);
	return (it != statRequirements.end()) ? it->second : 0.0f;
}

void ThrownConsumable::setThrownConsumableScalingValue(StatScaling, float scalingValue)
{
	scalingStats[scalingStat] = scalingValue;
}

void ThrownConsumable::setThrownConsumableRequirementValue(StatScaling, float requirementValue)
{
	statRequirements[statRequirement] = requirementValue;
}