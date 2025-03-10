#include "Character.h"
#include "Potion.h"
#include <vector>
#include <iostream>
#include "color.hpp"

Character::Character() {

}

Character::Character(bool isAlive, bool isPlayer, bool active, enum classChoice classChoice, std::string name, std::string characterClass, float health, float mana, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
	float manaPoints, float maxManaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float weightBurden, float level, float experience, float experienceToNextLevel,
	float gold, Inventory inventory, float distanceFromPlayer, bool alert)
{
	this->isAlive = isAlive;
	this->isPlayer = isPlayer;
	this->active = active;
	this->classChoice = classChoice;
	this->characterClass = characterClass;
	this->health = health;
	this->mana = mana;;
	this->strength = strength;
	this->agility = agility;
	this->arcane = arcane;
	this->faith = faith;
	this->luck = luck;
	this->healthPoints = healthPoints;
	this->maxHealthPoints = maxHealthPoints;
	this->manaPoints = manaPoints;
	this->maxManaPoints = maxManaPoints;
	this->speed = speed;
	this->critChance = critChance;
	this->dodgeChance = dodgeChance;
	this->blockChance = blockChance;
	this->blockAmount = blockAmount;
	this->damageReduction = damageReduction;
	this->weightBurden = weightBurden;
	this->level = level;
	this->experience = experience;
	this->experienceToNextLevel = experienceToNextLevel;
	this->gold = gold;
	this->inventory = inventory;
	this->distanceFromPlayer = distanceFromPlayer;
	this->alert = alert;
}

Character::~Character() {

}
void Character::setCharacterClass(enum classChoice option)
{
	switch (option)
	{
	case WIZARD:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Wizard";
		health = 10;
		mana = 20;
		strength = 7;
		agility = 7;
		arcane = 20;
		faith = 1;
		luck = 10;
		level = 1;
		//Spells
		MagicEffect effect = (MagicEffect("Damage Over Time", "The missile lingers in the target, doing a small amount of damage over time",
			1, 0, 3, 3, 1, MagicEffect::stats_effected::NONE));
		Spell startingSpell = Spell(effect, "Minor Magic Missile", "A small bolt of energy shot forth like a missile", 20, 0, 20, 10, 30, 10, Spell::magic_types::SORCERY, Spell::spell_effects::NONE);		//Mainhand default 1
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
		this->addSpell(startingSpell);
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case BATTLEMAGE:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Battle Mage";
		health = 16;
		mana = 10;
		strength = 10;
		agility = 10;
		arcane = 15;
		faith = 1;
		luck = 10;
		level = 1;
		//Spells
		MagicEffect effect = (MagicEffect("Damage Over Time", "The missile lingers in the target, doing a small amount of damage over time",
			1, 0, 3, 3, 1, MagicEffect::stats_effected::NONE));
		Spell startingSpell = Spell(effect, "Minor Magic Missile", "A small bolt of energy shot forth like a missile", 20, 0, 20, 10, 30, 10, Spell::magic_types::SORCERY, Spell::spell_effects::NONE);
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
		this->addSpell(startingSpell);
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case KNIGHT:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Knight";
		health = 16;
		mana = 5;
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
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case CLERIC:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Cleric";
		health = 10;
		mana = 15;
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
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case HUNTER:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Hunter";
		health = 10;
		mana = 5;
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
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case HIGHLANDER:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Highlander";
		health = 15;
		mana = 3;
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
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case WRETCH:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Wretch";
		health = 1;
		mana = 1;
		strength = 1;
		agility = 1;
		arcane = 1;
		faith = 1;
		luck = 1;
		level = 1;
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	default:
		std::cout << "Invalid class choice" << std::endl;
		break;
	}
}

void Character::refreshCharacterStats() {
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

	//this will be rolled against a random number between 1-100, if the random number wins it will not be a crit. If it does win, it will be a crit
	//set to -9 at first so each class will start with 1 crit chance
	(critChance >= 50) ? critChance = 50 : critChance = critChance;
	critChance = -9 + luck * 1 + agility * 0.1;
}

