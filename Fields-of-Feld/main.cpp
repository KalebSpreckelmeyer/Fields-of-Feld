#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include "color.hpp"

using namespace std;


class Item {
public:
	string name;
	string description;
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
	Item(string name, string description, item_types itemType, weapon_types weaponType, physical_damage_types physicalDamageType,
		magic_damage_types magicDamageType, equip_slots slot, int defense, int damage, int magicAdjust, int value, int weight,
		int quantity, bool twoHanded, bool needsAmmo, int reach, int attackSpeed) :
		name(name), description(description), itemType(itemType), weaponType(weaponType), physicalDamageType(physicalDamageType),
		magicDamageType(magicDamageType), slot(slot), defense(defense), damage(damage), magicAdjust(magicAdjust), value(value), weight(weight),
		quantity(quantity), twoHanded(twoHanded), needsAmmo(needsAmmo), reach(reach), attackSpeed(attackSpeed)
	{
		if (defense < 0) {
			throw invalid_argument("Defense must be a positive integer");
		}
		if (damage < 0) {
			throw invalid_argument("Damage must be a positive integer");
		}
		if (magicAdjust < 0) {
			throw invalid_argument("Magic Adjustment must be a positive integer");
		}
		if (value < 0) {
			throw invalid_argument("Value must be a positive integer");
		}
		if (weight < 0) {
			throw invalid_argument("Weight must be a positive integer");
		}
		if (quantity < 0) {
			throw invalid_argument("Quantity must be a positive integer");
		}
		if (reach < 0) {
			throw invalid_argument("Reach must be a positive integer");
		}
		if (attackSpeed < 0) {
			throw invalid_argument("Attack Speed must be a positive integer");
		}
	}
	Item() = default;

	//Functions to streamline item creation
	//Weapon
	Item createWeapon(string name, string description, int damage, int reach, int attackSpeed, int weight, int value, int quantity,
		bool twohanded, bool needsAmmo, Item::weapon_types weaponType, Item::physical_damage_types physType, Item::magic_damage_types magType,
		Item::equip_slots slot)
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
		item.quantity = quantity;
		item.twoHanded = twohanded;
		item.needsAmmo = needsAmmo;
		item.weaponType = weaponType;
		item.physicalDamageType = physType;
		item.magicDamageType = magType;
		item.slot = slot;

		//Default values for values associated with non weapons
		item.defense = 0;
		item.magicAdjust = 0;

		return item;
	}
	//Armor
	Item createArmor(string name, string description, int defense, int weight, int value, int quantity, Item::equip_slots slot)
	{
		Item item;
		item.itemType = Item::ARMOR;
		item.name = name;
		item.description = description;
		item.defense = defense;
		item.weight = weight;
		item.value = value;
		item.quantity = quantity;
		item.slot = slot;

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

		return item;
	}
	//Tools
	Item createTool(string name, string description, Item::item_types toolType, int weight, int value, int quantity, int magicAdjust, Item::equip_slots slot)
	{
		Item item;
		item.itemType = toolType;
		item.name = name;
		item.description = description;
		item.weight = weight;
		item.value = value;
		item.quantity = quantity;
		item.magicAdjust = magicAdjust;
		item.slot = slot;

		//Default values for values associated with non tools
		item.defense = 0;
		item.attackSpeed = 0;
		item.magicDamageType = Item::NOMAGICDAMAGE;
		item.needsAmmo = false;
		item.physicalDamageType = Item::NODAMAGE;
		item.reach = 0;
		item.twoHanded = false;
		item.weaponType = Item::NOTAWEAPON;

		return item;
	}
	//Loot Items
	Item createLootItem(string name, string description, int value, int weight, int quantity)
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
	//Trinkets
	//Light Sources
};

class Potion : public Item {
public:
	string name;
	string description;
	int magnitude;
	int value;
	int weight;
	int quantity;
	enum effect { HEALING, MANA, STAMINA, CUREDISEASE };
	effect effects;

	Potion(string name, string description, int magnitude, int value, int weight, int quantity, enum effect effects) :
		name(name), magnitude(magnitude), value(value), weight(weight), quantity(quantity), effects(effects)
	{
		if (magnitude < 0) {
			throw invalid_argument("Magnitude must be a positive integer.");
		}
		if (value < 0) {
			throw invalid_argument("Value must be a positive integer");
		}
		if (weight < 0) {
			throw invalid_argument("Weight must be a positive integer");
		}
		if (quantity < 0) {
			throw invalid_argument("Quantity must be a positive integer");
		}
	}
	Potion() = default;
	//Potions
	Potion createPotion(string name, string description, int magnitude, int value, int weight, int quantity, Potion::effect effect)
	{
		Potion potion;
		potion.name = name;
		potion.description = description;
		potion.magnitude = magnitude;
		potion.value = value;
		potion.weight = weight;
		potion.quantity = quantity;
		potion.effects = effect;

		return potion;
	}
};

class Ammo {
public:
	string name;
	int damage;
	int weight;
	int quantity;

	Ammo(string name, int damage, int weight, int quantity) :
		name(name), damage(damage), weight(weight), quantity(quantity)
	{
		if (damage < 0) {
			throw invalid_argument("Damage must be a positive integer");
		}
		if (weight < 0) {
			throw invalid_argument("Weight must be a positive integer");
		}
		if (quantity < 0) {
			throw invalid_argument("Quantity must be a positive integer");
		}
	}
};

class Inventory {
public:
	//lootable items (from an enemy or container)
	vector<Item> lootItems;

	void addLootItems(Item& item)
	{
		lootItems.push_back(item);
	}

	Item lootOneItem(string itemName)
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

	vector<Item> lootAll(vector<Item> container)
	{
		vector<Item> items;
		for (int i = 0; i < items.size(); i++)
		{
			items.push_back(container[i]);
		}
		return items;
		//needs error handling 
	}

	//equipped items
	vector<Item> equippedItems;

