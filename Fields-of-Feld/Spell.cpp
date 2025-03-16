#include "Spell.h"

Spell::Spell()
{
}

Spell::Spell(std::string name, std::string description, float duration, float magnitude, bool stackable,
	int stacks, int maxStacks)
	: Effect(name, description, duration, magnitude, stackable, stacks, maxStacks)
{
}

Spell::~Spell()
{
}