#include "Drink.h"

Drink::Drink(std::string name, std::string description, float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value)
{
}

nlohmann::json Drink::toJson() const
{
	return{
		{"id", id },
		{ "type", "Drink"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "magnitude", magnitude }
	};
}

std::shared_ptr<Item> Drink::fromJson(const nlohmann::json& j)
{
	auto drink = std::make_shared<Drink>(
		j.at("name"),
		j.at("description"),
		j.at("magnitude"),
		j.at("weight"),
		j.at("quantity"),
		j.at("value"));
	drink->id = j.at("id");
	return drink;
}