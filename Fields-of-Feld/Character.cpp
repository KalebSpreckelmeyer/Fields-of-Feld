#include "Character.h"
#include "Potion.h"
#include <vector>
#include <iostream>
#include "color.hpp"
#include <random>
#include <iomanip>

Character::Character()
{

}
Character::Character(bool namedCharacter, float confidenceLevel, bool isAlive, bool isPlayer, bool active, 
	enum Character::CharacterClass classChoice, std::string name, std::string characterClass, float health, 
	float mana, float strength, float agility, float arcane, float faith, float luck, float healthPoints, float maxHealthPoints,
	float manaPoints, float maxManaPoints, float speed, float critChance, float dodgeChance, float blockChance, float blockAmount, float damageReduction, float weightBurden, float level, float experience, float experienceToNextLevel,
	float gold, Inventory inventory, float distanceFromPlayer, bool alert)
	: confidenceLevel(confidenceLevel), isAlive(isAlive), isPlayer(isPlayer), active(active), classChoice(classChoice), name(name), characterClass(characterClass),
	health(health), mana(mana), strength(strength), agility(agility), arcane(arcane), faith(faith), luck(luck),
	healthPoints(healthPoints), maxHealthPoints(maxHealthPoints), manaPoints(manaPoints), maxManaPoints(maxManaPoints), speed(speed),
	critChance(critChance), dodgeChance(dodgeChance), blockChance(blockChance), blockAmount(blockAmount), damageReduction(damageReduction), weightBurden(weightBurden),
	level(level), experience(experience), experienceToNextLevel(experienceToNextLevel), gold(gold), inventory(inventory), distanceFromPlayer(distanceFromPlayer), alert(alert) {
}

Character::~Character() {

}

