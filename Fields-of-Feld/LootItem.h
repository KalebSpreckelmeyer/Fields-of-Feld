#ifndef LOOTITEM_H
#define LOOTITEM_H
#include "Item.h"
class LootItem :
    public Item
{
public:
	LootItem() = default;
	LootItem(std::string name, std::string description, float value, float weight, float quantity);
	~LootItem() = default;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

};
#endif // !LOOTITEM_H



