#include "Inventory.h"
#include <vector>
#include <string>
#include "color.hpp"

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

void Inventory::equipItem(Item& item, Item::equip_slots slot) {
	//gets all equipped items to check if there is room to equip item
	std::vector<Item> items = getEquippedItems();

	bool mainHand1Used = false;
	bool mainHand2Used = false;
	bool Offhand1Used = false;
	bool Offhand2Used = false;

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
	}
	if (slot == Item::MAINHAND1 && mainHand1Used == false) {
		item.slot = Item::MAINHAND1;
		equippedItems.push_back(item);

	}
	else if (slot == Item::MAINHAND2 && mainHand2Used == false) {
		item.slot = Item::MAINHAND2;
		equippedItems.push_back(item);

	}
	else if (slot == Item::OFFHAND1 && Offhand1Used == false) {
		item.slot = Item::OFFHAND1;
		equippedItems.push_back(item);

	}
	else if (slot == Item::OFFHAND2 && Offhand2Used == false) {
		item.slot = Item::OFFHAND2;
		equippedItems.push_back(item);
	}
	else
	{
		std::cout << item.name << dye::light_yellow(" could not be equipped as the slot is full")
			<< std::endl;
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

Potion& Inventory::getHealingPotion()
{
	std::vector<Potion> healingPotions;
	for (int i = 0; i < this->potions.size(); i++)
	{
		if (this->potions[i].effects == Potion::HEALING)
		{
			healingPotions.push_back(this->potions[i]);
		}
	}
	return healingPotions[0];
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
			if (item.slot == Item::RING)
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
		if (item.slot == Item::RING)
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