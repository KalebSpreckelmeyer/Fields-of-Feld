#include "Book.h"
#include <iostream>
#include "color.hpp"
#include "Character.h"

Book::Book(std::string name, std::string description, float magnitude, float weight, float quantity, float value)
	: Consumable(name, description, magnitude, weight, quantity, value), id(IDManager::getNextId())
{
}

void Book::use(std::shared_ptr<Character> consumer)
{
	if (consumer->inventory.findItemIndexById(this->id) != -1)
	{
		std::cout << dye::light_red("ERROR: Attempted to use a book that is not in the inventory.") << std::endl;
		return;
	}
	std::cout << dye::light_yellow(" " + consumer->name) << " reads a " << name << std::endl;
	for (auto& effect : effects)
	{
		effect->apply(consumer, consumer);
	}
	this->quantity--;
	if (this->quantity <= 0)
	{
		consumer->inventory.backpackItems.erase(consumer->inventory.backpackItems.begin() + consumer->inventory.findItemIndexById(this->id));
		std::cout << dye::light_yellow(" " + consumer->name) << " reads their last " << name << "!" << std::endl;
	}
}
nlohmann::json Book::toJson() const
{
	nlohmann::json j;

	j["id"] = id;
	j["type"] = "Book";
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

std::shared_ptr<Item> Book::fromJson(const nlohmann::json& j)
{
    auto book = std::make_shared<Book>();

    try {
        if (j.contains("name"))        book->name = j["name"];
        if (j.contains("description")) book->description = j["description"];
        if (j.contains("value"))       book->value = j["value"];
        if (j.contains("weight"))      book->weight = j["weight"];
        if (j.contains("quantity"))    book->quantity = j["quantity"];
        if (j.contains("magnitude"))   book->magnitude = j["magnitude"];
        if (j.contains("id"))          book->id = IDManager::getNextId();

        // Load effects
        if (j.contains("effects") && j["effects"].is_array()) {
            for (const auto& effectJson : j["effects"]) {
                book->effects.push_back(Effect::fromJson(effectJson));
            }
        }
        else {
            std::cerr << "[WARN] Book is missing 'effects' array." << std::endl;
        }

    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "[ERROR] Failed to load Book from JSON: " << e.what() << std::endl;
        return nullptr;
    }

    return book;
}