	//retrieve and return all equipped items
	vector<Item> getEquippedItems() {
		vector<Item> items;
		for (int i = 0; i < equippedItems.size(); i++)
		{
			items.push_back(equippedItems[i]);
		}
		return items;
	}

	//equip an item to the relevant slot. It checks if the slot is used before adding it
	void equipItem(Item& item, Item::equip_slots slot) {
		//gets all equipped items to check if there is room to equip item
		vector<Item> items = getEquippedItems();

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
			cout << item.name << dye::light_yellow(" could not be equipped as the slot is full")
				<< endl;
		}
	}

	//Swaps equipped items with an item in the backpack
	void swapEquippedItem(Item& equippedItem, Item& itemToEquip, Item::equip_slots slot) {
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
		cout << equippedItem.name << dye::light_yellow(" swapped with ") << itemToEquip.name << endl;
	}

	//backpack
	vector<Item> backpackItems;
	void addItemToBackpack(const Item& item) {
		backpackItems.push_back(item);
	}

	void removeItem(const Item& item) {
		for (auto it = backpackItems.begin(); it != backpackItems.end(); ++it) {
			if (it->name == item.name) {
				backpackItems.erase(it);
				return;
			}
		}
		throw invalid_argument("Item not found");
	}
	void removeAllItems() {
		backpackItems.clear();
		equippedItems.clear();
	}
	void updateItemQuantity(const string& itemName, int newQuantity) {
		for (Item& item : backpackItems) {
			if (item.name == itemName) {
				item.quantity = newQuantity;
				return;
			}
		}
		throw invalid_argument("Item not found");
	}
	Item findItem(const string& itemName) {
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
		throw invalid_argument("Item not found");
	}

	//potions
	vector<Potion> potions;
	void addPotion(const Potion& potion) {
		potions.push_back(potion);
	}

	void removePotion(const Potion& potion)
	{
		for (auto it = potions.begin(); it != potions.end(); ++it) {
			if (it->name == potion.name) {
				potions.erase(it);
				return;
			}
		}
		throw invalid_argument("Item not found");

	}
	Potion& findPotion(const string& potionName) {
		for (Potion& potion : potions) {
			if (potion.name == potionName) {
				return potion;
			}
		}
		throw invalid_argument("Item not found");
	}

	void updatePotionQuantity(const string& potionName, int newQuantity) {
		for (Potion& potion : potions) {
			if (potion.name == potionName) {
				potion.quantity = newQuantity;
				return;
			}
		}
		throw invalid_argument("Item not found");
	}
	//ammunition
	vector<Ammo> munitions;
	void addAmmo(const Ammo& ammo) {
		munitions.push_back(ammo);
	}

	void removeAmmo(const Ammo& ammo)
	{
		for (auto it = munitions.begin(); it != munitions.end(); ++it) {
			if (it->name == ammo.name) {
				munitions.erase(it);
				return;
			}
		}
		throw invalid_argument("Item not found");

	}
	Ammo& findAmmo(const string& ammoName) {
		for (Ammo& ammo : munitions) {
			if (ammo.name == ammoName) {
				return ammo;
			}
		}
		throw invalid_argument("Item not found");
	}

	void updateAmmoQuantity(const string& ammoName, int newQuantity) {
		for (Ammo& ammo : munitions) {
			if (ammo.name == ammoName) {
				ammo.quantity = newQuantity;
				return;
			}
		}
		throw invalid_argument("Item not found");
	}
