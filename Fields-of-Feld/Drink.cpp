#include "Drink.h"
#include <iostream>
#include "color.hpp"
#include "Character.h"

Drink::Drink(std::string name, std::string description, float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value), id(IDManager::getNextId())
{
}

void Drink::use(std::shared_ptr<Character> consumer)
{
	if (consumer->inventory.findItemIndexById(this->id) != -1)
	{
		std::cout << dye::light_red("ERROR: Attempted to use a drink that is not in the inventory.") << std::endl;
		return;
	}
	std::cout << dye::light_yellow(" " + consumer->name) << " drinks a " << name << std::endl;
	for (auto& effect : effects)
	{
		effect->apply(consumer, consumer);
	}
	this->quantity--;
	if (this->quantity <= 0)
	{
		consumer->inventory.backpackItems.erase(consumer->inventory.backpackItems.begin() + consumer->inventory.findItemIndexById(this->id));
		std::cout << dye::light_yellow(" " + consumer->name) << " drinks their last " << name << "!" << std::endl;
	}
}
nlohmann::json Drink::toJson() const
{
	nlohmann::json j;

	j["id"] = id;
	j["type"] = "Drink";
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

std::shared_ptr<Item> Drink::fromJson(const nlohmann::json& j)
{
	auto drink = std::make_shared<Drink>();

	try {
		if (j.contains("name"))        drink->name = j["name"];
		if (j.contains("description")) drink->description = j["description"];
		if (j.contains("value"))       drink->value = j["value"];
		if (j.contains("weight"))      drink->weight = j["weight"];
		if (j.contains("quantity"))    drink->quantity = j["quantity"];
		if (j.contains("magnitude"))   drink->magnitude = j["magnitude"];
		if (j.contains("id"))          drink->id = j["id"];

		if (j.contains("effects") && j["effects"].is_array()) {
			for (const auto& eff : j["effects"]) {
				auto effectPtr = Effect::fromJson(eff);
				if (effectPtr) drink->effects.push_back(effectPtr);
			}
		}
		else {
			std::cerr << "[WARN] Drink missing 'effects' or it is not an array.\n";
		}
	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "[ERROR] Failed to parse Drink from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return drink;
}
