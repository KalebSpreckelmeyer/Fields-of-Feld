#ifndef Item_h
#define Item_h
#include "Item.h"
#include <string>
#include <vector>

class Item {
public:
	bool hasBeenInitialized = false;
	std::string name = "ITEM NAME PLS CHANGE";
	std::string description = "ITEM DESCRIPTION PLS CHANGE";
	float value = 0.0f;
	float weight = 0.0f;
	float quantity = 0.0f;
	enum class EquipSlots { HEAD, CHEST, ARMS, LEGS, AMULET, RING1, RING2, MAINHAND, OFFHAND, RESERVE1, RESERVE2, MISC, BACKPACK, QUIVER1, QUIVER2, QUIVER3, QUIVER4 };
	EquipSlots slot = EquipSlots::BACKPACK;	

	Item();
	Item(bool hasBeenInitialized, std::string name, std::string description, float value, float weight, float quantity, Item::EquipSlots slot);
	virtual ~Item();
};

#endif // !Item_h