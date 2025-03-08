#ifndef Item_h
#define Item_h

#include <string>


class Item {
public:
	std::string name;
	std::string description;
	enum item_types { WEAPON, HOLYTOOL, ARCANETOOL, SHIELD, ARMOR, TRINKET, POTION, LOOT, LIGHT };
	enum weapon_types {
		NOTAWEAPON, DAGGER, STRAIGHTSWORD, GREATSWORD, FIST, MACE, GREATMACE,
		HATCHET, AXE, GREATAXE, THRUSTINGSWORD, SPEAR, GREATSPEAR,
		PARRYSHIELD, MEDIUMSHIELD, GREATSHIELD,
		LONGBOW, COMPOUNDBOW, GREATBOW, MINICROSSBOW, CROSSBOW, BALLISTA,
		TALISMAN, CHIME, TOME, WAND, STAFF, ORB
	};
	enum physical_damage_types { SLASH, BLUNT, PIERCE, NODAMAGE };
	enum magic_damage_types { FIRE, FROST, SHOCK, MAGIC, NATURE, SOUND, NOMAGICDAMAGE };
	enum equip_slots { HEAD, CHEST, LEGS, ARMS, AMULET, RING, MAINHAND1, MAINHAND2, OFFHAND1, OFFHAND2, BAREHAND, MISC, BACKPACK };
	item_types itemType;
	weapon_types weaponType;
	physical_damage_types physicalDamageType;
	magic_damage_types magicDamageType;
	equip_slots slot;
	int defense;
	int damage;
	int magicAdjust;
	int value;
	int weight;
	int quantity;
	bool twoHanded;
	bool needsAmmo;
	int reach;
	int attackSpeed;

	Item();
	Item(std::string name, std::string description, item_types itemType, weapon_types weaponType, physical_damage_types physicalDamageType,
		magic_damage_types magicDamageType, equip_slots slot, int defense, int damage, int magicAdjust, int value, int weight,
		int quantity, bool twoHanded, bool needsAmmo, int reach, int attackSpeed);
	~Item();
	//Functions to streamline item creation
	//Weapon
	Item createWeapon(std::string name, std::string description, int damage, int reach, int attackSpeed, int weight, int value, int quantity,
		bool twohanded, bool needsAmmo, Item::weapon_types weaponType, Item::physical_damage_types physType, Item::magic_damage_types magType,
		Item::equip_slots slot);
	
	//Armor
	Item createArmor(std::string name, std::string description, int defense, int weight, int value, int quantity, Item::equip_slots slot);
	
	//Tools
	Item createTool(std::string name, std::string description, Item::item_types toolType, int weight, int value, int quantity, int magicAdjust, Item::equip_slots slot);

	//Loot Items
	Item createLootItem(std::string name, std::string description, int value, int weight, int quantity);

	//Trinkets
	//Light Sources
};
#endif