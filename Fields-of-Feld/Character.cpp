#include "Character.h"
#include "Creature.h"
#include "Spell.h"
#include "Human.h"
#include <vector>
#include <iostream>
#include "color.hpp"
#include <random>
#include <iomanip>
#include "Weapon.h"
#include "optional"
#include "OffensiveEffect.h"
#include "DefensiveEffect.h"
#include "PassiveEffect.h"
#include "ConsumableEffect.h"
#include "Consumable.h"
#include "Food.h"
#include "Drink.h"
#include "Book.h"
#include "Potion.h"

Character::Character(bool isAlly, bool namedCharacter, bool isAlive, bool active, bool alert,
	std::string name, std::string description, float confidenceLevel,
	float healthPoints, float maxHealthPoints, float fatiguePoints,
	float maxFatiguePoints, float speed, float critChance, float dodgeChance,
	float blockChance, float bleedPoints, float maxBleedPoints,
	float burnPoints, float maxBurnPoints, float poisonPoints,
	float maxPoisonPoints, float frostPoints, float maxFrostPoints,
	float shockPoints, float maxShockPoints, float sleepPoints,
	float maxSleepPoints, const Inventory& inventory,
	float level, CombatFlags combatFlag) : id(IDManager::getNextId()),
	isAlly(isAlly), namedCharacter(namedCharacter), isAlive(isAlive), active(active), alert(alert), name(name), description(description),
	confidenceLevel(confidenceLevel), healthPoints(healthPoints), maxHealthPoints(maxHealthPoints), fatiguePoints(fatiguePoints),
	maxFatiguePoints(maxFatiguePoints), speed(speed), critChance(critChance), dodgeChance(dodgeChance), blockChance(blockChance),
	bleedPoints(bleedPoints), maxBleedPoints(maxBleedPoints),
	burnPoints(burnPoints), maxBurnPoints(maxBurnPoints), poisonPoints(poisonPoints), maxPoisonPoints(maxPoisonPoints), frostPoints(frostPoints),
	maxFrostPoints(maxFrostPoints), shockPoints(shockPoints), maxShockPoints(maxShockPoints),
	sleepPoints(sleepPoints), maxSleepPoints(maxSleepPoints), inventory(inventory), level(level), combatFlag(combatFlag)
{

}

int Character::getId() const {
	return id;
}

void Character::addCombatFlag(Character::CombatFlags flag) {
	if (std::find(combatFlags.begin(), combatFlags.end(), flag) == combatFlags.end())
		combatFlags.push_back(flag);
}

std::shared_ptr<Character> Character::fromJson(const nlohmann::json& j) {
	std::string type = j.at("type").get<std::string>();
	if (type == "Human") return Human::fromJson(j);
	if (type == "Creature") return Creature::fromJson(j);
	return nullptr;
}

void Character::addTag(std::string& tag)
{
	tags.push_back(std::make_shared<std::string>(tag));
}

float Character::getDefenseValue(Defense defenseValue)
{
	auto it = defenseValues.find(defenseValue);
	return (it != defenseValues.end()) ? it->second : 0.0f;
}

void Character::setDefenseValue(Defense stat, float defenseValue)
{
	defenseValues[stat] = defenseValue;
}

