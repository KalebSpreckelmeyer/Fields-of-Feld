#include "Item.h"
#include <string>
Item::Item() {
	
}

Item::Item(std::string name, std::string description, item_types itemType, weapon_types weaponType, physical_damage_types physicalDamageType,
	magic_damage_types magicDamageType, equip_slots slot, int defense, int damage, int magicAdjust, int value, int weight,
	int quantity, bool twoHanded, bool needsAmmo, int reach, int attackSpeed)
{
	this->name = name;
	this->description = description;
	this->itemType = itemType;
	this->weaponType = weaponType;
	this->physicalDamageType = physicalDamageType;
	this->magicDamageType = magicDamageType;
	this->slot = slot;
	this->defense = defense;
	this->damage = damage;
	this->magicAdjust = magicAdjust;
	this->value = value;
	this->weight = weight;
	this->quantity = quantity;
	this->twoHanded = twoHanded; 
	this->needsAmmo = needsAmmo;
	this->reach = reach;
	this->attackSpeed = attackSpeed;
}

Item::~Item() {

}
Item Item::createWeapon(std::string name, std::string description, int damage, int reach, int attackSpeed, int weight, int value,
	bool twohanded, bool needsAmmo, Item::weapon_types weaponType, Item::physical_damage_types physType, Item::magic_damage_types magType)
{
	Item item;
	item.itemType = Item::WEAPON;
	item.name = name;
	item.description = description;
	item.damage = damage;
	item.reach = reach;
	item.attackSpeed = attackSpeed;
	item.weight = weight;
	item.value = value;
	item.quantity = 1;
	item.twoHanded = 1;
	item.needsAmmo = needsAmmo;
	item.weaponType = weaponType;
	item.physicalDamageType = physType;
	item.magicDamageType = magType;

	//Default values for values associated with non weapons
	item.defense = 0;
	item.magicAdjust = 0;
	item.slot = Item::BACKPACK;

	return item;
}

Item Item::createArmor(std::string name, std::string description, int defense, int weight, int value)
{
	Item item;
	item.itemType = Item::ARMOR;
	item.name = name;
	item.description = description;
	item.defense = defense;
	item.weight = weight;
	item.value = value;
	item.quantity = 1;

	//Default values for values associated with non armors

	item.attackSpeed = 0;
	item.damage = 0;
	item.magicAdjust = 0;
	item.magicDamageType = Item::NOMAGICDAMAGE;
	item.needsAmmo = false;
	item.physicalDamageType = Item::NODAMAGE;
	item.reach = 0;
	item.twoHanded = false;
	item.weaponType = Item::NOTAWEAPON;
	item.slot = Item::BACKPACK;


	return item;
}

Item Item::createTool(std::string name, std::string description, Item::item_types toolType, int weight, int value, int quantity, int magicAdjust)
{
	Item item;
	item.itemType = toolType;
	item.name = name;
	item.description = description;
	item.weight = weight;
	item.value = value;
	item.quantity = quantity;
	item.magicAdjust = magicAdjust;

	//Default values for values associated with non tools
	item.defense = 0;
	item.attackSpeed = 0;
	item.magicDamageType = Item::NOMAGICDAMAGE;
	item.needsAmmo = false;
	item.physicalDamageType = Item::NODAMAGE;
	item.reach = 0;
	item.twoHanded = false;
	item.weaponType = Item::NOTAWEAPON;
	item.slot = Item::BACKPACK;


	return item;
}

Item Item::createLootItem(std::string name, std::string description, int value, int weight, int quantity)
{
	Item item;
	item.itemType = Item::item_types::LOOT;
	item.name = name;
	item.description = description;
	item.value = value;
	item.weight = weight;
	item.quantity = quantity;
	item.slot = Item::BACKPACK;

	//Default values for non loot item values
	item.attackSpeed = 0;
	item.damage = 0;
	item.defense = 0;
	item.magicAdjust = 0;
	item.magicDamageType = Item::NOMAGICDAMAGE;
	item.needsAmmo = false;
	item.twoHanded = false;
	item.reach = 0;
	item.weaponType = Item::weapon_types::NOTAWEAPON;

	return item;
}