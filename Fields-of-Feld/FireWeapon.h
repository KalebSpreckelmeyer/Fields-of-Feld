#pragma once
#include "Enchantment.h"
class FireWeapon :
    public Enchantment
{
public:
	FireWeapon(std::string name, std::string description, int stacks, int maxStacks, int duration, float damagePerTurn, float burstDamage);
};

