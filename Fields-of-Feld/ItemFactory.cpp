#include "ItemFactory.h"
#include <fstream>
#include <iostream>
#include "Potion.h"
#include "Food.h"
#include "Book.h"

using json = nlohmann::json;

std::unordered_map<std::string, json> ItemFactory::itemDatabase;

void ItemFactory::loadItemsFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Could not open file: " << fileName << std::endl;
		return;
	}
	
	josn j;
	file >> j;

	for (auto& [key, value] : j.items())
	{
		itemDatabase[key] = value;
	}
}

void ItemFactory::saveItemsToFile(const std::string& fileName)
{
	json j;

	for (const auto& [key, value] : itemDatabase)
	{
		j[key] = value;
	}

	std::ofstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Could not open file: " << fileName << std::endl;
		return;
	}

	file << j.dump(4);
}

std::shared_ptr<Consumable> ItemFactory::createConsumable(const std::string& id)
{
	if (itemDatabase.find(id) == itemDatabase.end())
	{
		std::cerr << "Item ID not found: " << id << std::endl;
		return nullptr;
	}
	const auto& data = itemDatabase[id];
	std::string type = data.value("type", "");
	std::string name = data.value("name", "Unkown Consumable");
	std::string description = data.value("description", "No description");
	float magnitude = data.value("magnitude", 0.0f);
	float weight = data.value("weight", 0.0f);
	float quantity = data.value("quantity", 1.0f);
	float value = data.value("value", 0.0f);

	if (type == "potion")
	{
		return std::make_unique<Potion>(name, description, magnitude, weight, quantity, value);
	}
	else if (type == "food")
	{
		return std::make_unique<Food>(name, description, magnitude, weight, quantity, value);
	}
	else if (type == "book")
	{
		return std::make_unique<Book>(name, description, magnitude, weight, quantity, value);
	}
	else
	{
		std::cerr << "Unknown consumable type: " << type << std::endl;
		return nullptr;
	}
}