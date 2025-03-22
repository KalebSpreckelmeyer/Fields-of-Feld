#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"
#include "Consumable.h"
#include "Ammunition.h"
#include "Book.h"
#include "Food.h"
#include "Potion.h"
#include "ThrownConsumable.h"

#include <string>
#include <iostream>

int Item::nextId = 1;

Item::Item(bool hasBeenInitialized, std::string name, std::string description , float value, float weight, float quantity, Item::EquipSlots slot) : id(nextId++),
	hasBeenInitialized(hasBeenInitialized), name(name), description(description)
	,value(value), weight(weight), quantity(quantity), slot(slot) {
}


std::shared_ptr<Item> Item::fromJson(const nlohmann::json& j)
{
	std::string type = j.at("type");
	if (type == "Consumable")
	{
		return Consumable::fromJson(j);
	}
	else if (type == "Weapon")
	{
		return Weapon::fromJson(j);
	}
	else if (type == "Armor")
	{
		return Armor::fromJson(j);
	}
	else if (type == "Trinket")
	{
		return Trinket::fromJson(j);
	}
	else if (type == "Ammunition")
	{
		return Ammunition::fromJson(j);
	}
	else if (type == "Book")
	{
		return Book::fromJson(j);
	}
	else if (type == "Food")
	{
		return Food::fromJson(j);
	}
	else if (type == "Potion")
	{
		return Potion::fromJson(j);
	}
	else if (type == "ThrownConsumable")
	{
		return ThrownConsumable::fromJson(j);
	}
	else
	{
		std::cerr << "Unknown item type: " << type << std::endl;
	}
	return nullptr;
}