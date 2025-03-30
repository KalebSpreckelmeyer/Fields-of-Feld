#include "Potion.h"
#include <string>
#include "HelperFunctions.h"
#include <iostream>
#include "color.hpp"

Potion::Potion(std::string name, std::string description,
	float magnitude, float weight, float quantity, float value, PotionEffect effect)
	: Consumable(name, description, magnitude, weight, quantity, value), id(IDManager::getNextId())
{

}

Potion::Potion()
{
	id = IDManager::getNextId();
}
void Potion::use(std::shared_ptr<Character> consumer) 
{
	if (consumer->inventory.findItemIndexById(this->id) != -1)
	{
		std::cout << dye::light_red("ERROR: Attempted to use a potion that is not in the inventory.") << std::endl;
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


nlohmann::json Potion::toJson() const
{
	nlohmann::json effectArray = nlohmann::json::array();
	for (const auto& effect : effects) {
		if (effect) effectArray.push_back(effect->toJson());
	}

	return {
		{"id", id},
		{"type", "Potion"},
		{"name", name},
		{"description", description},
		{"value", value},
		{"weight", weight},
		{"quantity", quantity},
		{"magnitude", magnitude},
		{"potionEffect", potionEffectToString(potionEffect)},
		{"effects", effectArray}
	};
}

std::shared_ptr<Item> Potion::fromJson(const nlohmann::json& j)
{
	auto potion = std::make_shared<Potion>();

	if (j.contains("id")) potion->id = j["id"];
	if (j.contains("name")) potion->name = j["name"];
	if (j.contains("description")) potion->description = j["description"];
	if (j.contains("value")) potion->value = j["value"];
	if (j.contains("weight")) potion->weight = j["weight"];
	if (j.contains("quantity")) potion->quantity = j["quantity"];
	if (j.contains("magnitude")) potion->magnitude = j["magnitude"];
	if (j.contains("potionEffect")) potion->potionEffect = stringToPotionEffect(j["potionEffect"].get<std::string>());

	// Load effects
	if (j.contains("effects") && j["effects"].is_array()) {
		for (const auto& effectJson : j["effects"]) {
			potion->effects.push_back(Effect::fromJson(effectJson));
		}
	}

	return potion;
}
