#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include "vector"
#include "optional"
#include "MagicDamageType.h"
#include "PhysicalDamageType.h"
#include "unordered_map"
#include "nlohmann/json.hpp"
#include "memory"

using json = nlohmann::json;

class Character;

class Effect
{
public:

	std::unordered_map<PhysicalDamageType, float> physicalDamage;
	std::unordered_map<MagicDamageType, float> magicDamage;

	std::string name = "EFFECT NAME";
	std::string description = "EFFECT DESC";
	float duration = 0.0f;
	float magnitude = 0.0f;
	bool stackable = false;
	int stacks = 0;
	int maxStacks = 0;
	float range = 0.0f;

	bool doesDamage = false;
	bool applied = false;
	bool areaOfEffect = false;

	Effect() = default;
	virtual ~Effect() = default;
	Effect(bool doesDamage, bool applied, std::string name, std::string description, float range, float duration, float magnitude, bool stackable,
		int stacks, int maxStacks, bool areaOfEffect);

	virtual nlohmann::json toJson() const = 0;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	virtual void apply(Character& target) = 0;
	virtual void tick(Character& target) = 0;
	virtual bool isExpired() const = 0;

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getEffectDamage(std::shared_ptr<Character> target, std::shared_ptr<Effect> effect);

	void refreshEffects(std::shared_ptr<Character> target);

	void deleteEffect(std::shared_ptr<Character> target, Effect& effectToDelete);

	void removeEffect(std::shared_ptr<Character> target, Effect& effectToRemove);

	//Called when attacking an enemy, applies target's defensive effects to attacker
	void applyDefensiveEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> wielder, std::shared_ptr<Character> attacker);

	//Called when attacking an enemy, applies attacker's offensive effects to target
	void applyOffensiveEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> attacker, std::shared_ptr<Character> target);

	//Called before attacking an enemy, applies enemy's passive effects to enemy
	void applyPassiveEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> wielder);
	
	//Called when using a 
	// 
	// 
	// , applies consumable's effects to target
	void applyConsumableEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> target);


};

#endif // !EFFECT_H


