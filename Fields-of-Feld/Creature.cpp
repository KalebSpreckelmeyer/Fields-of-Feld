#include "Creature.h"
#include "Spell.h"
#include "Effect.h"
#include "Enchantment.h"
#include <iostream>
#include "HelperFunctions.h"
#include "color.hpp"

Creature::Creature(bool namedCharacter, bool isAlly, bool isAlive, bool active, bool alert,
	std::string name, std::string description, float damage, float reach, float confidenceLevel,
	float healthPoints, float maxHealthPoints, float speed, float critChance, float dodgeChance,
	float blockChance, float bleedPoints, float maxBleedPoints,
	float burnPoints, float maxBurnPoints, float poisonPoints,
	float maxPoisonPoints, float frostPoints, float maxFrostPoints,
	float shockPoints, float maxShockPoints, float sleepPoints,
	float maxSleepPoints, const Inventory& inventory, CombatFlags combatFlag)
	: Character(isAlly, namedCharacter, isAlive, active, alert,
		name, description, confidenceLevel,
		healthPoints, maxHealthPoints, fatiguePoints,
		maxFatiguePoints, speed, critChance, dodgeChance,
		blockChance, bleedPoints, maxBleedPoints,
		burnPoints, maxBurnPoints, poisonPoints,
		maxPoisonPoints, frostPoints, maxFrostPoints,
		shockPoints, maxShockPoints, sleepPoints,
		maxSleepPoints, inventory,
		level, combatFlag), damage(damage), reach(reach), id(IDManager::getNextId()) {
}

nlohmann::json Creature::toJson() const {
	nlohmann::json j;

	//General Character Fields
	j["isAlly"] = isAlly;
	j["namedCharacter"] = namedCharacter;
	j["isAlive"] = isAlive;
	j["active"] = active;
	j["alert"] = alert;
	j["name"] = name;
	j["description"] = description;
	j["confidenceLevel"] = confidenceLevel;
	j["healthPoints"] = healthPoints;
	j["maxHealthPoints"] = maxHealthPoints;
	j["fatiguePoints"] = fatiguePoints;
	j["maxFatiguePoints"] = maxFatiguePoints;
	j["speed"] = speed;
	j["critChance"] = critChance;
	j["dodgeChance"] = dodgeChance;
	j["blockChance"] = blockChance;
	j["bleedPoints"] = bleedPoints;
	j["maxBleedPoints"] = maxBleedPoints;
	j["burnPoints"] = burnPoints;
	j["maxBurnPoints"] = maxBurnPoints;
	j["poisonPoints"] = poisonPoints;
	j["maxPoisonPoints"] = maxPoisonPoints;
	j["frostPoints"] = frostPoints;
	j["maxFrostPoints"] = maxFrostPoints;
	j["shockPoints"] = shockPoints;
	j["maxShockPoints"] = maxShockPoints;
	j["sleepPoints"] = sleepPoints;
	j["maxSleepPoints"] = maxSleepPoints;

	j["type"] = "Creature";
	j["id"] = id;

	// Creature-specific
	j["damage"] = damage;
	j["reach"] = reach;

	//Combat flags
	j["combatFlags"] = nlohmann::json::array();
	for (const auto& flag : combatFlags)
		j["combatFlags"].push_back(combatFlagToString(flag));

	//position
	j["position"] = positionToJson(position);

	// Effects
	for (const auto& eff : effects)
		j["effects"].push_back(eff->toJson());

	// Tags
	for (const auto& tag : tags)
		j["tags"].push_back(*tag);

	// Inventory & defenses
	j["inventory"] = inventory.toJson();
	// Resistances / defenses
	nlohmann::json defenseJson;
	for (const auto& [key, value] : defenseValues) {
		defenseJson[defenseToString(key)] = value;
	}
	j["defenseValues"] = defenseJson;

	return j;
}



