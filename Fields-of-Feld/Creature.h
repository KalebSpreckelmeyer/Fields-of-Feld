#ifndef CREATURE_H
#define CREATURE_H

#include "Character.h"

class Creature : public Character
{
public:
	float flatDamage; 
	std::string name = "Creature";
	float damage = 0.0f;
	float damageResistance = 0.0f;

	std::vector<Item> loot;

	Creature(std::string name, float damage, float damageResistnace);

	void lootExample();
};
#endif // !CREATURE_H



