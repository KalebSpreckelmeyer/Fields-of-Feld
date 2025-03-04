#include "Item.h"

//Private Functions
void Item::generate()
{
}

//Constructors / Destructors
Item::Item(
	std::string name,
	unsigned type,
	unsigned rarity,
	unsigned value,
	unsigned reach)
{
	this->name = name;
	this->type = type;
	this->rarity = rarity;
	this->value = value;
	this->reach = reach;
}	

Item::~Item()
{

}


//Accessors
const std::string& Item::getName()
{
	return this->name;
}

const unsigned& Item::getType()
{
	return this->type;
}

const unsigned& Item::getRarity()
{
	return this->rarity;
}

const unsigned& Item::getValue()
{
	return this->value;
}

//Functions

const std::string Item::toString() const
{
	std::stringstream ss;

	ss << "Name: " << this->name << " "
		<< "| Type: " << this->type << " "
		<< "| Rarity: " << this->rarity << " "
		<< "| Value: " << this->value << " ";
	return ss.str();
}