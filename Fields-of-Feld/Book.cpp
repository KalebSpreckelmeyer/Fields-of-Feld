#include "Book.h"

Book::Book(std::string name, std::string description, float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value)
{
}

void Book::use()
{
}
nlohmann::json Book::toJson() const
{
	return{
		{"id", id },
		{ "type", "Book"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "magnitude", magnitude }
	};
}

std::shared_ptr<Item> Book::fromJson(const nlohmann::json& j)
{
	auto book = std::make_shared<Book>(
		j.at("name"),
		j.at("description"),
		j.at("magnitude"),
		j.at("weight"),
		j.at("quantity"),
		j.at("value"));
	book->id = j.at("id");
	return book;
}