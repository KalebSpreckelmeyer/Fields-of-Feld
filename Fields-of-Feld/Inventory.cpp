#include "Inventory.h"
#include <vector>
#include <string>
#include "color.hpp"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"

//Equipped Items
Item* Inventory::findEquippedItem(std::string name)
{
	for (Item* item : equippedItems)
	{
		if (item->name == name) return item;
	}
}

void Inventory::getEquippedItems(Weapon*& mainHand, Weapon*& offHand, Weapon*& reserve1, Weapon*& reserve2, Armor*& head, Armor*& chest, 
	Armor*& legs, Armor*& arms, Trinket*& amulet, Trinket*& ring1, Trinket*& ring2, Trinket*& misc)
{
	for (int i = 0; i < this->equippedItems.size(); i++)
	{
		if (this->equippedItems[i]->slot == Item::EquipSlots::MAINHAND) mainHand = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::OFFHAND) offHand = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE1) reserve1 = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE2) reserve2 = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::HEAD) head = dynamic_cast<Armor*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::CHEST) chest = dynamic_cast<Armor*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::LEGS) legs = dynamic_cast<Armor*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::ARMS) arms = dynamic_cast<Armor*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::AMULET) amulet = dynamic_cast<Trinket*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::RING1) ring1 = dynamic_cast<Trinket*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::RING2) ring2 = dynamic_cast<Trinket*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::MISC) misc = dynamic_cast<Trinket*>(equippedItems[i]);
	}
}

void Inventory::getEquippedWeapons(Weapon* mainHand, Weapon* offHand, Weapon* reserve1, Weapon* reserve2)
{
	for (int i = 0; i < this->equippedItems.size(); i++)
	{
		if (this->equippedItems[i]->slot == Item::EquipSlots::MAINHAND) mainHand = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::OFFHAND) offHand = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE1) reserve1 = dynamic_cast<Weapon*>(equippedItems[i]);
		if (this->equippedItems[i]->slot == Item::EquipSlots::RESERVE2) reserve2 = dynamic_cast<Weapon*>(equippedItems[i]);
	}
}