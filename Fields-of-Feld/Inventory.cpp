#include "Inventory.h"
#include <vector>
#include <string>
#include <fstream>
#include "color.hpp"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"
#include "HelperFunctions.h"
#include "Drink.h"
#include "Food.h"
#include "Potion.h"

nlohmann::json Inventory::toJson() const
{
	nlohmann::json j;
	j["backpackItems"] = nlohmann::json::array();
	j["equippedItems"] = nlohmann::json::array();

	for (const auto& item : backpackItems)
	{
		j["backpackItems"].push_back(item->toJson());
	}
	for (const auto& item : equippedItems)
	{
		j["equippedItems"].push_back(item->toJson());
	}
	return j;
}

void Inventory::fromJson(const nlohmann::json& j)
{
	backpackItems.clear();
	equippedItems.clear();

	if (j.contains("backpackItems") && j["backpackItems"].is_array())
	{
		for (const auto& item : j["backpackItems"])
		{
			backpackItems.push_back(Item::fromJson(item));
		}
	}

	if (j.contains("equippedItems") && j["equippedItems"].is_array())
	{
		for (const auto& item : j["equippedItems"])
		{
			equippedItems.push_back(Item::fromJson(item));
		}
	}
}

void Inventory::getEquippedItems(std::shared_ptr<Weapon>& mainHand, std::shared_ptr<Weapon>& offHand, std::shared_ptr<Weapon>& reserve1, 
	std::shared_ptr<Weapon>& reserve2, std::shared_ptr<Armor>& head, std::shared_ptr<Armor>& chest, std::shared_ptr<Armor>& legs, 
	std::shared_ptr<Armor>& arms, std::shared_ptr<Trinket>& amulet, std::shared_ptr<Trinket>& ring1, std::shared_ptr<Trinket>& ring2, std::shared_ptr<Trinket>& misc)
{
	for (int i = 0; i < this->equippedItems.size(); i++)
	{
		//cast the shared pointer into a weapon
		auto weapon = std::dynamic_pointer_cast<Weapon>(equippedItems[i]);
		
		if (weapon)
		{
			//check the slot of the weapon
			switch (weapon->slot)
			{
			case Item::EquipSlots::MAINHAND:
				mainHand = weapon;
				break;
			case Item::EquipSlots::OFFHAND:
				offHand = weapon;
				break;
			case Item::EquipSlots::RESERVE1:
				reserve1 = weapon;
				break;
			case Item::EquipSlots::RESERVE2:
				reserve2 = weapon;
				break;
			}
		}

		//cast the shared pointer into an armor
		auto armor = std::dynamic_pointer_cast<Armor>(equippedItems[i]);

		if (armor)
		{
			//check the slot of the armor
			switch (armor->slot)
			{
			case Item::EquipSlots::HEAD:
				head = armor;
				break;
			case Item::EquipSlots::CHEST:
				chest = armor;
				break;
			case Item::EquipSlots::LEGS:
				legs = armor;
				break;
			case Item::EquipSlots::ARMS:
				arms = armor;
				break;
			}
		}
		

		//cast the shared pointer into a trinket
		auto trinket = std::dynamic_pointer_cast<Trinket>(equippedItems[i]);

		if (trinket)
		{
			//check the slot of the trinket
			switch (trinket->slot)
			{
			case Item::EquipSlots::AMULET:
				amulet = trinket;
				break;
			case Item::EquipSlots::RING1:
				ring1 = trinket;
				break;
			case Item::EquipSlots::RING2:
				ring2 = trinket;
				break;
			case Item::EquipSlots::MISC:
				misc = trinket;
				break;
			}
		}
	}
}

void Inventory::getEquippedWeapons(std::shared_ptr<Weapon>& mainHand, std::shared_ptr<Weapon>& offHand, std::shared_ptr<Weapon>& reserve1, std::shared_ptr<Weapon>& reserve2)
{
	for (int i = 0; i < this->equippedItems.size(); i++)
	{
		auto weapon = std::dynamic_pointer_cast<Weapon>(equippedItems[i]);
		if (!weapon) continue;

		// Then check which slot it's in
		switch (weapon->slot)
		{
		case Item::EquipSlots::MAINHAND:
			mainHand = weapon;
			break;
		case Item::EquipSlots::OFFHAND:
			offHand = weapon;
			break;
		case Item::EquipSlots::RESERVE1:
			reserve1 = weapon;
			break;
		case Item::EquipSlots::RESERVE2:
			reserve2 = weapon;
			break;
		default:
			break;
		}
	}
}

