#include "Trinket.h"
#include <string>
#include "HelperFunctions.h"
#include "IDManager.h"

Trinket::Trinket(std::string name, std::string description, float value, float weight, float quantity, TrinketType trinketType)
	: Item(name, description, value, weight, 1.0f, EquipSlots::BACKPACK),
	 id(IDManager::getNextId()), trinketType(trinketType)
{

}

Trinket::Trinket()
{
	id = IDManager::getNextId();
}
nlohmann::json Trinket::toJson() const {
	nlohmann::json j;

	j["type"] = "Trinket";
	j["id"] = id;
	j["name"] = name;
	j["description"] = description;
	j["value"] = value;
	j["weight"] = weight;
	j["quantity"] = quantity;
	j["trinketType"] = trinketTypeToString(trinketType);

	// Enchantments
	j["enchantments"] = nlohmann::json::array();
	for (const auto& ench : enchantments) {
		j["enchantments"].push_back(ench->toJson());
	}

	return j;
}


std::shared_ptr<Item> Trinket::fromJson(const nlohmann::json& j) {
	auto trinket = std::make_shared<Trinket>();

	if (j.contains("id")) trinket->id = j["id"];
	if (j.contains("name")) trinket->name = j["name"];
	if (j.contains("description")) trinket->description = j["description"];
	if (j.contains("value")) trinket->value = j["value"];
	if (j.contains("weight")) trinket->weight = j["weight"];
	if (j.contains("quantity")) trinket->quantity = j["quantity"];

	if (j.contains("trinketType") && j["trinketType"].is_string()) {
		trinket->trinketType = stringToTrinketType(j["trinketType"]);
	}

	if (j.contains("enchantments") && j["enchantments"].is_array()) {
		for (const auto& enchantJson : j["enchantments"]) {
			trinket->enchantments.push_back(Enchantment::fromJson(enchantJson));
		}
	}

	return trinket;
}