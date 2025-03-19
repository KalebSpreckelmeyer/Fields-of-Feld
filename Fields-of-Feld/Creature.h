#ifndef CREATURE_H
#define CREATURE_H

#include "Character.h"

class Creature : public Character
{
public:
	float damage = 0.0f;
	float reach = 0.0f;

	Creature();

	Creature(bool namedCharacter, bool isAlly, bool isAlive, bool active, bool alert,
		std::string name, std::string description, float damage, float reach, float confidenceLevel,
		float healthPoints, float maxHealthPoints, float speed, float critChance, float dodgeChance,
		float blockChance, float damageThreshold, float damageResistance, float bleedPoints, float maxBleedPoints,
		float burnPoints, float maxBurnPoints, float poisonPoints,
		float maxPoisonPoints, float frostPoints, float maxFrostPoints,
		float shockPoints, float maxShockPoints, float sleepPoints,
		float maxSleepPoints, const Inventory& inventory, float distanceFromPlayer, CombatFlags combatFlag);

	~Creature() override = default;

	void takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition,
		ThrownConsumable* consumable, Spell* spell, std::optional<std::vector<Character*>>& allies,
		std::optional<std::vector<Character*>>& enemyAllies) override;
};
#endif // !CREATURE_H



