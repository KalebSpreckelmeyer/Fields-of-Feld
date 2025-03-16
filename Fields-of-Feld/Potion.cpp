#include "Potion.h"
#include <string>
#include <stdexcept>

Potion::Potion() : Consumable() {

}
Potion::Potion(std::string name, std::string description, int magnitude, int value, int weight, int quantity, effect effects)
{
	this->name = name;
	this->description = description;
	this->magnitude = magnitude;
	this->value = value;
	this->weight = weight;
	this->quantity = quantity;
	this->effects = effects;
}

Potion::~Potion()
{

}

Potion Potion::createPotion(std::string name, std::string description, int magnitude, int value, int weight, int quantity, effect effects)
{
	Potion potion;
	potion.name = name;
	potion.description = description;
	potion.magnitude = magnitude;
	potion.value = value;
	potion.weight = weight;
	potion.quantity = quantity;
	potion.effects = effects;

	return potion;
} 

