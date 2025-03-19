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
	std::vector<Item*> equippedItems;

	std::vector<Item*> backpackItems;

	void getEquippedItems(Weapon*& mainHand, Weapon*& offHand, Weapon*& reserve1, Weapon*& reserve2, Armor*& head, Armor*& chest,
		Armor*& legs, Armor*& arms, Trinket*& amulet, Trinket*& ring1, Trinket*& ring2, Trinket*& misc);

	void getEquippedWeapons(Weapon* mainHand, Weapon* offHand, Weapon* reserve1, Weapon* reserve2);

	Item* findEquippedItem(std::string name);

};

#endif // !Inventory_h