Character Character::createHumanoid(bool namedCharacter, bool isPlayer, std::string name, Character::CharacterClass classChoice, float health,
	float mana, float strength, float agility, float arcane, float faith, float luck,
	float confidenceLevel, float gold, float distanceFromPlayer, float level)
{
	Character human;
	human.namedCharacter = namedCharacter;
	human.active = true;
	human.isAlive = true;
	human.isPlayer = isPlayer;
	human.confidenceLevel = confidenceLevel;
	human.name = name;
	human.classChoice = classChoice;
	human.gold = gold;
	human.distanceFromPlayer = distanceFromPlayer;
	human.health = health;
	human.mana = mana;
	human.strength = strength;
	human.agility = agility;
	human.arcane = arcane;
	human.faith = faith;
	human.luck = luck;
	human.level = level;
	human.setCharacterClass(classChoice);
	human.refreshCharacterStats();

	return human;
}
void Character::setCharacterClass(CharacterClass option)
{
	switch (option)
	{
	case CharacterClass::WIZARD:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		namedCharacter = true;
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
		Item startingSword = startingSword.createWeapon("Iron rapier", "A thin, sharp blade designed for thrusting", 10, 10, 70, 2, 15, false, false, Item::weapon_types::THRUSTINGSWORD, Item::physical_damage_types::PIERCE, Item::magic_damage_types::NOMAGICDAMAGE);
		//Offhand default 1
		Item startingWand = startingWand.createTool("Oak Wand", "A basic wooden wand barely capable of casting magic", Item::ARCANETOOL, Item::WAND, 1, 20, 1, 20);
		//Offhand default 2
		Item startingShield = startingShield.createWeapon("Sturdy Plank Shield", "A small shield composed of several thick oak boards bound together by rivets", 5, 2, 5, 5, 15, false, false, Item::weapon_types::MEDIUMSHIELD, Item::physical_damage_types::BLUNT, Item::magic_damage_types::NOMAGICDAMAGE);
		//No weapon equipped
		inventory.equipItem(startingSword, Item::MAINHAND1);
		inventory.equipItem(startingWand, Item::OFFHAND1);
		inventory.equipItem(startingShield, Item::OFFHAND2);
		this->addSpell(startingSpell);
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case CharacterClass::BATTLEMAGE:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();
		
		namedCharacter = true;
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
		Item startingAxe = startingAxe.createWeapon("Iron Battleaxe", "A hefty axe designed for cleaving through armor", 25, 5, 50, 5, 20, false, false, Item::weapon_types::AXE, Item::physical_damage_types::SLASH, Item::magic_damage_types::NOMAGICDAMAGE);
		//Offhand default 1
		Item startingWand = startingWand.createTool("Oak Wand", "A basic wooden wand barely capable of casting magic", Item::ARCANETOOL, Item::WAND, 1, 20, 1, 20);
		//Offhand default 2
		Item startingShield = startingShield.createWeapon("Sturdy Plank Shield", "A small shield composed of several thick oak boards bound together by rivets", 5, 2, 5, 5, 15, false, false, Item::weapon_types::MEDIUMSHIELD, Item::physical_damage_types::BLUNT, Item::magic_damage_types::NOMAGICDAMAGE);
		//No weapon equipped
		inventory.equipItem(startingAxe, Item::MAINHAND1);
		inventory.equipItem(startingWand, Item::OFFHAND1);
		inventory.equipItem(startingShield, Item::OFFHAND2);
		this->addSpell(startingSpell);
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case CharacterClass::KNIGHT:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		namedCharacter = true;
		isAlive = true;
		isPlayer = true;
		active = true;
		characterClass = "Knight";
		health = 22;
		mana = 5;
		strength = 16;
		agility = 16;
		arcane = 5;
		faith = 5;
		luck = 10;
		level = 5;
		//Mainhand default 1
		Item startingSword = startingSword.createWeapon("Iron Longsword", "A long blade designed for slashing and thrusting", 15, 9, 60, 3, 15, false, false, Item::weapon_types::STRAIGHTSWORD, Item::physical_damage_types::SLASH, Item::magic_damage_types::NOMAGICDAMAGE);
		//Offhand default 1
		Item startingShield = startingShield.createWeapon("Sturdy Plank Shield", "A small shield composed of several thick oak boards bound together by rivets", 5, 2, 5, 5, 15, false, false, Item::weapon_types::MEDIUMSHIELD, Item::physical_damage_types::BLUNT, Item::magic_damage_types::NOMAGICDAMAGE);
		inventory.equipItem(startingSword, Item::MAINHAND1);
		inventory.equipItem(startingShield, Item::OFFHAND1);
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case CharacterClass::CLERIC:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		namedCharacter = true;
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
		Item startingMace = startingMace.createWeapon("Iron Mace", "A heavy blunt weapon designed for crushing armor", 40, 3, 20, 5, 20, false, false, Item::weapon_types::MACE, Item::physical_damage_types::BLUNT, Item::magic_damage_types::NOMAGICDAMAGE);
		//Offhand default 1
		Item startingTalisman = startingTalisman.createTool("Tattered Cloth Talisman", "A small piece of cloth with a holy symbol stitched into it", Item::HOLYTOOL, Item::TALISMAN, 1, 20, 1, 20);
		inventory.equipItem(startingMace, Item::MAINHAND1);
		inventory.equipItem(startingTalisman, Item::OFFHAND1);
		std::vector<Item> items = this->inventory.getEquippedItems();
		setArmorValues(items);
		refreshCharacterStats();
		break;
	}
	case CharacterClass::HUNTER:
	{
		//clears items in case of a respec
		this->inventory.removeAllItemsFromBackpack();

		namedCharacter = true;
		this->isAlive = true;
		this->isPlayer = true;
		this->active = true;
		this->characterClass = "Hunter";
		this->health = 10;
		this->mana = 5;
		this->strength = 7;
		this->agility = 20;
		this->arcane = 10;
		this->faith = 5;
		this->luck = 10;
		this->level = 1;
		//Mainhand default 1	
		Item startingSword = startingSword.createWeapon("Hunter's Knife", "A small blade designed for gutting fish and game", 10, 3, 90, 1, 5, false, false, Item::weapon_types::DAGGER, Item::physical_damage_types::SLASH, Item::magic_damage_types::NOMAGICDAMAGE);
		Item startingBow = startingBow.createWeapon("Hunting Bow", "A worn bow once used to hunt game", 5, 100, 50, 4, 20, true, true, Item::weapon_types::LONGBOW, Item::physical_damage_types::PIERCE, Item::magic_damage_types::NOMAGICDAMAGE);
		//No weapon equipped
		this->inventory.equipItem(startingSword, Item::MAINHAND2);
		this->inventory.equipItem(startingBow, Item::MAINHAND1);
		std::vector<Item> items = this->inventory.getEquippedItems();
		this->setArmorValues(items);
		this->refreshCharacterStats();
		break;
	}
	case CharacterClass::HIGHLANDER:
	{
		//clears items in case of a respec
		this->inventory.removeAllItemsFromBackpack();

		namedCharacter = true;
		this->isAlive = true;
		this->isPlayer = true;
		this->active = true;
		this->characterClass = "Highlander";
		this->health = 15;
		this->mana = 3;
		this->strength = 17;
		this->agility = 16;
		this->arcane = 3;
		this->faith = 3;
		this->luck = 10;
		this->level = 1;

		Item startingSword = startingSword.createWeapon("Claymore", "A large two-handed sword with a long blade", 20, 15, 40, 10, 20, false, false, Item::weapon_types::GREATSWORD, Item::physical_damage_types::SLASH, Item::magic_damage_types::NOMAGICDAMAGE);
		this->inventory.equipItem(startingSword, Item::MAINHAND1);
		std::vector<Item> items = this->inventory.getEquippedItems();
		this->setArmorValues(items);
		this->refreshCharacterStats();
		break;
	}
	case CharacterClass::WRETCH:
	{
		//clears items in case of a respec
		inventory.removeAllItemsFromBackpack();

		namedCharacter = true;
		this->isAlive = true;
		this->isPlayer = true;
		this->active = true;
		this->characterClass = "Wretch";
		this->health = 1;
		this->mana = 1;
		this->strength = 1;
		this->agility = 1;
		this->arcane = 1;
		this->faith = 1;
		this->luck = 1;
		this->level = 1;
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
 	critChance = luck * 1 + agility * 0.1 + strength * 0.1;
	if (critChance > 50)
	{
		critChance = 50;
	}
	else
	{
		critChance = critChance;
	}
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
void Character::takeDamage(Item weapon, Character attacker, Item ammunition)
{
	//retrieves the optional ammo object, if it exists, assigns it to the ammo variable. If it doesn't, creates a default ammo object
	Item& ammo = attacker.inventory.findAmmunition(ammunition.name);
	
	//random number generator for crit chance, rolls a number between 1 - (100 - luck ). If the number is less than the crit chance, it's a crit
	int randomNum = (rand() % 100 - attacker.luck) + 1;

	//WEAPON SPECIFIC DAMAGE CALCULATIONS
	
	//archery
	if (weapon.weaponType == Item::LONGBOW || weapon.weaponType == Item::COMPOUNDBOW || weapon.weaponType == Item::BALLISTA || weapon.weaponType == Item::CROSSBOW ||
		weapon.weaponType == Item::GREATBOW || weapon.weaponType == Item::MINICROSSBOW)
	{
		//This is just Overwatch's damage falloff formula lmao
		
		//damage falloff variables
		float minDamage = ammo.damage * .3;
		float maxDamage = ammo.damage * 1.3;
		float nearRange = 10;

		float farRange = weapon.damage * 10;

		//normalized distance of the attacker from their target
		float normalizedDistance = (attacker.distanceFromPlayer - nearRange) / (farRange - nearRange);

		//raw damage of the arrow
		float arrowDamage = normalizedDistance * minDamage + (1.00 - normalizedDistance) * maxDamage;

		//crit damage modifier
		float critDamage = arrowDamage * 1.5;

		//damage reduction modfiiers
		float critDamageReduction = critDamage * damageReduction;
		float normalDamageReduction = arrowDamage * damageReduction;

		//final damage taken, either crit or non crit
		float critDamageTaken = critDamage - critDamageReduction;
		float damageTaken = arrowDamage - normalDamageReduction;

		//critical hit
		if (attacker.critChance >= randomNum)
		{
			//Is player
			if (isPlayer)
			{
				//arrow is fired from min or below range (extra damage)
				if (critDamageTaken == minDamage)
				{
					//Character has armor/shield to absorb some damage
					if (damageReduction > 0.01)
					{
						std::cout << dye::light_red("Critical Hit!") << std::endl;
						std::cout << std::setprecision(2) << "Your armor absorbs " << weapon.damage * damageReduction << " points of damage!" << std::endl;
						std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= critDamageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character has no armor/shield
					else {
						std::cout << dye::light_red("Critical Hit!") << std::endl;
						std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
						std::cout << std::setprecision(2) << std::setprecision(2) << "You take " << critDamageTaken << " points of from the " << attacker.name << "'s " << weapon.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= critDamageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character dies if health is less than 0

					if (healthPoints <= 0) {
						healthPoints = 0;
						killCharacter();
					}
				}
				//arrow is fired from maximum range (lowered damage)
				else if (critDamageTaken == maxDamage)
				{
					//Character has armor/shield to absorb some damage
					if (damageReduction > 0.01)
					{
						std::cout << dye::light_red("Critical Hit!") << std::endl;
						std::cout << std::setprecision(2) << "Your armor absorbs " << critDamageReduction << " points of damage!" << std::endl;
						std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= critDamageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character has no armor/shield
					else {
						std::cout << dye::light_red("Critical Hit!") << std::endl;
						std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << critDamageTaken << " points of from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= critDamageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character dies if health is less than 0

					if (healthPoints <= 0) {
						healthPoints = 0;
						killCharacter();
					}
				}
				else
				{
					//Character has armor/shield to absorb some damage
					if (damageReduction > 0.01)
					{
						std::cout << dye::light_red("Critical Hit!") << std::endl;
						std::cout << std::setprecision(2) << "Your armor absorbs " << critDamageReduction << " points of damage!" << std::endl;
						std::cout << std::setprecision(2) << "You take " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= critDamageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character has no armor/shield
					else {
						std::cout << dye::light_red("Critical Hit!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << critDamageTaken << " points of from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= critDamageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character dies if health is less than 0

					if (healthPoints <= 0) {
						healthPoints = 0;
						killCharacter();
					}
				}
			}
			//Is NPC
			else
			{
				if (!isPlayer)
				{
					//arrow is fired from min or below range (extra damage)
					if (critDamageTaken == minDamage)
					{
						//Character has armor/shield to absorb some damage
						if (damageReduction > 0.01)
						{
							std::cout << dye::light_red("Critical Hit!") << std::endl;
							std::cout << std::setprecision(2) << this->name << "'s armor absorbs " << critDamageReduction << " points of damage!" << std::endl;
							std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= critDamageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character has no armor/shield
						else {
							std::cout << dye::light_red("Critical Hit!") << std::endl;
							std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= critDamageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character dies if health is less than 0

						if (healthPoints <= 0) {
							healthPoints = 0;
							killCharacter();
						}
					}
					//arrow is fired from maximum range (lowered damage)
					else if (critDamageTaken == maxDamage)
					{
						//Character has armor/shield to absorb some damage
						if (damageReduction > 0.01)
						{
							std::cout << dye::light_red("Critical Hit!") << std::endl;
							std::cout << std::setprecision(2) << this->name << "'s armor absorbs " << critDamageReduction << " points of damage!" << std::endl;
							std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= critDamageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character has no armor/shield
						else {
							std::cout << dye::light_red("Critical Hit!") << std::endl;
							std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= critDamageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character dies if health is less than 0

						if (healthPoints <= 0) {
							healthPoints = 0;
							killCharacter();
						}
					}
					else
					{
						//Character has armor/shield to absorb some damage
						if (damageReduction > 0.01)
						{
							std::cout << dye::light_red("Critical Hit!") << std::endl;
							std::cout << std::setprecision(2) << this->name << "'s armor absorbs " << critDamageReduction << " points of damage!" << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= critDamageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character has no armor/shield
						else {
							std::cout << dye::light_red("Critical Hit!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= critDamageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character dies if health is less than 0

						if (healthPoints <= 0) {
							healthPoints = 0;
							killCharacter();
						}
					}
				}
			}
		}
		//normal hit
		else
		{
			//Is player
			if (isPlayer)
			{
				//arrow is fired from min or below range (extra damage)
				if (damageTaken == minDamage)
				{
					//Character has armor/shield to absorb some damage
					if (damageReduction > 0.01)
					{
						std::cout << std::setprecision(2) << "Your armor absorbs " << normalDamageReduction << " points of damage!" << std::endl;
						std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= damageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character has no armor/shield
					else {
						std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << damageTaken << " points of from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= damageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character dies if health is less than 0

					if (healthPoints <= 0) {
						healthPoints = 0;
						killCharacter();
					}
				}
				//arrow is fired from maximum range (lowered damage)
				else if (damageTaken == maxDamage)
				{
					//Character has armor/shield to absorb some damage
					if (damageReduction > 0.01)
					{
						std::cout << std::setprecision(2) << "Your armor absorbs " << normalDamageReduction << " points of damage!" << std::endl;
						std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= damageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character has no armor/shield
					else {
						std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
						std::cout << std::setprecision(2) << "You take " << damageTaken << " points of from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= damageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character dies if health is less than 0

					if (healthPoints <= 0) {
						healthPoints = 0;
						killCharacter();
					}
				}
				else
				{
					//Character has armor/shield to absorb some damage
					if (damageReduction > 0.01)
					{
						std::cout << std::setprecision(2) << "Your armor absorbs " << normalDamageReduction << " points of damage!" << std::endl;
						std::cout << std::setprecision(2) << "You take " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= damageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character has no armor/shield
					else {
						std::cout << std::setprecision(2) << "You take " << damageTaken << " points of from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
						std::cout << std::setprecision(6);
						this->healthPoints -= damageTaken;
						attacker.inventory.consumeAmmunition(ammo);
					}
					//Character dies if health is less than 0

					if (healthPoints <= 0) {
						healthPoints = 0;
						killCharacter();
					}
				}
			}
			//Is NPC
			else
			{
				if (!isPlayer)
				{
					//arrow is fired from min or below range (extra damage)
					if (damageTaken == minDamage)
					{
						//Character has armor/shield to absorb some damage
						if (damageReduction > 0.01)
						{
								std::cout << std::setprecision(2) << this->name << "'s armor absorbs " << normalDamageReduction << " points of damage!" << std::endl;
							std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= damageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character has no armor/shield
						else {
								std::cout << dye::light_yellow("The arrow's bite is dulled by the extreme distance it was fired from!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= damageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character dies if health is less than 0

						if (healthPoints <= 0) {
							healthPoints = 0;
							killCharacter();
						}
					}
					//arrow is fired from maximum range (lowered damage)
					else if (damageTaken == maxDamage)
					{
						//Character has armor/shield to absorb some damage
						if (damageReduction > 0.01)
						{
								std::cout << std::setprecision(2) << this->name << "'s armor absorbs " << normalDamageReduction << " points of damage!" << std::endl;
							std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= damageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character has no armor/shield
						else {
								std::cout << dye::light_yellow("The arrow's bite is amplified by the short time it spent in the air!") << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= damageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character dies if health is less than 0

						if (healthPoints <= 0) {
							healthPoints = 0;
							killCharacter();
						}
					}
					else
					{
						//Character has armor/shield to absorb some damage
						if (damageReduction > 0.01)
						{
								std::cout << std::setprecision(2) << this->name << "'s armor absorbs " << normalDamageReduction << " points of damage!" << std::endl;
							std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= damageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character has no armor/shield
						else {
								std::cout << std::setprecision(2) << this->name << " takes " << damageTaken << " points of damage from the " << attacker.name << "'s " << ammo.name << "!" << std::endl;
							std::cout << std::setprecision(6);
							this->healthPoints -= damageTaken;
							attacker.inventory.consumeAmmunition(ammo);
						}
						//Character dies if health is less than 0

						if (healthPoints <= 0) {
							healthPoints = 0;
							killCharacter();
						}
					}
				}
			}
		}
	}
	//magic
	else if (weapon.weaponType == Item::weapon_types::TALISMAN || weapon.weaponType == Item::weapon_types::CHIME || weapon.weaponType == Item::weapon_types::TOME ||
		weapon.weaponType == Item::weapon_types::WAND || weapon.weaponType == Item::weapon_types::STAFF || weapon.weaponType == Item::weapon_types::ORB)
	{

	}
	//melee
	else
	{
		float critDamage = 1.5 * weapon.damage;
		float critDamageTaken = critDamage - (critDamage * damageReduction);;
		float damageTaken = weapon.damage - (weapon.damage * damageReduction);

		//critical hit
		if (attacker.critChance >= randomNum)
		{
			//Is player
			if (isPlayer)
			{
				//Character has armor/shield to absorb some damage
				if (damageReduction > 0.01)
				{
					std::cout << dye::light_red("Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << "Your armor absorbs " << weapon.damage * damageReduction << " points of damage!" << std::endl;
					std::cout << "You take " << critDamageTaken << " points of damage from the " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= critDamageTaken;
				}
				//Character has no armor/shield
				else {
					std::cout << dye::light_red("Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << "You take " << critDamageTaken << " points of from the " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= critDamageTaken;
				}
				//Character dies if health is less than 0

				if (healthPoints <= 0) {
					healthPoints = 0;
					killCharacter();
				}
			}
			//Is NPC
			else
			{
				//Character has armor/shield to absorb some damage
				if (damageReduction > 0.01)
				{
					std::cout << dye::light_red("Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << "The " << this->name << "'s armor absorbs " << weapon.damage * damageReduction << " points of damage!" << std::endl;
					std::cout << "The " << this->name << " takes " << critDamageTaken << " points of damage from " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= critDamageTaken;
				}
				//Character has no armor/shield
				else {
					std::cout << dye::light_red("Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << "The " << this->name << " takes " << critDamageTaken << " points of damage from " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= critDamageTaken;
				}
				//Character dies if health is less than 0
				if (healthPoints <= 0) {
					healthPoints = 0;
					killCharacter();
				}
			}
		}
		//normal hit
		else
		{
			//Is player
			if (isPlayer)
			{
				//Character has armor/shield to absorb some damage
				if (damageReduction > 0.01)
				{
					std::cout << std::setprecision(2) << "Your armor absorbs " << weapon.damage * damageReduction << " points of damage!" << std::endl;
					std::cout << "You take " << damageTaken << " points of damage from the " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= damageTaken;
				}
				//Character has no armor/shield
				else {
					std::cout << std::setprecision(2) << "You take " << damageTaken << " points of from the " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= damageTaken;
				}
				//Character dies if health is less than 0
				if (healthPoints <= 0) {
					healthPoints = 0;
					killCharacter();
				}
			}
			//Is NPC
			else
			{
				//Character has armor/shield to absorb some damage
				if (damageReduction > 0.01)
				{
					std::cout << std::setprecision(2) << "The " << this->name << "'s armor absorbs " << weapon.damage * damageReduction << " points of damage!" << std::endl;
					std::cout << "The " << this->name << " takes " << damageTaken << " points of damage from " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= damageTaken;
				}
				//Character has no armor/shield
				else {
					std::cout << std::setprecision(2) << "The " << this->name << " takes " << damageTaken << " points of damage from " << attacker.name << "'s " << weapon.name << "!" << std::endl;
					std::cout << std::setprecision(6);
					this->healthPoints -= damageTaken;
				}
				//Character dies if health is less than 0
				if (healthPoints <= 0) {
					healthPoints = 0;
					killCharacter();
				}
			}
		}
	}
}

void Character::receiveHealing(float healing) {
	this->healthPoints += healing;
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
	float expDifference = 0;
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
						if (std::cin.fail() || choice > 7 || choice == 0 || choice < 0)
						{
							std::cout << "Enter a number from 1 - 7" << std::endl;
						}
						std::cin.clear();
						std::cin.ignore(10000, '\n');
					} while (std::cin.fail() || choice > 7 || choice == 0 || choice < 0);

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
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);

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
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);

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
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);

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
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);

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
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);

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
							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
							{
								std::cout << "Enter a number from 1 - 2" << std::endl;
							}
							std::cin.clear();
							std::cin.ignore(10000, '\n');
						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);

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
	if (this->isPlayer)
	{
		std::cout << dye::light_red("You have taken fatal damage...") << std::endl;
	}
	else
	{
		std::cout << "The " << this->name << " has taken" << dye::light_red(" fatal damage...") << std::endl;
	}
}
void Character::openLootInterface(Character& container)
{
	int tally = 1;
	bool quit = false;
	int input = 1;
	int goldCount = container.gold;

	//iterate through this list first, sorting it by equipped items first, then backpack, then loot

	std::vector<Item> initialLootItems = container.inventory.equippedItems;
	for (int i = 0; i < container.inventory.backpackItems.size(); i++)
	{
		initialLootItems.push_back(container.inventory.backpackItems[i]);
	}
	for (int i = 0; i < container.inventory.lootItems.size(); i++)
	{
		initialLootItems.push_back(container.inventory.lootItems[i]);
	}
	std::vector<Potion> initialLootPotions = container.inventory.potions;

	//this will contain the sorted items from the first 2 vectors and will be iterated through for any loop but the first one
	std::vector<Item> finalLootItems;
	std::vector<Potion> finalLootPotions;

	bool firstLoop = true;
	do {
		if (firstLoop == true)
		{
			//printing the items available to loot
			std::cout << "\n" << container.name << "'s spoils for the taking" << std::endl;
			//equipped items

			if (container.gold > 0)
			{
				tally = 1;
				std::cout << tally << "): " << container.gold << "x gold piece(s)" << std::endl;
			}
			if (!initialLootItems.empty())
			{
				for (int i = 0; i < initialLootItems.size(); i++)
				{
					if (initialLootItems[i].itemType == Item::item_types::WEAPON)
					{
						tally += 1;
						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
							<< initialLootItems[i].name << ", value: "
							<< initialLootItems[i].value << ", damage: "
							<< initialLootItems[i].damage << ", attack speed: "
							<< initialLootItems[i].attackSpeed << ", reach: "
							<< initialLootItems[i].reach << ", weight: "
							<< initialLootItems[i].weight << std::endl;
						finalLootItems.push_back(initialLootItems[i]);

					}
				}
			}
			if (!initialLootItems.empty())
			{
				for (int i = 0; i < initialLootItems.size(); i++)
				{

					if (initialLootItems[i].itemType == Item::item_types::ARMOR)
					{
						tally += 1;
						std::cout << tally << "): " << initialLootItems[i].quantity << "x " <<
							initialLootItems[i].name << ", value: "
							<< initialLootItems[i].value << ", defense: "
							<< initialLootItems[i].defense << ", weight: "
							<< initialLootItems[i].weight << std::endl;
						finalLootItems.push_back(initialLootItems[i]);
					}

				}
			}
			if (!initialLootItems.empty())
			{
				for (int i = 0; i < initialLootItems.size(); i++)
				{

					if (initialLootItems[i].itemType == Item::item_types::SHIELD)
					{
						tally += 1;
						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
							<< initialLootItems[i].name << ", value: "
							<< initialLootItems[i].value << ", defense: "
							<< initialLootItems[i].defense << ", weight: "
							<< initialLootItems[i].weight << std::endl;
						finalLootItems.push_back(initialLootItems[i]);
					}

				}

			}
			if (!initialLootItems.empty())
			{
				for (int i = 0; i < initialLootItems.size(); i++)
				{

					if (initialLootItems[i].itemType == Item::item_types::ARCANETOOL ||
						initialLootItems[i].itemType == Item::item_types::HOLYTOOL)
					{
						tally += 1;
						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
							<< initialLootItems[i].name << ", value: "
							<< initialLootItems[i].value << ", magic adjust: "
							<< initialLootItems[i].magicDamageType << ", weight: "
							<< initialLootItems[i].weight << std::endl;
						finalLootItems.push_back(initialLootItems[i]);

					}

				}

			}
			if (!initialLootItems.empty())
			{
				for (int i = 0; i < initialLootItems.size(); i++)
				{

					if (initialLootItems[i].itemType == Item::item_types::TRINKET)
					{

					}
					//TODO After trinkets and torches are implemented 

				}
			}
			if (!initialLootItems.empty())
			{
				for (int i = 0; i < initialLootItems.size(); i++)
				{
					if (initialLootItems[i].itemType == Item::item_types::LOOT)
					{
						tally += 1;
						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
							<< initialLootItems[i].name << ", value: "
							<< initialLootItems[i].value << ", weight: "
							<< initialLootItems[i].weight << std::endl;
						finalLootItems.push_back(initialLootItems[i]);

					}
				}
			}
			//potions

			std::string effects[] = { "Restores Health", "Restores Mana", "Cures Diseases" };
			if (!initialLootPotions.empty())
			{
				for (int i = 0; i < initialLootPotions.size(); i++)
				{
					tally += 1;
					std::cout << tally << "): " << initialLootPotions[i].quantity << "x "
						<< initialLootPotions[i].name << ", value: "
						<< initialLootPotions[i].value << ", effect: "
						<< effects[initialLootPotions[i].effects] << ", weight: "
						<< initialLootPotions[i].weight << std::endl;
					finalLootPotions.push_back(initialLootPotions[i]);
				}
			}
			firstLoop = false;
		}
		//loop 2
		else if (firstLoop == false)
		{
			//printing the items available to loot
			std::cout << "\n" << container.name << "'s spoils for the taking" << std::endl;
			//equipped items

			if (container.gold > 0)
			{
				tally = 1;
				std::cout << tally << "): " << container.gold << "x gold piece(s)" << std::endl;
			}
			if (!finalLootItems.empty())
			{
				for (int i = 0; i < finalLootItems.size(); i++)
				{
					if (finalLootItems[i].itemType == Item::item_types::WEAPON)
					{
						tally += 1;
						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
							<< finalLootItems[i].name << ", value: "
							<< finalLootItems[i].value << ", damage: "
							<< finalLootItems[i].damage << ", attack speed: "
							<< finalLootItems[i].attackSpeed << ", reach: "
							<< finalLootItems[i].reach << ", weight: "
							<< finalLootItems[i].weight << std::endl;
					}
				}
			}
			if (!finalLootItems.empty())
			{
				for (int i = 0; i < finalLootItems.size(); i++)
				{

					if (finalLootItems[i].itemType == Item::item_types::ARMOR)
					{
						tally += 1;
						std::cout << tally << "): " << finalLootItems[i].quantity << "x " <<
							finalLootItems[i].name << ", value: "
							<< finalLootItems[i].value << ", defense: "
							<< finalLootItems[i].defense << ", weight: "
							<< finalLootItems[i].weight << std::endl;
					}

				}
			}
			if (!finalLootItems.empty())
			{
				for (int i = 0; i < finalLootItems.size(); i++)
				{

					if (finalLootItems[i].itemType == Item::item_types::SHIELD)
					{
						tally += 1;
						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
							<< finalLootItems[i].name << ", value: "
							<< finalLootItems[i].value << ", defense: "
							<< finalLootItems[i].defense << ", weight: "
							<< finalLootItems[i].weight << std::endl;
					}

				}

			}
			if (!finalLootItems.empty())
			{
				for (int i = 0; i < finalLootItems.size(); i++)
				{

					if (finalLootItems[i].itemType == Item::item_types::ARCANETOOL ||
						finalLootItems[i].itemType == Item::item_types::HOLYTOOL)
					{
						tally += 1;
						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
							<< finalLootItems[i].name << ", value: "
							<< finalLootItems[i].value << ", magic adjust: "
							<< finalLootItems[i].magicDamageType << ", weight: "
							<< finalLootItems[i].weight << std::endl;
					}

				}

			}
			if (!finalLootItems.empty())
			{
				for (int i = 0; i < finalLootItems.size(); i++)
				{

					if (finalLootItems[i].itemType == Item::item_types::TRINKET)
					{

					}
					//TODO After trinkets and torches are implemented 

				}
			}
			if (!finalLootItems.empty())
			{
				for (int i = 0; i < finalLootItems.size(); i++)
				{
					if (finalLootItems[i].itemType == Item::item_types::LOOT)
					{
						tally += 1;
						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
							<< finalLootItems[i].name << ", value: "
							<< finalLootItems[i].value << ", weight: "
							<< finalLootItems[i].weight << std::endl;
					}
				}
			}
			//potions

			std::string effects[] = { "Restores Health", "Restores Mana", "Cures Diseases" };
			if (!finalLootPotions.empty())
			{
				for (int i = 0; i < finalLootPotions.size(); i++)
				{
					tally += 1;
					std::cout << tally << "): " << finalLootPotions[i].quantity << "x "
						<< finalLootPotions[i].name << ", value: "
						<< finalLootPotions[i].value << ", effect: "
						<< effects[finalLootPotions[i].effects] << ", weight: "
						<< finalLootPotions[i].weight << std::endl;
				}
			}
		}
		//selecting which items to loot

		if (!finalLootItems.empty() || !finalLootPotions.empty())
		{
			std::cout << "\nSelect the item to loot by typing the number besides its name" << std::endl;
			std::cout << "Type -1 to loot everything" << std::endl;
			std::cout << "Or, type -2 to leave the rest for the vultures" << std::endl;
			do
			{
				std::cout << "\n>>";
				std::cin >> input;
				if (std::cin.fail() || input > tally || input == 0 || input < -2)
				{
					std::cout << "Enter a number from 1 - " << tally << ", or enter -1 or -2" << std::endl;
				}
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			} while (std::cin.fail() || input > tally || input == 0 || input < -2);

			if (input == -1)
			{
				this->gold += goldCount;
				std::cout << goldCount << " gold pieces added to backpack!" << std::endl;
				//select all
				for (int i = 0; i < finalLootItems.size(); i++)
				{
					this->inventory.addItemToBackpack(finalLootItems[i]);
					std::cout << finalLootItems[i].name << " added to backpack!" << std::endl;
				}
				for (int i = 0; i < finalLootPotions.size(); i++)
				{
					this->inventory.addPotion(finalLootPotions[i]);
					std::cout << finalLootPotions[i].name << " added to backpack!" << std::endl;
				}
				quit = true;
			}
			if (input > 0 && input <= tally)
				//individual selection
			{
				if (container.gold > 0)
				{
					if (input == 1)
					{
						this->gold += goldCount;
						std::cout << goldCount << " gold pieces added to backpack!" << std::endl;
						container.gold -= goldCount;
						tally = 0;
					}
					else if (!finalLootItems.empty() && input < finalLootItems.size() + 2)
					{
						int num = input - 2;
						this->inventory.addItemToBackpack(finalLootItems[num]);
						std::cout << finalLootItems[num].name << " added to backpack!" << std::endl;
						finalLootItems.erase(finalLootItems.begin() + num);
						tally = 0;
					}
					else if (!finalLootPotions.empty() && input > finalLootItems.size() + 1)
					{
						int num = input - finalLootItems.size() - 2;
						this->inventory.addPotion(finalLootPotions[num]);
						std::cout << finalLootPotions[num].name << " added to backpack!" << std::endl;
						finalLootPotions.erase(finalLootPotions.begin() + num);
						tally = 0;
					}
					else
					{
						std::cout << "Item not found!" << std::endl;
						tally = 0;
					}
				}
				else
				{
					if (!finalLootItems.empty() && input < finalLootItems.size() + 1)
					{
						int num = input - 1;
						this->inventory.addItemToBackpack(finalLootItems[num]);
						std::cout << finalLootItems[num].name << " added to backpack!" << std::endl;
						finalLootItems.erase(finalLootItems.begin() + num);
						tally = 0;
					}
					else if (!finalLootPotions.empty() && input > finalLootItems.size())
					{
						int num = input - finalLootItems.size() - 1;
						this->inventory.addPotion(finalLootPotions[num]);
						std::cout << finalLootPotions[num].name << " added to backpack!" << std::endl;
						finalLootPotions.erase(finalLootPotions.begin() + num);
						tally = 0;
					}
					else
					{
						std::cout << "Item not found!" << std::endl;
						tally = 0;
					}

				}
			}
			if (input == -2)
			{
				quit = true;
				std::cout << "Departing..." << std::endl;
			}
		}
		//loops so long as there are items left in any inventory of the containe or until the user opts to quit
		if (finalLootItems.empty() && finalLootPotions.empty() && container.gold == 0)
		{
			std::cout << "You've pillaged every morsel!" << std::endl;
			quit = true;
		}
	} while (input != -2 && quit == false);
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

void Character::checkPlayer()
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Class: " << this->characterClass << std::endl;
	std::cout << "Level: " << this->level << std::endl;
	std::cout << std::endl;
	std::cout << "Health: " << this->health << std::endl;
	std::cout << "Mana: " << this->mana << std::endl;
	std::cout << "Strength: " << this->strength << std::endl;
	std::cout << "Agility: " << this->agility << std::endl;
	std::cout << "Arcane: " << this->arcane << std::endl;
	std::cout << "Faith: " << this->faith << std::endl;
	std::cout << "Luck: " << this->luck << std::endl;
	std::cout << std::endl;
	std::cout << "Health Points: " << this->healthPoints << "/" << this->maxHealthPoints << std::endl;
	std::cout << "Mana Points: " << this->manaPoints << "/" << this->maxManaPoints << std::endl;
	std::cout << std::endl;
	std::cout << "Speed: " << this->speed << std::endl;
	std::cout << "Damage Reduction: " << this->damageReduction << "%" << std::endl;
	std::cout << "Critical Chance: " << this->critChance << "%" << std::endl;
	std::cout << "Dodge Chance: " << this->dodgeChance << "%" << std::endl;
	std::cout << "Block Chance: " << this->blockChance << "%" << std::endl;
	std::cout << "Block Amount: " << this->blockAmount << std::endl;
	std::cout << std::endl;
	std::cout << "Experience: " << this->experience << "/" << this->experienceToNextLevel << std::endl;
	std::cout << "Gold: " << this->gold << std::endl;
}

void Character::checkCharacterIntro(Character player)
{
	//get all equipped items the character has access to
	std::vector<Potion> potions = this->inventory.potions;
	std::vector<Item> items = this->inventory.getEquippedItems();
	Item mainHand1;
	Item mainHand2;
	Item offHand1;
	Item offHand2;
	Item amulet;
	Item ring1;
	Item ring2;
	Item misc;

	//until I figure out how to ensure this is set to false by default, we need this because its true 
	//  by default 
	mainHand1.hasBeenInitialized = false;
	mainHand2.hasBeenInitialized = false;
	offHand1.hasBeenInitialized = false;
	offHand2.hasBeenInitialized = false;
	amulet.hasBeenInitialized = false;
	ring1.hasBeenInitialized = false;
	ring2.hasBeenInitialized = false;
	misc.hasBeenInitialized = false;
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].slot == Item::MAINHAND1)
		{
			mainHand1 = items[i];
		}
		else if (items[i].slot == Item::MAINHAND2)
		{
			mainHand2 = items[i];
		}
		else if (items[i].slot == Item::OFFHAND1)
		{
			offHand1 = items[i];
		}
		else if (items[i].slot == Item::OFFHAND2)
		{
			offHand2 = items[i];
		}
		else if (items[i].slot == Item::AMULET)
		{
			amulet = items[i];
		}
		else if (items[i].slot == Item::RING1)
		{
			ring1 = items[i];
		}
		else if (items[i].slot == Item::RING2)
		{
			ring2 = items[i];
		}
		else if (items[i].slot == Item::MISC)
		{
			misc = items[i];
		}
	}

	//Level difference text
	float levelDifference = (player.level / this->level);

	//should only print out when they're above 76% health to show that their stature is getting weaker as they take damage
	//their level is 50% greater than the player's level
	if (this->namedCharacter)
	{
		if (levelDifference < .66 && this->healthPoints > maxHealthPoints / 1.34)
		{
			std::cout << dye::light_yellow(this->name) << " has a foreboding presence. You should take care..." << std::endl;
		}
		//their level is 50% less than the player's level
		else if (levelDifference > 1.5 && this->healthPoints > maxHealthPoints / 1.34)
		{
			std::cout << dye::light_yellow(this->name) << " shuffles about nervously. You can take them." << std::endl;
		}
		else if (levelDifference > .83 && levelDifference < 1.25 && this->healthPoints > maxHealthPoints / 1.34)
		{
			std::cout << dye::light_yellow(this->name) << " and you appear to be evenly matched." << std::endl;
		}
	}
	else
	{
		if (levelDifference < .66 && this->healthPoints > maxHealthPoints / 1.34)
		{
			std::cout << "The " << dye::light_yellow(this->name) << " has a foreboding presence. You should take care..." << std::endl;
		}
		//their level is 50% less than the player's level
		else if (levelDifference > 1.5 && this->healthPoints > maxHealthPoints / 1.34)
		{
			std::cout << "The " << dye::light_yellow(this->name) << " shuffles about nervously. You can take them." << std::endl;
		}
		else if (levelDifference > .83 && levelDifference < 1.25 && this->healthPoints > maxHealthPoints / 1.34)
		{
			std::cout << "The " << dye::light_yellow(this->name) << " and you appear to be evenly matched." << std::endl;
		}
	}
	
	//weapon specific
	//what weapon(s) they are using?

	std::string weaponTypes[] = { "nothing", "dagger", "straight sword", "great sword",
		"fist weapon", "mace", "great mace", "hatchet", "axe", "great axe",
		"thrusting sword", "spear", "great spear", "halberd", "polehammer", "parrying shield",
		"average-sized shield", "great shield", "longbow", "compound bow",
		"great bow", "miniature crossbow", "crossbow", "handheld ballista",
		"talisman", "chime", "arcane tome", "magic wand", "magic staff", "magic orb" };

	//if they have an item in each hand
	if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == true)
	{
		std::cout << "They carry a "
			<< weaponTypes[mainHand1.weaponType] << " in their main hand, ";
		std::cout << "and a " << weaponTypes[offHand1.weaponType] << " in their off hand." << std::endl;
	}
	//if they have an item in both of their hands, plus weapons they can readily switch to
	else if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == true
		&& mainHand2.hasBeenInitialized == true && offHand2.hasBeenInitialized == true)
	{
		std::cout << "They carry a "
			<< weaponTypes[mainHand1.weaponType] << " in their main hand, ";
		std::cout << "and a " << weaponTypes[offHand1.weaponType] << " in their off hand." << std::endl;
		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " and a "
			<< weaponTypes[offHand2.weaponType] << " at the ready on their person." << std::endl;
	}
	//if they have an item in both of their hands, plus a twohanded weapon they can switch to
	else if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == true
		&& mainHand2.hasBeenInitialized == true && mainHand2.twoHanded == true)
	{
		std::cout << "They carry a "
			<< weaponTypes[mainHand1.weaponType] << " in their main hand,";
		std::cout << "and a " << weaponTypes[offHand1.weaponType] << " in their off hand." << std::endl;
		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " at the ready on their person." << std::endl;
	}
	//if they only have one weapon equipped
	else if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == false
		&& offHand2.hasBeenInitialized == false && mainHand1.hasBeenInitialized == false)
	{
		std::cout << "They carry nothing but a "
			<< weaponTypes[mainHand1.weaponType] << " in their main hand." << std::endl;
	}
	//if they have a two handed weapon and nothing else
	else if (mainHand1.hasBeenInitialized == true && mainHand1.twoHanded == true
		&& offHand1.hasBeenInitialized == false && offHand2.hasBeenInitialized == false
		&& mainHand2.hasBeenInitialized == false)
	{
		std::cout << "They wield a " << weaponTypes[mainHand1.weaponType] << " with both hands." << std::endl;
	}
	//if they have a two handed weapon and another twohanded weapon to switch to
	else if (mainHand1.hasBeenInitialized == true && mainHand1.twoHanded == true
		&& mainHand2.hasBeenInitialized == true && mainHand2.twoHanded == true)
	{
		std::cout << "They wield a " << weaponTypes[mainHand1.weaponType] << " with both hands." << std::endl;
		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " holstered on their back." << std::endl;
	}
	//if they have a two handed weapon and two more one handed items to switch to
	else if (mainHand1.hasBeenInitialized == true && mainHand1.twoHanded == true
		&& mainHand2.hasBeenInitialized == true && offHand2.hasBeenInitialized == true)
	{
		std::cout << "They wield a " << weaponTypes[mainHand1.weaponType] << " with both hands." << std::endl;
		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " and a " << weaponTypes[offHand1.weaponType] << " at the ready on their person." << std::endl;
	}
	else {
		std::cout << "They have the gall to approach you empty handed." << std::endl;
	}

	//what armor they are wearing?

	std::string armorTypes[] = { "not armor", "leather", "padded leather",
		"studded leather", "chainmail", "lamellar", "metal scale",
		"ringmail", "chain-plate", "full plate" };

	int numLight = 0;
	int numMedium = 0;
	int numHeavy = 0;

	//count the number of light, medium, and heavy armor pieces they have equipped
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].armorType == Item::LEATHER ||
			items[i].armorType == Item::PADDED ||
			items[i].armorType == Item::STUDDEDLEATHER)
		{
			numLight++;
		}
		else if (items[i].armorType == Item::CHAIN ||
			items[i].armorType == Item::LAMELLAR ||
			items[i].armorType == Item::SCALE)
		{
			numMedium++;
		}
		else if (items[i].armorType == Item::CHAINPLATE ||
			items[i].armorType == Item::FULLPLATE ||
			items[i].armorType == Item::BEASTSCALE)
		{
			numHeavy++;
		}
	}

	//outputs the kind of armor they are wearing at a glance. More detailed descriptions
	//  can be found in the check enemy menu
	if (numLight > 0 && numMedium == 0 && numHeavy == 0)
	{
		std::cout << "They are wearing light armor." << std::endl;
	}
	else if (numLight == 0 && numMedium > 0 && numHeavy == 0)
	{
		std::cout << "They are wearing medium armor." << std::endl;
	}
	else if (numLight == 0 && numMedium == 0 && numHeavy > 0)
	{
		std::cout << "They are wearing heavy armor." << std::endl;
	}

	//mixed armor types
	else if (numLight > 0 && numMedium > 0 && numHeavy == 0)
	{
		std::cout << "They are wearing a mixture of light and medium armor." << std::endl;
	}
	else if (numLight > 0 && numMedium == 0 && numHeavy > 0)
	{
		std::cout << "They are wearing a mixture of light and heavy armor." << std::endl;
	}
	else if (numLight == 0 && numMedium > 0 && numHeavy > 0)
	{
		std::cout << "They are wearing a mixture of medium and heavy armor." << std::endl;
	}
	else if (numLight > 0 && numMedium > 0 && numHeavy > 0)
	{
		std::cout << "They are wearing a mixture of light, medium, and heavy armor." << std::endl;
	}

	//if they have no armor equipped
	else if (numLight == 0 && numMedium == 0 && numHeavy == 0)
	{
		std::cout << "They are daring not to wear any armor." << std::endl;
	}
}
void Character::checkCharacter(Character player)
{
	//get all equipped items the character has access to
	std::vector<Potion> potions = this->inventory.potions;
	std::vector<Item> items = this->inventory.getEquippedItems();
	Item mainHand1;
	Item mainHand2;
	Item offHand1;
	Item offHand2;
	Item amulet;
	Item ring1;
	Item ring2;
	Item misc;

	//until I figure out how to ensure this is set to false by default, we need this because its true 
	//  by default 
	mainHand1.hasBeenInitialized = false;
	mainHand2.hasBeenInitialized = false;
	offHand1.hasBeenInitialized = false;
	offHand2.hasBeenInitialized = false;
	amulet.hasBeenInitialized = false;
	ring1.hasBeenInitialized = false;
	ring2.hasBeenInitialized = false;
	misc.hasBeenInitialized = false;
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].slot == Item::MAINHAND1)
		{
			mainHand1 = items[i];
		}
		else if (items[i].slot == Item::MAINHAND2)
		{
			mainHand2 = items[i];
		}
		else if (items[i].slot == Item::OFFHAND1)
		{
			offHand1 = items[i];
		}
		else if (items[i].slot == Item::OFFHAND2)
		{
			offHand2 = items[i];
		}
		else if (items[i].slot == Item::AMULET)
		{
			amulet = items[i];
		}
		else if (items[i].slot == Item::RING1)
		{
			ring1 = items[i];
		}
		else if (items[i].slot == Item::RING2)
		{
			ring2 = items[i];
		}
		else if (items[i].slot == Item::MISC)
		{
			misc = items[i];
		}
	}

	//Health based text

	//100%
	if (this->healthPoints == this->maxHealthPoints)
	{
		std::cout << "The " << this->name << " is completely healthy." << std::endl;
	}

	//75%
	else if (this->healthPoints >= maxHealthPoints * .75 && this->healthPoints <= maxHealthPoints)
	{
		std::cout << "The " << this->name << " has taken a few hits. Are they bleeding?" << std::endl;
	}

	//50%
	else if (this->healthPoints >= maxHealthPoints * .5 && this->healthPoints < maxHealthPoints * .75)
	{
		std::cout << "The " << this->name << " has a few large wounds. Best not to let them become scars." << std::endl;
	}

	//25%
	else if (this->healthPoints >= maxHealthPoints * .25 && this->healthPoints < maxHealthPoints * .75)
	{
		std::cout << "The " << this->name << " is on their last legs. Show them no mercy!" << std::endl;
	}

	//10%
	else if (this->healthPoints < maxHealthPoints * .25)
	{
		std::cout << "It's a marvel that the " << this->name << " is still standing after the punishment they've endured." << std::endl;
	}

	//Mana based text

	//100%
	if (this->manaPoints == this->maxManaPoints)
	{
		std::cout << "They are alert and attentive. Their mana must be close to full." << std::endl;
	}

	//75%
	else if (this->manaPoints >= maxManaPoints * .75 && this->manaPoints < maxManaPoints)
	{
		std::cout << "They look like they can keep the magic up for a while longer." << std::endl;
	}

	//50%
	else if (this->manaPoints >= maxManaPoints * .5 && this->manaPoints <= maxManaPoints * .75)
	{
		std::cout << "They look somewhat disoriented. Are they running out of mana?" << std::endl;
	}

	//25%
	else if (this->manaPoints >= maxManaPoints * .25&& this->manaPoints <= maxManaPoints * .5)
	{
		std::cout << "They look very disoriented. They must be running dry on mana." << std::endl;
	}

	//10%
	else if (this->manaPoints <= maxManaPoints* .25)
	{
		std::cout << "They look like they don't have the magical energy to muster a spark." << std::endl;
	}

	checkCharacterIntro(player);

	//if they are wearing jewelry

	//if they have an item in each jewelry slot
	if (amulet.hasBeenInitialized == true && ring1.hasBeenInitialized == true
		&& ring2.hasBeenInitialized == true)
	{
		std::cout << "They are wearing a plethora of jewelry." << std::endl;
	}

	//if they have an amulet
	else if (amulet.hasBeenInitialized == true && ring1.hasBeenInitialized == false
		&& ring2.hasBeenInitialized == false)
	{
		std::cout << "An amulet gleams in the light upon " << this->name << "'s neck." << std::endl;
	}

	//if they have an amulet and a ring
	else if (amulet.hasBeenInitialized == true && ring1.hasBeenInitialized == true
		&& ring2.hasBeenInitialized == false)
	{
		std::cout << "An amulet gleams in the light upon " << this->name <<
			"'s neck, and a ring glints on one of their fingers." << std::endl;
	}

	//if they are wearing just a ring
	else if (amulet.hasBeenInitialized == false && ring1.hasBeenInitialized == true
		&& ring2.hasBeenInitialized == false)
	{
		std::cout << "A ring glints on one of " << this->name << "'s fingers." << std::endl;
	}

	//if they are wearing two rings
	else if (amulet.hasBeenInitialized == false && ring1.hasBeenInitialized == true
		&& ring2.hasBeenInitialized == true)
	{
		std::cout << "Two rings glint in the light on " << this->name << "'s fingers." << std::endl;
	}

	//what potions do they have on them?

	std::string effects[] = { "Restores Health", "Restores Mana", "Cures Diseases" };
	int healingPotionCount = 0;
	int manaPotionCount = 0;
	int cureDiseaseCount = 0;

	for (int i = 0; i < potions.size(); i++)
	{
		if (potions[i].effects == Potion::HEALING)
		{
			healingPotionCount += 1;
		}
		else if (potions[i].effects == Potion::MANA)
		{
			manaPotionCount += 1;
		}
		else if (potions[i].effects == Potion::CUREDISEASE)
		{
			cureDiseaseCount += 1;
		}
	}

	//if they have all of one potion type
	if (healingPotionCount > 0 && manaPotionCount == 0 && cureDiseaseCount == 0)
	{
		std::cout << "Healing potions clink about on the " << this->name << "'s belt" << std::endl;
	}
	else if (healingPotionCount == 0 && manaPotionCount > 0 && cureDiseaseCount == 0)
	{
		std::cout << "Mana potions clink about on the " << this->name << "'s belt" << std::endl;
	}
	else if (healingPotionCount == 0 && manaPotionCount == 0 && cureDiseaseCount > 0)
	{
		std::cout << "Cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
	}

	//if they have a mixture of types
	else if (healingPotionCount > 0 && manaPotionCount > 0 && cureDiseaseCount == 0)
	{
		std::cout << "Healing and mana potions clink about on the " << this->name << "'s belt" << std::endl;
	}
	else if (healingPotionCount > 0 && manaPotionCount == 0 && cureDiseaseCount > 0)
	{
		std::cout << "Healing and cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
	}
	else if (healingPotionCount == 0 && manaPotionCount > 0 && cureDiseaseCount > 0)
	{
		std::cout << "Mana and cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
	}
	else if (healingPotionCount > 0 && manaPotionCount > 0 && cureDiseaseCount > 0)
	{
		std::cout << "Healing, mana, and cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
	}

	//do they have enough gold to be visible outside their pockets?
	if (this->gold >= 50)
	{
		std::cout << "A coin purse hangs from the " << this->name << "'s belt." << std::endl;
	}
	else if (this->gold >= 100)
	{
		std::cout << "A heavy coin purse hangs from the " << this->name << "'s belt." << std::endl;
	}
	else if (this->gold >= 200)
	{
		std::cout << "A bulging coin purse hangs from the " << this->name << "'s belt." << std::endl;
	}
	else if (this->gold >= 500)
	{
		std::cout << "A sack of gold hangs from the " << this->name << "'s belt." << std::endl;
	}
	else if (this->gold >= 1000)
	{
		std::cout << "A small chest, clinking with gold as they move, hangs from the " << this->name << "'s back." << std::endl;
	}
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