#ifndef CREATURE_H
#define CREATURE_H

#include "Character.h"

class Creature : public Character
{
public:
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
		float maxSleepPoints, const Inventory& inventory, float distanceFromPlayer, CombatFlags combatFlag);

	~Creature() override = default;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Character> fromJson(const nlohmann::json& j);

	void takeDamage(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon, std::shared_ptr<Ammunition> ammunition,
		std::shared_ptr<ThrownConsumable> consumable, Spell* spell, std::optional<std::vector<std::shared_ptr<Character>>>& allies,
		std::optional<std::vector<std::shared_ptr<Character>>>& enemyAllies) override;
};
#endif // !CREATURE_H



