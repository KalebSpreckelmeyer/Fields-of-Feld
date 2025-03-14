#include "Inventory.h"
#include <vector>
#include <string>
#include "color.hpp"



//GENERAL METHODS:

int Inventory::getItemWeight(Item item)
{
	int cumulativeWeight = item.quantity * item.weight;
	return cumulativeWeight;
}

//LOOT ITEMS

void Inventory::addLootItems(Item& item)
{
	lootItems.push_back(item);
}

Item Inventory::lootOneItem(std::string itemName)
{
	for (int i = 0; i < lootItems.size(); i++)
	{
		if (lootItems[i].name == itemName)
		{
			return lootItems[i];
		}
	}
	//needs error handling 
}

std::vector<Item> Inventory::lootAll(std::vector<Item> container)
{
	std::vector<Item> items;
	for (int i = 0; i < items.size(); i++)
	{
		items.push_back(container[i]);
	}
	return items;
	//needs error handling 
}

std::vector<Item> Inventory::getEquippedItems() {
	std::vector<Item> items;
	for (int i = 0; i < equippedItems.size(); i++)
	{
		items.push_back(equippedItems[i]);
	}
	return items;
}

//Equipped Items

void Inventory::getEquippedWeapons(Item& mainHand1, Item& mainHand2, Item& offHand1, Item& offHand2)
{
	//checks if the vector is empty first
	if (!equippedItems.empty())
	{
		//sets the weapons by slot
		for (int i = 0; i < equippedItems.size(); i++)
		{
			if (equippedItems[i].slot == Item::MAINHAND1)
			{
				mainHand1 = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::MAINHAND2)
			{
				mainHand2 = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::OFFHAND1)
			{
				offHand1 = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::OFFHAND2)
			{
				offHand2 = equippedItems[i];
			}
		}
	}
}

void Inventory::getEquippedArmor(Item& head, Item& chest, Item& arms, Item& legs)
{
	//check if the vector is empty first
	if (!equippedItems.empty())
	{
		//sets the armor by slot
		for (int i = 0; i < equippedItems.size(); i++)
		{
			if (equippedItems[i].slot == Item::HEAD)
			{
				head = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::CHEST)
			{
				chest = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::ARMS)
			{
				arms = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::LEGS)
			{
				legs = equippedItems[i];
			}
		}
	}
}

void Inventory::getEquippedMisc(Item& amulet, Item& ring1, Item& ring2, Item& misc)
{
	//check if the vector is empty first
	if (!equippedItems.empty())
	{
		//sets the armor by slot
		for (int i = 0; i < equippedItems.size(); i++)
		{
			if (equippedItems[i].slot == Item::AMULET)
			{
				amulet = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::RING1)
			{
				ring1 = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::RING2)
			{
				ring2 = equippedItems[i];
			}
			if (equippedItems[i].slot == Item::MISC)
			{
				misc = equippedItems[i];
			}
		}
	}
}

