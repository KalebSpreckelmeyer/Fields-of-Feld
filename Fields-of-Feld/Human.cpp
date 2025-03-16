#include "Human.h"
#include "Creature.h"
#include <string>
#include <cmath>
#include <iostream>
#include "color.hpp"
#include <algorithm> 
#include <iomanip>

Human::Human()
{
}

Human::Human(bool isPlayer, CharacterClass classChoice, Personality personality, float health, float mana, float strength, float agility, float charisma,
	float intelligence, float arcane, float faith, float luck, float weightBurden, float maxWeightBurden,
	double experience, double experienceToNextLevel,
	int gold)
	: Character(false, true, true, false,
		"NAME", "DESC", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, inventory, 1.0f,
		1.0f, CombatFlags::NEUTRAL),
	isPlayer(isPlayer), classChoice(classChoice), health(health), mana(mana),
	strength(strength), agility(agility), charisma(charisma), intelligence(intelligence),
	arcane(arcane), faith(faith), luck(luck), weightBurden(weightBurden),
	maxWeightBurden(maxWeightBurden), experience(experience), experienceToNextLevel(experienceToNextLevel),
	gold(gold)
{
	setInitialHumanStats();
}
Human::~Human()
{
}

void Human::setInitialHumanStats() {

	//Get all equipped items
	Item* mainHand = nullptr, * offHand = nullptr, * reserve1 = nullptr, * reserve2 = nullptr;
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

	float armorValue = 0;
	if (head) armorValue += head->defense;
	if (chest) armorValue += chest->defense;
	if (legs) armorValue += legs->defense;
	if (arms) armorValue += arms->defense;

	//exploratory values change as needed
	damageResistance = armorValue / (armorValue + 500);

	//exploratory values change as needed
	damageThreshold = armorValue * 0.1;

	//Experience needed to level up per level
	double baseXP = 100;
	experienceToNextLevel = baseXP * (std::pow(1.15, static_cast<double>(level)));

	//Max health calculation
	maxHealthPoints = (health * 10) + (strength * 2) + (mana / 3) + (agility / 3) + (charisma / 3) + (intelligence / 3) +
		(arcane / 3) + (faith / 3) + (luck / 3);
	healthPoints = maxHealthPoints;

	//Max mana calculation
	maxManaPoints = (mana * 10) + (arcane * 2) + (intelligence * 2) + (faith * 2);
	manaPoints = maxManaPoints;


	//crit chance calculation
	critChance = luck * 1 + agility * 0.1 + strength * 0.1;

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
	float weaponDefense = 0;
	if (offHand)
	{
		weaponDefense = dynamic_cast<Weapon*>(offHand)->defense;
	}

	blockChance = (strength * 0.25) + (speed / 100) + (weaponDefense / 10);
	blockChance = 75 * (blockChance / (blockChance + 50));  // Soft cap at 75%
}

void Human::updateHumanStats() {

}

void Human::getSpells()
{

}
void Human::setCharacterClass(Human::CharacterClass classChoice)
{
	switch (classChoice)
	{
	case Human::WIZARD:
	{
		//Wizard stats
		isAlive = true;
		isPlayer = true;
		health = 5;
		mana = 15;
		strength = 5;
		agility = 5;
		charisma = 5;
		intelligence = 15;
		arcane = 15;
		faith = 5;
		luck = 5;
		break;
	}
	case Human::KNIGHT:
	{
		//Knight stats
		isAlive = true;
		isPlayer = true;
		health = 15;
		mana = 5;
		strength = 15;
		agility = 5;
		charisma = 5;
		intelligence = 5;
		arcane = 5;
		faith = 5;
		luck = 5;
		break;
	}
	case Human::CLERIC:
	{
		//Cleric stats
		isAlive = true;
		isPlayer = true;
		health = 10;
		mana = 10;
		strength = 10;
		agility = 5;
		charisma = 10;
		intelligence = 5;
		arcane = 5;
		faith = 15;
		luck = 5;
		break;
	}
	case Human::HUNTER:
	{
		//Hunter stats
		isAlive = true;
		isPlayer = true;
		health = 10;
		mana = 5;
		strength = 10;
		agility = 15;
		charisma = 5;
		intelligence = 5;
		arcane = 5;
		faith = 5;
		luck = 15;
		break;
	}
	case Human::HIGHLANDER:
	{
		//Highlander stats
		isAlive = true;
		isPlayer = true;
		health = 15;
		mana = 5;
		strength = 15;
		agility = 10;
		charisma = 5;
		intelligence = 5;
		arcane = 5;
		faith = 5;
		luck = 5;
		break;
	}
	case Human::BATTLEMAGE:
	{
		//Battlemage stats
		isAlive = true;
		isPlayer = true;
		health = 10;
		mana = 10;
		strength = 10;
		agility = 10;
		charisma = 5;
		intelligence = 10;
		arcane = 10;
		faith = 5;
		luck = 5;
		break;
	}
	case Human::WRETCH:
	{
		//Wretch stats
		isAlive = true;
		isPlayer = true;
		health = 5;
		mana = 5;
		strength = 5;
		agility = 5;
		charisma = 5;
		intelligence = 5;
		arcane = 5;
		faith = 5;
		luck = 5;
		break;
	}
	case Human::BANDIT:
	{
		//Bandit stats
		isAlive = true;
		isPlayer = true;
		health = 10;
		mana = 5;
		strength = 10;
		agility = 10;
		charisma = 5;
		intelligence = 5;
		arcane = 5;
		faith = 5;
		luck = 10;
		break;
	}
	default:
	{
		//Default stats
		health = 10;
		mana = 10;
		strength = 10;
		agility = 10;
		charisma = 10;
		intelligence = 10;
		arcane = 10;
		faith = 10;
		luck = 10;
		break;
	}
	}
}

