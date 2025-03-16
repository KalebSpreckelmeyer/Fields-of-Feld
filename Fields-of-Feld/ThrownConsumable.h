#ifndef THROWNCONSUMABLE_H
#define THROWNCONSUMABLE_H
#include <string>
#include "Item.h"

class ThrownConsumable :
    public Item
{
public:
	bool specialDamage = false;
	float damage = 0.0f;
	float reach = 0.0f;
	float attackSpeed = 0.0f;
	float minRange = 0.0f;
	float maxRange = 0.0f;

	std::vector<Enchantment*> enchantments;

	ThrownConsumable();

	ThrownConsumable(bool specialDamage, std::string name, std::string description, float damage, float reach, float attackSpeed, float weight, float quantity, float value);

	~ThrownConsumable();
};
#endif // !THROWNCONSUMABLE_H