void Character::decayStatusEffects(std::shared_ptr<Character> target)
{
	float bleedDecay = target->maxBleedPoints * 0.05f;
	float burnDecay = target->maxBurnPoints * 0.05f;
	float poisonDecay = target->maxPoisonPoints * 0.05f;
	float frostDecay = target->maxFrostPoints * 0.05f;
	float shockDecay = target->maxShockPoints * 0.05f;
	float sleepDecay = target->maxSleepPoints * 0.05f;

	if (target->bleedPoints > 0)
	{
		target->bleedPoints -= bleedDecay;
		if (target->bleedPoints < 0) target->bleedPoints = 0;
	}
	if (target->burnPoints > 0)
	{
		target->burnPoints -= burnDecay;
		if (target->burnPoints < 0) target->burnPoints = 0;
	}
	if (target->poisonPoints > 0)
	{
		target->poisonPoints -= poisonDecay;
		if (target->poisonPoints < 0) target->poisonPoints = 0;
	}
	if (target->frostPoints > 0)
	{
		target->frostPoints -= frostDecay;
		if (target->frostPoints < 0) target->frostPoints = 0;
	}
	if (target->shockPoints > 0)
	{
		target->shockPoints -= shockDecay;
		if (target->shockPoints < 0) target->shockPoints = 0;
	}
	if (target->sleepPoints > 0)
	{
		target->sleepPoints -= sleepDecay;
		if (target->sleepPoints < 0) target->sleepPoints = 0;
	}
}
//this doesnt need to have ammo passed to it 
bool Character::chooseAmmunition(std::shared_ptr<Weapon> weapon, std::shared_ptr<Character> target, std::shared_ptr<Ammunition> ammo)
{
	//get the ammo the player has stored in each quiver slot

	std::vector<std::shared_ptr<Ammunition>> quiver;
	for (std::shared_ptr<Item> item : inventory.equippedItems)
	{
		auto ammo = std::dynamic_pointer_cast<Ammunition>(item);
		if (!ammo) continue;
		if (ammo->slot == Item::EquipSlots::QUIVER1) quiver.push_back(ammo);
		if (ammo->slot == Item::EquipSlots::QUIVER2) quiver.push_back(ammo);
		if (ammo->slot == Item::EquipSlots::QUIVER3) quiver.push_back(ammo);
		if (ammo->slot == Item::EquipSlots::QUIVER4) quiver.push_back(ammo);
	}
	//prints a menu of all the ammo the player has in their quiver
	std::cout << dye::light_yellow(" Choose your ammunition:") << std::endl;
	//keeps track of occupied quiver slots so empty slots can be printed out to make it clear that they have more slots to store arrows
	int occupiedSlots = 0;
	for (int i = 0; i < quiver.size(); i++)
	{
		float totalDamage = quiver[0]->getAmmoDamage(target, quiver[0]);
		if (quiver[i]->slot == Item::EquipSlots::QUIVER1)
		{
			std::cout << " " << dye::light_yellow(i + 1) << dye::light_yellow(") ") << quiver[i]->name
				<< "; damage: " << totalDamage << "; quantity: " << quiver[i]->quantity << std::endl;
			occupiedSlots++;
		}
		if (quiver[i]->slot == Item::EquipSlots::QUIVER2)
		{
			std::cout << " " << dye::light_yellow(i + 1) << dye::light_yellow(") ") << quiver[i]->name
				<< "; damage: " << totalDamage << "; quantity: " << quiver[i]->quantity << std::endl;
			occupiedSlots++;
		}
		if (quiver[i]->slot == Item::EquipSlots::QUIVER3)
		{
			std::cout << " " << dye::light_yellow(i + 1) << dye::light_yellow(") ") << quiver[i]->name
				<< "; damage: " << totalDamage << "; quantity: " << quiver[i]->quantity << std::endl;
			occupiedSlots++;
		}
		if (quiver[i]->slot == Item::EquipSlots::QUIVER4)
		{
			std::cout << " " << dye::light_yellow(i + 1) << dye::light_yellow(") ") << quiver[i]->name
				<< "; damage: " << totalDamage << "; quantity: " << quiver[i]->quantity << std::endl;
			occupiedSlots++;
		}
	}
	if (occupiedSlots == 0)
	{
		std::cout << " You are out of ammunition!" << std::endl;
		return false;
	}
	else
	{
		//prints out empty slots
		for (int i = occupiedSlots; i < 4; i++)
		{
			std::cout << " " << dye::grey(i + 1) << dye::grey(") ") << dye::grey("Empty Slot") << std::endl;
		}
		std::cout << " " << dye::light_yellow("5) Go Back...") << std::endl;
		//input validation
		int choice = 0;
		do
		{
			std::cout << dye::light_yellow(" Choose your ammunition: ");
			std::cin >> choice;
			if (choice == 5)
			{
				return false;
			}
			if (std::cin.fail() || choice < 1 || choice > quiver.size())
			{
				std::cout << dye::white(" Invalid choice. Please enter 1 - ") << quiver.size() << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		} while (choice < 1 || choice > quiver.size());


		//selects the ammo to be used
		ammo = quiver[choice - 1];
		return true;
		//fireRangedWeapon(target, weapon, ammo);
	}
}

void Character::fireRangedWeapon(std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon, std::shared_ptr<Ammunition> ammo)
{
	//target is a human
	if (std::dynamic_pointer_cast<Human>(target))
	{
		std::shared_ptr<Human> humanAttacker = std::dynamic_pointer_cast<Human>(shared_from_this());
		std::shared_ptr<Human> humanTarget = std::dynamic_pointer_cast<Human>(target);

		//APPLY DEFENSIVE EFFECTS OF TARGET IF IN RANGE
		//get enchantments of target
		for (std::shared_ptr<Item> item : target->inventory.equippedItems)
		{
			auto armor = std::dynamic_pointer_cast<Armor>(item);
			if (!armor) continue;
				for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(target, shared_from_this());
					}
				}
		}

		if (weapon->weaponType == Weapon::WeaponType::LONGBOW || weapon->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
			weapon->weaponType == Weapon::WeaponType::GREATBOW || weapon->weaponType == Weapon::WeaponType::MINICROSSBOW ||
			weapon->weaponType == Weapon::WeaponType::CROSSBOW || weapon->weaponType == Weapon::WeaponType::BALLISTA)
		{
			//archery specific sanity check
			if (ammo == nullptr)
			{
				std::cout << dye::light_red("ERROR: No ammunition provided for dealDamage method") << std::endl;
				return;
			}

			//Damage modifier will be changed to 0.7 if the player lacks requirements for the weapon, increases for every point of the stat it the weapon scales with
			float damageModifier = 1.0f;
			bool lacksRequirements = false;
			//Get the stat scaling values of the weapon, adjust damage values as needed
			float strengthRequirement = weapon->getWeaponRequirementValue(StatScaling::STRENGTH);
			if (strengthRequirement > this->getStrength()) lacksRequirements = true;
			float agilityRequirment = weapon->getWeaponRequirementValue(StatScaling::AGILITY);
			if (agilityRequirment > this->getAgility()) lacksRequirements = true;
			float intelligenceRequirement = weapon->getWeaponRequirementValue(StatScaling::INTELLIGENCE);
			if (intelligenceRequirement > this->getIntelligence()) lacksRequirements = true;
			float faithRequirement = weapon->getWeaponRequirementValue(StatScaling::FAITH);
			if (faithRequirement > this->getFaith()) lacksRequirements = true;
			float luckRequirement = weapon->getWeaponRequirementValue(StatScaling::LUCK);
			if (luckRequirement > this->getLuck()) lacksRequirements = true;
			float arcaneRequirement = weapon->getWeaponRequirementValue(StatScaling::ARCANE);
			if (arcaneRequirement > this->getArcane()) lacksRequirements = true;
			float charismaRequirement = weapon->getWeaponRequirementValue(StatScaling::CHARISMA);
			if (charismaRequirement > this->getCharisma()) lacksRequirements = true;

			//get random number for crit chance influenced by luck slightly
			int randomNum = (rand() % 100 - this->getLuck()) + 1;
			//This is just Overwatch's damage falloff formula lmao

			//Stat scaling variables
			float strengthScaling = weapon->getWeaponScalingValue(StatScaling::STRENGTH);
			float agilityScaling = weapon->getWeaponScalingValue(StatScaling::AGILITY);
			float intelligenceScaling = weapon->getWeaponScalingValue(StatScaling::INTELLIGENCE);
			float faithScaling = weapon->getWeaponScalingValue(StatScaling::FAITH);
			float luckScaling = weapon->getWeaponScalingValue(StatScaling::LUCK);
			float arcaneScaling = weapon->getWeaponScalingValue(StatScaling::ARCANE);
			float charismaScaling = weapon->getWeaponScalingValue(StatScaling::CHARISMA);

			float scalingModifier = max(((strengthScaling / 2) * this->getStrength() + (agilityScaling / 2) * this->getAgility() + (intelligenceScaling / 2) * this->getIntelligence()
				+ (faithScaling / 2) * this->getFaith() + (luckScaling / 2) * this->getLuck() + (arcaneScaling / 2) * this->getArcane() + (charismaScaling / 2) * this->getCharisma() / 5000), 0);

			damageModifier += scalingModifier;

			if (lacksRequirements) damageModifier = 0.7f;

			//Inform player of their lack of requirements
			if (lacksRequirements == true) std::cout << dye::light_red(" You lack the requirements to wield ")
				<< weapon->name << dye::light_red(" effectively! Normal damage is reduced by 30%!") << std::endl;

			//damage falloff variables
			float minDamage = ammo->getAmmoDamage(target, ammo) * .3;
			float maxDamage = ammo->getAmmoDamage(target, ammo) * 1.3;
			float nearRange = ammo->range * 0.1;

			float farRange = weapon->reach + ammo->range;

			//normalized distance of the attacker from their target
			float normalizedDistance = std::clamp((target->position[this->id] - nearRange) / (farRange - nearRange), 0.0f, 1.0f);

			//raw damage of the arrow
			float arrowDamage = max((maxDamage * (1.0f - normalizedDistance) + (normalizedDistance * minDamage) * damageModifier), 1.0f);

			//crit damage modifier
			float critDamage = arrowDamage * 1.5;

			//final damage taken, either crit or non crit
			float critDamageTaken = critDamage;
			float damageTaken = arrowDamage;

			//ensures that the damage will never be negative 
			if (critDamageTaken < 0) critDamageTaken = 0;
			if (damageTaken < 0) damageTaken = 0;

			//Critical Hit
			if (randomNum <= this->critChance)
			{
				//Player landed critical hit
				if (humanAttacker->isPlayer)
				{
					target->healthPoints -= critDamageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << dye::light_red(" Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					return;
				}
				//NPC landed critical hit
				else
				{
					target->healthPoints -= critDamageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << dye::light_red(" Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					return;
				}
			}
			//Normal Hit
			else
			{
				//Player landed normal hit
				if (humanAttacker->isPlayer)
				{
					target->healthPoints -= damageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					return;
				}
				//NPC landed normal hit
				else
				{
					target->healthPoints -= damageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
				}
			}
		}
		else
		{
			std::cout << dye::light_red("ERROR: Weapon is not a ranged weapon") << std::endl;
		}
	}
	//target is a creature
	else
	{
		//TODO
	}
}

void Character::consumeAmmo(std::shared_ptr<Ammunition> ammo)
{
	if (ammo == nullptr) {
		std::cout << "ERROR: Attempted to consume a nullptr ammo." << std::endl;
		return;
	}

	if (ammo->quantity == 1) {
		// Find and remove the item from the inventory
		auto it = std::remove(inventory.equippedItems.begin(), inventory.equippedItems.end(), ammo);

		if (it != inventory.equippedItems.end()) {
			inventory.equippedItems.erase(it, inventory.equippedItems.end());
			std::cout << " Removed " << ammo->name << " from inventory." << std::endl;
		}
		else {
			std::cout << "WARNING: Item not found in inventory during removal!" << std::endl;
		}
	}
	else {
		ammo->quantity--;
		std::cout << " Used one " << ammo->name << ", " << ammo->quantity << " remaining." << std::endl;
	}
}

void Character::throwThrownConsumable(std::shared_ptr<ThrownConsumable> consumable, std::shared_ptr<Character> target)
{
	//target is a human
	if (std::dynamic_pointer_cast<Human>(target))
	{

		std::shared_ptr<Human> humanAttacker = std::dynamic_pointer_cast<Human>(shared_from_this());
		std::shared_ptr<Human> humanTarget = std::dynamic_pointer_cast<Human>(target);

		//APPLY DEFENSIVE EFFECTS OF TARGET IF IN RANGE
		//get enchantments of target
		for (std::shared_ptr<Item> item : target->inventory.equippedItems)
		{
			auto armor = std::dynamic_pointer_cast<Armor>(item);
				for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(target, shared_from_this());
					}
				}
		}

        //sanity check
		if (consumable == nullptr)
		{
			std::cout << dye::light_red("ERROR: No ammunition provided for dealDamage method") << std::endl;
			return;
		}
		if (target == nullptr)
		{
			std::cout << dye::light_red("ERROR: No target provided for dealDamage method") << std::endl;
			return;
		}

		//Damage modifier will be changed to 0.7 if the player lacks requirements for the weapon
		float damageModifier = 1.0f;
		bool lacksRequirements = false;
		//Get the stat scaling values of the weapon, adjust damage values as needed
		float strengthScaling = consumable->getThrownConsumableRequirementValue(StatScaling::STRENGTH);
		if (strengthScaling > this->getStrength()) lacksRequirements = true;
		float agilityScaling = consumable->getThrownConsumableRequirementValue(StatScaling::AGILITY);
		if (agilityScaling > this->getAgility()) lacksRequirements = true;
		float intelligenceScaling = consumable->getThrownConsumableRequirementValue(StatScaling::INTELLIGENCE);
		if (intelligenceScaling > this->getIntelligence()) lacksRequirements = true;
		float faithScaling = consumable->getThrownConsumableRequirementValue(StatScaling::FAITH);
		if (faithScaling > this->getFaith()) lacksRequirements = true;
		float luckScaling = consumable->getThrownConsumableRequirementValue(StatScaling::LUCK);
		if (luckScaling > this->getLuck()) lacksRequirements = true;
		float arcaneScaling = consumable->getThrownConsumableRequirementValue(StatScaling::ARCANE);
		if (arcaneScaling > this->getArcane()) lacksRequirements = true;
		float charismaScaling = consumable->getThrownConsumableRequirementValue(StatScaling::CHARISMA);
		if (charismaScaling > this->getCharisma()) lacksRequirements = true;

		//get random number for crit chance influenced by luck slightly
		int randomNum = (rand() % 100 - this->getLuck()) + 1;
		//This is just Overwatch's damage falloff formula lmao

		//Stat scaling variables
		float strengthScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::STRENGTH);
		float agilityScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::AGILITY);
		float intelligenceScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::INTELLIGENCE);
		float faithScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::FAITH);
		float luckScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::LUCK);
		float arcaneScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::ARCANE);
		float charismaScalingValue = consumable->getThrownConsumableScalingValue(StatScaling::CHARISMA);

		float scalingModifier = max(((strengthScalingValue / 2) * this->getStrength() + (agilityScalingValue / 2) * this->getAgility() + (intelligenceScalingValue / 2) * this->getIntelligence()
			+ (faithScalingValue / 2) * this->getFaith() + (luckScalingValue / 2) * this->getLuck() + (arcaneScalingValue / 2) * this->getArcane() + (charismaScalingValue / 2) * this->getCharisma() / 5000), 0);

		damageModifier += scalingModifier;

		if (lacksRequirements) damageModifier = 0.7f;

		//Inform player of their lack of requirements
		if (lacksRequirements == true) std::cout << dye::light_red(" You lack the requirements to wield ")
			<< consumable->name << dye::light_red(" effectively! Normal damage is reduced by 30%!") << std::endl;

		//damage falloff variables
		float minDamage = consumable->getThrownConsumableDamage(target, *consumable) * .3;
		float maxDamage = consumable->getThrownConsumableDamage(target, *consumable) * 1.3;
		float nearRange = consumable->reach * 0.1;

		float farRange = consumable->reach;

		//normalized distance of the attacker from their target
		float normalizedDistance = std::clamp((target->position[this->id] - nearRange) / (farRange - nearRange), 0.0f, 1.0f);

		//raw damage of the arrow
		float consumableDamage = max((maxDamage * (1.0f - normalizedDistance) + (normalizedDistance * minDamage) * damageModifier), 1.0f);

		//crit damage modifier
		float critDamage = consumableDamage * 1.5;

		//final damage taken, either crit or non crit
		float critDamageTaken = critDamage;
		float damageTaken = consumableDamage;

		//ensures that the damage will never be negative 
		if (critDamageTaken < 0) critDamageTaken = 0;
		if (damageTaken < 0) damageTaken = 0;

		//Critical Hit
		if (randomNum <= this->critChance)
		{
			//Player landed critical hit
			if (humanAttacker->isPlayer)
			{
				target->healthPoints -= critDamageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << dye::light_red(" Critical Hit!") << std::endl;
				std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				return;
			}
			//NPC landed critical hit
			else
			{
				target->healthPoints -= critDamageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << dye::light_red(" Critical Hit!") << std::endl;
				std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				return;
			}
		}
		//Normal Hit
		else
		{
			//Player landed normal hit
			if (humanAttacker->isPlayer)
			{
				target->healthPoints -= damageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				return;
			}
			//NPC landed normal hit
			else
			{
				target->healthPoints -= damageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				return;
			}
		}
	}
	//target is a creature
	else
	{
		//TODO
	}
}

