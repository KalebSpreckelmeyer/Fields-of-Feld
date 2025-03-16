#include "Creature.h"
#include <iostream>
Creature::Creature()
{
}
Creature::Creature(float damage, float defense, float reach)
    : Character(false, true, true, false,
		"CREATURE NAME", "CREATURE DESCRIPTION", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, inventory, 0.0f, 0.0f, CombatFlags::NEUTRAL),
    damage(damage), defense(defense), reach(reach) {
}

Creature::~Creature()
{
}

void Creature::takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition,
	ThrownConsumable* consumable, Spell* spell)
{
	std::cout << "Creature taking damage" << std::endl;
	return;

}