#include "Inventory.h"
#include <vector>
#include <string>
#include <fstream>
#include "color.hpp"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"

nlohmann::json Inventory::toJson() const
{
	nlohmann::json j;
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
	for (const auto& item : j["backpackItems"])
	{
		backpackItems.push_back(Item::fromJson(item));
	}
	for (const auto& item : j["equippedItems"])
	{
		equippedItems.push_back(Item::fromJson(item));
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

void Inventory::addToBackpack(std::shared_ptr<Item> item)
{
	backpackItems.push_back(item);
}

void Inventory::addToEquippedItems(std::shared_ptr<Item> item)
{
	equippedItems.push_back(item);
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