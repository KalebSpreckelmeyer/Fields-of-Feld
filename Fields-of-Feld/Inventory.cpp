#include "Inventory.h"
#include <vector>
#include <string>
#include "color.hpp"
#include "Item.h"

//Equipped Items
Item* Inventory::findEquippedItem(std::string name)
{
	for (Item* item : equippedItems)
	{
		if (item->name == name) return item;
	}
}

void Inventory::getEquippedItems(Item* mainHand, Item* offHand, Item* reserve1, Item* reserve2, Item* head, Item* chest, 
	Item* legs, Item* arms, Item* amulet, Item* ring1, Item* ring2, Item* misc)
{
	for (int i = 0; i < this->equippedItems.size(); i++)
	{
		if (this->equippedItems[i]->slot == Item::EquipSlots::MAINHAND) mainHand = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::OFFHAND) offHand = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE1) reserve1 = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE2) reserve2 = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::HEAD) head = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::CHEST) chest = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::LEGS) legs = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::ARMS) arms = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::AMULET) amulet = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::RING1) ring1 = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::RING2) ring2 = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::MISC) misc = equippedItems[i];
	}
}

void Inventory::getEquippedWeapons(Item* mainHand, Item* offHand, Item* reserve1, Item* reserve2)
{
	for (int i = 0; i < this->equippedItems.size(); i++)
	{
		if (this->equippedItems[i]->slot == Item::EquipSlots::MAINHAND) mainHand = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::OFFHAND) offHand = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE1) reserve1 = equippedItems[i];
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE2) reserve2 = equippedItems[i];
	}
}