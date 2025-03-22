#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include <unordered_map>
#include "nlohmann/json.hpp"
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include "Consumable.h"

using josn = nlohmann::json;
class ItemFactory
{
public:
	static void loadItemsFromFile(const std::string& fileName);
	static void saveItemsToFile(const std::string& fileName);

	//std::unique_ptr<Item> createWeapon(const std::string& id);
	std::shared_ptr<Consumable> createConsumable(const std::string& type);

	static std::unordered_map<std::string, nlohmann::json> itemDatabase;
};

#endif // !ITEMFACTORY_H


