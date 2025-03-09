#include "Spell.h"
Spell::Spell() {

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