void Character::consumeThrownConsumable(std::shared_ptr<ThrownConsumable> consumable)
{
	if (consumable == nullptr) {
		std::cout << "ERROR: Attempted to consume a nullptr consumable." << std::endl;
		return;
	}

	if (consumable->quantity == 1) {
		// Find and remove the item from the inventory
		auto it = std::remove(inventory.backpackItems.begin(), inventory.backpackItems.end(), consumable);

		if (it != inventory.backpackItems.end()) {
			inventory.backpackItems.erase(it, inventory.backpackItems.end());
			std::cout << " Removed " << consumable->name << " from inventory." << std::endl;
		}
		else {
			std::cout << "WARNING: Item not found in inventory during removal!" << std::endl;
		}
	}
	else {
		consumable->quantity--;
		std::cout << " Used one " << consumable->name << ", " << consumable->quantity << " remaining." << std::endl;
	}
}



void Character::killCharacter()
{
	//Last minute sanity check to ensure the character is alive before printing out that they've been killed
	if (isAlive) std::cout << dye::light_red(" " + this->name + " has been slain!") << std::endl;
	isAlive = false;
	if (healthPoints < 0) healthPoints = 0;
	return;
}

//SPELLS
bool Character::chooseSpell(Weapon& weapon, std::shared_ptr<Character> target, std::shared_ptr<Spell>& spell)
{
	//checks if they're using an appropriate casting tool
	if (weapon.weaponType == Weapon::WeaponType::WAND || weapon.weaponType == Weapon::WeaponType::STAFF ||
		weapon.weaponType == Weapon::WeaponType::ORB || weapon.weaponType == Weapon::WeaponType::CHIME ||
		weapon.weaponType == Weapon::WeaponType::TALISMAN || weapon.weaponType == Weapon::WeaponType::TOME)
	{
		int choice = 0;
		//keep looping until the player chooses a spell or chooses to go back
		do
		{
			//check if the character can cast the spell
			//print out the spell menu
			std::cout << "\n=--->\n" << std::endl;
			std::cout << dye::light_green(" Fatigue ") << this->fatiguePoints << "/" << this->maxFatiguePoints << std::endl;
			std::cout << "\n=--->\n" << std::endl;
			//used to keep track of the amount of used spell slots and to print empty slots for any spell not attuned
			int numCategories = 0;
			for (int i = 0; i < this->attunedSpells.size(); i++)
			{
				//print the spell out as grey if the player doesn't have enough fatigue to cast it or if it is out of range of all targets
				// also checks if the spell in question is used on an ally or self, in which case let it go through because those ones have a range of 0
				if (this->attunedSpells[i]->fatigueCost <= this->fatiguePoints
					&& this->attunedSpells[i]->range >= target->position[this->id]
					&& !this->attunedSpells[i]->useOnSelf
					&& !this->attunedSpells[i]->useOnAlly
					&& this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()))
				{
					std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
					numCategories++;
				}
				else if (this->attunedSpells[i]->fatigueCost <= this->fatiguePoints && this->attunedSpells[i]->useOnSelf
					&& this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()) || this->attunedSpells[i]->useOnAlly
					&& this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()))
				{
					std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
					numCategories++;
				}
				else if (this->attunedSpells[i]->fatigueCost > this->fatiguePoints && this->attunedSpells[i]->range < target->position[this->id]
					&& !this->attunedSpells[i]->useOnSelf && !this->attunedSpells[i]->useOnAlly)
				{
					std::cout << dye::grey(" ") << dye::grey(i + 1) << dye::grey(") ") << dye::grey(this->attunedSpells[i]->name) << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
					numCategories++;
				}
				else {
					std::cout << dye::grey(" ") << dye::grey(i + 1) << dye::grey(") ") << dye::grey(this->attunedSpells[i]->name) << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
					numCategories++;
				}
			}
			for (int i = numCategories; i < 7; i++)
			{
				std::cout << " " << dye::grey(i + 1) << dye::grey(") Empty Slot") << std::endl;
			}
			std::cout << dye::light_yellow(" ") << dye::light_yellow("8) Go Back...") << std::endl;
			do
			{
				std::cout << dye::light_yellow(" Choose your spell: ");
				std::cin >> choice;
				if (choice == 8)
				{
					//user chose to go back without casting a spell6
					return false;
					break;
				}
				if (std::cin.fail() || choice < 1 || choice > this->attunedSpells.size())
				{
					std::cout << dye::white(" Invalid choice. Please enter 1 - ")
						<< this->attunedSpells.size() << " or 8 to go back..." << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
			} while (choice < 1 || choice > this->attunedSpells.size());
			//get fatigue cost of the spell, dont allow them to cast it if they can't
			// return without progressing a turn if they can't cast the spell
			if (fatiguePoints < this->attunedSpells[choice - 1]->fatigueCost)
			{
				//user does not have enough fatigue to cast the spell
				std::cout << dye::light_red(" Not enough fatigue to cast spell!") << std::endl;
				return false;
			}
			//spell is a self cast, ignore range check
			else if (this->attunedSpells[choice - 1]->checkSpellRequirements(this->attunedSpells[choice - 1], shared_from_this()) && this->attunedSpells[choice - 1]->useOnSelf)
			{
				spell = this->attunedSpells[choice - 1];
				return true;
				break;
			}
			//spell is an ally cast, ignore range check
			else if (this->attunedSpells[choice - 1]->checkSpellRequirements(this->attunedSpells[choice - 1], shared_from_this()) && this->attunedSpells[choice - 1]->useOnAlly)
			{
				spell = this->attunedSpells[choice - 1];
				return true;
				break;
			}
			//Spell is out of ransge
			else if (this->attunedSpells[choice - 1]->range < target->position[this->getId()])
			{
				std::cout << " You are not in range of that target with " << this->attunedSpells[choice - 1]->name << std::endl;
				return false;
				break;
			}
			else if (this->attunedSpells[choice - 1]->checkSpellRequirements(this->attunedSpells[choice - 1], shared_from_this()))
			{
				spell = this->attunedSpells[choice - 1];
				return true;
				break;
			}
			else
			{
				std::cout << dye::light_red(" You lack the requirements to cast that spell!") << std::endl;
				return false;
				break;
			}
		} while (!spell || choice == 8);
	}
	else
	{
		std::cout << dye::light_red(" ERROR: INCORRECT WEAPON TYPE PASSED TO CHOOSESPELL!") << std::endl;
		return false;
	}
}

