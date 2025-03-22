#include "LootItem.h"
#include <string>

LootItem::LootItem(std::string name, std::string description, float value, float weight, float quantity)
	: Item(true, name, description, value, weight, quantity, EquipSlots::BACKPACK)
{
}

nlohmann::json LootItem::toJson() const {
    return {
        {"type", "Loot"},
        {"name", name},
        {"description", description},
        {"value", value},
		{"weight", weight},
		{"quantity", quantity}
    };
}

std::shared_ptr<Item> LootItem::fromJson(const nlohmann::json& j) {
    return std::make_shared<LootItem>(
        j.at("name"),
        j.at("description"),
        j.at("value"),
		j.at("weight"),
		j.at("quantity")
    );
}