#ifndef CREATURE_H
#define CREATURE_H

#include "Character.h"

class Creature : public Character
{
public:
	float damage = 0.0f;
	float defense = 0.0f;
	float reach = 0.0f;

	Creature();

	Creature(float damage, float defense, float reach);

	~Creature();

	void takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition,
		ThrownConsumable* consumable, Spell* spell) override;
};
#endif // !CREATURE_H



