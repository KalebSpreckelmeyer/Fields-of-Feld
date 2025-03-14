#include "Spell.h"
Spell::Spell()
{
	effect = MagicEffect();
	name = "NONE";
	description = "NONE";
	damage = 0;
	healing = 0;
	range = 0;
	attackSpeed = 0;
	manaCost = 0;
	staminaCost = 0;
	magicType = SORCERY;
	spellEffect = NONE;
}

Spell::Spell(MagicEffect effect, std::string name, std::string description, int damage, int healing,
	int range, int attackSpeed, int manaCost, int staminaCost,
	magic_types magicType, spell_effects spellEffect)
{
	effect = effect;

	this->name = name;
	this->description = description;
	this->damage = damage;
	this->healing = healing;
	this->range = range;
	this->attackSpeed = attackSpeed;
	this->manaCost = manaCost;
	this->staminaCost = staminaCost;
	this->magicType = magicType;
	this->spellEffect = spellEffect;
}

Spell::~Spell(){

}