#pragma region printInventory
	void printEquippedItems() {
		int tally;
		cout << dye::light_yellow("->Weapon(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::WEAPON)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Damage: ") << item.damage << endl;
				cout << dye::light_yellow("  Attack Speed: ") << item.attackSpeed << endl;
				cout << dye::light_yellow("  Reach: ") << item.reach << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				if (item.physicalDamageType == Item::BLUNT)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << endl;
				}
				if (item.physicalDamageType == Item::SLASH)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << endl;
				}
				if (item.physicalDamageType == Item::PIERCE)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << endl;
				}

				if (item.magicDamageType == Item::FIRE)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << endl;
				}
				if (item.magicDamageType == Item::FROST)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << endl;
				}
				if (item.magicDamageType == Item::SHOCK)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << endl;
				}
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Armor(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::ARMOR)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Defense: ") << item.defense << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				if (item.slot == Item::HEAD)
				{
					cout << dye::light_yellow("  Item type: ") << "Helmet" << endl;
				}
				if (item.slot == Item::CHEST)
				{
					cout << dye::light_yellow("  Item type: ") << "Cuirass" << endl;
				}
				if (item.slot == Item::ARMS)
				{
					cout << dye::light_yellow("  Item type: ") << "Gauntlets" << endl;
				}

				if (item.slot == Item::LEGS)
				{
					cout << dye::light_yellow("  Item type: ") << "Leggings" << endl;
				}
				if (item.slot == Item::AMULET)
				{
					cout << dye::light_yellow("  Item type: ") << "Amulet" << endl;
				}
				if (item.slot == Item::TRINKET)
				{
					cout << dye::light_yellow("  Item type: ") << "Trinket" << endl;
				}
				if (item.slot == Item::RING)
				{
					cout << dye::light_yellow("  Item type: ") << "Ring" << endl;
				}
				if (item.slot == Item::MISC)
				{
					cout << dye::light_yellow("  Item type: ") << "Miscellaneous" << endl;
				}
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Shield(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::SHIELD)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Defense: ") << item.defense << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Damage: ") << item.damage << endl;
				cout << dye::light_yellow("  Block chance: ") << "TODO" << "%" << endl;
				if (item.physicalDamageType == Item::BLUNT)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << endl;
				}
				if (item.physicalDamageType == Item::SLASH)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << endl;
				}
				if (item.physicalDamageType == Item::PIERCE)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << endl;
				}

				if (item.magicDamageType == Item::FIRE)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << endl;
				}
				if (item.magicDamageType == Item::FROST)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << endl;
				}
				if (item.magicDamageType == Item::SHOCK)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << endl;
				}
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Arcane Casting Tools(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::ARCANETOOL)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << endl;
				cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Holy Casting Tools(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::HOLYTOOL)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Trinket(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::TRINKET)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Light Source(s): ") << endl;
		tally = 1;
		for (Item& item : equippedItems) {
			if (item.itemType == Item::LIGHT)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
	}
	void printBackpack()
	{
		int tally;
		cout << dye::light_yellow("->Weapon(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::WEAPON)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Damage: ") << item.damage << endl;
				cout << dye::light_yellow("  Attack Speed: ") << item.attackSpeed << endl;
				cout << dye::light_yellow("  Reach: ") << item.reach << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				if (item.physicalDamageType == Item::BLUNT)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << endl;
				}
				if (item.physicalDamageType == Item::SLASH)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << endl;
				}
				if (item.physicalDamageType == Item::PIERCE)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << endl;
				}

				if (item.magicDamageType == Item::FIRE)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << endl;
				}
				if (item.magicDamageType == Item::FROST)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << endl;
				}
				if (item.magicDamageType == Item::SHOCK)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << endl;
				}
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Armor(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::ARMOR)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Defense: ") << item.defense << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				if (item.slot == Item::HEAD)
				{
					cout << dye::light_yellow("  Item type: ") << "Helmet" << endl;
				}
				if (item.slot == Item::CHEST)
				{
					cout << dye::light_yellow("  Item type: ") << "Cuirass" << endl;
				}
				if (item.slot == Item::ARMS)
				{
					cout << dye::light_yellow("  Item type: ") << "Gauntlets" << endl;
				}

				if (item.slot == Item::LEGS)
				{
					cout << dye::light_yellow("  Item type: ") << "Leggings" << endl;
				}
				if (item.slot == Item::AMULET)
				{
					cout << dye::light_yellow("  Item type: ") << "Amulet" << endl;
				}
				if (item.slot == Item::TRINKET)
				{
					cout << dye::light_yellow("  Item type: ") << "Trinket" << endl;
				}
				if (item.slot == Item::RING)
				{
					cout << dye::light_yellow("  Item type: ") << "Ring" << endl;
				}
				if (item.slot == Item::MISC)
				{
					cout << dye::light_yellow("  Item type: ") << "Miscellaneous" << endl;
				}
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Shield(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::SHIELD)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Defense: ") << item.defense << endl;
				cout << dye::light_yellow("  Damage: ") << item.damage << endl;
				cout << dye::light_yellow("  Block chance: ") << "TODO" << "%" << endl;
				if (item.physicalDamageType == Item::BLUNT)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Blunt" << endl;
				}
				if (item.physicalDamageType == Item::SLASH)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Slash" << endl;
				}
				if (item.physicalDamageType == Item::PIERCE)
				{
					cout << dye::light_yellow("  Physical Damage Type: ") << "Pierce" << endl;
				}

				if (item.magicDamageType == Item::FIRE)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Fire" << endl;
				}
				if (item.magicDamageType == Item::FROST)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Frost" << endl;
				}
				if (item.magicDamageType == Item::SHOCK)
				{
					cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << endl;
				}
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Arcane Casting Tools(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::ARCANETOOL)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << endl;
				cout << dye::light_yellow("  Magic Damage Type: ") << "Shock" << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Holy Casting Tools(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::HOLYTOOL)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Magic Scaling: ") << item.magicAdjust << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Potion(s): ") << endl;
		tally = 1;
		for (Potion& potion : potions) {
			cout << dye::light_yellow("  Name: ") << potion.name << endl;
			cout << dye::light_yellow("  Weight: ") << potion.weight << endl;
			if (potion.effects == Potion::HEALING)
			{
				cout << dye::light_yellow("  Potion Effect") << " Healing" << endl;
			}
			cout << dye::light_yellow("  Magnitude: ") << potion.magnitude << endl;
			cout << dye::light_yellow("  Quantity: ") << potion.quantity << endl;
			cout << dye::light_yellow("  Value: ") << potion.value << endl;
			cout << "\n";
			tally += 1;
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Trinket(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::TRINKET)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Light Source(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::LIGHT)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
		cout << dye::light_yellow("->Loot Item(s): ") << endl;
		tally = 1;
		for (Item& item : backpackItems) {
			if (item.itemType == Item::LOOT)
			{
				cout << dye::light_yellow("  Name: ") << item.name << endl;
				cout << dye::light_yellow("  Weight: ") << item.weight << endl;
				cout << dye::light_yellow("  Quantity: ") << item.quantity << endl;
				cout << dye::light_yellow("  Value: ") << item.value << endl;
				cout << "\n";
				tally += 1;
			}
		}
		if (tally == 1)
		{
			cout << dye::light_yellow("  None") << endl;
		}
	}
#pragma endregion printInventory
};

class Character
{
public:
	bool active;
	enum classChoice { DEFAULT, WIZARD, KNIGHT, CLERIC, HUNTER, HIGHLANDER, BATTLEMAGE, WRETCH };
	classChoice classChoice;
	string characterClass;

	//Core Attributes
	int health;
	int mana;
	int stamina;
	int strength;
	int agility;
	int arcane;
	int faith;
	int luck;

	//Derived Attributes
	int healthPoints;
	int maxHealthPoints;
	int manaPoints;
	int maxManaPoints;
	int staminaPoints;
	int maxStaminaPoints;
	int speed;

	//Derived Stats
	int critChance;
	int dodgeChance;
	int blockChance;
	int blockAmount;
	int damageReduction;

	int level;
	int experience;
	int experienceToNextLevel;
	int gold;

	Inventory inventory;

	//Enemy Specific Stats
	int distanceFromPlayer;
	bool alert;

