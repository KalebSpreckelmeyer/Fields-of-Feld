#ifndef Inventory_h
#define Inventory_h

#include <vector>
#include <string>
#include <optional>

class Item;
class Inventory {
public:

	//equipped items
	std::vector<Item*> equippedItems;

	std::vector<Item*> backpackItems;

	void getEquippedItems(Item* mainHand, Item* offHand, Item* reserve1, Item* reserve2, Item* head, Item* body,
		Item* legs, Item* arms, Item* amulet, Item* ring1, Item* ring2, Item* misc);

	void getEquippedWeapons(Item* mainHand, Item* offHand, Item* reserve1, Item* reserve2);

	Item* findEquippedItem(std::string name);

};

#endif // !Inventory_h
