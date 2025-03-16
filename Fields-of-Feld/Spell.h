#ifndef SPELL_H
#define SPELL_H
#include <string>
#include <vector>
#include "Effect.h"

class Spell : public Effect {
public:

	std::vector<Effect> effects;

	Spell();
	Spell(std::string name, std::string description, float duration, float magnitude, bool stackable,
		int stacks, int maxStacks);
	~Spell();
};
#endif // !SPELL_H
