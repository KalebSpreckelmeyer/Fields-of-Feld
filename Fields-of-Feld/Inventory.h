#ifndef Inventory_h
#define Inventory_h

#include <vector>
#include <string>
#include <optional>
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"

class Item;
class Inventory {
public:
	//equipped items
	std::vector<std::shared_ptr<Item>> equippedItems;

	std::vector<std::shared_ptr<Item>>  backpackItems;

	nlohmann::json toJson() const;
	void fromJson(const nlohmann::json& j);

	void getEquippedItems(std::shared_ptr<Weapon>& mainHand, std::shared_ptr<Weapon>& offHand, std::shared_ptr<Weapon>& reserve1,
		std::shared_ptr<Weapon>& reserve2, std::shared_ptr<Armor>& head, std::shared_ptr<Armor>& chest, std::shared_ptr<Armor>& legs,
		std::shared_ptr<Armor>& arms, std::shared_ptr<Trinket>& amulet, std::shared_ptr<Trinket>& ring1, std::shared_ptr<Trinket>& ring2, std::shared_ptr<Trinket>& misc);

	void getEquippedWeapons(std::shared_ptr<Weapon>& mainHand, std::shared_ptr<Weapon>& offHand, std::shared_ptr<Weapon>& reserve1, 
		std::shared_ptr<Weapon>& reserve2);
	
	void printInventory() const;
	void addToBackpack(std::shared_ptr<Item> item);
	void addToEquippedItems(std::shared_ptr<Item> item);
	//DESC: Fetches the index of an item in the backpackItems vector, returning -1 if not found
	//PRE: Item ideally should exist. If it doesnt, preare for it to return -1
	//POST: Returns the index of the item in the backpackItems vector
	int findItemIndexById(int id);
	//DESC:
	//PRE:
	//POST:
	void swapEquippedItems(std::shared_ptr<Weapon> mainHand, std::shared_ptr<Weapon> offHand, std::shared_ptr<Weapon> reserve1, std::shared_ptr<Weapon> reserve2);
	void save(const std::string& fileName) const;
	void load(const std::string& fileName);
	void print() const;
};

#endif // !Inventory_h
