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
#include "LootItem.h"
#include <string>
#include "Drink.h"
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include "IDManager.h"


Item::Item( std::string name, std::string description , float value, float weight, float quantity, Item::EquipSlots slot) : 
	id(IDManager::getNextId()), name(name), description(description) ,value(value), weight(weight), quantity(quantity), slot(slot) {
}

std::shared_ptr<Item> Item::fromJson(const nlohmann::json& j)
{
	if (!j.contains("type") || !j["type"].is_string()) {
		throw std::runtime_error("Missing or invalid 'type' field in item JSON.");
	}

	std::string type = j["type"].get<std::string>();
	if (type == "Weapon")
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
	else if (type == "Drink")
	{
		return Drink::fromJson(j);
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
	else if (type == "Loot")
	{
		return LootItem::fromJson(j);
	}
	else
	{
		std::cerr << "Unknown item type: " << type << std::endl;
	}
	return nullptr;
}