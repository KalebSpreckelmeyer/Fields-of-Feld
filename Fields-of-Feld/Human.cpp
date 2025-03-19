#include "Human.h"
#include "Creature.h"
#include <string>
#include "Spell.h"
#include <cmath>
#include <iostream>
#include "color.hpp"
#include <algorithm> 
#include <iomanip>
#include "optional"

Human::Human()
{
}

Human::Human(bool isPlayer, bool isAlly, CharacterClass classChoice, Personality personality, float flatDefense, float health, float mana, float strength, float agility, float charisma,
	float intelligence, float arcane, float faith, float luck, float weightBurden, float maxWeightBurden,
	double experience, double experienceToNextLevel,
	int gold)
	: Character(isAlly, namedCharacter, true, true, false,
		"NAME", "DESC", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, inventory, 1.0f,
		1.0f, CombatFlags::NEUTRAL),
	flatDefense(flatDefense), isPlayer(isPlayer), classChoice(classChoice), health(health), fatigue(fatigue),
	strength(strength), agility(agility), charisma(charisma), intelligence(intelligence), 
	arcane(arcane), faith(faith), luck(luck), weightBurden(weightBurden),
	maxWeightBurden(maxWeightBurden), experience(experience), experienceToNextLevel(experienceToNextLevel),
	gold(gold)
{
	setInitialHumanStats();
}

void Human::setInitialHumanStats() {

	//Get all equipped items
	Weapon* mainHand = nullptr, * offHand = nullptr, * reserve1 = nullptr, * reserve2 = nullptr;
	Armor* head = nullptr, * chest = nullptr, * legs = nullptr, * arms = nullptr;
	Trinket* amulet = nullptr, * ring1 = nullptr, * ring2 = nullptr, * misc = nullptr;
	inventory.getEquippedItems(mainHand, offHand, reserve1, reserve2, head, chest, legs, arms, amulet, ring1, ring2, misc);

	float backPackWeight = 0;
	for (Item* item : inventory.backpackItems)
	{
		if (item) backPackWeight += item->weight;
	}

	//Separate the Item pointers into their respective types
	float equipmentWeight = 0;
	if (mainHand) equipmentWeight += mainHand->weight;
	if (offHand) equipmentWeight += offHand->weight;
	if (reserve1) equipmentWeight += reserve1->weight;
	if (reserve2) equipmentWeight += reserve2->weight;
	if (head) equipmentWeight += head->weight;
	if (chest) equipmentWeight += chest->weight;
	if (legs) equipmentWeight += legs->weight;
	if (arms) equipmentWeight += arms->weight;
	if (amulet) equipmentWeight += amulet->weight;
	if (ring1) equipmentWeight += ring1->weight;
	if (ring2) equipmentWeight += ring2->weight;

	// ------------------------------------------------------- ADD MORE ADVANCED CALCULATIONS FOR DEFENSE HERE 
	float armorValue = 0;
	//if (head) armorValue += head->defense;
	//if (chest) armorValue += chest->defense;
	//if (legs) armorValue += legs->defense;
	//if (arms) armorValue += arms->defense;

	//exploratory values change as needed
	damageResistance = armorValue / (armorValue + 500);

	//exploratory values change as needed
	damageThreshold = armorValue * 0.1;

	//Experience needed to level up per level
	double baseXP = 100;
	experienceToNextLevel = baseXP * (std::pow(1.15, static_cast<double>(level)));

	//Max health calculation
	maxHealthPoints = (health * 10) + (strength * 2) + (fatigue / 3) + (agility / 3) + (charisma / 3) + (intelligence / 3) +
		(arcane / 3) + (faith / 3) + (luck / 3);
	healthPoints = maxHealthPoints;

	//Max mana calculation
	maxFatiguePoints = (fatigue * 10) + (arcane * 2) + (intelligence * 2) + (faith * 2);
	fatiguePoints = maxFatiguePoints;

	//crit chance calculation
	critChance = luck * 0.5f + arcane * 0.25f + agility * 0.1f + strength * 0.1f;

	//crit chance caps at 50%

	// Replace the problematic line with the following:
	critChance = std::min<float>(critChance, 50.0f);
	//weight burden calculation
	weightBurden = equipmentWeight + (backPackWeight / 3);

	//max weight burden calculation
	maxWeightBurden = (strength * 10) + (agility * 5);

	//speed calculation

	//base speed values before weight modification
	speed = sqrt((agility * 15) + (strength * 10)) * 12 - (weightBurden);

	float burdenRatio = weightBurden / maxWeightBurden;

	if (burdenRatio > 1.0) {
		speed *= 0.2;  // If overburdened, severe reduction
	}
	else if (burdenRatio > 0.75) {
		speed *= 1.0 - ((burdenRatio - 0.75) * 2); // Scale from 100% to 50%
	}
	else if (burdenRatio > 0.5) {
		speed *= 1.0 - ((burdenRatio - 0.5) * 0.5); // Scale from 100% to 75%
	}

	// Ensure speed doesn't drop below 1
	speed = max(speed, 1.0f);

	//dodge chance calculation
	dodgeChance = (agility * 0.5) + (speed / 50) - (weightBurden / 100);
	dodgeChance = 75 * (dodgeChance / (dodgeChance + 50));  // Soft cap at 75%
	dodgeChance = max(dodgeChance, 5);  // Minimum 5% dodge chance

	//block chance calculation
	float stability = 0;
	if (offHand) stability = offHand->stability;
	blockChance = (strength * 0.25) + (speed / 100) + ( stability / 10);
	blockChance = 75 * (blockChance / (blockChance + 50));  // Soft cap at 75%
}