void Inventory::equipItem(Item& item, Item::equip_slots slot) {
	//gets all equipped items to check if there is room to equip item
	std::vector<Item> items = getEquippedItems();

	bool mainHand1Used = false;
	bool mainHand2Used = false;
	bool Offhand1Used = false;
	bool Offhand2Used = false;
	bool headUsed = false;
	bool chestUsed = false;
	bool legsUsed = false;
	bool armsUsed = false;
	bool amuletUsed = false;
	bool ring1Used = false;
	bool ring2Used = false;
	bool miscUsed = false;
	bool quiver1Used = false;
	bool quiver2Used = false;
	bool quiver3Used = false;
	bool quiver4Used = false;

	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].slot == Item::MAINHAND1)
		{
			mainHand1Used = true;
		}
		if (items[i].slot == Item::MAINHAND2)
		{
			mainHand2Used = true;
		}
		if (items[i].slot == Item::OFFHAND1)
		{
			Offhand1Used = true;
		}
		if (items[i].slot == Item::OFFHAND2)
		{
			Offhand2Used = true;
		}
		if (items[i].slot == Item::OFFHAND2)
		{
			Offhand2Used = true;
		}
		if (items[i].slot == Item::HEAD)
		{
			headUsed = true;
		}
		if (items[i].slot == Item::CHEST)
		{
			chestUsed = true;
		}
		if (items[i].slot == Item::LEGS)
		{
			legsUsed = true;
		}
		if (items[i].slot == Item::ARMS)
		{
			armsUsed = true;
		}
		if (items[i].slot == Item::AMULET)
		{
			amuletUsed = true;
		}
		if (items[i].slot == Item::RING1)
		{
			ring1Used = true;
		}
		if (items[i].slot == Item::RING2)
		{
			ring2Used = true;
		}
		if (items[i].slot == Item::MISC)
		{
			miscUsed = true;
		}
		if (items[i].slot == Item::QUIVER1)
		{
			quiver1Used = true;
		}
		if (items[i].slot == Item::QUIVER2)
		{
			quiver2Used = true;
		}
		if (items[i].slot == Item::QUIVER3)
		{
			quiver3Used = true;
		}
		if (items[i].slot == Item::QUIVER4)
		{
			quiver4Used = true;
		}

	}
	//if they're trying to equip a two handed weapon
	if (slot == Item::MAINHAND1 && item.twoHanded == true && mainHand1Used == false && Offhand1Used == false)
	{
		item.slot = Item::MAINHAND1;
		equippedItems.push_back(item);
	}
	else if (slot == Item::OFFHAND1 && item.twoHanded == true && mainHand1Used == false && Offhand1Used == false)
	{
		std::cout << "ERROR: " << item.name << " could not be equipped. It must be equipped in mainhand1 or mainhand2 " << std::endl;
	}
	else if (slot == Item::MAINHAND2 && item.twoHanded == true && mainHand2Used == false && Offhand2Used == false)
	{
		item.slot = Item::MAINHAND2;
		equippedItems.push_back(item);
	}
	else if (slot == Item::OFFHAND2 && item.twoHanded == true && mainHand2Used == false && Offhand2Used == false)
	{
		std::cout << "ERROR: " << item.name << " could not be equipped. It must be equipped in mainhand1 or mainhand2 " << std::endl;
	}
	//if they're trying to equip a one handed weapon
	else if (slot == Item::MAINHAND1 && item.twoHanded == false && mainHand1Used == false)
	{
		item.slot = Item::MAINHAND1;
		equippedItems.push_back(item);
	}
	else if (slot == Item::MAINHAND2 && item.twoHanded == false && mainHand2Used == false)
	{
		item.slot = Item::MAINHAND2;
		equippedItems.push_back(item);
	}
	else if (slot == Item::OFFHAND1 && item.twoHanded == false && Offhand1Used == false)
	{
		item.slot = Item::OFFHAND1;
		equippedItems.push_back(item);
	}
	else if (slot == Item::OFFHAND2 && item.twoHanded == false && Offhand2Used == false)
	{
		item.slot = Item::OFFHAND2;
		equippedItems.push_back(item);
	}
	//if they're trying to equip armor
	else if (slot == Item::HEAD && headUsed == false)
	{
		item.slot = Item::HEAD;
		equippedItems.push_back(item);
	}
	else if (slot == Item::CHEST && chestUsed == false)
	{
		item.slot = Item::CHEST;
		equippedItems.push_back(item);
	}
	else if (slot == Item::LEGS && legsUsed == false)
	{
		item.slot = Item::LEGS;
		equippedItems.push_back(item);
	}
	else if (slot == Item::ARMS && armsUsed == false)
	{
		item.slot = Item::ARMS;
		equippedItems.push_back(item);
	}
	//if they're trying to equip a trinket
	else if (slot == Item::AMULET && amuletUsed == false)
	{
		item.slot = Item::AMULET;
		equippedItems.push_back(item);
	}
	else if (slot == Item::RING1 && ring1Used == false)
	{
		item.slot = Item::RING1;
		equippedItems.push_back(item);
	}
	else if (slot == Item::RING2 && ring2Used == false)
	{
		item.slot = Item::RING2;
		equippedItems.push_back(item);
	}
	else if (slot == Item::MISC && miscUsed == false)
	{
		item.slot = Item::MISC;
		equippedItems.push_back(item);
	}
	//If they're trying to equip ammunition
	else if (slot == Item::QUIVER1 && quiver1Used == false)
	{
		item.slot = Item::QUIVER1;
		equippedItems.push_back(item);
	}
	else if (slot == Item::QUIVER2 && quiver2Used == false)
	{
		item.slot = Item::QUIVER2;
		equippedItems.push_back(item);
	}
	else if (slot == Item::QUIVER3 && quiver3Used == false)
	{
		item.slot = Item::QUIVER3;
		equippedItems.push_back(item);
	}
	else if (slot == Item::QUIVER4 && quiver4Used == false)
	{
		item.slot = Item::QUIVER4;
		equippedItems.push_back(item);
	}
	else
	{
		std::cout << "ERROR: " << item.name << " could not be equipped. Slot is already occupied." << std::endl;
	}

}


