#ifndef EFFECT_H
#define EFFECT_H
#include <string>

#include "Character.h"
 
class Effect
{
public:
	std::string name = "EFFECT NAME";
	std::string description = "EFFECT DESC";
	float duration = 0.0f;
	float magnitude = 0.0f;
	bool stackable = 0.0f;
	int stacks = 0;
	int maxStacks = 0;

	/*bool applied = false;*/

	virtual ~Effect();
	Effect() = default;
	Effect(std::string name, std::string description, float duration, float magnitude, bool stackable, 
		int stacks, int maxStacks);

	void refreshEffects(Character& target);

	void removeEffect(Character& target, Effect& effectToDelete);

	void applyEffect(Character& attacker, Character& target, Effect& effect);
};

#endif // !EFFECT_H


