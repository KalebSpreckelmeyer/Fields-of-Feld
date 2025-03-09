#ifndef Inventory_h
#define Inventory_h

#include <vector>
#include <string>

#include "Item.h"
#include "Potion.h"
#include "Ammo.h"

class Inventory {
public:
	//lootable items (from an enemy or container)
	std::vector<Item> lootItems;

	void addLootItems(Item& item);

	Item lootOneItem(std::string itemName);

	std::vector<Item> lootAll(std::vector<Item> container);

	//equipped items
	std::vector<Item> equippedItems;

	//retrieve and return all equipped items
	std::vector<Item> getEquippedItems();

	//equip an item to the relevant slot. It checks if the slot is used before adding it
	void equipItem(Item& item, Item::equip_slots slot);

	//Swaps equipped items with an item in the backpack
	void swapEquippedItem(Item& equippedItem, Item& itemToEquip, Item::equip_slots slot);

	//backpack

	std::vector<Item> backpackItems;

	void addItemToBackpack(const Item& item);

	void removeItemFromBackpack(const Item& item);

	void removeAllItemsFromBackpack();

	void updateItemQuantityInBackpack(const std::string& itemName, int newQuantity);

	Item findItemInBackpack(const std::string& itemName);

	//potions

	std::vector<Potion> potions;

	Potion& getHealingPotion();
	void addPotion(const Potion& potion);

	void removePotion(const Potion& potion);

	Potion& findPotion(const std::string& potionName);

	void updatePotionQuantity(const std::string& potionName, int newQuantity);

	//Printing Information

	void printEquippedItems();

	void printBackpack();
};

#endif // !Inventory_h
