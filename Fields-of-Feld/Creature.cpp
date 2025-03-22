#include "Creature.h"
#include "Spell.h"
#include "Effect.h"
#include "Enchantment.h"
#include <iostream>

Creature::Creature(bool namedCharacter, bool isAlly, bool isAlive, bool active, bool alert,
	std::string name, std::string description, float damage, float reach, float confidenceLevel,
	float healthPoints, float maxHealthPoints, float speed, float critChance, float dodgeChance,
	float blockChance, float bleedPoints, float maxBleedPoints,
	float burnPoints, float maxBurnPoints, float poisonPoints,
	float maxPoisonPoints, float frostPoints, float maxFrostPoints,
	float shockPoints, float maxShockPoints, float sleepPoints,
	float maxSleepPoints, const Inventory& inventory, float distanceFromPlayer, CombatFlags combatFlag)
    : Character(isAlly, namedCharacter, isAlive, active, alert,
		name, description, confidenceLevel,
		healthPoints, maxHealthPoints, fatiguePoints,
		maxFatiguePoints, speed, critChance, dodgeChance,
		 blockChance, bleedPoints, maxBleedPoints,
		burnPoints, maxBurnPoints, poisonPoints,
		 maxPoisonPoints, frostPoints, maxFrostPoints,
		 shockPoints, maxShockPoints, sleepPoints,
		 maxSleepPoints, inventory, distanceFromPlayer,
		level, combatFlag), damage(damage), reach(reach) {
}

nlohmann::json Creature::toJson() const {
    nlohmann::json j;

    j["type"] = "Creature";
    j["id"] = id;
    j["isAlly"] = isAlly;
    j["namedCharacter"] = namedCharacter;
    j["isAlive"] = isAlive;
    j["active"] = active;
    j["alert"] = alert;

    j["name"] = name;
    j["description"] = description;

    // Creature-specific
    j["damage"] = damage;
    j["reach"] = reach;

    // Core stats
    j["confidenceLevel"] = confidenceLevel;
    j["healthPoints"] = healthPoints;
    j["maxHealthPoints"] = maxHealthPoints;
    j["fatiguePoints"] = fatiguePoints;
    j["maxFatiguePoints"] = maxFatiguePoints;
    j["speed"] = speed;
    j["critChance"] = critChance;
    j["dodgeChance"] = dodgeChance;
    j["blockChance"] = blockChance;

    // Status buildup
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

    // Position
    j["distanceFromPlayer"] = distanceFromPlayer;

    // Combat flags
    for (const auto& flag : combatFlags)
        j["combatFlags"].push_back(static_cast<int>(flag));

    // Effects
    for (const auto& eff : effects)
        j["effects"].push_back(eff->toJson());

    // Tags
    for (const auto& tag : tags)
        j["tags"].push_back(*tag);

    // Inventory & defenses
    j["inventory"] = inventory.toJson();
    j["defenseValues"] = defenseValues;

    return j;
}


std::shared_ptr<Character> Creature::fromJson(const nlohmann::json& j) {
    auto c = std::make_shared<Creature>();

    // Basic flags & identity
    c->id = j.at("id");
    c->isAlly = j.at("isAlly");
    c->namedCharacter = j.at("namedCharacter");
    c->isAlive = j.at("isAlive");
    c->active = j.at("active");
    c->alert = j.at("alert");

    c->name = j.at("name");
    c->description = j.at("description");

    // Creature-specific values
    c->damage = j.at("damage");
    c->reach = j.at("reach");

    // Core stats
    c->confidenceLevel = j.at("confidenceLevel");
    c->healthPoints = j.at("healthPoints");
    c->maxHealthPoints = j.at("maxHealthPoints");
    c->fatiguePoints = j.at("fatiguePoints");
    c->maxFatiguePoints = j.at("maxFatiguePoints");
    c->speed = j.at("speed");
    c->critChance = j.at("critChance");
    c->dodgeChance = j.at("dodgeChance");
    c->blockChance = j.at("blockChance");

    // Status buildup values
    c->bleedPoints = j.at("bleedPoints");
    c->maxBleedPoints = j.at("maxBleedPoints");
    c->burnPoints = j.at("burnPoints");
    c->maxBurnPoints = j.at("maxBurnPoints");
    c->poisonPoints = j.at("poisonPoints");
    c->maxPoisonPoints = j.at("maxPoisonPoints");
    c->frostPoints = j.at("frostPoints");
    c->maxFrostPoints = j.at("maxFrostPoints");
    c->shockPoints = j.at("shockPoints");
    c->maxShockPoints = j.at("maxShockPoints");
    c->sleepPoints = j.at("sleepPoints");
    c->maxSleepPoints = j.at("maxSleepPoints");

    // Positioning
    c->distanceFromPlayer = j.at("distanceFromPlayer");

    // Combat behavior
    for (const auto& flag : j["combatFlags"])
        c->combatFlags.push_back(static_cast<CombatFlags>(flag.get<int>()));

    // Inventory
    c->inventory.fromJson(j["inventory"]);

    // Effects
    for (const auto& eff : j["effects"])
        c->effects.push_back(Effect::fromJson(eff));

    // Tags
    for (const auto& tag : j["tags"])
        c->tags.push_back(std::make_shared<std::string>(tag.get<std::string>()));

    // Resistances / defenses
    c->defenseValues = j.at("defenseValues");

    return c;
}

void Creature::takeDamage(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon, std::shared_ptr<Ammunition> ammunition,
	std::shared_ptr<ThrownConsumable> consumable, Spell* spell, std::optional<std::vector<std::shared_ptr<Character>>>& allies,
	std::optional<std::vector<std::shared_ptr<Character>>>& enemyAllies)
{
	std::cout << "Creature taking damage" << std::endl;
	return;

}