	Character(bool active, enum classChoice classChoice, string characterClass, int health, int mana, int stamina, int strength, int agility, int arcane, int faith, int luck, int healthPoints, int maxHealthPoints,
		int manaPoints, int maxManaPoints, int staminaPoints, int maxStaminaPoints, int speed, int critChance, int dodgeChance, int blockChance, int blockAmount, int damageReduction, int level, int experience, int experienceToNextLevel,
		int gold, Inventory inventory, int distanceFromPlayer, bool alert)
		: active(active), classChoice(classChoice), characterClass(characterClass), health(health), mana(mana), stamina(stamina), strength(strength), agility(agility), arcane(arcane), faith(faith), luck(luck),
		healthPoints(healthPoints), maxHealthPoints(maxHealthPoints), manaPoints(manaPoints), maxManaPoints(maxManaPoints), staminaPoints(staminaPoints), maxStaminaPoints(maxStaminaPoints), speed(speed),
		critChance(critChance), dodgeChance(dodgeChance), blockChance(blockChance), blockAmount(blockAmount), damageReduction(damageReduction), level(level), experience(experience), experienceToNextLevel(experienceToNextLevel), gold(gold),
		inventory(inventory), distanceFromPlayer(distanceFromPlayer), alert(alert)
	{

	}
	Character() = default;
	void setCharacterClass(enum classChoice option)
	{
		switch (option)
		{
		case WIZARD:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Wizard";
			health = 10;
			mana = 20;
			stamina = 7;
			strength = 7;
			agility = 7;
			arcane = 20;
			faith = 1;
			luck = 10;
			level = 1;
			//Mainhand default 1
			Item startingSword = (Item("Weathered Arming Sword", "A short blade that could use a good sharpening",
				Item::WEAPON, Item::STRAIGHTSWORD, Item::SLASH, Item::NOMAGICDAMAGE, Item::MAINHAND1, 0, 8, 0, 10, 1, 1, false, false, 7, 11));
			//Offhand default 1
			Item startingWand = (Item("Oak Wand", "A basic wooden wand barely capable of casting magic",
				Item::ARCANETOOL, Item::WAND, Item::BLUNT, Item::MAGIC, Item::OFFHAND1, 0, 1, 20, 20, 1, 1, false, false, 1, 10));
			//Offhand default 2
			Item startingShield = (Item("Plank Shield", "A small shield composed of several thin oak boards",
				Item::SHIELD, Item::MEDIUMSHIELD, Item::BLUNT, Item::NOMAGICDAMAGE, Item::OFFHAND2, 5, 2, 0, 10, 2, 1, false, false, 2, 3));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NOMAGICDAMAGE, Item::BAREHAND,
				0, 1, 0, 0, 0, 1, false, false, 3, 10);
			inventory.equipItem(startingSword, Item::MAINHAND1);
			inventory.equipItem(startingWand, Item::OFFHAND1);
			inventory.equipItem(startingShield, Item::OFFHAND2);
			inventory.addItemToBackpack(fists);
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		case BATTLEMAGE:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Battle Mage";
			health = 16;
			mana = 10;
			stamina = 10;
			strength = 10;
			agility = 10;
			arcane = 15;
			faith = 1;
			luck = 10;
			level = 1;
			//Mainhand default 1
			Item startingAxe = (Item("Weathered Hand Axe", "An weathered axe of moderate size",
				Item::WEAPON, Item::AXE, Item::SLASH, Item::NOMAGICDAMAGE, Item::MAINHAND1, 0, 12, 0, 5, 4, 1, false, false, 11, 8));
			//Offhand default 1
			Item startingWand = (Item("Oak Wand", "A basic wooden wand barely capable of casting magic",
				Item::ARCANETOOL, Item::WAND, Item::BLUNT, Item::MAGIC, Item::OFFHAND1, 0, 1, 20, 20, 1, 1, false, false, 1, 10));
			//Offhand default 2
			Item startingShield = (Item("Sturdy Plank Shield", "A small shield composed of several thick oak boards bound together by rivets",
				Item::SHIELD, Item::MEDIUMSHIELD, Item::BLUNT, Item::NOMAGICDAMAGE, Item::OFFHAND2, 10, 2, 0, 5, 2, 1, false, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NOMAGICDAMAGE, Item::BAREHAND,
				0, 1, 0, 0, 0, 1, false, false, 3, 10);
			inventory.equipItem(startingAxe, Item::MAINHAND1);
			inventory.equipItem(startingWand, Item::MAINHAND2);
			inventory.equipItem(startingShield, Item::OFFHAND1);
			inventory.addItemToBackpack(fists);
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		case KNIGHT:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Knight";
			health = 16;
			mana = 5;
			stamina = 15;
			strength = 16;
			agility = 10;
			arcane = 5;
			faith = 5;
			luck = 10;
			level = 1;
			//Mainhand default 1
			Item startingSword = (Item("Weathered Longsword", "A long blade that has seen a good amount of combat",
				Item::WEAPON, Item::STRAIGHTSWORD, Item::SLASH, Item::NOMAGICDAMAGE, Item::MAINHAND1, 0, 10, 0, 5, 1, 1, false, false, 6, 10));
			//Offhand default 1
			Item startingShield = (Item("Weathered Kite Shield", "A basic metal shield emblazened with a crest so faded it can't be made out",
				Item::SHIELD, Item::MEDIUMSHIELD, Item::BLUNT, Item::NOMAGICDAMAGE, Item::OFFHAND1, 15, 2, 0, 5, 1, 1, false, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NOMAGICDAMAGE, Item::BAREHAND,
				0, 1, 0, 0, 0, 1, false, false, 3, 10);
			inventory.equipItem(startingSword, Item::MAINHAND1);
			inventory.equipItem(startingShield, Item::OFFHAND1);
			inventory.addItemToBackpack(fists);
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		case CLERIC:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Cleric";
			health = 10;
			mana = 15;
			stamina = 10;
			strength = 10;
			agility = 5;
			arcane = 2;
			faith = 20;
			luck = 10;
			level = 1;
			//Mainhand default 1
			Item startingMace = (Item("Weathered Mace", "A hefty mace that, although weathered, could still crack a skull or two",
				Item::WEAPON, Item::MACE, Item::BLUNT, Item::NOMAGICDAMAGE, Item::MAINHAND1, 0, 15, 0, 5, 3, 1, false, false, 5, 7));
			//Offhand default 1
			Item startingTalisman = (Item("Tarnished Talisman", "A basic talisman that cannels ones faith and allows the casting of miracles",
				Item::HOLYTOOL, Item::TALISMAN, Item::BLUNT, Item::NOMAGICDAMAGE, Item::OFFHAND1, 0, 2, 20, 20, 1, 1, false, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NOMAGICDAMAGE, Item::BAREHAND,
				0, 1, 0, 0, 0, 1, false, false, 3, 10);
			inventory.equipItem(startingMace, Item::MAINHAND1);
			inventory.equipItem(startingTalisman, Item::OFFHAND1);
			inventory.addItemToBackpack(fists);
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		case HUNTER:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Hunter";
			health = 10;
			mana = 5;
			stamina = 15;
			strength = 7;
			agility = 20;
			arcane = 10;
			faith = 5;
			luck = 10;
			level = 1;
			//Mainhand default 1	
			Item startingSword = (Item("Weathered Dagger", "A short blade mostly used for gutting fish and harvesting animal skins. It could stand to be sharpened",
				Item::WEAPON, Item::DAGGER, Item::SLASH, Item::NOMAGICDAMAGE, Item::MAINHAND1, 0, 5, 0, 10, 1, 1, false, false, 2, 15));
			//Offhand default 1
			Item startingBow = (Item("Hunting Bow", "A basic wooden bow of average build",
				Item::WEAPON, Item::LONGBOW, Item::PIERCE, Item::NOMAGICDAMAGE, Item::OFFHAND1, 0, 10, 0, 10, 4, 1, false, true, 40, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NOMAGICDAMAGE, Item::BAREHAND,
				0, 1, 0, 0, 0, 1, false, false, 3, 10);
			inventory.equipItem(startingSword, Item::MAINHAND1);
			inventory.equipItem(startingBow, Item::MAINHAND2);
			inventory.addItemToBackpack(fists);
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		case HIGHLANDER:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Highlander";
			health = 15;
			mana = 3;
			stamina = 15;
			strength = 17;
			agility = 16;
			arcane = 3;
			faith = 3;
			luck = 10;
			level = 1;

			Item startingSword = (Item("Iron Claymore", "A massive blade that requires ample strength and two hands to wield. Typically used to cleave through horses it will makes short work of a man",
				Item::WEAPON, Item::GREATSWORD, Item::SLASH, Item::NOMAGICDAMAGE, Item::MAINHAND1, 0, 25, 0, 30, 10, 1, true, false, 15, 5));
			inventory.equipItem(startingSword, Item::MAINHAND1);
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NOMAGICDAMAGE, Item::BAREHAND,
				0, 1, 0, 0, 0, 1, false, false, 3, 10);
			inventory.addItemToBackpack(fists);
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		case WRETCH:
		{
			//clears items in case of a respec
			inventory.removeAllItems();

			active = true;
			characterClass = "Wretch";
			health = 1;
			mana = 1;
			stamina = 1;
			strength = 1;
			agility = 1;
			arcane = 1;
			faith = 1;
			luck = 1;
			level = 1;
			vector<Item> items = this->inventory.getEquippedItems();
			refreshCharacterStats(items);
			break;
		}
		default:
			cout << "Invalid class choice" << endl;
			break;
		}
	}

	//called when the player stats need to be refreshed, either when first initializing them or when they level up
	void refreshCharacterStats(vector<Item> items) {
		experienceToNextLevel = level * 100;
		maxHealthPoints = (health * 10) + (strength * 2);
		healthPoints = maxHealthPoints;
		//sets mana points to mainly rely on the mana stat, with bonuses from arcane or faith depending on which is higher.
		//    the smaller of the two will still give a smaller bonus. If they're equal, they both contribute equally at a slightly reduced value.
		if (arcane > faith)
		{
			maxManaPoints = (mana * 10) + (arcane * 2) + (faith * 1);
		}
		else if (arcane < faith)
		{
			maxManaPoints = (mana * 10) + (faith * 2) + (arcane * 1);
		}
		else if (arcane == faith)
		{
			maxManaPoints = (mana * 10) + (faith * 1.5) + (arcane * 1.5);
		}
		manaPoints = maxManaPoints;
		maxStaminaPoints = (stamina * 10) + (strength * 2);
		staminaPoints = maxStaminaPoints;

		//this will be rolled against a random number between 1-100, if the random number wins it will not be a crit. If it does win, it will be a crit
		//set to -9 at first so each class will start with 1 crit chance
		(critChance >= 50) ? critChance = 50 : critChance = critChance;
		critChance = -9 + luck * 1 + agility * 0.1;

		//iterates through all items in the player's equipped inventory and adds their equipment weights together for calculations
		int equipmentWeight = 0;
		for (int i = 0; i < items.size(); i++)
		{
			equipmentWeight += items[i].weight;
		}
		speed = (agility * 10) + (strength * 5) + (stamina * 2) - equipmentWeight;

		dodgeChance = (agility * 0.5) + (speed / 100);
		(dodgeChance >= 50) ? dodgeChance = 50 : dodgeChance = dodgeChance - (equipmentWeight / 100);

		int armorValue = 0;
		for (int i = 0; i < items.size(); i++)
		{
			armorValue += items[i].defense;
		}
		damageReduction = armorValue / (armorValue + 100);
	}

	void takeDamage(int damage)
	{
		healthPoints -= damage;
		if (healthPoints < 0) {
			healthPoints = 0;
			//add function to handle character death
		}
	}

	void receiveHealing(int healing)
	{
		healthPoints += healing;
		if (healthPoints > maxHealthPoints) {
			healthPoints = maxHealthPoints;
		}
	}

	//Gets the weapon in the main hand. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getMainWeapon1(Character& character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.backpackItems.size(); i++)
		{
			if (character.inventory.backpackItems[i].itemType == Item::MAINHAND1)
			{
				bool found = true;
				return character.inventory.backpackItems[i];
			}
		}
		cout << " No mainhand weapon 1 found" << endl;
	}
	//Gets the weapon in the main hand 2. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getMainWeapon2(Character& character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.backpackItems.size(); i++)
		{
			if (character.inventory.backpackItems[i].itemType == Item::MAINHAND2)
			{
				bool found = true;
				return character.inventory.backpackItems[i];
			}
		}
		cout << " No mainhand weapon 2 found" << endl;
	}
	//Gets the weapon in the off hand. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getOffhandWeapon1(Character& character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.backpackItems.size(); i++)
		{
			if (character.inventory.backpackItems[i].itemType == Item::OFFHAND1)
			{
				bool found = true;
				return character.inventory.backpackItems[i];
			}
		}
		cout << " No offhand weapon 1 found" << endl;
	}
	//Gets the weapon in the off hand 2. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getOffhandWeapon2(Character& character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.backpackItems.size(); i++)
		{
			if (character.inventory.backpackItems[i].itemType == Item::OFFHAND2)
			{
				bool found = true;
				return character.inventory.backpackItems[i];
			}
		}
		cout << " No offhand weapon 2 found" << endl;
	}

	void printCharacterStats(Character& character)
	{
		cout << dye::light_yellow("  Class: ") << character.characterClass << endl;
		cout << dye::light_yellow("  Health Points: ") << character.healthPoints << "/" << character.maxHealthPoints << endl;
		cout << dye::light_yellow("  Stamina Points: ") << character.staminaPoints << "/" << character.maxStaminaPoints << endl;
		cout << dye::light_yellow("  Mana Points: ") << character.manaPoints << "/" << character.maxManaPoints << endl;
		cout << "\n";
		cout << dye::light_yellow("  Health: ") << character.health << endl;
		cout << dye::light_yellow("  Mana: ") << character.mana << endl;
		cout << dye::light_yellow("  Stamina: ") << character.stamina << endl;
		cout << dye::light_yellow("  Strength: ") << character.strength << endl;
		cout << dye::light_yellow("  Agility: ") << character.agility << endl;
		cout << dye::light_yellow("  Arcane: ") << character.arcane << endl;
		cout << dye::light_yellow("  Faith: ") << character.faith << endl;
		cout << dye::light_yellow("  Luck: ") << character.luck << endl;
		cout << "\n";
		cout << dye::light_yellow("  Speed: ") << character.speed << endl;
		cout << dye::light_yellow("  Damage Reduction: ") << character.damageReduction << "%" << endl;
		//under construction below
		cout << dye::light_yellow("  Critical Chance: ") << character.critChance << "%" << endl;
		cout << dye::light_yellow("  Dodge Chance: ") << character.dodgeChance << "%" << endl;
		cout << dye::light_yellow("  Block Chance: ") << character.blockChance << "%" << endl;
		cout << dye::light_yellow("  Block Amount: ") << character.blockAmount << endl;
		cout << "\n";
		cout << dye::light_yellow("  Level: ") << character.level << endl;
		cout << dye::light_yellow("  Experience: ") << character.experience << "/" << character.experienceToNextLevel << endl;
		cout << "\n";
		cout << dye::light_yellow("  Gold: ") << character.gold << endl;
	}

	//Enemy Specifc Functions
	void createEnemy(string name, string description, int healthPoints, int staminaPoints, int manaPoints, int speed, int reach, int critChance,
		int dodgeChance, int blockChance, int blockAmount, int damageReduction, int level)
	{
		name = name;
		description = description;
		healthPoints = healthPoints;
		maxHealthPoints = healthPoints;
		staminaPoints = staminaPoints;
		maxStaminaPoints = staminaPoints;
		manaPoints = manaPoints;
		maxManaPoints = manaPoints;
		speed = speed;
		reach = reach;
		critChance = critChance;
		dodgeChance = dodgeChance;
		blockChance = blockChance;
		blockAmount = blockAmount;
		damageReduction = damageReduction;
		level = level;
	}
	void addItemToEnemy(Character enemy, Item item, Item::equip_slots slot)
	{

	}

	void drinkPotion(Potion& potion) {
		if (potion.effects == Potion::HEALING) {
			if (this->healthPoints == this->maxHealthPoints) {
				cout << dye::light_yellow("You are already at full health and did not consume the potion.") << endl;
			}
			else {
				this->receiveHealing(potion.magnitude);
				if (potion.quantity == 1) {
					this->inventory.removePotion(potion);
				}
				else {
					this->inventory.updatePotionQuantity(potion.name, potion.quantity - 1);
				}
				cout << potion.name << " consumed, " << potion.magnitude << " points of healing administered." << endl;
			}
		}
		else
		{
			cout << "Invalid potion" << endl;
		}
	}

	void sellItem(Item& item) {
		cout << "Are you sure you want to sell this " << item.name << " for " << item.value << " gold pieces?" << endl;
		cout << "1 = Yes, 2 = No" << endl;
		int choice;
		do
		{
			cout << ">> ";
			cin >> choice;
			if (cin.fail() || choice > 5 || choice == 0)
			{
				cout << "Enter a number from 1 - 2" << endl;
			}
			cin.clear();
			cin.ignore(10000, '\n');
		} while (cin.fail() || choice > 5 || choice == 0);
		if (choice == 1)
		{
			if (item.quantity == 1)
			{
				this->inventory.removeItem(item);
				this->gold += item.value;
				cout << item.name << " sold for " << item.value << " gold pieces!" << endl;
			}
			else {
				item.quantity -= 1;
				this->gold += item.value;
				cout << item.name << " sold for " << item.value << " gold pieces!" << endl;
			}
		}
		else {
			cout << "Item not sold" << endl;
		}
	}
};

