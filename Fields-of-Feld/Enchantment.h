#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include <vector>
#include "Effect.h"

class Enchantment :
	public Effect
{
public:

	std::vector<Effect*> effects;
	//Virtual Destructor

	Enchantment();

	virtual ~Enchantment();

	Enchantment(bool doesDamage, bool applied, std::string name, std::string description, float duration, bool stackable,
		int stacks, int maxStacks, bool areaOfEffect, PhysicalDamageType physType,
		MagicDamageType magType);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getEnchantmentDamage(Character* target, Enchantment Enchantment);

	void applyEnchantment(Character* wielder, Character* target);

	void removeEnchantment(Character& wielder, Enchantment* enchant);

	void interactWith(Enchantment& otherEnchantment);

	//WEAPON ENCHANTMENTS
	Enchantment* getMagicWeaponEffect(Character& wielder);
	//ARMOR ENCHANTMENTS
	Enchantment* getMagicArmorEffect(Character& wielder);
	Enchantment* getLightningArmorEffect(Character& wielder);
	Enchantment* getBloodArmorEffect(Character& wielder);
	Enchantment* getFrostArmorEffect(Character& wielder);
	Enchantment* getFireArmorEffect(Character& wielder);
	Enchantment* getPoisonArmorEffect(Character& wielder);
	Enchantment* getWindArmorEffect(Character& wielder);
	Enchantment* getEarthenArmorEffect(Character& wielder);
	Enchantment* getSleepArmorEffect(Character& wielder);
	Enchantment* getHolyArmorEffect(Character& wielder);
	Enchantment* getDarkArmorEffect(Character& wielder);
	//TRINKET ENCHANTMENTS
};

#endif // !ENCHANTMENT_H


