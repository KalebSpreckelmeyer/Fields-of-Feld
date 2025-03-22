#include "Potion.h"
#include <string>

Potion::Potion(std::string name, std::string description,
	float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value)
{

}

void Potion::use() 
{

}


nlohmann::json Potion::toJson() const
{
	return{
		{"id", id },
		{ "type", "Potion"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "magnitude", magnitude }
	};
}

std::shared_ptr<Item> Potion::fromJson(const nlohmann::json& j)
{
	auto potion = std::make_shared<Potion>(
		j.at("name"),
		j.at("description"),
		j.at("magnitude"),
		j.at("weight"),
		j.at("quantity"),
		j.at("value"));
	potion->id = j.at("id");
	return potion;
}
