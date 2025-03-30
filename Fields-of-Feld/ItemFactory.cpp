#include "ItemFactory.h"
#include <fstream>
#include <iostream>
#include "Potion.h"
#include "Food.h"
#include "Book.h"

bool ItemFactory::loadItemsFromFile(const std::string& filePath)
{
	//opens the file
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return false;
	}

	//writes file information into a json object
	nlohmann::json data;
	file >> data;

	//loops through json object, getting the type of the item and its contents and adds both to the itemTemplates map
	for (const auto& itemJson : data)
	{
		std::string type = itemJson["type"];
		itemTemplates[type].push_back(itemJson);
	}
	return true;
}

std::shared_ptr<Item> ItemFactory::createRandomItem(const std::string& type)
{
	//finds the list of item templates by type
	auto it = itemTemplates.find(type);
	if (it == itemTemplates.end() || it->second.empty()) return nullptr;
	
	//randomly picks a weapon from the list
	size_t index = rand() % it->second.size();
	return Item::fromJson(it->second[index]);
}

std::shared_ptr<Item> ItemFactory::createItemByIndex(const std::string& type, size_t index)
{
	//finds the list of item templates by type
	auto it = itemTemplates.find(type);
	if (it == itemTemplates.end() || index >= it->second.size()) return nullptr;

	//creates the item from the json object
	return Item::fromJson(it->second[index]);
}