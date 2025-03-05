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
	enum item_types { WEAPON, HOLYTOOL, ARCANETOOL, SHIELD, ARMOR, TRINKET, POTION, LOOT };
	enum weapon_types {
		DAGGER, STRAIGHTSWORD, GREATSWORD, FIST, MACE, GREATMACE, 
		HATCHET, AXE, GREATAXE, THRUSTINGSWORD, SPEAR, GREATSPEAR, 
		PARRYSHIELD, MEDIUMSHIELD, GREATSHIELD, 
		LONGBOW, COMPOUNDBOW, GREATBOW, MINICROSSBOW, CROSSBOW, BALLISTA,
		TALISMAN, CHIME, TOME, WAND, STAFF, ORB
	};
	enum physical_damage_types { SLASH, BLUNT, PIERCE };
	enum magic_damage_types { FIRE, FROST, SHOCK, NONE };
	enum equip_slots { HEAD, CHEST, LEGS, ARMS, AMULET, RING, MAINHAND1, MAINHAND2, OFFHAND1, OFFHAND2, BAREHAND, MISC };
	int storedSlot;
	int defense;
	int damage;
	int value;
	int weight;
	int quantity;
	bool twoHanded;
	int reach;
	int attackSpeed;

	Item(string name, string description, enum item_types itemType, enum weapon_types weaponType, enum physical_damage_types physicalDamageType,
		enum magic_damage_types magicDamageType, enum equip_slots slot, int storedSlot, int defense, int damage, int value, int weight, int quantity, bool twoHanded, int reach, int attackSpeed) {
		this->name = name;
		this->description = description;
		itemType = itemType;
		weaponType = weaponType;
		physicalDamageType = physicalDamageType;
		magicDamageType = magicDamageType;
		slot = slot;
		this->storedSlot = storedSlot;
		this->defense = defense;
		this->damage = damage;
		this->value = value;
		this->weight = weight;
		this->quantity = quantity;
		this->twoHanded = twoHanded;
		this->reach = reach;
		this->attackSpeed = attackSpeed;
	}
};

class Inventory {
public:
	//stored as a list of items
	vector<Item> items;

	void addItem(const Item& item) {
		items.push_back(item);
	}
	void removeItem(const Item& item) {
		for (auto it = items.begin(); it != items.end(); ++it) {
			if (it->name == item.name) {
				items.erase(it);
				return;
			}
		}
		cout << "Item not found in inventory" << endl;
	}
	void updateItemQuantity(const string& itemName, int newQuantity) {
		for (Item& item : items) {
			if (item.name == itemName) {
				item.quantity = newQuantity;
				return;
			}
		}
		cout << "Item not found in inventory" << endl;
	}
	Item findItem(const string& itemName) {
		for (Item& item : items) {
			if (item.name == itemName) {
				return item;
			}
		}
		cout << "Item not found in inventory" << endl;
	}
	void printInventory() {
		for (Item& item : items) {
			cout << "Name: " << item.name << endl;
			cout << "Damage: " << item.damage << endl;
			cout << "Value: " << item.value << endl;
			cout << "Weight: " << item.weight << endl;
			cout << "Quantity: " << item.quantity << endl;
			cout << "Stackable: " << item.twoHanded << endl;
			cout << endl;
		}
	}
};

class Character
{
public:
	enum classChoice { DEFAULT, WIZARD, KNIGHT, CLERIC, HUNTER, HIGHLANDER, BATTLEMAGE };
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

	int level;
	int experience;
	int experienceToNextLevel;
	int gold;

	Inventory inventory;

	//Enemy Specific Stats
	int distanceFromPlayer;
	bool alert;

