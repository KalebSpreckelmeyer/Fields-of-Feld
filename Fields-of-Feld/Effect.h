#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include "vector"
#include "optional"
#include "MagicDamageType.h"
#include "PhysicalDamageType.h"
#include "unordered_map"

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

	Effect();
	virtual ~Effect() = default;
	Effect(bool doesDamage, bool applied, std::string name, std::string description, PhysicalDamageType physType,
		MagicDamageType magType, float range, float duration, float magnitude, bool stackable,
		int stacks, int maxStacks, bool areaOfEffect);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getEffectDamage(Character* target, Effect ammo);

	void refreshEffects(Character* target);

	void deleteEffect(Character& target, Effect& effectToDelete);

	void removeEffect(Character& target, Effect& effectToRemove);


	void applyEffect(Effect* effect, Character* attacker, Character* target);
};

#endif // !EFFECT_H


