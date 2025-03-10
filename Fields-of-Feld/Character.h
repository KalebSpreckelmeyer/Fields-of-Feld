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
	float speed;

	//Derived Stats
	float critChance;
	float dodgeChance;
	float blockChance;
	float blockAmount;
	float damageReduction;
	float weightBurden;

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
	Character(bool isAlive, bool isPlayer, bool active, enum classChoice classChoice, std::string name, std::string characterClass, float health, float mana, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
		float manaPoints, float maxManaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float weightBurden, float level, float experience, float experienceToNextLevel,
		float gold, Inventory inventory, float distanceFromPlayer, bool alert);

	//Deconstructor
	~Character();

	void setCharacterClass(enum classChoice option);

	//called when the player stats need to be refreshed, either when first initializing them or when they level up
	void refreshCharacterStats();

	void setArmorValues(std::vector<Item> items);

	void takeDamage(Character damageDealer);

	void receiveHealing(int healing);

	void gainExperience(Character enemy);

	void levelUp(float extraExp);

	void killCharacter();

	void printCharacterStats(Character& character);

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