	Character() {
		//Core Attributes
		characterClass = "";
		health = health;
		mana = mana;
		stamina = stamina;
		strength = strength;
		agility = agility;
		arcane = arcane;
		faith = faith;
		luck = luck;

		//Derived Attributes
		healthPoints = healthPoints;
		maxHealthPoints = maxHealthPoints;
		manaPoints = manaPoints;
		maxManaPoints = maxManaPoints;
		staminaPoints = staminaPoints;
		maxStaminaPoints = maxStaminaPoints;
		speed = speed;

		//Derived Stats
		critChance = critChance;
		dodgeChance = dodgeChance;
		blockChance = blockAmount;
		blockAmount = blockAmount;

		level = 1;
		experience = experience;
		experienceToNextLevel = experienceToNextLevel;
		gold = 0;

		inventory = inventory;

		//Enemy Specific Stats
		distanceFromPlayer = distanceFromPlayer;
		alert = alert;
	}
	void setCharacterClass(enum classChoice option)
	{
		switch (option)
		{
		case WIZARD:
		{
			characterClass = "Wizard";
			health = 10;
			mana = 20;
			stamina = 7;
			strength = 7;
			agility = 7;
			arcane = 20;
			faith = 1;
			luck = 10;
			initializeCharacterStats();
			//Mainhand default 1
			inventory.addItem(Item("Weathered Arming Sword", "A short blade that could use a good sharpening",
				Item::WEAPON, Item::STRAIGHTSWORD, Item::SLASH, Item::NONE, Item::MAINHAND1, 6, 0, 8, 10, 1, 1, false, 7, 11));
			//Offhand default 1
			inventory.addItem(Item("Oak Wand", "A basic wooden wand barely capable of casting magic",
				Item::ARCANETOOL, Item::WAND, Item::BLUNT, Item::NONE, Item::OFFHAND1, 8, 0, 1, 10, 1, 1, false, 1, 10));
			//Offhand default 2
			inventory.addItem(Item("Plank Shield", "A small shield composed of several thin oak boards",
				Item::SHIELD, Item::MEDIUMSHIELD, Item::BLUNT, Item::NONE, Item::OFFHAND2, 9, 7, 2, 5, 2, 1, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NONE, Item::BAREHAND, 12, 0, 1, 0, 0, 1, false, 3, 10);
			inventory.addItem(fists);
			break;
		}
		case BATTLEMAGE:
		{
			characterClass = "Battle Mage";
			health = 16;
			mana = 10;
			stamina = 10;
			strength = 10;
			agility = 10;
			arcane = 15;
			faith = 1;
			luck = 10;
			initializeCharacterStats();
			//Mainhand default 1
			inventory.addItem(Item("Weathered Hand Axe", "An weathered axe of moderate size",
				Item::WEAPON, Item::AXE, Item::SLASH, Item::NONE, Item::MAINHAND1, 6, 0, 12, 5, 4, 1, false, 11, 8));
			//Offhand default 1
			inventory.addItem(Item("Oak Wand", "A basic wooden wand barely capable of casting magic",
				Item::ARCANETOOL, Item::WAND, Item::BLUNT, Item::NONE, Item::OFFHAND1, 8, 0, 1, 20, 1, 1, false, 1, 10));
			//Offhand default 2
			inventory.addItem(Item("Sturdy Plank Shield", "A small shield composed of several thick oak boards bound together by rivets",
				Item::SHIELD, Item::MEDIUMSHIELD, Item::BLUNT, Item::NONE, Item::OFFHAND2, 9, 10, 2, 5, 2, 1, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NONE, Item::BAREHAND, 12, 0, 1, 0, 0, 1, false, 3, 10);
			inventory.addItem(fists);
			break;
		}
		case KNIGHT:
		{
			characterClass = "Knight";
			health = 16;
			mana = 5;
			stamina = 15;
			strength = 16;
			agility = 10;
			arcane = 5;
			faith = 5;
			luck = 10;
			initializeCharacterStats();
			//Mainhand default 1
			inventory.addItem(Item("Weathered Longsword", "A long blade that has seen a good amount of combat",
				Item::WEAPON, Item::STRAIGHTSWORD, Item::SLASH, Item::NONE, Item::MAINHAND1, 6, 0, 10, 5, 1, 1, false, 6, 10));
			//Offhand default 1
			inventory.addItem(Item("Weathered Kite Shield", "A basic metal shield emblazened with a crest so faded it can't be made out",
				Item::SHIELD, Item::MEDIUMSHIELD, Item::BLUNT, Item::NONE, Item::OFFHAND1, 8, 15, 2, 5, 1, 1, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NONE, Item::BAREHAND, 12, 0, 1, 0, 0, 1, false, 3, 10);
			inventory.addItem(fists);
			break;
		}
		case CLERIC:
		{
			characterClass = "Cleric";
			health = 10;
			mana = 15;
			stamina = 10;
			strength = 10;
			agility = 5;
			arcane = 2;
			faith = 20;
			luck = 10;
			initializeCharacterStats();
			//Mainhand default 1
			inventory.addItem(Item("Weathered Mace", "A hefty mace that, although weathered, could still crack a skull or two",
				Item::WEAPON, Item::MACE, Item::BLUNT, Item::NONE, Item::MAINHAND1, 6, 0, 15, 5, 3, 1, false, 5, 7));
			//Offhand default 1
			inventory.addItem(Item("Tarnished Talisman", "A basic talisman that cannels ones faith and allows the casting of miracles",
				Item::HOLYTOOL, Item::TALISMAN, Item::BLUNT, Item::NONE, Item::OFFHAND1, 8, 0, 2, 5, 1, 1, false, 1, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NONE, Item::BAREHAND, 12, 0, 1, 0, 0, 1, false, 3, 10);
			inventory.addItem(fists);
			break;
		}
		case HUNTER:
		{
			characterClass = "Hunter";
			health = 10;
			mana = 5;
			stamina = 15;
			strength = 7;
			agility = 20;
			arcane = 10;
			faith = 5;
			luck = 10;
			initializeCharacterStats();
			//Mainhand default 1	
			inventory.addItem(Item("Weathered Dagger", "A short blade mostly used for gutting fish and harvesting animal skins. It could stand to be sharpened",
				Item::WEAPON, Item::DAGGER, Item::SLASH, Item::NONE, Item::MAINHAND1, 6, 0, 5, 5, 1, 1, false, 2, 15));
			//Offhand default 1
			inventory.addItem(Item("Hunting Bow", "A basic wooden bow of average build",
				Item::WEAPON, Item::LONGBOW, Item::PIERCE, Item::NONE, Item::OFFHAND1, 8, 0, 10, 10, 4, 1, false, 40, 5));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NONE, Item::BAREHAND, 12, 0, 1, 0, 0, 1, false, 3, 10);
			inventory.addItem(fists);
			break;
		}
		case HIGHLANDER:
		{
			characterClass = "Highlander";
			health = 15;
			mana = 3;
			stamina = 15;
			strength = 17;
			agility = 16;
			arcane = 3;
			faith = 3;
			luck = 10;
			initializeCharacterStats();
			inventory.addItem(Item("Iron Claymore", "A massive blade that requires ample strength and two hands to wield. Typically used to cleave through horses it will makes short work of a man", 
				Item::WEAPON, Item::GREATSWORD, Item::SLASH, Item::NONE, Item::MAINHAND1, 6, 0, 25, 15, 10, 1, true, 15, 5));
			inventory.addItem(Item("Weathered Dagger", "A short blade mostly used for gutting fish and harvesting animal skins. It could stand to be sharpened",
				Item::WEAPON, Item::DAGGER, Item::SLASH, Item::NONE, Item::MAINHAND2, 7, 0, 5, 5, 1, 1, false, 2, 15));
			//No weapon equipped
			Item fists = Item("Fists", "Your bare hands", Item::WEAPON, Item::FIST, Item::BLUNT, Item::NONE, Item::BAREHAND, 10, 0, 1, 0, 0, 1, false, 3, 10);
			inventory.addItem(fists);
			break;
		}
		default:
			break;
		}
	}

	void initializeCharacterStats() {
		maxHealthPoints = (health * 10) + (strength * 2) + (agility * 2);
		healthPoints = maxHealthPoints;
		maxManaPoints = (arcane >= faith) ? (mana * 10) + (arcane * 2)  + (faith * 1) : (mana * 10) + (faith * 2) + (arcane * 1);
		manaPoints = maxManaPoints;
		maxStaminaPoints = (stamina * 10) + (strength * 2);
		staminaPoints = maxStaminaPoints;

		speed = (agility * 20) + (stamina * 2);
	}

	//Gets the weapon in the main hand. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getMainWeapon1(Character character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.items.size(); i++)
		{
			if (character.inventory.items[i].storedSlot == Item::MAINHAND1)
			{
				bool found = true;
				return character.inventory.items[i];
			}
		}
		if (found == false) {
			return character.inventory.findItem("Fists");
		}
	}
	//Gets the weapon in the main hand 2. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getMainWeapon2(Character character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.items.size(); i++)
		{
			if (character.inventory.items[i].storedSlot == Item::MAINHAND2)
			{
				bool found = true;
				return character.inventory.items[i];
			}
		}
		if (found == false) {
			return character.inventory.findItem("Fists");
		}
	}
	//Gets the weapon in the off hand. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getOffhandWeapon1(Character character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.items.size(); i++)
		{
			if (character.inventory.items[i].storedSlot == Item::OFFHAND1)
			{
				bool found = true;
				return character.inventory.items[i];
			}
		}
		if (found == false) {
			return character.inventory.findItem("Fists");
		}
	}
	//Gets the weapon in the off hand 2. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getOffhandWeapon2(Character character)
	{
		bool found = false;
		for (int i = 0; i < character.inventory.items.size(); i++)
		{
			if (character.inventory.items[i].storedSlot == Item::OFFHAND2)
			{
				bool found = true;
				return character.inventory.items[i];
			}
		}
		if (found == false) {
			return character.inventory.findItem("Fists");
		}
	}
};
#pragma region Function Declarations

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
#pragma endregion Function Declarations

