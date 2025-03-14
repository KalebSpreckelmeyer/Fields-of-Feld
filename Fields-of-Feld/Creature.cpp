#include "Creature.h"

Creature::Creature(std::string name, float health, float damage)
    : Character(
        false, 0.0f, true, false, true, Character::CharacterClass::DEFAULT, name, "Creature",
        health, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, health, health, 50.0f, 50.0f,
        1.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 100.0f, 0.0f,
        Inventory(), 0.0f, false
    ),
    flatDamage(damage)  
{
	lootExample();
}

void Creature::lootExample() {
	Item item;
	item.name = "Sword";
	item.description = "A simple sword";
	item.value = 10;
	item.weight = 5;
	item.quantity = 1;
	loot.push_back(item);
}