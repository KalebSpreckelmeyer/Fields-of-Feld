#include "MagicEffect.h"

MagicEffect::MagicEffect() {

}

MagicEffect::MagicEffect(std::string name, std::string description, int damage, int healing,
	int turnsActive, int turnsRemaining, int magnitude, stats_effected statEffected){
	this->name = name;
	this->description = description;
	this->damage = damage;
	this->healing = healing;
	this->turnsActive = turnsActive;
	this->turnsRemaining = turnsRemaining;
	this->magnitude = magnitude;
	this->statEffected = statEffected;
}

MagicEffect::~MagicEffect() {

}