void Character::viewSpells()
{
	int choice = 0;
	do
	{
		std::cout << "\n=--->\n" << std::endl;
		int numCategories = 0;
		std::cout << dye::light_yellow(" Select a Spell to View Details...") << std::endl;
		std::cout << dye::light_green(" Fatigue ") << this->fatiguePoints << "/" << this->maxFatiguePoints << std::endl;
		std::cout << "\n=--->\n" << std::endl;
		for (int i = 0; i < this->attunedSpells.size(); i++)
		{
			//print the spell out as grey if the player doesn't have enough fatigue to cast it
			if (this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()) && this->attunedSpells[i]->fatigueCost <= this->fatiguePoints) std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
			if (!this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()) && this->attunedSpells[i]->fatigueCost > this->fatiguePoints)std::cout << dye::grey(" ") << dye::grey(i + 1) << dye::grey(") ") << dye::grey(this->attunedSpells[i]->name) << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
			numCategories++;
		}
		for (int i = numCategories; i < 7; i++)
		{
			std::cout << " " << dye::grey(i + 1) << dye::grey(") Empty Slot") << std::endl;
		}
		std::cout << dye::light_yellow(" ") << dye::light_yellow("8) Go Back...") << std::endl;
		do
		{
			std::cout << dye::light_yellow(" Choose your spell: ");
			std::cin >> choice;
			if (choice == 8)
			{
				//user chose to go back without viewing a spell in detail
				return;
			}
			if (std::cin.fail() || choice < 1 || choice > this->attunedSpells.size())
			{
				std::cout << dye::white(" Invalid choice. Please enter 1 - ")
					<< this->attunedSpells.size() << " or 8 to go back..." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		} while (choice < 1 || choice > this->attunedSpells.size());

		std::unordered_map<std::string, int> requirements;
		requirements = this->attunedSpells[choice - 1]->getStatRequirements();

		std::cout << " " + this->attunedSpells[choice - 1]->name + "; fatigue cost: "
			<< this->attunedSpells[choice - 1]->fatigueCost << "; "
			<< this->attunedSpells[choice - 1]->description << "; ";
		std::cout << "Requirements: " << std::endl;
		for (auto& [stat, value] : requirements)
		{
			std::cout << " " << stat << ": " << value << std::endl;
		}
		std::cout << " Scaling: " << std::endl;
		if (this->attunedSpells[choice - 1]->arcaneScaling > 0) std::cout << " Arcane: " << this->attunedSpells[choice - 1]->arcaneScaling << std::endl;
		if (this->attunedSpells[choice - 1]->charismaScaling > 0) std::cout << " Charisma: " << this->attunedSpells[choice - 1]->charismaScaling << std::endl;
		if (this->attunedSpells[choice - 1]->faithScaling > 0) std::cout << " Faith: " << this->attunedSpells[choice - 1]->faithScaling << std::endl;
		if (this->attunedSpells[choice - 1]->intelligenceScaling > 0) std::cout << " Intelligence: " << this->attunedSpells[choice - 1]->intelligenceScaling << std::endl;
		if (this->attunedSpells[choice - 1]->luckScaling > 0) std::cout << " Luck: " << this->attunedSpells[choice - 1]->luckScaling << std::endl;
	} while (choice != 8);
}

