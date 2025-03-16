#ifndef EFFECT_H
#define EFFECT_H
#include <string>

class Character;

class Effect
{
public:
	std::string name = "EFFECT NAME";
	std::string description = "EFFECT DESC";
	float duration = 0.0f;
	float magnitude = 0.0f;
	bool stackable = false;
	int stacks = 0;
	int maxStacks = 0;

	/*bool applied = false;*/
	Effect();
	virtual ~Effect() = default;
	Effect(std::string name, std::string description, float duration, float magnitude, bool stackable, 
		int stacks, int maxStacks);

	void refreshEffects(Character& target);

	void removeEffect(Character& target, Effect& effectToDelete);

	void applyEffect(Character& attacker, Character& target, Effect& effect);
};

#endif // !EFFECT_H


