#ifndef Item_h
#define Item_h
#include "Item.h"
#include <string>
#include <vector>
#include <array>
#include "MagicDamageType.h"
#include "PhysicalDamageType.h"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Item {
protected:
	static int nextId;
	int id;
public:	
	bool hasBeenInitialized = false;
	std::string name = "ITEM NAME PLS CHANGE";
	std::string description = "ITEM DESCRIPTION PLS CHANGE";
	float value = 0.0f;
	float weight = 0.0f;
	float quantity = 0.0f;
	enum class EquipSlots { HEAD, CHEST, ARMS, LEGS, AMULET, RING1, RING2, MAINHAND, OFFHAND, RESERVE1, RESERVE2, MISC, BACKPACK, QUIVER1, QUIVER2, QUIVER3, QUIVER4 };
	EquipSlots slot = EquipSlots::BACKPACK;	

	//loading and saving items to json
	virtual nlohmann::json toJson() const = 0;
	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);


	Item() = default;
	Item(bool hasBeenInitialized, std::string name, std::string description, float value, float weight, float quantity,
		Item::EquipSlots slot);

	virtual ~Item() = default;
};

#endif // !Item_h