void Character::viewSpellsBrief()
{
	int numCategories = 0;
	std::cout << dye::light_yellow(" Your Attuned Spells...") << std::endl;
	for (int i = 0; i < this->attunedSpells.size(); i++)
	{
		//print the spell out as grey if the player doesn't have enough fatigue to cast it
		if (this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()) && this->attunedSpells[i]->fatigueCost <= this->fatiguePoints) std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << std::endl;
		if (!this->attunedSpells[i]->checkSpellRequirements(this->attunedSpells[i], shared_from_this()) && this->attunedSpells[i]->fatigueCost > this->fatiguePoints)std::cout << dye::grey(" ") << dye::grey(i + 1) << dye::grey(") ") << dye::grey(this->attunedSpells[i]->name) << std::endl;
		numCategories++;
	}
	for (int i = numCategories; i < 7; i++)
	{
		std::cout << " " << dye::grey(i + 1) << dye::grey(") Empty Slot") << std::endl;
	}
}
void Character::castSpell(Spell& spell, std::shared_ptr<Character> target, float playerMovement)
{
	std::shared_ptr<Character> character = (shared_from_this());
	

	if (std::dynamic_pointer_cast<Human>(target))
	{
		std::shared_ptr<Human> humanAttacker = std::dynamic_pointer_cast<Human>(shared_from_this());
		
		//APPLY DEFENSIVE EFFECTS OF TARGET IF IN RANGE
		//get enchantments of target
		for (std::shared_ptr<Item> item : target->inventory.equippedItems)
		{
			if (std::dynamic_pointer_cast<std::shared_ptr<Armor>>(item))
			{
				std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
				for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(target, shared_from_this());
					}
				}
			}
		}
		//Individual spell logic
		//Electrify Armament has 2 effects, one applied to the caster and one to nearby enemies. This is to ensure they apply
		// to the correct targets
		if (spell.name == "Electrify Armament I" || spell.name == "Electrify Armament II" || spell.name == "Electrify Armament III")
		{
			for (auto& eff : spell.effects)
			{
				if (eff->getType() == "ArmamentBuff")
				{
					eff->apply(shared_from_this(), shared_from_this());
				}
				else
				{
					eff->apply(shared_from_this(), target);
				}
			}
		}
		//Check if the spell is a self-use spell
		else if (spell.useOnSelf)
		{
			for (auto& eff : spell.effects)
			{
				eff->apply(shared_from_this(), shared_from_this());
			}
		}
		//Check if the spell is an ally-use spell
		else if (spell.useOnAlly)
		{
			for (auto& eff : spell.effects)
			{
				for (auto& ally : humanAttacker->allies)
				{
					eff->apply(shared_from_this(), ally);
				}
			}
		}
		//Check if the spell is an enemy-use spell
		else if (spell.useOnEnemy)
		{
			for (auto& eff : spell.effects)
			{
				eff->apply(shared_from_this(), target);
			}
		}
		else
		{
			std::cout << "ERROR: SPELL COULD NOT BE CAST BECAUSE IT DOES NOT MEET THE CONDITIONS SET IN CAST SPELL" << std::endl;
		}
	}
}

