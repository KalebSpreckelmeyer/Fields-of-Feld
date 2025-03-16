#include "FireWeapon.h"
#include <string>

FireWeapon::FireWeapon(std::string name, std::string description, int stacks, int maxStacks, int duration, float damagePerTurn, float burstDamage) :
	Enchantment(name, description, stacks, maxStacks, duration)
{
}

