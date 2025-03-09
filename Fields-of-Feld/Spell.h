#ifndef Spell_h
#define Spell_h

#include <string>
#include "MagicEffect.h"

class Spell
{
public:

	MagicEffect effect;
	std::string name;
	std::string description;
	int damage;
	int healing;
	int range;
	int attackSpeed;
	int manaCost;
	int staminaCost;
	enum magic_types { SORCERY, MIRACLE, NATURE };
	enum spell_effects { NONE, DAMAGEOVERTIME, HEALINGOVERTIME, STATDEBUFF };
	magic_types magicType;
	spell_effects spellEffect;

	Spell();

	Spell(MagicEffect effect, std::string name, std::string description, int damage, int healing, 
		int range, int attackSpeed, int manaCost, int staminaCost, 
		magic_types magicType, spell_effects spellEffect);

	~Spell();
};
#endif // !Spell_h