void Character::attackWithMelee(std::shared_ptr<Weapon> weapon, std::shared_ptr<Character> target)
{
	if (std::dynamic_pointer_cast<Human>(target))
	{
		std::shared_ptr<Human> humanAttacker = std::dynamic_pointer_cast<Human>(shared_from_this());
		std::shared_ptr<Human> humanTarget = std::dynamic_pointer_cast<Human>(target);

		//Apply enchantment effects first:
		for (std::shared_ptr<Enchantment> enchantment : weapon->enchantments)
		{
			for (std::shared_ptr<Effect> effect : enchantment->effects)
			{
				effect->apply(shared_from_this(), target);
			}
		}

		//Damage modifier will be changed to 0.7 if the player lacks requirements for the weapon
		float damageModifier = 1.0f;
		bool lacksRequirements = false;
		//Get the stat scaling values of the weapon, adjust damage values as needed
		float strengthScaling = weapon->getWeaponRequirementValue(StatScaling::STRENGTH);
		if (strengthScaling > this->getStrength()) lacksRequirements = true;
		float agilityScaling = weapon->getWeaponRequirementValue(StatScaling::AGILITY);
		if (agilityScaling > this->getAgility()) lacksRequirements = true;
		float intelligenceScaling = weapon->getWeaponRequirementValue(StatScaling::INTELLIGENCE);
		if (intelligenceScaling > this->getIntelligence()) lacksRequirements = true;
		float faithScaling = weapon->getWeaponRequirementValue(StatScaling::FAITH);
		if (faithScaling > this->getFaith()) lacksRequirements = true;
		float luckScaling = weapon->getWeaponRequirementValue(StatScaling::LUCK);
		if (luckScaling > this->getLuck()) lacksRequirements = true;
		float arcaneScaling = weapon->getWeaponRequirementValue(StatScaling::ARCANE);
		if (arcaneScaling > this->getArcane()) lacksRequirements = true;
		float charismaScaling = weapon->getWeaponRequirementValue(StatScaling::CHARISMA);
		if (charismaScaling > this->getCharisma()) lacksRequirements = true;

		//Stat scaling variables
		float strengthScalingValue = weapon->getWeaponScalingValue(StatScaling::STRENGTH);
		float agilityScalingValue = weapon->getWeaponScalingValue(StatScaling::AGILITY);
		float intelligenceScalingValue = weapon->getWeaponScalingValue(StatScaling::INTELLIGENCE);
		float faithScalingValue = weapon->getWeaponScalingValue(StatScaling::FAITH);
		float luckScalingValue = weapon->getWeaponScalingValue(StatScaling::LUCK);
		float arcaneScalingValue = weapon->getWeaponScalingValue(StatScaling::ARCANE);
		float charismaScalingValue = weapon->getWeaponScalingValue(StatScaling::CHARISMA);

		float scalingModifier = max(((strengthScalingValue / 2) * this->getStrength() + (agilityScalingValue / 2) * this->getAgility() + (intelligenceScalingValue / 2) * this->getIntelligence()
			+ (faithScalingValue / 2) * this->getFaith() + (luckScalingValue / 2) * this->getLuck() + (arcaneScalingValue / 2) * this->getArcane() + (charismaScalingValue / 2) * this->getCharisma() / 5000), 0);

		damageModifier += scalingModifier;

		if (lacksRequirements) damageModifier = 0.7f;

		//Inform player of their lack of requirements
		if (lacksRequirements == true) std::cout << dye::light_red(" You lack the requirements to wield ")
			<< weapon->name << dye::light_red(" effectively! Normal damage is reduced by 30%!") << std::endl;

		//Calculate crit damage and damage reduction
		int randomNum = (rand() % 100 - this->getLuck()) + 1;

		float normalDamage = weapon->getWeaponDamage(target, weapon) * damageModifier;
		float critDamage = weapon->getWeaponDamage(target, weapon) * 1.5f * damageModifier;

		//ensures that the damage will never be negative
		if (critDamage < 0) critDamage = 0;
		if (normalDamage < 0) normalDamage = 0;

		//Critical Hit

		if (randomNum <= humanAttacker->critChance)
		{
			//Player landed critical hit
			if (humanAttacker->isPlayer)
			{
				target->healthPoints -= critDamage;
				std::cout << dye::light_red(" Critical Hit!") << std::endl;
				std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamage << " points of damage from the "
					<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				//get enchantments of target
				for (std::shared_ptr<Item> item : target->inventory.equippedItems)
				{
					if (std::dynamic_pointer_cast<Armor>(item))
					{
						std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
						for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
						{
							for (std::shared_ptr<Effect> effect : enchantment->effects)
							{
								if(humanAttacker->isAlive) effect->apply(target, shared_from_this());
							}
						}
					}
				}
				return;
			}
			//NPC landed a critical hit
			else
			{
				target->healthPoints -= critDamage;
				std::cout << std::setprecision(2) << " You take " << critDamage << " points of damage from the "
					<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				//get enchantments of target
				for (std::shared_ptr<Item> item : target->inventory.equippedItems)
				{
					if (std::dynamic_pointer_cast<Armor>(item))
					{
						std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
						for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
						{
							for (std::shared_ptr<Effect> effect : enchantment->effects)
							{
								if (humanAttacker->isAlive) effect->apply(target, shared_from_this());
							}
						}
					}
				}
				return;
			}
		}
		else
		{
			//NORMAL HIT
			//Player landed normal hit
			if (humanAttacker->isPlayer)
			{
				target->healthPoints -= normalDamage;
				std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << normalDamage << " points of damage from the "
					<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				//get enchantments of target
				for (std::shared_ptr<Item> item : target->inventory.equippedItems)
				{
					if (std::dynamic_pointer_cast<Armor>(item))
					{
						std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
						for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
						{
							for (std::shared_ptr<Effect> effect : enchantment->effects)
							{
								if (humanAttacker->isAlive) effect->apply(target, shared_from_this());
							}
						}
					}
				}
				return;
			}
			//NPC landed a normal hit
			else
			{
				target->healthPoints -= normalDamage;
				std::cout << std::setprecision(2) << " You take " << normalDamage << " points of damage from the "
					<< dye::light_yellow(humanAttacker->name) << "'s " << weapon->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				//get enchantments of target
				for (std::shared_ptr<Item> item : target->inventory.equippedItems)
				{
					if (std::dynamic_pointer_cast<Armor>(item))
					{
						std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
						for (std::shared_ptr<Enchantment> enchantment : armor->enchantments)
						{
							for (std::shared_ptr<Effect> effect : enchantment->effects)
							{
								if (humanAttacker->isAlive) effect->apply(target, shared_from_this());
							}
						}
					}
				}
				return;
			}
		}
	}
	else
	{
		//TODO
	}

}

void Character::useConsumable(std::shared_ptr<Consumable> consumable)
{
	if (consumable == nullptr)
	{
		std::cout << "ERROR: Attempted to use a nullptr consumable." << std::endl;
		return;
	}
	if (auto potion = std::dynamic_pointer_cast<Potion>(consumable))
	{
		potion->use(shared_from_this());
	}
	else if (auto food = std::dynamic_pointer_cast<Food>(consumable))
	{
		food->use(shared_from_this());
	}
	else if (auto drink = std::dynamic_pointer_cast<Drink>(consumable))
	{
		drink->use(shared_from_this());
	}
	else if (auto book = std::dynamic_pointer_cast<Book>(consumable))
	{
		book->use(shared_from_this());
	}
	else
	{
		std::cout << "ERROR: Consumable type not recognized." << std::endl;
	}
}