//BACKPACK ITEMS

void Inventory::swapEquippedItem(Item& equippedItem, Item& itemToEquip, Item::equip_slots slot) {
	//Checks the slot of the item they're storing away and assigns it to the item they're equipping
	if (equippedItem.slot == Item::MAINHAND1)
	{
		itemToEquip.slot = Item::MAINHAND1;
	}
	else if (equippedItem.slot == Item::MAINHAND2)
	{
		itemToEquip.slot = Item::MAINHAND2;
	}
	else if (equippedItem.slot == Item::OFFHAND1)
	{
		itemToEquip.slot = Item::OFFHAND1;
	}
	else if (equippedItem.slot == Item::OFFHAND2)
	{
		itemToEquip.slot = Item::OFFHAND2;
	}

	//swaps items
	Item temp;
	temp = equippedItem;
	equippedItem = itemToEquip;
	itemToEquip = temp;

	//prints message informing player of the change
	std::cout << equippedItem.name << dye::light_yellow(" swapped with ") << itemToEquip.name << std::endl;
}

void Inventory::addItemToBackpack(const Item& item) {
	backpackItems.push_back(item);
}

void Inventory::removeItemFromBackpack(const Item& item) {
	for (auto it = backpackItems.begin(); it != backpackItems.end(); ++it) {
		if (it->name == item.name) {
			backpackItems.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Inventory::removeAllItemsFromBackpack() {
	backpackItems.clear();
	equippedItems.clear();
}

void Inventory::updateItemQuantityInBackpack(const std::string& itemName, int newQuantity) {
	for (Item& item : backpackItems) {
		if (item.name == itemName) {
			item.quantity = newQuantity;
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

Item Inventory::findItemInBackpack(const std::string& itemName) {
	for (Item& item : backpackItems) {
		if (item.name == itemName) {
			return item;
		}
	}
	for (Item& item : equippedItems) {
		if (item.name == itemName) {
			return item;
		}
	}
	throw std::invalid_argument("Item not found");
}


//POTION

std::optional<Potion> Inventory::getHealingPotion()
{
	if (!potions.empty())
	{
		for (int i = 0; i < this->potions.size(); i++)
		{
			if (this->potions[i].effects == Potion::HEALING)
			{
				return this->potions[i];
			}
		}
	}
	else
	{
		return std::nullopt;
	}
}
void Inventory::addPotion(const Potion& potion) {
	potions.push_back(potion);
}

void Inventory::removePotion(const Potion& potion)
{
	for (auto it = potions.begin(); it != potions.end(); ++it) {
		if (it->name == potion.name) {
			potions.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");

}

Potion& Inventory::findPotion(const std::string& potionName) {
	for (Potion& potion : potions) {
		if (potion.name == potionName) {
			return potion;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Inventory::updatePotionQuantity(const std::string& potionName, int newQuantity) {
	for (Potion& potion : potions) {
		if (potion.name == potionName) {
			potion.quantity = newQuantity;
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Inventory::printEquippedItems() {
	int tally;
	std::cout << dye::light_yellow("->Weapon(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::WEAPON)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Damage: ") << item.damage << std::endl;
			std::cout << dye::light_yellow("  Attack Speed: ") << item.attackSpeed << std::endl;
			std::cout << dye::light_yellow("  Reach: ") << item.reach << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			if (item.physicalDamageType == Item::BLUNT)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << std::endl;
			}
			if (item.physicalDamageType == Item::SLASH)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << std::endl;
			}
			if (item.physicalDamageType == Item::PIERCE)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << std::endl;
			}

			if (item.magicDamageType == Item::FIRE)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << std::endl;
			}
			if (item.magicDamageType == Item::FROST)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << std::endl;
			}
			if (item.magicDamageType == Item::SHOCK)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << std::endl;
			}
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Armor(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::ARMOR)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Defense: ") << item.defense << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			if (item.slot == Item::HEAD)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Helmet" << std::endl;
			}
			if (item.slot == Item::CHEST)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Cuirass" << std::endl;
			}
			if (item.slot == Item::ARMS)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Gauntlets" << std::endl;
			}

			if (item.slot == Item::LEGS)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Leggings" << std::endl;
			}
			if (item.slot == Item::AMULET)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Amulet" << std::endl;
			}
			if (item.slot == Item::TRINKET)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Trinket" << std::endl;
			}
			if (item.slot == Item::RING1 || item.slot == Item::RING2)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Ring" << std::endl;
			}
			if (item.slot == Item::MISC)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Miscellaneous" << std::endl;
			}
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Shield(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::SHIELD)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Defense: ") << item.defense << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Damage: ") << item.damage << std::endl;
			std::cout << dye::light_yellow("  Block chance: ") << "TODO" << "%" << std::endl;
			if (item.physicalDamageType == Item::BLUNT)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << std::endl;
			}
			if (item.physicalDamageType == Item::SLASH)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << std::endl;
			}
			if (item.physicalDamageType == Item::PIERCE)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << std::endl;
			}

			if (item.magicDamageType == Item::FIRE)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << std::endl;
			}
			if (item.magicDamageType == Item::FROST)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << std::endl;
			}
			if (item.magicDamageType == Item::SHOCK)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << std::endl;
			}
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Arcane Casting Tools(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::ARCANETOOL)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << std::endl;
			std::cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Holy Casting Tools(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::HOLYTOOL)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Trinket(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::TRINKET)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Light Source(s): ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::LIGHT)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Ammunition: ") << std::endl;
	tally = 1;
	for (Item& item : equippedItems) {
		if (item.itemType == Item::AMMO)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Damage: ") << item.damage << std::endl;
			std::cout << dye::light_yellow("  Reach: ") << item.reach << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
}

