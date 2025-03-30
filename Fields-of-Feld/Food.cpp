#include "Food.h"
#include <iostream>
#include "color.hpp"
#include "Character.h"

Food::Food(std::string name, std::string description, float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value), id(IDManager::getNextId())
{
}

void Food::use(std::shared_ptr<Character> consumer)
{
	if (consumer->inventory.findItemIndexById(this->id) != -1)
	{
		std::cout << dye::light_red("ERROR: Attempted to use a food that is not in the inventory.") << std::endl;
		return;
	}
	std::cout << dye::light_yellow(" " + consumer->name) << " eats a " << name << std::endl;
	for (auto& effect : effects)
	{
		effect->apply(consumer, consumer);
	}
	this->quantity--;
	if (this->quantity <= 0)
	{
		consumer->inventory.backpackItems.erase(consumer->inventory.backpackItems.begin() + consumer->inventory.findItemIndexById(this->id));
		std::cout << dye::light_yellow(" " + consumer->name) << " eats their last " << name << "!" << std::endl;
	}
}
nlohmann::json Food::toJson() const
{
	nlohmann::json j;

	j["id"] = id;
	j["type"] = "Food";
	j["name"] = name;
	j["description"] = description;
	j["value"] = value;
	j["weight"] = weight;
	j["quantity"] = quantity;
	j["magnitude"] = magnitude;

	// Save effects properly
	j["effects"] = nlohmann::json::array();
	for (const auto& effect : effects)
	{
		if (effect)
			j["effects"].push_back(effect->toJson());
	}

	return j;
}

std::shared_ptr<Item> Food::fromJson(const nlohmann::json& j)
{
	auto food = std::make_shared<Food>();

	try {
		if (j.contains("id"))          food->id = j["id"];
		if (j.contains("name"))        food->name = j["name"];
		if (j.contains("description")) food->description = j["description"];
		if (j.contains("value"))       food->value = j["value"];
		if (j.contains("weight"))      food->weight = j["weight"];
		if (j.contains("quantity"))    food->quantity = j["quantity"];
		if (j.contains("magnitude"))   food->magnitude = j["magnitude"];

		if (j.contains("effects") && j["effects"].is_array()) {
			for (const auto& eff : j["effects"]) {
				auto effectPtr = Effect::fromJson(eff);
				if (effectPtr) food->effects.push_back(effectPtr);
			}
		}
		else {
			std::cerr << "[WARN] Food missing 'effects' or it is not an array.\n";
		}
	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "[ERROR] Failed to load Food item from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return food;
}
