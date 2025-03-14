#ifndef Item_h
#define Item_h

#include <string>


class Item {
public:
	bool hasBeenInitialized = false;
	std::string name = "ITEM NAME PLS CHANGE";
	std::string description = "ITEM DESCRIPTION PLS CHANGE";
	enum item_types { WEAPON, HOLYTOOL, ARCANETOOL, SHIELD, ARMOR, TRINKET, POTION, LOOT, LIGHT, AMMO, CONSUMABLE, THROWN};
	enum weapon_types {
		NOTAWEAPON, DAGGER, STRAIGHTSWORD, GREATSWORD, FIST, MACE, GREATMACE,
		HATCHET, AXE, GREATAXE, THRUSTINGSWORD, SPEAR, GREATSPEAR, HALBERD, POLEHAMMER, 
		PARRYSHIELD, MEDIUMSHIELD, GREATSHIELD,
		LONGBOW, COMPOUNDBOW, GREATBOW, MINICROSSBOW, CROSSBOW, BALLISTA,
		TALISMAN, CHIME, TOME, WAND, STAFF, ORB, ARROW, BOLT, GREATARROW, GREATBOLT
	};
	enum armor_types { NOTARMOR, LEATHER, PADDED, STUDDEDLEATHER, CHAIN, LAMELLAR, SCALE, CHAINPLATE, BEASTSCALE, FULLPLATE,  };
	enum physical_damage_types { SLASH, BLUNT, PIERCE, NODAMAGE };
	enum magic_damage_types { FIRE, FROST, SHOCK, MAGIC, NATURE, SOUND, NOMAGICDAMAGE };
	enum equip_slots { HEAD, CHEST, LEGS, ARMS, AMULET, RING1, RING2, MAINHAND1, MAINHAND2, OFFHAND1, OFFHAND2, BAREHAND, MISC, BACKPACK, QUIVER1, QUIVER2, QUIVER3, QUIVER4};
	enum consumable_effects { NOEFFECT, HEALTHRESTORE, MANARESTORE, MAXHEALTH, MAXMANA, STRENGTH, AGILITY, ARCANE, FAITH, LUCK, SPEED, CRITCHANCE, BLOCKCHANCE, DAMAGEREDUCTION, WEIGHTBURDEN};
	consumable_effects consumableEffect;
	armor_types armorType;
	item_types itemType;
	weapon_types weaponType;
	physical_damage_types physicalDamageType;
	magic_damage_types magicDamageType;
	equip_slots slot;
	float defense = 0.0f;
	float damage = 0.0f;
	float magnitude = 0.0f;
	float magicAdjust = 0.0f;
	float value = 0.0f;
	float weight = 0.0f;
	float quantity = 0.0f;
	bool twoHanded = false;
	bool needsAmmo = false;
	float reach = 0.0f;
	float attackSpeed = 0.0f;

	Item();
	Item(bool hasBeenInitialized, std::string name, std::string description, consumable_effects consumableEffect, item_types itemType, weapon_types weaponType, armor_types armorType, physical_damage_types physicalDamageType,
		magic_damage_types magicDamageType, equip_slots slot, float defense, float damage, float magnitude, float magicAdjust, float value, float weight,
		float quantity, bool twoHanded, bool needsAmmo, float reach, float attackSpeed);
	~Item();

	//Functions to streamline item creation
	//Weapon
	Item createWeapon(std::string name, std::string description, float damage, float reach, float attackSpeed, float weight, float value,
		bool twohanded, bool needsAmmo, Item::weapon_types weaponType, Item::physical_damage_types physType, Item::magic_damage_types magType);
	
	//Armor
	Item createArmor(std::string name, std::string description, Item::armor_types armorType, float defense, float weight, float value);
	
	//Tools
	Item createTool(std::string name, std::string description, Item::item_types toolType, Item::weapon_types weaponType, float weight, float value, float quantity, float magicAdjust);

	//Loot Items
	Item createLootItem(std::string name, std::string description, float value, float weight, float quantity);

	//Trinkets
	Item createJewelry(std::string name, std::string description, Item::item_types itemType, float value, float weight, float quantity);
	
	//Light Sources

	//Ammunition
	Item createAmmunition(std::string name, std::string description, float damage, float value, float weight, float quantity, float reach, Item::physical_damage_types damageType, Item::weapon_types ammoType);

	//Consumables

	Item createConsumable(std::string name, std::string description, float magnitude, float value, float weight, float quantity, Item::consumable_effects effect);
};

#endif // !Item_h