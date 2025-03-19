#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include <vector>
#include "Effect.h"

class Enchantment :
	public Effect
{
public:

	std::unordered_map<PhysicalDamageType, float> physicalDamage;
	std::unordered_map<MagicDamageType, float> magicDamage;

	std::vector<Effect*> effects;
	//Virtual Destructor
	virtual ~Enchantment();

	Enchantment(std::string name, std::string description, PhysicalDamageType physDmg, MagicDamageType magDmg, float duration, float magnitude, bool stackable,
		int stacks, int maxStacks, bool applied, bool doesDamage);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getEnchantmentDamage(Character* target, Enchantment Enchantment);

	void applyEnchantment();
	void removeEnchantment();

	void interactWith(Enchantment& otherEnchantment);
};

#endif // !ENCHANTMENT_H


