#ifndef Character_h
#define Character_h

#include <string>
#include "Item.h"
#include "Inventory.h"

class Character
{
public:
	bool active;
	enum classChoice { DEFAULT, WIZARD, KNIGHT, CLERIC, HUNTER, HIGHLANDER, BATTLEMAGE, WRETCH };
	classChoice classChoice;
	std::string characterClass;

	//Core Attributes
	float health;
	float mana;
	float stamina;
	float strength;
	float agility;
	float arcane;
	float faith;
	float luck;

	//Derived Attributes
	float healthPoints;
	float maxHealthPoints;
	float manaPoints;
	float maxManaPoints;
	float staminaPoints;
	float maxStaminaPoints;
	float speed;

	//Derived Stats
	float critChance;
	float dodgeChance;
	float blockChance;
	float blockAmount;
	float damageReduction;

	float level;
	float experience;
	float experienceToNextLevel;
	float gold;

	Inventory inventory;

	//Enemy Specific Stats
	float distanceFromPlayer;
	bool alert;

	//Default Constructor
	Character();

	//Main Constructor
	Character(bool active, enum classChoice classChoice, std::string characterClass, float health, float mana, float stamina, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
		float manaPoints, float maxManaPoints, float staminaPoints, float maxStaminaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float level, float experience, float experienceToNextLevel,
		float gold, Inventory inventory, float distanceFromPlayer, bool alert);

	//Deconstructor
	~Character();

	void setCharacterClass(enum classChoice option);

	//called when the player stats need to be refreshed, either when first initializing them or when they level up
	void refreshCharacterStats(std::vector<Item> items);

	void takeDamage(int damage);

	void receiveHealing(int healing);

	//Gets the weapon in the main hand. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getMainWeapon1(Character& character);

	//Gets the weapon in the main hand 2. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getMainWeapon2(Character& character);

	//Gets the weapon in the off hand. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getOffhandWeapon1(Character& character);

	//Gets the weapon in the off hand 2. It can be a one-handed weapon with the MAINHAND1 enum, 
	// a two-handed weapon with the BOTHHANDS enum, or a weapon that can be wielded in either hand with the HANDS enum
	Item getOffhandWeapon2(Character& character);

	void printCharacterStats(Character& character);

	//Enemy Specifc Functions
	void createEnemy(std::string name, std::string description, int healthPoints, int staminaPoints, int manaPoints, int speed, int reach, int critChance,
		int dodgeChance, int blockChance, int blockAmount, int damageReduction, int level);
	
	void addItemToEnemy(Character enemy, Item item, Item::equip_slots slot);
	
	void drinkPotion(Potion& potion);

	void sellItem(Item& item);
};

#endif // !Character_h


