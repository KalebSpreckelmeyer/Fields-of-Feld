#pragma once
#include "Item.h"
#include "Effect.h"
#include "Enchantment.h"
#include <vector>
class Trinket :
    public Item
{
public:
	int id;
	std::vector<std::shared_ptr<Enchantment>> enchantments;
	enum class TrinketType { AMULET, RING, MISC};
	TrinketType trinketType = TrinketType::MISC;

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Trinket();
	Trinket(std::string name, std::string description, float value, float weight, float quantity, TrinketType trinketType);
	~Trinket() = default;
};