void Character::setArmorValues(std::vector<Item> items)
{
	//iterates through all items in the player's equipped inventory and adds their equipment weights together for calculations
	float equipmentWeight = 0;
	for (int i = 0; i < items.size(); i++)
	{
		equipmentWeight += items[i].weight;
	}
	speed = (agility * 10) + (strength * 5) - equipmentWeight;

	dodgeChance = (agility * 0.5) + (speed / 100);
	(dodgeChance >= 50) ? dodgeChance = 50 : dodgeChance = dodgeChance - (equipmentWeight / 100);

	float armorValue = 0;
	for (int i = 0; i < items.size(); i++)
	{
		armorValue += items[i].defense;
	}
	damageReduction = armorValue / (armorValue + 500);
}
void Character::takeDamage(Character damageDealer)
{
	Item mainhand1;
	Item mainhand2;
	Item offhand1;
	Item offhand2;
	damageDealer.inventory.getEquippedWeapons(mainhand1, mainhand2, offhand1, offhand2);
	float damageTaken = mainhand1.damage - (mainhand1.damage * damageReduction);
	healthPoints -= damageTaken;
	if (isPlayer == true)
	{
		if (damageReduction > 0.01)
		{
			std::cout << "Your armor absorbs " << mainhand1.damage * damageReduction << " points of damage!" << std::endl;
			std::cout << "You take " << damageTaken << " points of damage!" << std::endl;
		}
		else {
			std::cout << "You take " << damageTaken << " points of damage!" << std::endl;
		}
		if (healthPoints < 0) {
			healthPoints = 0;
			killCharacter();
		}
	}
	else
	{
		if (damageReduction > 0.01)
		{
			std::cout << "The " << this->name << "'s armor absorbs " << mainhand1.damage * damageReduction << " points of damage!" << std::endl;
			std::cout << "The " << this->name << " takes " << damageTaken << " points of damage!" << std::endl;
		}
		else {
			std::cout << "The " << this->name << " takes " << damageTaken << " points of damage!" << std::endl;
		}
		if (healthPoints < 0) {
			healthPoints = 0;
			killCharacter();
		}
	}

}

void Character::receiveHealing(int healing)
{
	healthPoints += healing;
	if (healthPoints > maxHealthPoints) {
		healthPoints = maxHealthPoints;
	}
}

void Character::gainExperience(Character enemy)
{
	float expGained = enemy.level * 50;
	std::cout << this->name << " gained " << expGained << " points of experience for their victory!" << std::endl;

	if (expGained + experience >= experienceToNextLevel)
	{
		levelUp(expGained);
	}
	else
	{
		this->experience += expGained;
	}
}

