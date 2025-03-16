#include "PoisonEnchantment.h"
#include <string>

PoisonEnchantment::PoisonEnchantment(std::string name, std::string description, int stacks, int maxStacks, int duration, int damagePerTurn) :
	Enchantment(name, description, stacks, maxStacks, duration), damagePerTurn(damagePerTurn)
{
}