void Human::takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition, ThrownConsumable* consumable, Spell* spell)
{
	//initial sanity checks
	if (attacker == nullptr)
	{
		std::cout << dye::light_red("ERROR: No attacker provided for dealDamage function") << std::endl;
		return;
	}
	if (target == nullptr)
	{
		std::cout << dye::light_red("ERROR: No target provided for dealDamage function") << std::endl;
		return;
	}
	if (weapon == nullptr && consumable == nullptr && spell == nullptr)
	{
		std::cout << dye::light_red("ERROR: No weapon, consumable, or spell provided for dealDamage function") << std::endl;
		return;
	}

	//checks if the attacker is a human or a creature
	if (Human* humanAttacker = dynamic_cast<Human*>(attacker))
	{
		//random number generator for crit chance, rolls a number between 1 - (100 - luck ). If the number is less than the crit chance, it's a crit
		int randomNum = (rand() % 100 - humanAttacker->luck) + 1;

		//MAGIC
		if (weapon->weaponType == Weapon::WeaponType::STAFF || weapon->weaponType == Weapon::WeaponType::CHIME ||
			weapon->weaponType == Weapon::WeaponType::ORB || weapon->weaponType == Weapon::WeaponType::TALISMAN ||
			weapon->weaponType == Weapon::WeaponType::TOME || weapon->weaponType == Weapon::WeaponType::WAND)
		{
			if (isPlayer)
			{

			}
			else
			{

			}
		}


		//THROWN CONSUMABLE
		//initally checks if the attacker is using a thrown consumable
		if (consumable)
		{
			//damage falloff variables
			float minDamage = consumable->damage * .3f;
			float maxDamage = consumable->damage * 1.3f;
			float nearRange = consumable->reach * 0.1;

			float farRange = consumable->reach * 4;

			//normalized distance of the attacker from their target
			float normalizedDistance = std::clamp((target->distanceFromPlayer - nearRange) / (farRange - nearRange), 0.0f, 1.0f);

			//raw damage of the arrow
			float consumableDamage = max((1.0f - normalizedDistance) * maxDamage + normalizedDistance * minDamage, 1.0f);

			//crit damage modifier
			float critDamage = consumableDamage * 1.5f;

			//damage reduction modfiiers
			float critDamageReduction = max(critDamage * this->damageResistance + this->damageThreshold / 2.0f, 0.0f);
			float normalDamageReduction = max(consumableDamage * this->damageResistance + this->damageThreshold, 0.0f);

			//final damage taken, either crit or non crit
			float critDamageTaken = critDamage - critDamageReduction;
			float damageTaken = consumableDamage - normalDamageReduction;

			//ensures that the damage will never be negative 
			if (critDamageTaken < 0) critDamageTaken = 0;
			if (damageTaken < 0) damageTaken = 0;

			//Critical Hit
			if (randomNum <= humanAttacker->critChance)
			{
				//Player landed critical hit
				if (humanAttacker->isPlayer)
				{
					for (Effect* effect : consumable->enchantments)
					{
						effect->applyEffect(*attacker, *target, *effect);
					}
					target->healthPoints -= critDamageTaken;
					attacker->consumeThrownConsumable(consumable);
					std::cout << dye::light_red(" Critical Hit!") << std::endl;
					if (critDamageReduction > 0) std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << "'s armor absorbs " << critDamageReduction << " points of damage from the projectile!" << std::endl;
					std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from"
						<< attacker->name << "'s " << consumable->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
				}
				//NPC landed critical hit
				else
				{
					for (Effect* effect : consumable->enchantments)
					{
						effect->applyEffect(*attacker, *target, *effect);
					}
					target->healthPoints -= critDamageTaken;
					attacker->consumeThrownConsumable(consumable);
					std::cout << dye::light_red(" Critical Hit!") << std::endl;
					if (critDamageReduction > 0) std::cout << std::setprecision(2) << " Your armor absorbs " << critDamageReduction << " points of damage from the projectile!" << std::endl;
					std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
						<< attacker->name << "'s " << consumable->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
				}
			}
			//Normal Hit
			else
			{
				//Player landed normal hit
				if (humanAttacker->isPlayer)
				{
					for (Effect* effect : consumable->enchantments)
					{
						effect->applyEffect(*attacker, *target, *effect);
					}
					target->healthPoints -= damageTaken;
					attacker->consumeThrownConsumable(consumable);
					if (normalDamageReduction > 0) std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << "'s armor absorbs " << normalDamageReduction << " points of damage from the projectile!" << std::endl;
					std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from "
						<< attacker->name << "'s " << consumable->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
				}
				//NPC landed normal hit
				else
				{
					for (Effect* effect : consumable->enchantments)
					{
						effect->applyEffect(*attacker, *target, *effect);
					}
					target->healthPoints -= damageTaken;
					attacker->consumeThrownConsumable(consumable);
					if (normalDamageReduction > 0) std::cout << std::setprecision(2) << " Your armor absorbs " << normalDamageReduction << " points of damage from the projectile!" << std::endl;
					std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
						<< attacker->name << "'s " << consumable->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
				}
			}
		}
		//sanity check for archery and melee
		if (weapon == nullptr)
		{
			std::cout << dye::light_red("ERROR: No weapon provided for dealDamage function") << std::endl;
			return;
		}
		//ARCHERY AND MELEE
		else
		{
			//ARCHERY 
			if (weapon->weaponType == Weapon::WeaponType::LONGBOW || weapon->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
				weapon->weaponType == Weapon::WeaponType::GREATBOW || weapon->weaponType == Weapon::WeaponType::MINICROSSBOW ||
				weapon->weaponType == Weapon::WeaponType::CROSSBOW || weapon->weaponType == Weapon::WeaponType::BALLISTA)
			{
				//archery specific sanity check
				if (ammunition == nullptr)
				{
					std::cout << dye::light_red("ERROR: No ammunition provided for dealDamage function") << std::endl;
					return;
				}

				//This is just Overwatch's damage falloff formula lmao

				//damage falloff variables
				float minDamage = ammunition->damage * .3;
				float maxDamage = ammunition->damage * 1.3;
				float nearRange = ammunition->range * 0.1;

				float farRange = weapon->reach + ammunition->range;

				//normalized distance of the attacker from their target
				float normalizedDistance = std::clamp((target->distanceFromPlayer - nearRange) / (farRange - nearRange), 0.0f, 1.0f);

				//raw damage of the arrow
				float arrowDamage = max((1.0f - normalizedDistance) * maxDamage + normalizedDistance * minDamage, 1.0f);

				//crit damage modifier
				float critDamage = arrowDamage * 1.5;

				//damage reduction modfiiers
				float critDamageReduction = max(critDamage * this->damageResistance + this->damageThreshold / 2, 0.0f);
				float normalDamageReduction = max(arrowDamage * this->damageResistance + this->damageThreshold, 0.0f);

				//final damage taken, either crit or non crit
				float critDamageTaken = critDamage - critDamageReduction;
				float damageTaken = arrowDamage - normalDamageReduction;

				//ensures that the damage will never be negative 
				if (critDamageTaken < 0) critDamageTaken = 0;
				if (damageTaken < 0) damageTaken = 0;

				//Critical Hit
				if (randomNum <= humanAttacker->critChance)
				{
					//Player landed critical hit
					if (humanAttacker->isPlayer)
					{
						for (Effect* effect : ammunition->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= critDamageTaken;
						attacker->consumeAmmo(ammunition);
						std::cout << dye::light_red(" Critical Hit!") << std::endl;
						if (critDamageReduction > 0) std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << "'s armor absorbs " << critDamageReduction << " points of damage from the projectile!" << std::endl;
						std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from "
							<< attacker->name << "'s " << ammunition->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
					//NPC landed critical hit
					else
					{
						for (Effect* effect : ammunition->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= critDamageTaken;
						attacker->consumeAmmo(ammunition);
						std::cout << dye::light_red(" Critical Hit!") << std::endl;
						if (critDamageReduction > 0) std::cout << std::setprecision(2) << " Your armor absorbs " << critDamageReduction << " points of damage from the projectile!" << std::endl;
						std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
							<< attacker->name << "'s " << ammunition->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
				}
				//Normal Hit
				else
				{
					//Player landed normal hit
					if (humanAttacker->isPlayer)
					{
						for (Effect* effect : ammunition->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= damageTaken;
						attacker->consumeAmmo(ammunition);
						if (normalDamageReduction > 0) std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << "'s armor absorbs " << normalDamageReduction << " points of damage from the projectile!" << std::endl;
						std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from "
							<< attacker->name << "'s " << ammunition->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
					//NPC landed normal hit
					else
					{
						for (Effect* effect : ammunition->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= damageTaken;
						attacker->consumeAmmo(ammunition);
						if (normalDamageReduction > 0) std::cout << std::setprecision(2) << " Your armor absorbs " << normalDamageReduction << " points of damage from the projectile!" << std::endl;
						std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
							<< attacker->name << "'s " << ammunition->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
				}
			}
			//MELEE
			else
			{
				//Calculate crit damage and damage reduction
				float critDamage = weapon->damage * 1.5f;
				float critDamageReduction = max(critDamage * this->damageResistance + this->damageThreshold / 2, 0.0f);
				float normalDamageReduction = max(weapon->damage * this->damageResistance + this->damageThreshold, 0.0f);

				float critDamageTaken = critDamage - critDamageReduction;
				float damageTaken = weapon->damage - normalDamageReduction;

				//ensures that the damage will never be negative
				if (critDamageTaken < 0) critDamageTaken = 0;
				if (damageTaken < 0) damageTaken = 0;

				//Critical Hit

				if (randomNum <= humanAttacker->critChance)
				{
					//Player landed critical hit
					if (humanAttacker->isPlayer)
					{
						target->healthPoints -= critDamageTaken;
						for (Effect* effect : weapon->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						std::cout << dye::light_red(" Critical Hit!") << std::endl;
						if (critDamageReduction > 0) std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name)
							<< "'s armor absorbs" << critDamageReduction << " points of damage from "
							<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
						std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from the "
							<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
					//NPC landed a critical hit
					else
					{
						for (Effect* effect : weapon->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= critDamageTaken;
						std::cout << dye::light_red(" Critical Hit!") << std::endl;
						if (critDamageReduction > 0) std::cout << std::setprecision(2) << " Your armor absorbs" << critDamageReduction
							<< " points of damage from the " << dye::light_yellow(attacker->name) << "'s " << weapon->name << "!" << std::endl;
						std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
							<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
				}
				else
				{
					//NORMAL HIT
					//Player landed normal hit
					if (humanAttacker->isPlayer)
					{
						for (Effect* effect : weapon->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= damageTaken;
						if (critDamageReduction > 0) std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name)
							<< "'s armor absorbs" << critDamageReduction << " points of damage from "
							<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
						std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from the "
							<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
					//NPC landed a normal hit
					else
					{
						for (Effect* effect : weapon->enchantments)
						{
							effect->applyEffect(*attacker, *target, *effect);
						}
						target->healthPoints -= damageTaken;
						if (critDamageReduction > 0) std::cout << std::setprecision(2) << " Your armor absorbs" << critDamageReduction
							<< " points of damage from the " << dye::light_yellow(attacker->name) << "'s " << weapon->name << "!" << std::endl;
						std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
							<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
						if (target->healthPoints <= 0) target->killCharacter();
						return;
					}
				}
			}
		}
	}
	else {
		std::cout << dye::light_red("ERROR: Attacker is not a valid character type") << std::endl;
		return;
	}
}