void Inventory::printBackpack() {
	int tally;
	std::cout << dye::light_yellow("->Weapon(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::WEAPON)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Damage: ") << item.damage << std::endl;
			std::cout << dye::light_yellow("  Attack Speed: ") << item.attackSpeed << std::endl;
			std::cout << dye::light_yellow("  Reach: ") << item.reach << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			if (item.physicalDamageType == Item::BLUNT)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << std::endl;
			}
			if (item.physicalDamageType == Item::SLASH)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << std::endl;
			}
			if (item.physicalDamageType == Item::PIERCE)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << std::endl;
			}

			if (item.magicDamageType == Item::FIRE)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << std::endl;
			}
			if (item.magicDamageType == Item::FROST)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << std::endl;
			}
			if (item.magicDamageType == Item::SHOCK)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << std::endl;
			}
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Armor(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::ARMOR)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Defense: ") << item.defense << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			if (item.slot == Item::HEAD)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Helmet" << std::endl;
			}
			if (item.slot == Item::CHEST)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Cuirass" << std::endl;
			}
			if (item.slot == Item::ARMS)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Gauntlets" << std::endl;
			}

			if (item.slot == Item::LEGS)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Leggings" << std::endl;
			}
			if (item.slot == Item::AMULET)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Amulet" << std::endl;
			}
			if (item.slot == Item::TRINKET)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Trinket" << std::endl;
			}
			if (item.slot == Item::RING1 || item.slot == Item::RING2)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Ring" << std::endl;
			}
			if (item.slot == Item::MISC)
			{
				std::cout << dye::light_yellow("  Item type: ") << "Miscellaneous" << std::endl;
			}
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Shield(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::SHIELD)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Defense: ") << item.defense << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Damage: ") << item.damage << std::endl;
			std::cout << dye::light_yellow("  Block chance: ") << "TODO" << "%" << std::endl;
			if (item.physicalDamageType == Item::BLUNT)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << std::endl;
			}
			if (item.physicalDamageType == Item::SLASH)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << std::endl;
			}
			if (item.physicalDamageType == Item::PIERCE)
			{
				std::cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << std::endl;
			}

			if (item.magicDamageType == Item::FIRE)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << std::endl;
			}
			if (item.magicDamageType == Item::FROST)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << std::endl;
			}
			if (item.magicDamageType == Item::SHOCK)
			{
				std::cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << std::endl;
			}
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Arcane Casting Tools(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::ARCANETOOL)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << std::endl;
			std::cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Holy Casting Tools(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::HOLYTOOL)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Trinket(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::TRINKET)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
	std::cout << dye::light_yellow("->Light Source(s): ") << std::endl;
	tally = 1;
	for (Item& item : backpackItems) {
		if (item.itemType == Item::LIGHT)
		{
			std::cout << dye::light_yellow("  Name: ") << item.name << std::endl;
			std::cout << dye::light_yellow("  Weight: ") << item.weight << std::endl;
			std::cout << dye::light_yellow("  Quantity: ") << item.quantity << std::endl;
			std::cout << dye::light_yellow("  Value: ") << item.value << std::endl;
			std::cout << "\n";
			tally += 1;
		}
	}
	if (tally == 1)
	{
		std::cout << dye::light_yellow("  None") << std::endl;
	}
}