#pragma region Function Declarations
//DESC: Prints the main menu and takes in user input to determine what to do next
// PRE: None
// POST: Returns a character object with the selected class
void printMainMenu(Character character);
//DESC: Starts a combat encounter and prints the relevant menus
//PRE: Player and Enemy Characters must be initialized
//POST: Player values will be updated depending on the results of the battle
void printMainCombatMenu(Character player, Character enemy);
//DESC: Takes in a character and prints their health, stamina, or mana respectively as a bar
//PRE: Character object must be initialized first with setCharacterClass() in order to have a health/mana/stamina value
//POST: Prints health, stamina, or mana bar to console
void printHealthBar(Character player);
void printStaminaBar(Character player);
void printManaBar(Character player);
//DESC: Calls all 3 bar functions 
//PRE: None
//POST: All 3 will be printed to console
void printAllBars(Character character);
//DESC: Opens up the shop interface 
//PRE: Character should be initialized first
//POST: Modifies the character's inventory or gold value based on interactions within the shop
void openShop(Character& character);

#pragma endregion Function Declarations

int main()
{
	Character player;;
	printMainMenu(player);

	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> distribution(1, 100);
	int randomNum = distribution(generator);
	return 0;
}

void printMainMenu(Character character)
{
	//Initialize all classes so they can be printed 
	Character wizard;
	wizard.setCharacterClass(Character::WIZARD);
	Character battleMage;
	battleMage.setCharacterClass(Character::BATTLEMAGE);
	Character knight;
	knight.setCharacterClass(Character::KNIGHT);
	Character cleric;
	cleric.setCharacterClass(Character::CLERIC);
	Character hunter;
	hunter.setCharacterClass(Character::HUNTER);
	Character highlander;
	highlander.setCharacterClass(Character::HIGHLANDER);
	Character wretch;
	wretch.setCharacterClass(Character::WRETCH);
	//TODO: Make the buttons grey out if unselectable
	int choice;
	do
	{
		cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
			<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
			<< dye::bright_white(" |   1) Continue     |   |   2) New Game     |   | 3) View Inventory |   | 4) View Character |   |      5) Exit      |  ") << endl
			<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
			<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;


		//input validation
		do
		{
			cout << ">> ";
			cin >> choice;
			if (cin.fail() || choice > 5 || choice == 0)
			{
				cout << "Enter a number from 1 - 5" << endl;
			}
			cin.clear();
			cin.ignore(10000, '\n');
		} while (cin.fail() || choice > 5 || choice == 0);
		switch (choice)
		{
		case 1:
		{
			//Continue
			if (character.active == true)
			{
				//for now this adds items to the selected character for testing		
				Item goblet = goblet.createLootItem("Fine Gold Goblet", "A golden goblet inlaid with emeralds. Will fetch a nice price.", 100, 1, 1);
				character.inventory.addItemToBackpack(goblet);
				openShop(character);
				break;
			}
			else
			{
				cout << "  No save file found" << endl;
				break;
			}
		}
		case 2:
		{
			//New Game
			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |  6) The Wizard    |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;

			wizard.printCharacterStats(wizard);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" | 5) The Battlemage |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			battleMage.printCharacterStats(battleMage);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |   4) The Knight   |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			knight.printCharacterStats(knight);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |   3) The Cleric   |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			cleric.printCharacterStats(cleric);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |   2) The Hunter   |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			hunter.printCharacterStats(hunter);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" | 1) The Highlander |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			highlander.printCharacterStats(highlander);

			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::light_yellow(" =-------------------=---=-------------------=---=-------------------=---=-------------------=---=-------------------=  ") << endl
				<< dye::bright_white(" |                                                 Select Your Class                                                 |  ") << endl
				<< dye::light_yellow(" =-------------------=---=-------------------=---=-------------------=---=-------------------=---=-------------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;


			int classChoice;
			//input validation
			do
			{
				cout << ">> ";
				cin >> classChoice;
				if (cin.fail() || classChoice > 7 || classChoice == 0)
				{
					cout << "Enter a number from 1 - 7" << endl;
				}
				cin.clear();
				cin.ignore(10000, '\n');
			} while (cin.fail() || classChoice > 7 || classChoice == 0);

			switch (classChoice)
			{
			case 1:
				character.setCharacterClass(Character::HIGHLANDER);
				break;
			case 2:
				character.setCharacterClass(Character::HUNTER);
				break;
			case 3:
				character.setCharacterClass(Character::CLERIC);
				break;
			case 4:
				character.setCharacterClass(Character::KNIGHT);
				break;
			case 5:
				character.setCharacterClass(Character::BATTLEMAGE);

				break;
			case 6:
				character.setCharacterClass(Character::WIZARD);
				break;
			case 7:
				character.setCharacterClass(Character::WRETCH);
				//Return to main menu for now
				break;
			case 8:
				//Return to main menu for now
				break;
			}
			break;
		}
		case 3:
			if (character.active == true)
			{
				cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
					<< dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
					<< dye::bright_white(" |   1) View Equipped Items   |              |   2) View Backpack Items  |              |         3) Go back         |  ") << endl
					<< dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
					<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

				int inventoryChoice;
				do
				{
					cout << ">> ";
					cin >> inventoryChoice;
					if (cin.fail() || inventoryChoice > 3 || inventoryChoice == 0)
					{
						cout << "Enter a number from 1 - 3" << endl;
					}
					cin.clear();
					cin.ignore(10000, '\n');
				} while (cin.fail() || inventoryChoice > 3 || inventoryChoice == 0);
				switch (inventoryChoice)
				{
				case 1:
				{
					character.inventory.printEquippedItems();
					break;
				}
				case 2:
				{
					character.inventory.printBackpack();
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					cout << "  Enter a number between 1 - 3" << endl;
					break;
				}
				}
			}
			else
			{
				cout << "  No save file found" << endl;
				break;
			}
			break;
		case 4:
			//Inspect Character Stats
			if (character.active == true)
			{
				character.printCharacterStats(character);
			}
			else
			{
				cout << "  No save file found" << endl;
				break;
			}
			break;
			break;
		case 5:
		{
			//Exit
			break;
		}
		}
	} while (choice != 5);
}

