#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "IDManager.h"
#include "Item.h"
class Recipe
{
public:
	std::string name;
	std::unordered_map<std::string, int> ingredients;
	float experienceGained;

	std::vector<std::shared_ptr<Item>> results;
};

