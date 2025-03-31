#include "LootItem.h"
#include <string>

LootItem::LootItem(std::string name, std::string description, float value, float weight, float quantity)
	: Item(name, description, value, weight, quantity, EquipSlots::BACKPACK), id(IDManager::getNextId())
{
}

nlohmann::json LootItem::toJson() const {
	return {
		{"id", id},
        {"type", "Loot"},
        {"name", name},
        {"description", description},
        {"value", value},
		{"weight", weight},
		{"quantity", quantity}
    };
}

std::shared_ptr<Item> LootItem::fromJson(const nlohmann::json& j) {
    auto loot = std::make_shared<LootItem>();

    if (j.contains("id")) loot->id = IDManager::getNextId();
    if (j.contains("name")) loot->name = j["name"];
    if (j.contains("description")) loot->description = j["description"];
    if (j.contains("value")) loot->value = j["value"];
    if (j.contains("weight")) loot->weight = j["weight"];
    if (j.contains("quantity")) loot->quantity = j["quantity"];

    return loot;
}