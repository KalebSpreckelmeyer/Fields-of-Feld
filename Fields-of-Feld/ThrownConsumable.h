#ifndef THROWNCONSUMABLE_H
#define THROWNCONSUMABLE_H
#include <string>
#include "Item.h"
#include "Enchantment.h"
#include <vector>
#include <unordered_map>

class Enchantment;

class ThrownConsumable :
    public Item
{
public:
	std::unordered_map<PhysicalDamageType, float>physicalDamages;
	std::unordered_map<MagicDamageType, float> magicDamages;

	bool specialDamage = false;
	float reach = 0.0f;
	float attackSpeed = 0.0f;
	float minRange = 0.0f;
	float maxRange = 0.0f;

	std::vector<Enchantment*> enchantments;

	float getThrownConsumableDamage(Character* target, ThrownConsumable consumable);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	ThrownConsumable();

	ThrownConsumable(bool specialDamage, std::string name, std::string description, PhysicalDamageType physType, MagicDamageType magType,
		float reach, float attackSpeed, float weight, float quantity, float value);

	~ThrownConsumable();
};
#endif // !THROWNCONSUMABLE_H



