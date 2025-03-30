#ifndef CREATURE_H
#define CREATURE_H

#include "Character.h"
#include "IDManager.h"

class Creature : public Character
{
public:
	int id;
	float damage = 0.0f;
	float reach = 0.0f;

	Creature() = default;

	Creature(bool namedCharacter, bool isAlly, bool isAlive, bool active, bool alert,
		std::string name, std::string description, float damage, float reach, float confidenceLevel,
		float healthPoints, float maxHealthPoints, float speed, float critChance, float dodgeChance,
		float blockChance, float bleedPoints, float maxBleedPoints,
		float burnPoints, float maxBurnPoints, float poisonPoints,
		float maxPoisonPoints, float frostPoints, float maxFrostPoints,
		float shockPoints, float maxShockPoints, float sleepPoints,
		float maxSleepPoints, const Inventory& inventory, CombatFlags combatFlag);

	~Creature() override = default;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Character> fromJson(const nlohmann::json& j);

	void printCreatureStats();
};
#endif // !CREATURE_H