void Human::updateHumanStats() {

}

void Human::getSpells()
{

}
Human* Human::setCharacterClass(Human::CharacterClass classChoice)
{
	switch (classChoice)
	{
	case Human::WIZARD:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::KNIGHT:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::CLERIC:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::HUNTER:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::HIGHLANDER:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::BATTLEMAGE:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::WRETCH:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	case Human::BANDIT:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	default:
	{
		Human* human = new Human();
		//Wizard stats
		human->isAlive = true;
		human->isPlayer = true;
		human->health = 5;
		human->fatigue = 15;
		human->strength = 5;
		human->agility = 5;
		human->charisma = 5;
		human->intelligence = 15;
		human->arcane = 15;
		human->faith = 5;
		human->luck = 5;
		return human;
	}
	}
}
float Human::softCapMultiplier(float statValue) {
	if (statValue < 30) return statValue;             // Full scaling below 30
	if (statValue < 60) return 30 + (statValue - 30) * 0.75f;  // 75% scaling from 30-60
	return 52.5f + (statValue - 60) * 0.5f;           // 50% scaling beyond 60
}
void Human::takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition, 
	ThrownConsumable* consumable, Spell* spell, std::optional<std::vector<Character*>>& allies, 
	std::optional<std::vector<Character*>>& enemyAllies)
{
	//if (!allies)
	//{

	//}
	////initial sanity checks
	//if (attacker == nullptr)
	//{
	//	std::cout << dye::light_red("ERROR: No attacker provided for dealDamage function") << std::endl;
	//	return;
	//}
	//if (target == nullptr)
	//{
	//	std::cout << dye::light_red("ERROR: No target provided for dealDamage function") << std::endl;
	//	return;
	//}
	//if (weapon == nullptr && consumable == nullptr && spell == nullptr)
	//{
	//	std::cout << dye::light_red("ERROR: No weapon, consumable, or spell provided for dealDamage function") << std::endl;
	//	return;
	//}

	////checks if the attacker is a human or a creature
	//if (Human* humanAttacker = dynamic_cast<Human*>(attacker))
	//{
	//	//random number generator for crit chance, rolls a number between 1 - (100 - luck ). If the number is less than the crit chance, it's a crit
	//	int randomNum = (rand() % 100 - humanAttacker->luck) + 1;

	//	//MAGIC
	//	if (weapon->weaponType == Weapon::WeaponType::STAFF || weapon->weaponType == Weapon::WeaponType::CHIME ||
	//		weapon->weaponType == Weapon::WeaponType::ORB || weapon->weaponType == Weapon::WeaponType::TALISMAN ||
	//		weapon->weaponType == Weapon::WeaponType::TOME || weapon->weaponType == Weapon::WeaponType::WAND)
	//	{
	//		//spell damage calculation
	//		float spellDamage = spell->magnitude;

	//		// Apply Crits
	//		bool isCritical = (rand() % 100) < critChance;
	//		float critMultiplier = isCritical ? 1.5f : 1.0f;
	//		spellDamage *= critMultiplier;
	//		if (humanAttacker->isPlayer)
	//		{
	//			for (Effect* effect : spell->effects)
	//			{
	//				//don't want to run this code if the effect is a summoned animal
	//				if (effect->doesDamage || spell->doesDamage)
	//				{
	//					spell->applied = true;
	//					effect->applyEffect(*attacker, *target, std::nullopt, enemyAllies, *effect);
	//					for (int i = 0; i < 101;)
	//					{
	//						target->healthPoints -= spellDamage;
	//						if (critMultiplier > 1.0f) std::cout << " " << dye::light_red(" Critical Hit!") << std::endl;
	//						std::cout << " " << dye::light_yellow(target->name) << " takes " << spellDamage << " points of damage from " << humanAttacker->name << "'s " << spell->name << "!" << std::endl;
	//						if (target->healthPoints <= 0) target->killCharacter();
	//						i += (100 - spell->attackSpeed);
	//					}
	//					return;
	//				}
	//				else
	//				{
	//					spell->applied = true;
	//					effect->applyEffect(*attacker, *target, allies, *effect);

	//				}
	//			}
	//			
	//		}
	//		else
	//		{
	//			for (Effect* effect : spell->effects)
	//			{
	//				if (effect->doesDamage || spell->doesDamage)
	//				{
	//					spell->applied = true;
	//					effect->applyEffect(*attacker, *target, enemyAllies, *effect);
	//					for (int i = 0; i < 101;)
	//					{
	//						target->healthPoints -= spellDamage;
	//						if (critMultiplier > 1.0f) std::cout << " " << dye::light_red(" Critical Hit!") << std::endl;
	//						std::cout << " " << dye::light_yellow(" You") << " take " << spellDamage << " points of damage from " << humanAttacker->name << "'s " << spell->name << "!" << std::endl;
	//						if (target->healthPoints <= 0) target->killCharacter();
	//						i += (100 - spell->attackSpeed);
	//					}
	//					return;
	//				}
	//				else
	//				{
	//					spell->applied = true;
	//					effect->applyEffect(*attacker, *target, allies, *effect);

	//				}
	//			}
	//			
	//		}
	//	}
	//	//THROWN CONSUMABLE
	//	
	//	//sanity check for archery and melee
	//	if (weapon == nullptr)
	//	{
	//		std::cout << dye::light_red("ERROR: No weapon provided for dealDamage function") << std::endl;
	//		return;
	//	}
	//	//ARCHERY AND MELEE
	//	else
	//	{
	//		
	//		//MELEE
	//		else
	//		{
	//			if (weapon->weaponType == Weapon::WeaponType::STAFF || weapon->weaponType == Weapon::WeaponType::CHIME ||
	//				weapon->weaponType == Weapon::WeaponType::ORB || weapon->weaponType == Weapon::WeaponType::TALISMAN ||
	//				weapon->weaponType == Weapon::WeaponType::TOME || weapon->weaponType == Weapon::WeaponType::WAND)
	//			{
	//				return;
	//			}
	//			
	//		}
	//	}
	//}
	//else {
	//	std::cout << dye::light_red("ERROR: Attacker is not a valid character type") << std::endl;
	//	return;
	//}
}