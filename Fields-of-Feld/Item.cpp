#include "Item.h"
#include <string>
Item::Item() {
	
}

Item::Item(bool hasBeenInitialized, std::string name, std::string description, consumable_effects consumableEffect, item_types itemType, weapon_types weaponType, armor_types armorType, physical_damage_types physicalDamageType,
	magic_damage_types magicDamageType, equip_slots slot, float defense, float damage, float magnitude, float magicAdjust, float value, float weight,
	float quantity, bool twoHanded, bool needsAmmo, float reach, float attackSpeed)
{
	this->hasBeenInitialized;
	this->name = name;
	this->description = description;
	this->itemType = itemType;
	this->weaponType = weaponType;
	this->armorType = armorType;
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

Item Item::createWeapon(std::string name, std::string description, float damage, float reach, float attackSpeed, float weight, float value,
	bool twohanded, bool needsAmmo, Item::weapon_types weaponType, Item::physical_damage_types physType, Item::magic_damage_types magType)
{
	Item item;
	item.hasBeenInitialized = true;
	item.itemType = Item::WEAPON;
	item.name = name;
	item.description = description;
	item.damage = damage;
	item.reach = reach;
	item.attackSpeed = attackSpeed;
	item.weight = weight;
	item.value = value;
	item.quantity = 1;
	item.twoHanded = twohanded;
	item.needsAmmo = needsAmmo;
	item.weaponType = weaponType;
	item.physicalDamageType = physType;
	item.magicDamageType = magType;

	//Default values for values associated with non weapons
	item.consumableEffect = Item::NOEFFECT;
	item.magnitude = 0;
	item.defense = 0;
	item.magicAdjust = 0;
	item.slot = Item::BACKPACK;

	return item;
}

Item Item::createArmor(std::string name, std::string description, Item::armor_types armorType, float defense, float weight, float value)
{
	Item item;
	item.hasBeenInitialized = true;
	item.itemType = Item::ARMOR;
	item.armorType = armorType;
	item.name = name;
	item.description = description;
	item.defense = defense;
	item.weight = weight;
	item.value = value;
	item.quantity = 1;

	//Default values for values associated with non armors

	item.consumableEffect = Item::NOEFFECT;
	item.magnitude = 0;
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

Item Item::createTool(std::string name, std::string description, Item::item_types toolType, Item::weapon_types weaponType, float weight, float value, float quantity, float magicAdjust)
{
	Item item;
	item.hasBeenInitialized = true;
	item.itemType = toolType;
	item.name = name;
	item.description = description;
	item.weight = weight;
	item.value = value;
	item.quantity = quantity;
	item.magicAdjust = magicAdjust;
	item.weaponType = weaponType;

	//Default values for values associated with non tools
	item.consumableEffect = Item::NOEFFECT;
	item.magnitude = 0;
	item.defense = 0;
	item.attackSpeed = 0;
	item.magicDamageType = Item::NOMAGICDAMAGE;
	item.needsAmmo = false;
	item.physicalDamageType = Item::NODAMAGE;
	item.reach = 0;
	item.twoHanded = false;
	item.slot = Item::BACKPACK;


	return item;
}

Item Item::createLootItem(std::string name, std::string description, float value, float weight, float quantity)
{
	Item item;
	item.hasBeenInitialized = true;
	item.itemType = Item::item_types::LOOT;
	item.name = name;
	item.description = description;
	item.value = value;
	item.weight = weight;
	item.quantity = quantity;
	item.slot = Item::BACKPACK;

	//Default values for non loot item values
	item.consumableEffect = Item::NOEFFECT;
	item.magnitude = 0;
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

Item Item::createJewelry(std::string name, std::string description, Item::item_types itemType, float value, float weight, float quantity)
{
	Item item;
	item.hasBeenInitialized = true;
	item.itemType = itemType;
	item.name = name;
	item.description = description;
	item.value = value;
	item.weight = weight;
	item.quantity = quantity;
	item.slot = Item::BACKPACK;

	//Default values for non loot item values
	item.consumableEffect = Item::NOEFFECT;
	item.magnitude = 0;
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

Item Item::createAmmunition(std::string name, std::string description, float damage, float value, float weight, float quantity, float reach, Item::physical_damage_types damageType, Item::weapon_types ammoType)
{
	Item ammo;
	ammo.name = name;
	ammo.description = description;
	ammo.damage = damage;
	ammo.value = value;
	ammo.weight = weight;
	ammo.quantity = quantity;
	ammo.reach = reach;
	ammo.physicalDamageType = damageType;
	ammo.weaponType = ammoType;
	ammo.hasBeenInitialized = true;
	
	//set default values
	ammo.consumableEffect = Item::NOEFFECT;
	ammo.magnitude = 0;
	ammo.attackSpeed = 0;
	ammo.defense = 0;
	ammo.magicAdjust = 0;
	ammo.magicDamageType = Item::NOMAGICDAMAGE;
	ammo.needsAmmo = false;
	ammo.twoHanded = false;
	ammo.itemType = Item::item_types::AMMO;
	ammo.slot = Item::BACKPACK;

	return ammo;
}

Item Item::createConsumable(std::string name, std::string description, float magnitude, float value, float weight, float quantity, Item::consumable_effects effect)
{
	Item consumable;
	consumable.name = name;
	consumable.description = description;
	consumable.magnitude = magnitude;
	consumable.value = value;
	consumable.weight = weight;
	consumable.quantity = quantity;
	consumable.hasBeenInitialized = true;
	consumable.itemType = Item::item_types::CONSUMABLE;
	consumable.slot = Item::BACKPACK;
	consumable.consumableEffect = effect;

	//set default values

	consumable.attackSpeed = 0;
	consumable.damage = 0;
	consumable.defense = 0;
	consumable.magicAdjust = 0;
	consumable.magicDamageType = Item::NOMAGICDAMAGE;
	consumable.needsAmmo = false;
	consumable.reach = 0;
	consumable.twoHanded = false;
	consumable.weaponType = Item::NOTAWEAPON;
	return consumable;
}