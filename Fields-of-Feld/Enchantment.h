#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include <vector>
#include "Effect.h"

class Enchantment :
	public Effect
{
public:
	std::vector<Effect*> effects;
	//Virtual Destructor
	virtual ~Enchantment();

	Enchantment(std::string name, std::string description, float duration, float magnitude, bool stackable,
		int stacks, int maxStacks, bool applied);

	void applyEnchantment();
	void removeEnchantment();

	void interactWith(Enchantment& otherEnchantment);
};

#endif // !ENCHANTMENT_H


