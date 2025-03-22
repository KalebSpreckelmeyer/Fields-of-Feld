#include "Consumable.h"
#include <string>
#include "Potion.h"

Consumable::Consumable(std::string name, std::string description,
	float magnitude, float weight, float quantity, float value)
	: Item(hasBeenInitialized, name, description, value, weight, quantity, slot), magnitude(magnitude)
{
}

nlohmann::json Consumable::toJson() const
{
	return{
		{"id", id },
		{ "type", "Consumable"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "magnitude", magnitude }
	};
}

std::shared_ptr<Item> Consumable::fromJson(const nlohmann::json& j)
{
	std::string type = j.at("type");

	/*if (type == "Potion") {
		return std::make_shared<Potion>(Potion::fromJson(j));
	}*/
}