#ifndef POISONENCHANTMENT_H
#define POISONENCHANTMENT_H

#include "Enchantment.h"
class PoisonEnchantment :
    public Enchantment
{
public:
    int damagePerTurn;
	PoisonEnchantment(std::string name, std::string description, int stacks, int maxStacks, int duration, int damagePerTurn);
};

#endif // !POISONENCHANTMENT_H