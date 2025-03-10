#ifndef Inventory_h
#define Inventory_h

#include <vector>
#include <string>
#include <optional>

#include "Item.h"
#include "Potion.h"
#include "Ammo.h"

class Inventory {
public:
	//GENERAL METHODS
	int getItemWeight(Item item);

	//lootable items (from an enemy or container)
	std::vector<Item> lootItems;

	void addLootItems(Item& item);

	Item lootOneItem(std::string itemName);

	std::vector<Item> lootAll(std::vector<Item> container);

	//equipped items
	std::vector<Item> equippedItems;

	//retrieve and return all equipped items as a vector of items
	std::vector<Item> getEquippedItems();

	//Retrieves and sets 4 objects referring to the 4 slots a character can have an item equipped to
	void getEquippedWeapons(Item& mainHand1, Item& mainHand2, Item& offHand1, Item& offHand2);

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

	std::optional<Potion> getHealingPotion();

	void addPotion(const Potion& potion);

	void removePotion(const Potion& potion);

	Potion& findPotion(const std::string& potionName);

	void updatePotionQuantity(const std::string& potionName, int newQuantity);

	//Printing Information

	void printEquippedItems();

	void printBackpack();
};

#endif // !Inventory_h