std::shared_ptr<Character> Creature::fromJson(const nlohmann::json& j) {
	auto creature = std::make_shared<Creature>();

	try {
		// Base character info
		if (j.contains("id")) creature->id = j["id"];
		if (j.contains("isAlly")) creature->isAlly = j["isAlly"];
		if (j.contains("namedCharacter")) creature->namedCharacter = j["namedCharacter"];
		if (j.contains("isAlive")) creature->isAlive = j["isAlive"];
		if (j.contains("active")) creature->active = j["active"];
		if (j.contains("alert")) creature->alert = j["alert"];
		if (j.contains("name")) creature->name = j["name"];
		if (j.contains("description")) creature->description = j["description"];
		if (j.contains("confidenceLevel")) creature->confidenceLevel = j["confidenceLevel"];

		if (j.contains("healthPoints")) creature->healthPoints = j["healthPoints"];
		if (j.contains("maxHealthPoints")) creature->maxHealthPoints = j["maxHealthPoints"];
		if (j.contains("fatiguePoints")) creature->fatiguePoints = j["fatiguePoints"];
		if (j.contains("maxFatiguePoints")) creature->maxFatiguePoints = j["maxFatiguePoints"];
		if (j.contains("speed")) creature->speed = j["speed"];
		if (j.contains("critChance")) creature->critChance = j["critChance"];
		if (j.contains("dodgeChance")) creature->dodgeChance = j["dodgeChance"];
		if (j.contains("blockChance")) creature->blockChance = j["blockChance"];

		// Status points
		if (j.contains("bleedPoints")) creature->bleedPoints = j["bleedPoints"];
		if (j.contains("maxBleedPoints")) creature->maxBleedPoints = j["maxBleedPoints"];
		if (j.contains("burnPoints")) creature->burnPoints = j["burnPoints"];
		if (j.contains("maxBurnPoints")) creature->maxBurnPoints = j["maxBurnPoints"];
		if (j.contains("poisonPoints")) creature->poisonPoints = j["poisonPoints"];
		if (j.contains("maxPoisonPoints")) creature->maxPoisonPoints = j["maxPoisonPoints"];
		if (j.contains("frostPoints")) creature->frostPoints = j["frostPoints"];
		if (j.contains("maxFrostPoints")) creature->maxFrostPoints = j["maxFrostPoints"];
		if (j.contains("shockPoints")) creature->shockPoints = j["shockPoints"];
		if (j.contains("maxShockPoints")) creature->maxShockPoints = j["maxShockPoints"];
		if (j.contains("sleepPoints")) creature->sleepPoints = j["sleepPoints"];
		if (j.contains("maxSleepPoints")) creature->maxSleepPoints = j["maxSleepPoints"];

		// Creature-specific
		if (j.contains("damage")) creature->damage = j["damage"];
		if (j.contains("reach")) creature->reach = j["reach"];

		// Combat flags
		if (j.contains("combatFlags") && j["combatFlags"].is_array()) {
			for (const auto& f : j["combatFlags"])
				creature->combatFlags.push_back(stringToCombatFlag(f.get<std::string>()));
		}

		// Position map
		if (j.contains("position") && j["position"].is_object()) {
			creature->position = positionFromJson(j["position"]);
		}

		// Effects
		if (j.contains("effects") && j["effects"].is_array()) {
			for (const auto& eff : j["effects"]) {
				creature->effects.push_back(Effect::fromJson(eff));
			}
		}

		// Tags
		if (j.contains("tags") && j["tags"].is_array()) {
			for (const auto& tag : j["tags"]) {
				creature->tags.push_back(std::make_shared<std::string>(tag.get<std::string>()));
			}
		}

		// Inventory
		if (j.contains("inventory")) {
			creature->inventory.fromJson(j["inventory"]);
		}

		// Defense values
		if (j.contains("defenseValues") && j["defenseValues"].is_object()) {
			for (const auto& [key, value] : j["defenseValues"].items()) {
				creature->defenseValues[stringToDefense(key)] = value.get<float>();
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to load Creature from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return creature;
}

void Creature::printCreatureStats()
{
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Name: ") << name << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Health Points: ") << healthPoints << " / " << maxHealthPoints << std::endl;
	std::cout << dye::light_yellow(" Fatigue Points: ") << fatiguePoints << " / " << maxFatiguePoints << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Bleed Points: ") << bleedPoints << " / " << maxBleedPoints << std::endl;
	std::cout << dye::light_yellow(" Burn Points: ") << burnPoints << " / " << maxBurnPoints << std::endl;
	std::cout << dye::light_yellow(" Poison Points: ") << poisonPoints << " / " << maxPoisonPoints << std::endl;
	std::cout << dye::light_yellow(" Frost Points: ") << frostPoints << " / " << maxFrostPoints << std::endl;
	std::cout << dye::light_yellow(" Shock Points: ") << shockPoints << " / " << maxShockPoints << std::endl;
	std::cout << dye::light_yellow(" Sleep Points: ") << sleepPoints << " / " << maxSleepPoints << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << "Damage: " << damage << std::endl;
	std::cout << "Reach: " << reach << std::endl;
}