void openShop(Character& character)
{
	cout << dye::yellow(" Shopkeep:") << endl;
	cout << dye::light_yellow("  Welcome to my shop traveler. Take a look around. I'm sure we've got what you're looking for.") << endl;
	cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
		 << dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
		 << dye::bright_white(" |       1) View Wares        |              |     2) Sell your Items    |              |         3) Go back         |  ") << endl
		 << dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
		 << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
	int choice;
	do {
		cout << ">> ";
		cin >> choice;
		if (cin.fail() || choice > 3 || choice == 0)
		{
			cout << "Enter a number from 1 - 3" << endl;
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || choice > 3 || choice == 0);
	switch (choice)
	{
	case 1:
	{
		//buy items
		break;
	}
	case 2:
	{
		//sell items
		break;
	}
	case 3:
	{
		//go back
		break;
	}
	}
}

void printMainCombatMenu(Character player, Character enemy)
{

	cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
		<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		<< dye::bright_white(" |     1) Move       |   |    2) Attack      |   |   3) Use Item     |   |  4) Check Enemy   |   | 5) Attempt to Run |  ") << endl
		<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

	//input validation
	printAllBars(player);
	int choice;
	do {
		cout << ">> ";
		cin >> choice;
		if (cin.fail() || choice > 5 || choice == 0)
		{
			cout << "Enter a number from 1 - 5" << endl;
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || choice > 5 || choice == 0);
	switch (choice)
	{
	case 1:
		if (player.getMainWeapon1(player).reach >= enemy.distanceFromPlayer ||
			player.getOffhandWeapon1(player).reach >= enemy.distanceFromPlayer)
		{
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				<< dye::bright_white(" |    1) Attack      |   |  2) Move Forward  |   | 3) Move Backward  |   | 4) Retreat & Attack |   |    5) Return    |  ") << endl
				<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
			printAllBars(player);
		}
		else
		{
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::grey(" |    1) Attack      |   ") << dye::bright_white("|  2) Move Forward  |   | 3) Move Backward  |   | 4) Move Back & Attack |   |   5) Return   |  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
			printAllBars(player);


			//Scuffed color pallet lmao
			/*cout << dye::light_yellow("  This is a ") << dye::yellow("legendary") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  This is an ") << dye::light_blue("epic") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  This is an ") << dye::light_green("uncommon") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  This is a ") << dye::bright_white("common") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  It's wizard time motherfucker, ") << dye::light_red("FIREBALL") << endl;
			cout << dye::light_yellow("  It's wizard time motherfucker, ") << dye::aqua("ICE SPEAR") << endl;
			cout << dye::light_yellow("  It's wizard time motherfucker, ") << dye::purple("THUNDERBOLT") << endl;
			cout << dye::light_yellow("  It's sword time motherfucker, ") << dye::white("SLASH") << endl;
			cout << dye::light_yellow("  You recieve 10 points of ") << dye::green("healing") << endl;
			cout << dye::light_yellow("  You take 10 points of ") << dye::red("damage") << endl;
			cout << dye::light_yellow("  You have been ") << dye::light_green("buffed") << endl;
			cout << dye::light_yellow("  You have been ") << dye::light_purple("debuffed") << endl;*/

		}
		break;
	case 2:

		break;
	case 3:

		break;

	case 4:

		break;
	case 5:

		break;
	}

}

void printAllBars(Character character)
{
	printHealthBar(character);
	printStaminaBar(character);
	printManaBar(character);
}

void printHealthBar(Character player) {
	//red portion of health bar (health remaining)
	int healthRemainingSegments = player.healthPoints / 10;
	//white portion of health bar (health missing)
	int numHealthSegments = player.maxHealthPoints / 10;
	string healthBarText = " Health Remaining:  ";
	cout << healthBarText;
	for (int i = 0; i < healthRemainingSegments; i++)
	{
		cout << dye::red("[]");
	}
	for (int i = 0; i < (player.maxHealthPoints - player.healthPoints) / 10; i++) {
		cout << dye::light_yellow("[]");
	}
	cout << endl;
	cout << endl;
}

void printStaminaBar(Character player) {
	//green portion of stamina bar (stamina remaining)
	int staminaRemainingSegments = player.staminaPoints / 10;
	//white portion of stamina bar (stamina missing)
	int numStaminaSegments = player.maxStaminaPoints / 10;
	string staminaBarText = " Stamina Remaining: ";
	cout << staminaBarText;
	for (int i = 0; i < staminaRemainingSegments; i++)
	{
		cout << dye::green("[]");
	}
	for (int i = 0; i < (player.maxStaminaPoints - player.staminaPoints) / 10; i++) {
		cout << dye::light_yellow("[]");
	}
	cout << endl;
	cout << endl;
}

void printManaBar(Character player)
{
	//green portion of mana bar (mana remaining)
	int manaRemainingSegments = player.manaPoints / 10;
	//white portion of mana bar (mana missing)
	int nummanaSegments = player.maxManaPoints / 10;
	string manaBarText = " Mana Remaining:    ";
	cout << manaBarText;
	for (int i = 0; i < manaRemainingSegments; i++)
	{
		cout << dye::blue("[]");
	}
	for (int i = 0; i < (player.maxManaPoints - player.manaPoints) / 10; i++) {
		cout << dye::light_yellow("[]");
	}
	cout << endl;
	cout << endl;
}