void Inventory::printInventory() const
{
	std::cout << dye::light_yellow(" Equipped Items: ") << std::endl;
	for (const auto& item : equippedItems)
	{
		std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(item);
		std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
		std::shared_ptr<Trinket> trinket = std::dynamic_pointer_cast<Trinket>(item);
		std::cout << (" Name: ") <<  item->name << std::endl;
		std::cout << (" Weight: ") << item->weight * item->quantity << std::endl;
		std::cout << (" Slot: ") << equipSlotToString(item->slot) << std::endl;
		if (weapon) std::cout << (" Damage: ") << weapon->getWeaponDamageBase(weapon) << std::endl;
		if (weapon && weapon->enchantments.size() > 0) std::cout << (" Enchantment: ") << weapon->enchantments[0]->name << std::endl;
		if (armor) std::cout << (" Defense: ") << armor->getArmorDefenseBase(armor) << std::endl;
		if (armor && armor->enchantments.size() > 0) std::cout << (" Enchantment: ") << armor->enchantments[0]->name << std::endl;
		if (trinket && trinket->enchantments.size() > 0) std::cout << (" Enchantment: ") << trinket->enchantments[0]->name << std::endl;
		std::cout << (" Value: ") << item->value << std::endl;
		std::cout << (" Quantity: ") << item->quantity << std::endl;
		std::cout << ("=--->") << std::endl;
	}
	std::cout << dye::light_yellow(" Backpack Items: ") << std::endl;
	for (const auto& item : backpackItems)
	{
		std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(item);
		std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
		std::shared_ptr<Trinket> trinket = std::dynamic_pointer_cast<Trinket>(item);
		std::shared_ptr<Food> food = std::dynamic_pointer_cast<Food>(item);
		std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item);
		std::shared_ptr<Drink> drink = std::dynamic_pointer_cast<Drink>(item);
		std::cout << (" Name: ") << item->name << std::endl;
		std::cout << (" Weight: ") << item->weight * item->quantity << std::endl;
		std::cout << (" Slot: ") << equipSlotToString(item->slot) << std::endl;
		if (weapon) std::cout << (" Damage: ") << weapon->getWeaponDamageBase(weapon) << std::endl;
		if (weapon && weapon->enchantments.size() > 0) std::cout << (" Enchantment: ") << weapon->enchantments[0]->name << std::endl;
		if (armor) std::cout << (" Defense: ") << armor->getArmorDefenseBase(armor) << std::endl;
		if (armor && armor->enchantments.size() > 0) std::cout << (" Enchantment: ") << armor->enchantments[0]->name << std::endl;
		if (trinket && trinket->enchantments.size() > 0) std::cout << (" Enchantment: ") << trinket->enchantments[0]->name << std::endl;
		if (food) std::cout << (" Magnitude: ") << food->magnitude << std::endl;
		if (potion) std::cout << (" Magnitude: ") << potion->magnitude << std::endl;
		if (drink) std::cout << (" Magnitude: ") << drink->magnitude << std::endl;
		std::cout << (" Value: ") << item->value << std::endl;
		std::cout << (" Quantity: ") << item->quantity << std::endl;
		std::cout << ("=--->") << std::endl;
	}
}

void Inventory::addToBackpack(std::shared_ptr<Item> item)
{
	backpackItems.push_back(item);
}

void Inventory::addToEquippedItems(std::shared_ptr<Item> item)
{
	equippedItems.push_back(item);
}

int Inventory::findItemIndexById(int id) {
	int index = -1;
	std::shared_ptr<Item> itemToFind;
	for (const auto& item : backpackItems)
	{
		if (item->id == id)
		{
			itemToFind = item;
		}
	}
	auto it = std::find(backpackItems.begin(), backpackItems.end(), itemToFind);
	if (it != backpackItems.end()) {
		int index = std::distance(backpackItems.begin(), it);
	}
	return index;
}

void Inventory::swapEquippedItems(std::shared_ptr<Weapon> mainHand, std::shared_ptr<Weapon> offHand, std::shared_ptr<Weapon> reserve1, std::shared_ptr<Weapon> reserve2)
{
	if (mainHand && offHand && reserve1 && reserve1)
	{
		std::shared_ptr<Weapon> temp = mainHand;
		mainHand = reserve1;
		reserve1 = temp;
		temp = offHand;
		offHand = reserve2;
		reserve2 = temp;
	}
	else if (mainHand && reserve1)
	{
		std::shared_ptr<Weapon> temp = mainHand;
		mainHand = reserve1;
		reserve1 = temp;
	}
	else if (offHand && reserve2)
	{
		std::shared_ptr<Weapon> temp = offHand;
		offHand = reserve2;
		reserve2 = temp;
	}
	else
	{
		std::cout << "ERROR: Incorrect data sent to swapEquippedItems" << std::endl;
	}
}
void Inventory::save(const std::string& filename) const {
	json j;
	for (const auto& item : backpackItems)
	{
		j["backpackItems"].push_back(item->toJson());
	}
	for (const auto& item : equippedItems)
	{
		j["equippedItems"].push_back(item->toJson());
	}
	std::ofstream out(filename);
	out << j.dump(4);
}

void Inventory::load(const std::string& filename)
{
	backpackItems.clear();
	equippedItems.clear();
	std::ifstream in(filename);
	json j;
	in >> j;

	for (const auto& item : j["backpackItems"])
	{
		backpackItems.push_back(Item::fromJson(item));
	}
	for (const auto& item : j["equippedItems"])
	{
		equippedItems.push_back(Item::fromJson(item));
	}
}

void Inventory::print() const
{
	std::cout << "Equipped Items: " << std::endl;
	for (const auto& item : equippedItems)
	{
		std::cout << item->name << std::endl;
	}
	std::cout << "Backpack Items: " << std::endl;
	for (const auto& item : backpackItems)
	{
		std::cout << item->name << std::endl;
	}
}