#include "Character.h"
#include "Potion.h"
#include <vector>
#include <iostream>
#include "color.hpp"

Character::Character() {

}

Character::Character(bool active, enum classChoice classChoice, std::string name, std::string characterClass, float health, float mana, float stamina, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
	float manaPoints, float maxManaPoints, float staminaPoints, float maxStaminaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float level, float experience, float experienceToNextLevel,
	float gold, Inventory inventory, float distanceFromPlayer, bool alert) 
{
	this->active = active;
	this->classChoice = classChoice;
	this->characterClass = characterClass;
	this->health = health;
	this->mana = mana;
	this->stamina = stamina;
	this->strength = strength;
	this->agility = agility;
	this->arcane = arcane;
	this->faith = faith;
	this->luck = luck;
	this->healthPoints = healthPoints;
	this->maxHealthPoints = maxHealthPoints;
	this->manaPoints = manaPoints;
	this->maxManaPoints = maxManaPoints;
	this->staminaPoints = staminaPoints;
	this->maxStaminaPoints = maxStaminaPoints;
	this->speed = speed;
	this->critChance = critChance;
	this->dodgeChance = dodgeChance;
	this->blockChance = blockChance;
	this->blockAmount = blockAmount;
	this->damageReduction = damageReduction;
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
		refreshCharacterStats(items);
		break;
	}
	case BATTLEMAGE:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

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
		//Spells
		MagicEffect effect = (MagicEffect("Damage Over Time", "The missile lingers in the target, doing a small amount of damage over time",
			1, 0, 3, 3, 1,MagicEffect::stats_effected::NONE));
		Spell startingSpell = Spell(effect,"Minor Magic Missile", "A small bolt of energy shot forth like a missile", 20, 0, 20, 10, 30, 10, Spell::magic_types::SORCERY, Spell::spell_effects::NONE);
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
		refreshCharacterStats(items);
		break;
	}
	case KNIGHT:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

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
		std::vector<Item> items = this->inventory.getEquippedItems();
		refreshCharacterStats(items);
		break;
	}
	case CLERIC:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

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
		std::vector<Item> items = this->inventory.getEquippedItems();
		refreshCharacterStats(items);
		break;
	}
	case HUNTER:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

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
		std::vector<Item> items = this->inventory.getEquippedItems();
		refreshCharacterStats(items);
		break;
	}
	case HIGHLANDER:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

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
		std::vector<Item> items = this->inventory.getEquippedItems();
		refreshCharacterStats(items);
		break;
	}
	case WRETCH:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

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
		std::vector<Item> items = this->inventory.getEquippedItems();
		refreshCharacterStats(items);
		break;
	}
	default:
		std::cout << "Invalid class choice" << std::endl;
		break;
	}
}

void Character::refreshCharacterStats(std::vector<Item> items) {
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
	float equipmentWeight = 0;
	for (int i = 0; i < items.size(); i++)
	{
		equipmentWeight += items[i].weight;
	}
	speed = (agility * 10) + (strength * 5) + (stamina * 2) - equipmentWeight;

	dodgeChance = (agility * 0.5) + (speed / 100);
	(dodgeChance >= 50) ? dodgeChance = 50 : dodgeChance = dodgeChance - (equipmentWeight / 100);

	float armorValue = 0;
	for (int i = 0; i < items.size(); i++)
	{
		armorValue += items[i].defense;
	}
	damageReduction = armorValue / (armorValue + 100);
}

void Character::takeDamage(int damage)
{
	healthPoints -= damage;
	if (healthPoints < 0) {
		healthPoints = 0;
		//add function to handle character death
	}
}

void Character::receiveHealing(int healing)
{
	healthPoints += healing;
	if (healthPoints > maxHealthPoints) {
		healthPoints = maxHealthPoints;
	}
}

Item Character::getMainWeapon1(Character& character)
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
	std::cout << " No mainhand weapon 1 found" << std::endl;
}

Item Character::getMainWeapon2(Character& character)
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
	std::cout << " No mainhand weapon 2 found" << std::endl;
}

Item Character::getOffhandWeapon1(Character& character)
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
	std::cout << " No offhand weapon 1 found" << std::endl;
}

Item Character::getOffhandWeapon2(Character& character)
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
	std::cout << " No offhand weapon 2 found" << std::endl;
}

void Character::printCharacterStats(Character& character)
{
	std::cout << dye::light_yellow("  Class: ") << character.characterClass << std::endl;
	std::cout << dye::light_yellow("  Health Points: ") << character.healthPoints << "/" << character.maxHealthPoints << std::endl;
	std::cout << dye::light_yellow("  Stamina Points: ") << character.staminaPoints << "/" << character.maxStaminaPoints << std::endl;
	std::cout << dye::light_yellow("  Mana Points: ") << character.manaPoints << "/" << character.maxManaPoints << std::endl;
	std::cout << "\n";
	std::cout << dye::light_yellow("  Health: ") << character.health << std::endl;
	std::cout << dye::light_yellow("  Mana: ") << character.mana << std::endl;
	std::cout << dye::light_yellow("  Stamina: ") << character.stamina << std::endl;
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

Character Character::createEnemy(std::string name, float healthPoints, float staminaPoints, float manaPoints, float speed, float reach, float critChance,
	float dodgeChance, float blockChance, float blockAmount, float damageReduction, float level, float distanceFromPlayer)
{
	Character enemy;
	enemy.name = name;
	enemy.healthPoints = healthPoints;
	enemy.maxHealthPoints = healthPoints;
	enemy.staminaPoints = staminaPoints;
	enemy.maxStaminaPoints = staminaPoints;
	enemy.manaPoints = manaPoints;
	enemy.maxManaPoints = manaPoints;
	enemy.speed = speed;
	enemy.critChance = critChance;
	enemy.dodgeChance = dodgeChance;
	enemy.blockChance = blockChance;
	enemy.blockAmount = blockAmount;
	enemy.damageReduction = damageReduction;
	enemy.level = level;
	enemy.distanceFromPlayer = distanceFromPlayer;

	Item ironDagger = ironDagger.createWeapon("Iron Dagger", "A short blade stained brown with blood", 5,
		3, 10, 1, 1, false, false, Item::weapon_types::DAGGER, Item::physical_damage_types::SLASH,
		Item::magic_damage_types::NOMAGICDAMAGE);
	enemy.inventory.equipItem(ironDagger, Item::MAINHAND1);

	return enemy;
}

void Character::addItemToEnemy(Character enemy, Item item, Item::equip_slots slot)
{

}

void Character::drinkPotion(Potion& potion) {
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