int main()
{
	int choice;
	Character player;
	Character enemy;
	
	player.setCharacterClass(Character::HIGHLANDER);
	enemy.setCharacterClass(Character::BATTLEMAGE);
	enemy.distanceFromPlayer = 10;
	enemy.inventory.addItem(Item("Weathered Dagger", "A short blade mostly used for gutting fish and harvesting animal skins. It could stand to be sharpened",
		Item::WEAPON, Item::DAGGER, Item::SLASH, Item::NONE, Item::MAINHAND1, 6, 0, 15, 5, 1, 1, false, 2, 15));
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> distribution(1, 2);
	int randomNum = distribution(generator);
	cout << player.getMainWeapon1(player).name << endl;
	cout << player.getMainWeapon2(player).name << endl;
	cout << player.getOffhandWeapon1(player).name << endl;
	cout << player.getOffhandWeapon2(player).name << endl;
	printMainCombatMenu(player, enemy);
	return 0;
}

void printMainCombatMenu(Character player, Character enemy)
{
	cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
		<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		<< dye::light_yellow(" |     1) Move       |   |    2) Attack      |   |   3) Use Item     |   |  4) Check Enemy   |   | 5) Attempt to Run |  ") << endl
		<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
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
				<< dye::light_yellow(" |    1) Attack      |   |  2) Move Forward  |   | 3) Move Backward  |   | 4) Retreat & Attack |   |    5) Return    |  ") << endl
				<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
			printAllBars(player);
		}
		else
		{
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::grey(" |    1) Attack      |   ") << dye::light_yellow("|  2) Move Forward  |   | 3) Move Backward  |   | 4) Move Back & Attack |   |   5) Return   |  ") << endl
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