//this is an arcane monstrocity that I am not proud of
void Character::levelUp(float exp)
{
	experience += exp;
	float expDifference;
	do
	{
		bool levelUpComplete = false;
		do {
			int iterator = 0;
			std::cout << dye::yellow("Level up! You are now level: ") << dye::yellow(level + 1) << std::endl;
			for (int i = 3; i > 0; i--)
			{
				int areYouSure = 0;
				do
				{
					std::cout << dye::yellow("Select ") << dye::yellow(i) << dye::yellow(" stats to increase by 3!") << std::endl;
					std::cout << dye::light_yellow("1) Health: ") << this->health << std::endl;
					std::cout << dye::light_yellow("2) Mana: ") << this->mana << std::endl;
					std::cout << dye::light_yellow("3) Strength: ") << this->strength << std::endl;
					std::cout << dye::light_yellow("4) Agility: ") << this->agility << std::endl;
					std::cout << dye::light_yellow("5) Arcane: ") << this->arcane << std::endl;
					std::cout << dye::light_yellow("6) Faith: ") << this->faith << std::endl;
					std::cout << dye::light_yellow("7) Luck: ") << this->luck << std::endl;
					int choice;
					//input validation
					do
					{
						std::cout << ">> ";
						std::cin >> choice;
						if (std::cin.fail() || choice > 7 || choice == 0)
						{
							std::cout << "Enter a number from 1 - 7" << std::endl;
						}
						std::cin.clear();
						std::cin.ignore(10000, '\n');
					} while (std::cin.fail() || choice > 7 || choice == 0);

					switch (choice)
					{
					case 1:
					{
						std::cout << "Health: " << this->health << " -> " << this->health + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;

						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->health += 3;
						}
						else
						{
							break;
						}
						break;
					}
					case 2:
					{
						std::cout << "Mana: " << this->mana << " -> " << this->mana + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->mana += 3;
						}
						else
						{
							break;
						}
						break;
					}
					case 3:
					{
						std::cout << "Strength: " << this->strength << " -> " << this->strength + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->strength += 3;
						}
						else
						{
							break;
						}
						break;
					}
					case 4:
					{
						std::cout << "Agility: " << this->agility << " -> " << this->agility + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->agility += 3;
						}
						else
						{
							break;
						}
						break;
					}
					case 5:
					{
						std::cout << "Arcane: " << this->arcane << " -> " << this->arcane + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->arcane += 3;
						}
						else
						{
							break;
						}
						break;
					}
					case 6:
					{
						std::cout << "Faith: " << this->faith << " -> " << this->faith + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->faith += 3;
						}
						else
						{
							break;
						}
						break;
					}
					case 7:
					{
						std::cout << "Luck: " << this->luck << " -> " << this->luck + 3 << std::endl;
						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
						//input validation
						do
						{
							std::cout << ">> ";
							std::cin >> areYouSure;
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);

						if (areYouSure == 1)
						{
							this->luck += 3;
						}
						else
						{
							break;
						}
						break;
					}
					}

				} while (areYouSure == 2);
				iterator += 1;
			}
			if (iterator == 3)
			{
				levelUpComplete = true;
			}
		} while (levelUpComplete == false);

		//this prints out the stats a final time after they are done leveling up so they can see their final results
		std::cout << dye::light_yellow("1) Health: ") << this->health << std::endl;
		std::cout << dye::light_yellow("2) Mana: ") << this->mana << std::endl;
		std::cout << dye::light_yellow("4) Strength: ") << this->strength << std::endl;
		std::cout << dye::light_yellow("5) Agility: ") << this->agility << std::endl;
		std::cout << dye::light_yellow("6) Arcane: ") << this->arcane << std::endl;
		std::cout << dye::light_yellow("7) Faith: ") << this->faith << std::endl;
		std::cout << dye::light_yellow("8) Luck: ") << this->luck << std::endl;

		//loops so long as there is enough experience to level up again after consuming enough for a level
		exp -= experienceToNextLevel;
		level += 1;
		refreshCharacterStats();
	} while (exp >= experienceToNextLevel);
	experience = exp;
}

void Character::killCharacter()
{
	this->isAlive = false;
	std::cout << this->name << " has taken" << dye::light_red(" fatal damage...") << std::endl;
}