//AMMUNITION

void Inventory::addAmmunition(const Item& ammo) {
	ammunition.push_back(ammo);
}

void Inventory::removeAmmunition(const Item& ammo) {
	for (auto it = ammunition.begin(); it != ammunition.end(); ++it) {
		if (it->name == ammo.name) {
			ammunition.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Inventory::removeAllAmmunition() {
	ammunition.clear();
}

Item& Inventory::findAmmunition(const std::string& ammoName) {
	for (Item& ammo : ammunition) {
		if (ammo.name == ammoName) {
			return ammo;
		}
	}
	throw std::invalid_argument("Item not found");
}
//std::optional<Item> Inventory::chooseAmmunition() {
//	//// Helper function for input validation
//	//Item ammo;
//	//auto getValidChoice = [&](int min, int max) {
//	//	int choice;
//	//	do {
//	//		std::cout << ">> ";
//	//		std::cin >> choice;
//	//		if (std::cin.fail() || choice < min || choice > max) {
//	//			std::cin.clear();
//	//			std::cin.ignore(1000, '\n');
//	//			std::cout << dye::light_red("Enter a number between ") << min << " - " << max << std::endl;
//	//		}
//	//	} while (std::cin.fail() || choice < min || choice > max);
//	//	return choice;
//	//	};
//	//if (!ammunition.empty()) {
//	//	std::cout << dye::light_yellow("Choose ammunition: ") << std::endl;
//	//	for (int i = 0; i < ammunition.size(); ++i) {
//	//		std::cout << i + 1 << ") " << ammunition[i].name << "; damage: " << ammunition[i].damage
//	//			<< "; reach: " << ammunition[i].reach << "; quantity: " << ammunition[i].quantity << std::endl;
//	//	}
//	//	std::cout << dye::light_yellow(ammunition.size() + 1) << dye::light_yellow(") Go back") << std::endl;
//
//	//	int choice = getValidChoice(1, ammunition.size() + 1);
//	//	if (choice == ammunition.size() + 1) {
//	//		return std::nullopt;  // Go back option
//	//	}
//
//	//	ammo = ammunition[choice - 1];
//	//	return ammo;  // Return the selected ammo
//	//}
//	//else {
//	//	return std::nullopt;  // No ammo available
//	//}
//
//
//	//return std::nullopt;  // Default return if there's an error
//}

void Inventory::consumeAmmunition(Item& ammo)
{
	std::cout << "Before consume: " << ammo.quantity << std::endl;

	//check that ammo is passed correctly
	if (ammo.hasBeenInitialized)
	{
		//check ammo quantity
		if (ammo.quantity > 0)
		{
			//decrement ammo quantity
			ammo.quantity--;
			std::cout << "After consume: " << ammo.quantity << std::endl;

			//remove ammo if quantity is 0
			if (ammo.quantity == 0)
			{
				removeAmmunition(ammo);
			}
		}
		else
		{
			std::cout << dye::light_red("ERROR: Ammo quantity is 0") << std::endl;
		}
	}
	else
	{
		std::cout << dye::light_red("ERROR: Ammo not found") << std::endl;
	}
}

//COSUMABLES

void Inventory::addConsumable(const Item& consumable) {
	consumables.push_back(consumable);
}

void Inventory::removeConsumable(const Item& consumable) {
	for (auto it = consumables.begin(); it != consumables.end(); ++it) {
		if (it->name == consumable.name) {
			consumables.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Inventory::removeAllConsumables() {
	consumables.clear();
}

std::vector<Item*> Inventory::getConsumables() {
	std::vector<Item*> consumablesTemp;
	for (auto& consumable : consumables) {
		consumablesTemp.push_back(&consumable);
	}
	return consumablesTemp;
}
Item& Inventory::findConsumable(const std::string& consumableName) {
	for (Item& consumable : consumables) {
		if (consumable.name == consumableName) {
			return consumable;
		}
	}
	throw std::invalid_argument("Item not found");
}

void consumeConsumable(Item& consumable)
{
	//TODO
}

//THROWN WEAPONS

void Inventory::addThrownWeapon(const Item& thrownWeapon) {
	thrownWeapons.push_back(thrownWeapon);
}

void Inventory::removeThrownWeapon(const Item& thrownWeapon) {
	for (auto it = thrownWeapons.begin(); it != thrownWeapons.end(); ++it) {
		if (it->name == thrownWeapon.name) {
			thrownWeapons.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Inventory::removeAllThrownWeapons() {
	thrownWeapons.clear();
}

Item& Inventory::findThrownWeapon(const std::string& thrownWeaponName) {
	for (Item& thrownWeapon : thrownWeapons) {
		if (thrownWeapon.name == thrownWeaponName) {
			return thrownWeapon;
		}
	}
	throw std::invalid_argument("Item not found");
}

std::vector<Item*> Inventory::getThrownWeapons() {
	std::vector<Item*> thrownWeaponsTemp;
	for (auto& thrownWeapon : thrownWeapons) {
		thrownWeaponsTemp.push_back(&thrownWeapon);
	}
	return thrownWeaponsTemp;
}

void throwWeapon(Item& thrownWeapon)
{
	//TODO
}