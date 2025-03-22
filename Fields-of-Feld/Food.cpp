#include "Food.h"

Food::Food(std::string name, std::string description, float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value)
{
}

nlohmann::json Food::toJson() const
{
	return{
		{"id", id },
		{ "type", "Food"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "magnitude", magnitude }
	};
}

std::shared_ptr<Item> Food::fromJson(const nlohmann::json& j)
{
	auto food = std::make_shared<Food>(
		j.at("name"),
		j.at("description"),
		j.at("magnitude"),
		j.at("weight"),
		j.at("quantity"),
		j.at("value"));
	food->id = j.at("id");
	return food;
}