void Character::openLootInterface(Character& container)
{
	int i = 0;

	int goldCount = container.gold;

	//the number used to keep track of whether or not an item in one category exists
	int tally = 0;
	//the number to keep track of the total # of items in a list (loot items, equipped items, etc...)
	int totalCategory = 0;

	std::vector<Item> loot;
	std::vector<Potion> lootPotions;
	std::cout << container.name << "'s spoils: " << std::endl;


	//loot items go here


	//looting 
	int input;
	int totalItems = totalCategory;
	do
	{
		if (!inventory.equippedItems.empty())
		{
			std::cout << "Equipment: " << std::endl;
			for (int j = 0; j < container.inventory.equippedItems.size(); j++)
			{
				if (container.inventory.equippedItems[i].itemType == Item::WEAPON)
				{
					tally += 1;
				}
			}
			if (tally != 0)
			{
				std::cout << "Weapons: " << std::endl;
				for (i = 1; i < container.inventory.equippedItems.size() + 1; i++)
				{
					if (container.inventory.equippedItems[i - 1].itemType == Item::WEAPON)
					{
						std::cout << i << ") " << container.inventory.equippedItems[i - 1].name << ", damage: "
							<< container.inventory.equippedItems[i - 1].damage << ", attack speed: "
							<< container.inventory.equippedItems[i - 1].attackSpeed << ", weight: "
							<< container.inventory.equippedItems[i - 1].weight << ", value: "
							<< container.inventory.equippedItems[i - 1].value << std::endl;
						totalCategory += 1;
						loot.push_back(container.inventory.equippedItems[i - 1]);
					}
				}
			}
			tally = 0;
			for (int j = 0; j < container.inventory.equippedItems.size(); j++)
			{
				if (container.inventory.equippedItems[i - totalCategory - 1].itemType == Item::ARMOR)
				{
					tally += 1;
				}
			}
			if (tally != 0)
			{
				std::cout << "Armor: " << std::endl;
				for (i = i; i < container.inventory.equippedItems.size() + totalCategory - 1; i++)
				{
					if (container.inventory.equippedItems[i - totalCategory - 1].itemType == Item::ARMOR)
					{
						std::cout << i << ") " << container.inventory.equippedItems[i - totalCategory - 1].name << ", defense: "
							<< container.inventory.equippedItems[i - totalCategory - 1].defense << ", weight: "
							<< container.inventory.equippedItems[i - totalCategory - 1].weight << ", value: "
							<< container.inventory.equippedItems[i - totalCategory - 1].value << std::endl;
						loot.push_back(container.inventory.equippedItems[i - totalCategory - 1]);
						totalCategory += 1;

					}
				}
			}
			tally = 0;
			for (int j = 0; j < container.inventory.equippedItems.size(); j++)
			{
				if (container.inventory.equippedItems[i - totalCategory - 1].itemType == Item::ARCANETOOL ||
					container.inventory.equippedItems[i - totalCategory - 1].itemType == Item::HOLYTOOL)
				{
					tally += 1;
				}
			}
			if (tally != 0)
			{
				std::cout << "Tools: " << std::endl;
				tally = 0;
				for (i = i; i < container.inventory.equippedItems.size() + totalCategory - 1; i++)
				{
					if (container.inventory.equippedItems[i - totalCategory - 1].itemType == Item::ARCANETOOL ||
						container.inventory.equippedItems[i - totalCategory - 1].itemType == Item::HOLYTOOL)
					{
						std::cout << i << ") " << container.inventory.equippedItems[i - totalCategory - 1].name << ", defense: "
							<< container.inventory.equippedItems[i - totalCategory - 1].defense << ", weight: "
							<< container.inventory.equippedItems[i - totalCategory - 1].weight << ", value: "
							<< container.inventory.equippedItems[i - totalCategory - 1].value << ", Magic Adjust: "
							<< container.inventory.equippedItems[i - totalCategory - 1].magicAdjust << std::endl;
						loot.push_back(container.inventory.equippedItems[i - totalCategory - 1]);
						totalCategory += 1;
					}
				}
			}
			tally = 0;
			if (!container.inventory.potions.empty())
			{
				std::string types[] = { "Restore Health", "Restore Mana", "Cure Disease" };
				std::cout << "Potions: " << std::endl;
				tally = 0;
				int num = container.inventory.potions.size() + totalCategory + 1;
				for (i = i; i < num; i++)
				{
					std::cout << i << ") " << container.inventory.potions[i - totalCategory - 1].name << ", weight: "
						<< container.inventory.potions[i - totalCategory - 1].weight << ", value: "
						<< container.inventory.potions[i - totalCategory - 1].value << ", effect: "
						<< types[container.inventory.potions[i - totalCategory - 1].effects] << ", quantity: "
						<< container.inventory.potions[i - totalCategory - 1].quantity << std::endl;
					lootPotions.push_back(container.inventory.potions[i - totalCategory - 1]);
					totalCategory += 1;
				}
			}
		}
	} while (input != -2 || loot.empty() || lootPotions.empty());

	std::cout << "Enter the number of the item you want to loot!" << std::endl;
	std::cout << "Or, type -1 to loot everything!" << std::endl;
	std::cout << "Enter -2 to stop looting!" << std::endl;
	do
	{
		std::cout << ">> ";
		std::cin >> input;
		if (std::cin.fail() || input < -2 || input == 0 || input > totalItems)
		{
			std::cout << "Enter either -1 for all items, 1 - " << totalItems << " for a specific item, or -2 to stop looting" << std::endl;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	} while (std::cin.fail() || input < -2 || input == 0 || input > totalItems);
	if (!loot.empty())
	{
		if (input == -1)
		{
			for (int j = 0; j < loot.size(); j++)
			{
				if (!loot.empty())
				{
					this->inventory.backpackItems.push_back(loot[j]);
					std::cout << loot[j].name << " added!" << std::endl;
					container.inventory.equippedItems.erase(container.inventory.equippedItems.begin() + j);
				}
			}
		}
		else if (input == -2)
		{
			std::cout << "Looting ceased..." << std::endl;
		}
		else
		{
			if (input > 0 && input <= loot.size() && !loot.empty())
			{
				int end = input - 1;
				this->inventory.backpackItems.push_back(loot[input - 1]);
				std::cout << loot[input - 1].name << " added!" << std::endl;
				//loot.erase(loot.begin() + end);
			}
		}
	}
	if (!lootPotions.empty())
	{
		if (input == -1)
		{
			for (int j = 0; j < lootPotions.size(); j++)
			{
				if (!lootPotions.empty())
				{
					this->inventory.potions.push_back(lootPotions[j]);
					std::cout << lootPotions[j].name << " added!" << std::endl;
					container.inventory.potions.erase(container.inventory.potions.begin() + j);
				}
			}
		}
		else if (input == -2)
		{
			std::cout << "Looting ceased..." << std::endl;
		}
		else if (input > loot.size() && !lootPotions.empty())
		{
			int end = input - loot.size();
			this->inventory.potions.push_back(lootPotions[input - loot.size() - 1]);
			std::cout << lootPotions[input - loot.size() - 1].name << " added!" << std::endl;
			//lootPotions.erase(lootPotions.begin() + end);
		}
	}
}

void Character::printCharacterStats(Character& character)
{
	std::cout << dye::light_yellow("  Class: ") << character.characterClass << std::endl;
	std::cout << dye::light_yellow("  Health Points: ") << character.healthPoints << "/" << character.maxHealthPoints << std::endl;
	std::cout << dye::light_yellow("  Mana Points: ") << character.manaPoints << "/" << character.maxManaPoints << std::endl;
	std::cout << "\n";
	std::cout << dye::light_yellow("  Health: ") << character.health << std::endl;
	std::cout << dye::light_yellow("  Mana: ") << character.mana << std::endl;
	std::cout << dye::light_yellow("  Strength: ") << character.strength << std::endl;
	std::cout << dye::light_yellow("  Agility: ") << character.agility << std::endl;
	std::cout << dye::light_yellow("  Arcane: ") << character.arcane << std::endl;
	std::cout << dye::light_yellow("  Faith: ") << character.faith << std::endl;
	std::cout << dye::light_yellow("  Luck: ") << character.luck << std::endl;
	std::cout << "\n";
	std::cout << dye::light_yellow("  Speed: ") << character.speed << std::endl;
	std::cout << dye::light_yellow("  Damage Reduction: ") << character.damageReduction << "%" << std::endl;
	//under construction below
	std::cout << dye::light_yellow("  Critical Chance: ") << character.critChance << "%" << std::endl;
	std::cout << dye::light_yellow("  Dodge Chance: ") << character.dodgeChance << "%" << std::endl;
	std::cout << dye::light_yellow("  Block Chance: ") << character.blockChance << "%" << std::endl;
	std::cout << dye::light_yellow("  Block Amount: ") << character.blockAmount << std::endl;
	std::cout << "\n";
	std::cout << dye::light_yellow("  Level: ") << character.level << std::endl;
	std::cout << dye::light_yellow("  Experience: ") << character.experience << "/" << character.experienceToNextLevel << std::endl;
	std::cout << "\n";
	std::cout << dye::light_yellow("  Gold: ") << character.gold << std::endl;
}

void Character::addItemToEnemy(Character enemy, Item item, Item::equip_slots slot)
{

}

void Character::checkEnemy()
{
	std::cout << dye::light_yellow("------------------------------------------------------------------------------") << std::endl;
	std::cout << dye::light_yellow("  Name: ") << this->name << std::endl;
	std::cout << dye::light_yellow("  Health: ") << this->healthPoints << std::endl;
	std::cout << dye::light_yellow("  Mana: ") << this->manaPoints << std::endl;
	std::cout << dye::light_yellow("  Speed: ") << this->speed << std::endl;
	std::cout << dye::light_yellow("------------------------------------------------------------------------------") << std::endl;
}

void Character::openPotionDialogue(bool& turnOver)
{
	if (this->isAlive == false)
	{
		std::cout << "Your enemy was too quick and you're dead before the potion can reach your lips..." << std::endl;
	}
	else
	{
		std::vector<Potion> healingPotions;
		int potionQuantity = 0;
		for (int i = 0; i < this->inventory.potions.size(); i++)
		{
			if (this->inventory.potions[i].effects == Potion::HEALING)
			{
				healingPotions.push_back(this->inventory.potions[i]);
				potionQuantity += this->inventory.potions[i].quantity;
			}
		}
		std::cout << "You have " << potionQuantity << " healing potions left." << std::endl;
		std::cout << "Would you like to drink one? 1 = yes, 2 = no" << std::endl;
		//input validation
		int choice;
		do
		{
			std::cout << ">> ";
			std::cin >> choice;
			if (std::cin.fail() || choice > 2 || choice == 0)
			{
				std::cout << "Enter a number from 1 - 2" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		} while (std::cin.fail() || choice > 2 || choice == 0);

		//yes
		if (choice == 1)
		{
			std::cout << "Choose a potion.." << std::endl;
			for (int i = 1; i < healingPotions.size() + 1; i++)
			{
				std::cout << i << ") " << healingPotions[i - 1].name << ", magnitude of "
					<< healingPotions[i - 1].magnitude << ", quantity of " << healingPotions[i - 1].quantity << std::endl;
			}
			do
			{
				std::cout << ">> ";
				std::cin >> choice;
				if (std::cin.fail() || choice > healingPotions.size() || choice == 0)
				{
					std::cout << "Enter a number from 1 - " << healingPotions.size() << std::endl;
				}
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			} while (std::cin.fail() || choice > healingPotions.size() || choice == 0);

			this->drinkPotion(healingPotions[choice - 1]);
		}
		if (choice == 2)
		{
			turnOver = false;
		}
	}
}

void Character::drinkPotion(Potion& potion) {
	if (this->isPlayer == true)
	{
		if (potion.effects == Potion::HEALING) {
			if (this->healthPoints == this->maxHealthPoints) {
				std::cout << dye::light_yellow("You are already at full health and did not consume the potion.") << std::endl;
			}
			else {
				this->receiveHealing(potion.magnitude);
				if (potion.quantity == 1) {
					this->inventory.removePotion(potion);
				}
				else {
					this->inventory.updatePotionQuantity(potion.name, potion.quantity - 1);
				}
				std::cout << potion.name << " consumed, " << potion.magnitude << " points of healing administered." << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid potion" << std::endl;
		}
	}
	else
	{
		if (potion.effects == Potion::HEALING) {
			if (this->healthPoints == this->maxHealthPoints) {
				std::cout << dye::light_yellow(this->name) << dye::light_yellow(" tried to drink a potion, but they were already at full health and did not consume the potion.") << std::endl;
			}
			else {
				this->receiveHealing(potion.magnitude);
				if (potion.quantity == 1) {
					this->inventory.removePotion(potion);
				}
				else {
					this->inventory.updatePotionQuantity(potion.name, potion.quantity - 1);
				}
				std::cout << this->name << " consumed a " << potion.name << ", " << potion.magnitude << " points of healing administered." << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid potion" << std::endl;
		}
	}

}

void Character::sellItem(Item& item) {
	std::cout << "Are you sure you want to sell this " << item.name << " for " << item.value << " gold pieces?" << std::endl;
	std::cout << "1 = Yes, 2 = No" << std::endl;
	int choice;
	do
	{
		std::cout << ">> ";
		std::cin >> choice;
		if (std::cin.fail() || choice > 5 || choice == 0)
		{
			std::cout << "Enter a number from 1 - 2" << std::endl;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	} while (std::cin.fail() || choice > 5 || choice == 0);
	if (choice == 1)
	{
		if (item.quantity == 1)
		{
			this->inventory.removeItemFromBackpack(item);
			this->gold += item.value;
			std::cout << item.name << " sold for " << item.value << " gold pieces!" << std::endl;
		}
		else {
			item.quantity -= 1;
			this->gold += item.value;
			std::cout << item.name << " sold for " << item.value << " gold pieces!" << std::endl;
		}
	}
	else {
		std::cout << "Item not sold" << std::endl;
	}
}

//AMMO
#pragma region AMMO
Ammo Character::createAmmo(std::string name, int damage, int weight, int quantity, Ammo::ammo_Types ammoType)
{
	Ammo ammo;
	ammo.name = name;
	ammo.damage = damage;
	ammo.weight = weight;
	ammo.quantity = quantity;
	ammo.ammoType = ammoType;

	return ammo;
}

void Character::addAmmo(const Ammo& ammo) {
	munitions.push_back(ammo);
}

void Character::removeAmmo(const Ammo& ammo)
{
	for (auto it = munitions.begin(); it != munitions.end(); ++it) {
		if (it->name == ammo.name) {
			munitions.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

Ammo& Character::findAmmo(const std::string& ammoName) {
	for (Ammo& ammo : munitions) {
		if (ammo.name == ammoName) {
			return ammo;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Character::updateAmmoQuantity(const std::string& ammoName, int newQuantity) {
	for (Ammo& ammo : munitions) {
		if (ammo.name == ammoName) {
			ammo.quantity = newQuantity;
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

int Character::getAmmoCount(Character character)
{
	int ammoCount = 0;
	for (int i = 0; i < munitions.size(); i++)
	{
		ammoCount += 1;
	}
	return ammoCount;
}

void Character::depleteAmmo(Ammo& ammunition)
{
	if (ammunition.quantity == 1)
	{
		this->removeAmmo(ammunition);
	}
	else {
		ammunition.quantity -= 1;
	}
}
#pragma endregion AMMO

//SPELLS
#pragma region SPELLS
void Character::addSpell(const Spell& spell) {
	spells.push_back(spell);
}

void Character::removeSpell(const Spell& spell) {
	for (auto it = spells.begin(); it != spells.end(); ++it) {
		if (it->name == spell.name) {
			spells.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Character::removeAllSpells() {
	spells.clear();
}


Spell Character::findSpell(const std::string& spellName) {
	for (Spell& spell : spells) {
		if (spell.name == spellName) {
			return spell;
		}
	}
	throw std::invalid_argument("Item not found");
}


void Character::castSpell(Spell& spellName, Character& enemy) {
	if (this->manaPoints < spellName.manaCost)
	{
		std::cout << "You do not have enough mana to cast this spell" << std::endl;
	}
	else {
		this->manaPoints -= spellName.manaCost;
		enemy.healthPoints -= spellName.damage;
		std::cout << "You cast " << spellName.name << " at the " << enemy.name <<
			" and deal " << spellName.damage << " damage!" << std::endl;
	}
}

#pragma endregion SPELLS

#pragma region MAGICEFFECTS
void Character::addMagicEffect(const MagicEffect& spell) {
	magicEffects.push_back(spell);
}

void Character::removeMagicEffect(const MagicEffect& spell) {
	for (auto it = magicEffects.begin(); it != magicEffects.end(); ++it) {
		if (it->name == spell.name) {
			magicEffects.erase(it);
			return;
		}
	}
	throw std::invalid_argument("Item not found");
}

void Character::removeAllMagicEffects() {
	magicEffects.clear();
}


MagicEffect Character::findMagicEffect(const std::string& effectName) {
	for (MagicEffect& effect : magicEffects) {
		if (effect.name == effectName) {
			return effect;
		}
	}
	throw std::invalid_argument("Item not found");
}

MagicEffect Character::createMagicEffect(std::string name, std::string description, int damage, int healing,
	int turnsActive, int turnsRemaining, int magnitude, MagicEffect::stats_effected statEffected)
{
	MagicEffect effect;
	effect.name = name;
	effect.description = description;
	effect.damage = damage;
	effect.healing = healing;
	effect.turnsActive = turnsActive;
	effect.turnsRemaining = turnsRemaining;
	effect.magnitude = magnitude;
	effect.statEffected = statEffected;

	return effect;
}
#pragma endregion MAGICEFFECTS