#ifndef Character_h
#define Character_h

#include <string>
#include "Inventory.h"
#include "Item.h"
#include "Spell.h"
#include "MagicEffect.h"

class Character
{
public:
	bool isAlive;
	bool isPlayer;
	bool active;
	std::string name;
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
	Character(bool isAlive, bool isPlayer, bool active, enum classChoice classChoice, std::string name, std::string characterClass, float health, float mana, float stamina, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
		float manaPoints, float maxManaPoints, float staminaPoints, float maxStaminaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float level, float experience, float experienceToNextLevel,
		float gold, Inventory inventory, float distanceFromPlayer, bool alert);

	//Deconstructor
	~Character();

	void setCharacterClass(enum classChoice option);

	//called when the player stats need to be refreshed, either when first initializing them or when they level up
	void refreshCharacterStats();

	void setArmorValues(std::vector<Item> items);

	void takeDamage(int damage);

	void receiveHealing(int healing);

	void gainExperience(Character enemy);

	void levelUp(float extraExp);

	void killCharacter();

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

	int getStaminaCost(Item weapon);

	void consumeStamina(Item weapon);

	//Enemy Specifc Functions
	
	void addItemToEnemy(Character enemy, Item item, Item::equip_slots slot);

	void checkEnemy();

	void openPotionDialogue(bool & turnOver);
	
	void drinkPotion(Potion& potion);

	void sellItem(Item& item);

	//Ammunition
#pragma region AMMO
	std::vector<Ammo> munitions;

	Ammo createAmmo(std::string name, int damage, int weight, int quantity, Ammo::ammo_Types ammoType);

	void addAmmo(const Ammo& ammo);

	void removeAmmo(const Ammo& ammo);

	Ammo& findAmmo(const std::string& ammoName);

	void updateAmmoQuantity(const std::string& ammoName, int newQuantity);

	int getAmmoCount(Character character);

	void depleteAmmo(Ammo& ammunition);
#pragma endregion AMMO

	//SPELLS
#pragma region SPELLS
	std::vector<Spell> spells;

	void addSpell(const Spell& spell);

	void removeSpell(const Spell& item);

	void removeAllSpells();

	Spell findSpell(const std::string& spellName);

	void castSpell(Spell& spellName, Character& enemy);

#pragma endregion SPELLS

#pragma region MAGICEFFECTS
	std::vector<MagicEffect> magicEffects;

	void addMagicEffect(const MagicEffect& effect);

	void removeMagicEffect(const MagicEffect& effect);

	void removeAllMagicEffects();

	MagicEffect findMagicEffect(const std::string& effectName);

	MagicEffect createMagicEffect(std::string name, std::string description, int damage, int healing,
		int turnsActive, int turnsRemaining, int magnitude, MagicEffect::stats_effected statEffected);

#pragma endregion MAGICEFFECTS
};

#endif // !Character_h


