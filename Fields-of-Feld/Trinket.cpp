#include "Trinket.h"
#include <string>

Trinket::Trinket(std::string name, std::string description, float value, float weight, float quantity, TrinketType trinketType)
	: Item(true, name, description, value, weight, 1.0f, EquipSlots::BACKPACK),
	 trinketType(trinketType)
{

}

nlohmann::json Trinket::toJson() const
{
	return{
		{"id", id },
		{ "type", "Trinket"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "trinketType", trinketType }
	};
}

std::shared_ptr<Item> Trinket::fromJson(const nlohmann::json& j)
{
	auto trinket = std::make_shared<Trinket>(
		j.at("name"),
		j.at("description"),
		j.at("value"),
		j.at("weight"),
		j.at("quantity"),
		j.at("trinketType"));
	trinket->id = j.at("id");
	return trinket;
}