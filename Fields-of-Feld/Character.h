#ifndef Character_h
#define Character_h

#include <string>
#include "Inventory.h"
#include "Item.h"
#include "Spell.h"
#include "MagicEffect.h"
#include <functional>

class Character
{
public:
	bool namedCharacter = false; 
	float confidenceLevel = 0.0f; 

	bool isAlive = true; 
	bool isPlayer = false; 
	bool active = true; 
	std::string name = "CHARACTER NAME PLS CHANGE"; 
	enum class CharacterClass { DEFAULT, WIZARD, KNIGHT, CLERIC, HUNTER, HIGHLANDER, BATTLEMAGE, WRETCH, BANDIT };
	CharacterClass classChoice = CharacterClass::DEFAULT; 
	std::string characterClass = "Default"; 

	//Core Attributes
	float health = 10.0f; 
	float mana = 10.0f; 
	float strength = 10.0f; 
	float agility = 10.0f; 
	float arcane = 10.0f;
	float faith = 10.0f; 
	float luck = 10.0f; 

	//Derived Attributes
	float healthPoints = 100.0f; 
	float maxHealthPoints = 100.0f; 
	float manaPoints = 50.0f;
	float maxManaPoints = 50.0f;
	float speed = 1.0f;

	//Derived Stats
	float critChance = 5.0f;
	float dodgeChance = 5.0f;
	float blockChance = 0.0f; 
	float blockAmount = 0.0f; 
	float damageReduction = 0.0f; 
	float weightBurden = 0.0f; 

	float level = 1.0f; 
	float experience = 0.0f; 
	float experienceToNextLevel = 100.0f; 
	float gold = 0.0f; 

	Inventory inventory; 

	//Enemy Specific Stats
	float distanceFromPlayer = 0.0f; 
	bool alert = false; 

	//Default Constructor
	Character();

	//Main Constructor
	Character(bool namedCharacter, float confidenceLevel, bool isAlive, bool isPlayer, bool active, enum Character::CharacterClass classChoice, std::string name, std::string characterClass, float health, float mana, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
		float manaPoints, float maxManaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float weightBurden, float level, float experience, float experienceToNextLevel,
		float gold, Inventory inventory, float distanceFromPlayer, bool alert);

	//Deconstructor
	~Character();

	Character createHumanoid(bool namedCharacter, bool isPlayer, std::string name, Character::CharacterClass classChoice, float health,
		float mana, float strength, float agility, float arcane, float faith, float luck,
		float confidenceLevel, float gold, float distanceFromPlayer, float level);

	void setCharacterClass(CharacterClass option);

	//called when the player stats need to be refreshed, either when first initializing them or when they level up
	void refreshCharacterStats();

	void setArmorValues(std::vector<Item> items);

	void takeDamage(Item weapon, Character attacker, Item ammunition = Item());

	void receiveHealing(float healing);

	void gainExperience(Character enemy);

	void levelUp(float extraExp);

	void killCharacter();

	void openLootInterface(Character& container);

	void printCharacterStats(Character& character);

	//Enemy Specifc Functions
	
	void addItemToEnemy(Character enemy, Item item, Item::equip_slots slot);

	void checkPlayer();
		
	void checkCharacterIntro(Character player);

	void checkCharacter(Character player);

	void openPotionDialogue(bool & turnOver);
	
	void drinkPotion(Potion& potion);

	void sellItem(Item& item);

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


