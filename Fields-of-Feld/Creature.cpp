#include "Creature.h"
#include <iostream>
Creature::Creature()
{
}
Creature::Creature(bool namedCharacter, bool isAlly, bool isAlive, bool active, bool alert,
	std::string name, std::string description, float damage, float reach, float confidenceLevel,
	float healthPoints, float maxHealthPoints, float speed, float critChance, float dodgeChance,
	float blockChance, float damageThreshold, float damageResistance, float bleedPoints, float maxBleedPoints,
	float burnPoints, float maxBurnPoints, float poisonPoints,
	float maxPoisonPoints, float frostPoints, float maxFrostPoints,
	float shockPoints, float maxShockPoints, float sleepPoints,
	float maxSleepPoints, const Inventory& inventory, float distanceFromPlayer, CombatFlags combatFlag)
    : Character(isAlly, namedCharacter, isAlive, active, alert,
		name, description, confidenceLevel,
		healthPoints, maxHealthPoints, fatiguePoints,
		maxFatiguePoints, speed, critChance, dodgeChance,
		 blockChance, damageThreshold, damageResistance, bleedPoints, maxBleedPoints,
		burnPoints, maxBurnPoints, poisonPoints,
		 maxPoisonPoints, frostPoints, maxFrostPoints,
		 shockPoints, maxShockPoints, sleepPoints,
		 maxSleepPoints, inventory, distanceFromPlayer,
		level, combatFlag), damage(damage), reach(reach) {
	std::cout << "Creature Constructor: " << typeid(*this).name() << " at " << this << std::endl;
}

void Creature::takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition,
	ThrownConsumable* consumable, Spell* spell, std::optional<std::vector<Character*>>& allies,
	std::optional<std::vector<Character*>>& enemyAllies)
{
	std::cout << "Creature taking damage" << std::endl;
	return;

}