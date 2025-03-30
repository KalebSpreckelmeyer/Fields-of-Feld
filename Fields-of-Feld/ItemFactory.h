#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include <unordered_map>
#include "nlohmann/json.hpp"
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Potion.h"
#include "Food.h"
#include "Book.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

using josn = nlohmann::json;

class ItemFactory
{
private:
	std::unordered_map<std::string, std::vector<nlohmann::json>> itemTemplates;
public:
	bool loadItemsFromFile(const std::string& filePath);

	//create a random item of a specific type
	std::shared_ptr<Item> createRandomItem(const std::string& type);

	//create a specific item by index or name
	std::shared_ptr<Item> createItemByIndex(const std::string& type, size_t index);
};

#endif // !ITEMFACTORY_H


