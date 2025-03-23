#include "Character.h"
#include "Creature.h"
#include "Spell.h"
#include "Potion.h"
#include "Human.h"
#include <vector>
#include <iostream>
#include "color.hpp"
#include <random>
#include <iomanip>
#include "Weapon.h"
#include "optional"
int Character::nextId = 1;

Character::Character(bool isAlly, bool namedCharacter, bool isAlive, bool active, bool alert,
	std::string name, std::string description, float confidenceLevel,
	float healthPoints, float maxHealthPoints, float fatiguePoints,
	float maxFatiguePoints, float speed, float critChance, float dodgeChance,
	float blockChance, float bleedPoints, float maxBleedPoints,
	float burnPoints, float maxBurnPoints, float poisonPoints,
	float maxPoisonPoints, float frostPoints, float maxFrostPoints,
	float shockPoints, float maxShockPoints, float sleepPoints,
	float maxSleepPoints, const Inventory& inventory,
	float level, CombatFlags combatFlag) : id(nextId++),
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
	std::string type = j.at("type");
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

			if (lacksRequirements) damageModifier = 0.7f;

			//Inform player of their lack of requirements
			if (lacksRequirements == true) std::cout << dye::light_red(" You lack the requirements to wield ")
				<< weapon->name << dye::light_red(" effectively! Normal damage is reduced by 30%!") << std::endl;

			//get random number for crit chance influenced by luck slightly
			int randomNum = (rand() % 100 - this->getLuck()) + 1;
			//This is just Overwatch's damage falloff formula lmao

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
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					target->healthPoints -= critDamageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << dye::light_red(" Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
				}
				//NPC landed critical hit
				else
				{
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					target->healthPoints -= critDamageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << dye::light_red(" Critical Hit!") << std::endl;
					std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
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
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					target->healthPoints -= damageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
				}
				//NPC landed normal hit
				else
				{
					for (std::shared_ptr<Enchantment> enchantment : ammo->enchantments)
					{
						for (std::shared_ptr<Effect> effect : enchantment->effects)
						{
							effect->apply(shared_from_this(), target);
						}
					}
					target->healthPoints -= damageTaken;
					humanAttacker->consumeAmmo(ammo);
					std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
						<< humanAttacker->name << "'s " << ammo->name << "!" << std::endl;
					if (target->healthPoints <= 0) target->killCharacter();
					return;
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

		//archery specific sanity check
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

		if (lacksRequirements) damageModifier = 0.7f;

		//Inform player of their lack of requirements
		if (lacksRequirements == true) std::cout << dye::light_red(" You lack the requirements to wield ")
			<< consumable->name << dye::light_red(" effectively! Normal damage is reduced by 30%!") << std::endl;

		//get random number for crit chance influenced by luck slightly
		int randomNum = (rand() % 100 - this->getLuck()) + 1;
		//This is just Overwatch's damage falloff formula lmao

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
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				target->healthPoints -= critDamageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << dye::light_red(" Critical Hit!") << std::endl;
				std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << critDamageTaken << " points of damage from "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				return;
			}
			//NPC landed critical hit
			else
			{
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				target->healthPoints -= critDamageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << dye::light_red(" Critical Hit!") << std::endl;
				std::cout << std::setprecision(2) << " You take " << critDamageTaken << " points of damage from the "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
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
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				target->healthPoints -= damageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << std::setprecision(2) << " " << dye::light_yellow(target->name) << " takes " << damageTaken << " points of damage from "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
				return;
			}
			//NPC landed normal hit
			else
			{
				for (std::shared_ptr<Enchantment> enchantment : consumable->enchantments)
				{
					for (std::shared_ptr<Effect> effect : enchantment->effects)
					{
						effect->apply(shared_from_this(), target);
					}
				}
				target->healthPoints -= damageTaken;
				humanAttacker->consumeThrownConsumable(consumable);
				std::cout << std::setprecision(2) << " You take " << damageTaken << " points of damage from the "
					<< humanAttacker->name << "'s " << consumable->name << "!" << std::endl;
				if (target->healthPoints <= 0) target->killCharacter();
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
	std::cout << dye::light_red(" " + this->name + " has been slain!") << std::endl;
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
					&& !this->attunedSpells[i]->useOnAlly)
				{
					std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
					numCategories++;
				}
				else if (this->attunedSpells[i]->fatigueCost <= this->fatiguePoints && this->attunedSpells[i]->useOnSelf
					|| this->attunedSpells[i]->useOnAlly)
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
			//player tried to cast a summon spell that was already applied
			for (const std::shared_ptr<Effect> effect : this->effects)
			{
				//global variable for now: add more if summons should last more or less than 10 turns
				if (effect->name == "Summon Cooldown" && this->attunedSpells[choice - 1]->summon)
				{
					std::cout << " You can't summon another ally until your current ally dies or for "
						<< effect->duration << " turns!" << std::endl;
				}
			}
			//get fatigue cost of the spell, dont allow them to cast it if they can't
			// return without progressing a turn if they can't cast the spell
			if (fatiguePoints < this->attunedSpells[choice - 1]->fatigueCost)
			{
				//user does not have enough fatigue to cast the spell
				std::cout << dye::light_red(" Not enough fatigue to cast spell!") << std::endl;
				return false;
			}
			//spell is a self cast, ignore range check
			if (this->attunedSpells[choice - 1]->useOnSelf)
			{
				spell = this->attunedSpells[choice - 1];
				return true;
				break;
			}
			//spell is an ally cast, ignore range check
			if (this->attunedSpells[choice - 1]->useOnAlly)
			{
				spell = this->attunedSpells[choice - 1];
				return true;
				break;
			}
			//spell is a summon, ignore range check
			if (this->attunedSpells[choice - 1]->summon)
			{
				spell = this->attunedSpells[choice - 1];
				return true;
				break;
			}
			//Spell is out of ransge
			if (this->attunedSpells[choice - 1]->range < target->position[this->getId()])
			{
				std::cout << " You are not in range of that target with " << this->attunedSpells[choice - 1]->name << std::endl;
				return false;
				break;
			}
			else
			{
				spell = this->attunedSpells[choice - 1];
				return true;
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
			if (this->attunedSpells[i]->fatigueCost <= this->fatiguePoints) std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
			if (this->attunedSpells[i]->fatigueCost > this->fatiguePoints)std::cout << dye::grey(" ") << dye::grey(i + 1) << dye::grey(") ") << dye::grey(this->attunedSpells[i]->name) << "; cost: " << this->attunedSpells[i]->fatigueCost << std::endl;
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

		std::cout << " " + this->attunedSpells[choice - 1]->name + "; fatigue cost: " << this->attunedSpells[choice - 1]->fatigueCost << "; " << this->attunedSpells[choice - 1]->description << std::endl;
	} while (choice != 8);
}

void Character::viewSpellsBrief()
{
	int numCategories = 0;
	std::cout << dye::light_yellow(" Your Attuned Spells...") << std::endl;
	for (int i = 0; i < this->attunedSpells.size(); i++)
	{
		//print the spell out as grey if the player doesn't have enough fatigue to cast it
		if (this->attunedSpells[i]->fatigueCost <= this->fatiguePoints) std::cout << dye::light_yellow(" ") << dye::light_yellow(i + 1) << dye::light_yellow(") ") << this->attunedSpells[i]->name << std::endl;
		if (this->attunedSpells[i]->fatigueCost > this->fatiguePoints)std::cout << dye::grey(" ") << dye::grey(i + 1) << dye::grey(") ") << dye::grey(this->attunedSpells[i]->name) << std::endl;
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

		//CHECK THE TYPE OF SPELL

		//SUMMON ALLY
		if (spell.summon)
		{
			//SUBTRACT FATIGUE
			this->fatiguePoints -= spell.fatigueCost;

			//adds summoning cooldown to caster
			for (std::shared_ptr<Effect> effect : spell.effects)
			{
				effect->apply(character, character);
				return;
			}
		}
		//CAPTIVE SUN SPECIFIC LOGIC
		else if (spell.name == "Captive Sun")
		{
			//SUBTRACT FATIGUE
			this->fatiguePoints -= spell.fatigueCost;

			for (int i = 90; i < humanAttacker->castSpeed;)
			{
				target->healthPoints -= spell.calculateSpellDamage(target, spell);
				if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " takes " << spell.calculateSpellDamage(target, spell) << " points of damage!" << std::endl;
				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " takes " << spell.calculateSpellDamage(target, spell) << " points of damage!" << std::endl;
				i += abs(spell.attackSpeed - 100);
				//apply effects to target
				for (std::shared_ptr<Effect> effect : spell.effects)
				{
					if (target->isAlive)
					{
						if (!effect->areaOfEffect)
						{
							effect->apply(shared_from_this(), target);
						}
					}
				}
				//apply effects to all allies
				for (std::shared_ptr<Character> ally : target->allies)
				{
					if (ally->isAlive)
					{
						for (std::shared_ptr<Effect> effect : spell.effects)
						{
							if (ally->position[this->id] <= effect->range)
							{

								ally->healthPoints -= spell.calculateSpellDamage(ally, spell);
								effect->apply(shared_from_this(), ally);

							}
						}
					}
				}
			}
		}
		//AOE DAMAGING SPELL THAT DOES APPLY AOE EFFECT TO MAIN TARGET
		else if (spell.areaOfEffect)
		{
			//SUBTRACT FATIGUE
			this->fatiguePoints -= spell.fatigueCost;

			for (int i = 0; i < humanAttacker->castSpeed;)
			{
				target->healthPoints -= spell.calculateSpellDamage(target, spell);
				if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " takes " << spell.calculateSpellDamage(target, spell) << " points of damage!" << std::endl;
				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " takes " << spell.calculateSpellDamage(target, spell) << " points of damage!" << std::endl;
				i += abs(spell.attackSpeed - 100);
				//apply effects to target
				for (std::shared_ptr<Effect> effect : spell.effects)
				{
					effect->apply(character, target);
				}
				//apply effects to all allies
				for (std::shared_ptr<Character> ally : target->allies)
				{
					if (ally->isAlive)
					{
						for (std::shared_ptr<Effect> effect : spell.effects)
						{
							if (ally->position[this->id] <= effect->range)
							{

								ally->healthPoints -= spell.calculateSpellDamage(ally, spell);
								if (ally->healthPoints <= 0)
								{
									ally->killCharacter();
									break;
								}
								effect->apply(shared_from_this(), ally);

							}
						}
					}
				}
			}
		}
		//SELF CAST
		else if (spell.useOnSelf)
		{
			//SUBTRACT FATIGUE
			this->fatiguePoints -= spell.fatigueCost;

			
				if (this->namedCharacter) std::cout << dye::light_yellow(" " + this->name) << " has a buff applied to them!" << std::endl;
				if (!this->namedCharacter) std::cout << " The " << dye::light_yellow(this->name) << " has a buff applied to them!" << std::endl;
				for (std::shared_ptr<Effect> effect : spell.effects)
				{
					effect->apply(shared_from_this(), shared_from_this());
				}
			
		}
		//ALLY CAST
		else if (spell.useOnAlly)
		{
			//SUBTRACT FATIGUE
			this->fatiguePoints -= spell.fatigueCost;

			
				//apply effects to target
				for (std::shared_ptr<Effect> effect : spell.effects)
				{
					effect->apply(shared_from_this(), shared_from_this());
				}
				//apply effects to all allies
				for (std::shared_ptr<Character> ally : target->allies)
				{
					if (ally->position[this->id] <= 10)
					{
						ally->healthPoints -= spell.calculateSpellDamage(ally, spell);
						for (std::shared_ptr<Effect> effect : spell.effects)
						{
							effect->apply(shared_from_this(), ally);
						}
					}
				}
			
		}
		//SINGLE TARGET DAMAGE
		else if (spell.range >= target->position[this->getId()])
		{
			//SUBTRACT FATIGUE
			this->fatiguePoints -= spell.fatigueCost;

			for (int i = 0; i < humanAttacker->castSpeed;)
			{
				target->healthPoints -= spell.calculateSpellDamage(target, spell);
				if (target->healthPoints <= 0)
				{
					target->killCharacter();
					break;
				}
				if (target->namedCharacter && spell.calculateSpellDamage(target, spell) > 0) std::cout << dye::light_yellow(" " + target->name) << " takes " << spell.calculateSpellDamage(target, spell) << " points of damage!" << std::endl;
				if (!target->namedCharacter && spell.calculateSpellDamage(target, spell) > 0) std::cout << " The " << dye::light_yellow(target->name) << " takes " << spell.calculateSpellDamage(target, spell) << " points of damage!" << std::endl;
				i += abs(spell.attackSpeed - 100);
				//apply effects to target
				for (std::shared_ptr<Effect> effect : spell.effects)
				{
					effect->apply(character, target);
				}
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

		if (lacksRequirements) damageModifier = 0.7f;

		//Inform player of their lack of requirements
		if(lacksRequirements == true) std::cout << dye::light_red(" You lack the requirements to wield ") 
			<< weapon->name << dye::light_red(" effectively! Normal damage is reduced by 30%!") << std::endl;

		//Calculate crit damage and damage reduction
		int randomNum = (rand() % 100 - this->getLuck()) + 1;

		float normalDamage = weapon->getWeaponDamage(target, *weapon) * damageModifier;
		float critDamage = weapon->getWeaponDamage(target, *weapon) * 1.5f * damageModifier;

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
//void Character::receiveHealing(float healing) {
//	this->healthPoints += healing;
//	if (healthPoints > maxHealthPoints) {
//		healthPoints = maxHealthPoints;
//	}
//}
//
//void Character::gainExperience(Character enemy)
//{
//	float expGained = enemy.level * 50;
//	std::cout << this->name << " gained " << expGained << " points of experience for their victory!" << std::endl;
//
//	if (expGained + experience >= experienceToNextLevel)
//	{
//		levelUp(expGained);
//	}
//	else
//	{
//		this->experience += expGained;
//	}
//}
//
////this is an arcane monstrocity that I am not proud of
//void Character::levelUp(float exp)
//{
//	experience += exp;
//	float expDifference = 0;
//	do
//	{
//		bool levelUpComplete = false;
//		do {
//			int iterator = 0;
//			std::cout << dye::yellow("Level up! You are now level: ") << dye::yellow(level + 1) << std::endl;
//			for (int i = 3; i > 0; i--)
//			{
//				int areYouSure = 0;
//				do
//				{
//					std::cout << dye::yellow("Select ") << dye::yellow(i) << dye::yellow(" stats to increase by 3!") << std::endl;
//					std::cout << dye::light_yellow("1) Health: ") << this->health << std::endl;
//					std::cout << dye::light_yellow("2) fatigue: ") << this->fatigue << std::endl;
//					std::cout << dye::light_yellow("3) Strength: ") << this->strength << std::endl;
//					std::cout << dye::light_yellow("4) Agility: ") << this->agility << std::endl;
//					std::cout << dye::light_yellow("5) Arcane: ") << this->arcane << std::endl;
//					std::cout << dye::light_yellow("6) Faith: ") << this->faith << std::endl;
//					std::cout << dye::light_yellow("7) Luck: ") << this->luck << std::endl;
//					int choice;
//					//input validation
//					do
//					{
//						std::cout << ">> ";
//						std::cin >> choice;
//						if (std::cin.fail() || choice > 7 || choice == 0 || choice < 0)
//						{
//							std::cout << "Enter a number from 1 - 7" << std::endl;
//						}
//						std::cin.clear();
//						std::cin.ignore(10000, '\n');
//					} while (std::cin.fail() || choice > 7 || choice == 0 || choice < 0);
//
//					switch (choice)
//					{
//					case 1:
//					{
//						std::cout << "Health: " << this->health << " -> " << this->health + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0);
//
//						if (areYouSure == 1)
//						{
//							this->health += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					case 2:
//					{
//						std::cout << "fatigue: " << this->fatigue << " -> " << this->fatigue + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);
//
//						if (areYouSure == 1)
//						{
//							this->fatigue += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					case 3:
//					{
//						std::cout << "Strength: " << this->strength << " -> " << this->strength + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);
//
//						if (areYouSure == 1)
//						{
//							this->strength += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					case 4:
//					{
//						std::cout << "Agility: " << this->agility << " -> " << this->agility + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);
//
//						if (areYouSure == 1)
//						{
//							this->agility += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					case 5:
//					{
//						std::cout << "Arcane: " << this->arcane << " -> " << this->arcane + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);
//
//						if (areYouSure == 1)
//						{
//							this->arcane += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					case 6:
//					{
//						std::cout << "Faith: " << this->faith << " -> " << this->faith + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);
//
//						if (areYouSure == 1)
//						{
//							this->faith += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					case 7:
//					{
//						std::cout << "Luck: " << this->luck << " -> " << this->luck + 3 << std::endl;
//						std::cout << "Are you sure? 1 = Yes, 2 = No" << std::endl;
//						//input validation
//						do
//						{
//							std::cout << ">> ";
//							std::cin >> areYouSure;
//							if (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0)
//							{
//								std::cout << "Enter a number from 1 - 2" << std::endl;
//							}
//							std::cin.clear();
//							std::cin.ignore(10000, '\n');
//						} while (std::cin.fail() || areYouSure > 2 || areYouSure == 0 || choice < 0);
//
//						if (areYouSure == 1)
//						{
//							this->luck += 3;
//						}
//						else
//						{
//							break;
//						}
//						break;
//					}
//					}
//
//				} while (areYouSure == 2);
//				iterator += 1;
//			}
//			if (iterator == 3)
//			{
//				levelUpComplete = true;
//			}
//		} while (levelUpComplete == false);
//
//		//this prints out the stats a final time after they are done leveling up so they can see their final results
//		std::cout << dye::light_yellow("1) Health: ") << this->health << std::endl;
//		std::cout << dye::light_yellow("2) fatigue: ") << this->fatigue << std::endl;
//		std::cout << dye::light_yellow("4) Strength: ") << this->strength << std::endl;
//		std::cout << dye::light_yellow("5) Agility: ") << this->agility << std::endl;
//		std::cout << dye::light_yellow("6) Arcane: ") << this->arcane << std::endl;
//		std::cout << dye::light_yellow("7) Faith: ") << this->faith << std::endl;
//		std::cout << dye::light_yellow("8) Luck: ") << this->luck << std::endl;
//
//		//loops so long as there is enough experience to level up again after consuming enough for a level
//		exp -= experienceToNextLevel;
//		level += 1;
//		refreshCharacterStats();
//	} while (exp >= experienceToNextLevel);
//	experience = exp;
//}
//
//void Character::killCharacter()
//{
//	this->isAlive = false;
//	if (this->isPlayer)
//	{
//		std::cout << dye::light_red("You have taken fatal damage...") << std::endl;
//	}
//	else
//	{
//		std::cout << "The " << this->name << " has taken" << dye::light_red(" fatal damage...") << std::endl;
//	}
//}
//void Character::openLootInterface(Character& container)
//{
//	int tally = 1;
//	bool quit = false;
//	int input = 1;
//	int goldCount = container.gold;
//
//	//iterate through this list first, sorting it by equipped items first, then backpack, then loot
//
//	std::vector<Item> initialLootItems = container.inventory.equippedItems;
//	for (int i = 0; i < container.inventory.backpackItems.size(); i++)
//	{
//		initialLootItems.push_back(container.inventory.backpackItems[i]);
//	}
//	for (int i = 0; i < container.inventory.lootItems.size(); i++)
//	{
//		initialLootItems.push_back(container.inventory.lootItems[i]);
//	}
//	std::vector<Potion> initialLootPotions = container.inventory.potions;
//
//	//this will contain the sorted items from the first 2 vectors and will be iterated through for any loop but the first one
//	std::vector<Item> finalLootItems;
//	std::vector<Potion> finalLootPotions;
//
//	bool firstLoop = true;
//	do {
//		if (firstLoop == true)
//		{
//			//printing the items available to loot
//			std::cout << "\n" << container.name << "'s spoils for the taking" << std::endl;
//			//equipped items
//
//			if (container.gold > 0)
//			{
//				tally = 1;
//				std::cout << tally << "): " << container.gold << "x gold piece(s)" << std::endl;
//			}
//			if (!initialLootItems.empty())
//			{
//				for (int i = 0; i < initialLootItems.size(); i++)
//				{
//					if (initialLootItems[i].itemType == Item::item_types::WEAPON)
//					{
//						tally += 1;
//						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
//							<< initialLootItems[i].name << ", value: "
//							<< initialLootItems[i].value << ", damage: "
//							<< initialLootItems[i].damage << ", attack speed: "
//							<< initialLootItems[i].attackSpeed << ", reach: "
//							<< initialLootItems[i].reach << ", weight: "
//							<< initialLootItems[i].weight << std::endl;
//						finalLootItems.push_back(initialLootItems[i]);
//
//					}
//				}
//			}
//			if (!initialLootItems.empty())
//			{
//				for (int i = 0; i < initialLootItems.size(); i++)
//				{
//
//					if (initialLootItems[i].itemType == Item::item_types::ARMOR)
//					{
//						tally += 1;
//						std::cout << tally << "): " << initialLootItems[i].quantity << "x " <<
//							initialLootItems[i].name << ", value: "
//							<< initialLootItems[i].value << ", defense: "
//							<< initialLootItems[i].defense << ", weight: "
//							<< initialLootItems[i].weight << std::endl;
//						finalLootItems.push_back(initialLootItems[i]);
//					}
//
//				}
//			}
//			if (!initialLootItems.empty())
//			{
//				for (int i = 0; i < initialLootItems.size(); i++)
//				{
//
//					if (initialLootItems[i].itemType == Item::item_types::SHIELD)
//					{
//						tally += 1;
//						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
//							<< initialLootItems[i].name << ", value: "
//							<< initialLootItems[i].value << ", defense: "
//							<< initialLootItems[i].defense << ", weight: "
//							<< initialLootItems[i].weight << std::endl;
//						finalLootItems.push_back(initialLootItems[i]);
//					}
//
//				}
//
//			}
//			if (!initialLootItems.empty())
//			{
//				for (int i = 0; i < initialLootItems.size(); i++)
//				{
//
//					if (initialLootItems[i].itemType == Item::item_types::ARCANETOOL ||
//						initialLootItems[i].itemType == Item::item_types::HOLYTOOL)
//					{
//						tally += 1;
//						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
//							<< initialLootItems[i].name << ", value: "
//							<< initialLootItems[i].value << ", magic adjust: "
//							<< initialLootItems[i].magicDamageType << ", weight: "
//							<< initialLootItems[i].weight << std::endl;
//						finalLootItems.push_back(initialLootItems[i]);
//
//					}
//
//				}
//
//			}
//			if (!initialLootItems.empty())
//			{
//				for (int i = 0; i < initialLootItems.size(); i++)
//				{
//
//					if (initialLootItems[i].itemType == Item::item_types::TRINKET)
//					{
//
//					}
//					//TODO After trinkets and torches are implemented 
//
//				}
//			}
//			if (!initialLootItems.empty())
//			{
//				for (int i = 0; i < initialLootItems.size(); i++)
//				{
//					if (initialLootItems[i].itemType == Item::item_types::LOOT)
//					{
//						tally += 1;
//						std::cout << tally << "): " << initialLootItems[i].quantity << "x "
//							<< initialLootItems[i].name << ", value: "
//							<< initialLootItems[i].value << ", weight: "
//							<< initialLootItems[i].weight << std::endl;
//						finalLootItems.push_back(initialLootItems[i]);
//
//					}
//				}
//			}
//			//potions
//
//			std::string effects[] = { "Restores Health", "Restores fatigue", "Cures Diseases" };
//			if (!initialLootPotions.empty())
//			{
//				for (int i = 0; i < initialLootPotions.size(); i++)
//				{
//					tally += 1;
//					std::cout << tally << "): " << initialLootPotions[i].quantity << "x "
//						<< initialLootPotions[i].name << ", value: "
//						<< initialLootPotions[i].value << ", effect: "
//						<< effects[initialLootPotions[i].effects] << ", weight: "
//						<< initialLootPotions[i].weight << std::endl;
//					finalLootPotions.push_back(initialLootPotions[i]);
//				}
//			}
//			firstLoop = false;
//		}
//		//loop 2
//		else if (firstLoop == false)
//		{
//			//printing the items available to loot
//			std::cout << "\n" << container.name << "'s spoils for the taking" << std::endl;
//			//equipped items
//
//			if (container.gold > 0)
//			{
//				tally = 1;
//				std::cout << tally << "): " << container.gold << "x gold piece(s)" << std::endl;
//			}
//			if (!finalLootItems.empty())
//			{
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//					if (finalLootItems[i].itemType == Item::item_types::WEAPON)
//					{
//						tally += 1;
//						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
//							<< finalLootItems[i].name << ", value: "
//							<< finalLootItems[i].value << ", damage: "
//							<< finalLootItems[i].damage << ", attack speed: "
//							<< finalLootItems[i].attackSpeed << ", reach: "
//							<< finalLootItems[i].reach << ", weight: "
//							<< finalLootItems[i].weight << std::endl;
//					}
//				}
//			}
//			if (!finalLootItems.empty())
//			{
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//
//					if (finalLootItems[i].itemType == Item::item_types::ARMOR)
//					{
//						tally += 1;
//						std::cout << tally << "): " << finalLootItems[i].quantity << "x " <<
//							finalLootItems[i].name << ", value: "
//							<< finalLootItems[i].value << ", defense: "
//							<< finalLootItems[i].defense << ", weight: "
//							<< finalLootItems[i].weight << std::endl;
//					}
//
//				}
//			}
//			if (!finalLootItems.empty())
//			{
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//
//					if (finalLootItems[i].itemType == Item::item_types::SHIELD)
//					{
//						tally += 1;
//						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
//							<< finalLootItems[i].name << ", value: "
//							<< finalLootItems[i].value << ", defense: "
//							<< finalLootItems[i].defense << ", weight: "
//							<< finalLootItems[i].weight << std::endl;
//					}
//
//				}
//
//			}
//			if (!finalLootItems.empty())
//			{
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//
//					if (finalLootItems[i].itemType == Item::item_types::ARCANETOOL ||
//						finalLootItems[i].itemType == Item::item_types::HOLYTOOL)
//					{
//						tally += 1;
//						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
//							<< finalLootItems[i].name << ", value: "
//							<< finalLootItems[i].value << ", magic adjust: "
//							<< finalLootItems[i].magicDamageType << ", weight: "
//							<< finalLootItems[i].weight << std::endl;
//					}
//
//				}
//
//			}
//			if (!finalLootItems.empty())
//			{
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//
//					if (finalLootItems[i].itemType == Item::item_types::TRINKET)
//					{
//
//					}
//					//TODO After trinkets and torches are implemented 
//
//				}
//			}
//			if (!finalLootItems.empty())
//			{
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//					if (finalLootItems[i].itemType == Item::item_types::LOOT)
//					{
//						tally += 1;
//						std::cout << tally << "): " << finalLootItems[i].quantity << "x "
//							<< finalLootItems[i].name << ", value: "
//							<< finalLootItems[i].value << ", weight: "
//							<< finalLootItems[i].weight << std::endl;
//					}
//				}
//			}
//			//potions
//
//			std::string effects[] = { "Restores Health", "Restores fatigue", "Cures Diseases" };
//			if (!finalLootPotions.empty())
//			{
//				for (int i = 0; i < finalLootPotions.size(); i++)
//				{
//					tally += 1;
//					std::cout << tally << "): " << finalLootPotions[i].quantity << "x "
//						<< finalLootPotions[i].name << ", value: "
//						<< finalLootPotions[i].value << ", effect: "
//						<< effects[finalLootPotions[i].effects] << ", weight: "
//						<< finalLootPotions[i].weight << std::endl;
//				}
//			}
//		}
//		//selecting which items to loot
//
//		if (!finalLootItems.empty() || !finalLootPotions.empty())
//		{
//			std::cout << "\nSelect the item to loot by typing the number besides its name" << std::endl;
//			std::cout << "Type -1 to loot everything" << std::endl;
//			std::cout << "Or, type -2 to leave the rest for the vultures" << std::endl;
//			do
//			{
//				std::cout << "\n>>";
//				std::cin >> input;
//				if (std::cin.fail() || input > tally || input == 0 || input < -2)
//				{
//					std::cout << "Enter a number from 1 - " << tally << ", or enter -1 or -2" << std::endl;
//				}
//				std::cin.clear();
//				std::cin.ignore(10000, '\n');
//			} while (std::cin.fail() || input > tally || input == 0 || input < -2);
//
//			if (input == -1)
//			{
//				this->gold += goldCount;
//				std::cout << goldCount << " gold pieces added to backpack!" << std::endl;
//				//select all
//				for (int i = 0; i < finalLootItems.size(); i++)
//				{
//					this->inventory.addItemToBackpack(finalLootItems[i]);
//					std::cout << finalLootItems[i].name << " added to backpack!" << std::endl;
//				}
//				for (int i = 0; i < finalLootPotions.size(); i++)
//				{
//					this->inventory.addPotion(finalLootPotions[i]);
//					std::cout << finalLootPotions[i].name << " added to backpack!" << std::endl;
//				}
//				quit = true;
//			}
//			if (input > 0 && input <= tally)
//				//individual selection
//			{
//				if (container.gold > 0)
//				{
//					if (input == 1)
//					{
//						this->gold += goldCount;
//						std::cout << goldCount << " gold pieces added to backpack!" << std::endl;
//						container.gold -= goldCount;
//						tally = 0;
//					}
//					else if (!finalLootItems.empty() && input < finalLootItems.size() + 2)
//					{
//						int num = input - 2;
//						this->inventory.addItemToBackpack(finalLootItems[num]);
//						std::cout << finalLootItems[num].name << " added to backpack!" << std::endl;
//						finalLootItems.erase(finalLootItems.begin() + num);
//						tally = 0;
//					}
//					else if (!finalLootPotions.empty() && input > finalLootItems.size() + 1)
//					{
//						int num = input - finalLootItems.size() - 2;
//						this->inventory.addPotion(finalLootPotions[num]);
//						std::cout << finalLootPotions[num].name << " added to backpack!" << std::endl;
//						finalLootPotions.erase(finalLootPotions.begin() + num);
//						tally = 0;
//					}
//					else
//					{
//						std::cout << "Item not found!" << std::endl;
//						tally = 0;
//					}
//				}
//				else
//				{
//					if (!finalLootItems.empty() && input < finalLootItems.size() + 1)
//					{
//						int num = input - 1;
//						this->inventory.addItemToBackpack(finalLootItems[num]);
//						std::cout << finalLootItems[num].name << " added to backpack!" << std::endl;
//						finalLootItems.erase(finalLootItems.begin() + num);
//						tally = 0;
//					}
//					else if (!finalLootPotions.empty() && input > finalLootItems.size())
//					{
//						int num = input - finalLootItems.size() - 1;
//						this->inventory.addPotion(finalLootPotions[num]);
//						std::cout << finalLootPotions[num].name << " added to backpack!" << std::endl;
//						finalLootPotions.erase(finalLootPotions.begin() + num);
//						tally = 0;
//					}
//					else
//					{
//						std::cout << "Item not found!" << std::endl;
//						tally = 0;
//					}
//
//				}
//			}
//			if (input == -2)
//			{
//				quit = true;
//				std::cout << "Departing..." << std::endl;
//			}
//		}
//		//loops so long as there are items left in any inventory of the containe or until the user opts to quit
//		if (finalLootItems.empty() && finalLootPotions.empty() && container.gold == 0)
//		{
//			std::cout << "You've pillaged every morsel!" << std::endl;
//			quit = true;
//		}
//	} while (input != -2 && quit == false);
//}
//void Character::printCharacterStats(Character& character)
//{
//	std::cout << dye::light_yellow("  Class: ") << character.characterClass << std::endl;
//	std::cout << dye::light_yellow("  Health Points: ") << character.healthPoints << "/" << character.maxHealthPoints << std::endl;
//	std::cout << dye::light_yellow("  fatigue Points: ") << character.fatiguePoints << "/" << character.maxfatiguePoints << std::endl;
//	std::cout << "\n";
//	std::cout << dye::light_yellow("  Health: ") << character.health << std::endl;
//	std::cout << dye::light_yellow("  fatigue: ") << character.fatigue << std::endl;
//	std::cout << dye::light_yellow("  Strength: ") << character.strength << std::endl;
//	std::cout << dye::light_yellow("  Agility: ") << character.agility << std::endl;
//	std::cout << dye::light_yellow("  Arcane: ") << character.arcane << std::endl;
//	std::cout << dye::light_yellow("  Faith: ") << character.faith << std::endl;
//	std::cout << dye::light_yellow("  Luck: ") << character.luck << std::endl;
//	std::cout << "\n";
//	std::cout << dye::light_yellow("  Speed: ") << character.speed << std::endl;
//	std::cout << dye::light_yellow("  Damage Reduction: ") << character.damageReduction << "%" << std::endl;
//	//under construction below
//	std::cout << dye::light_yellow("  Critical Chance: ") << character.critChance << "%" << std::endl;
//	std::cout << dye::light_yellow("  Dodge Chance: ") << character.dodgeChance << "%" << std::endl;
//	std::cout << dye::light_yellow("  Block Chance: ") << character.blockChance << "%" << std::endl;
//	std::cout << dye::light_yellow("  Block Amount: ") << character.blockAmount << std::endl;
//	std::cout << "\n";
//	std::cout << dye::light_yellow("  Level: ") << character.level << std::endl;
//	std::cout << dye::light_yellow("  Experience: ") << character.experience << "/" << character.experienceToNextLevel << std::endl;
//	std::cout << "\n";
//	std::cout << dye::light_yellow("  Gold: ") << character.gold << std::endl;
//}
//
//void Character::addItemToEnemy(Character enemy, Item item, Item::equip_slots slot)
//{
//
//}
//
//void Character::checkPlayer()
//{
//	std::cout << "Name: " << this->name << std::endl;
//	std::cout << "Class: " << this->characterClass << std::endl;
//	std::cout << "Level: " << this->level << std::endl;
//	std::cout << std::endl;
//	std::cout << "Health: " << this->health << std::endl;
//	std::cout << "fatigue: " << this->fatigue << std::endl;
//	std::cout << "Strength: " << this->strength << std::endl;
//	std::cout << "Agility: " << this->agility << std::endl;
//	std::cout << "Arcane: " << this->arcane << std::endl;
//	std::cout << "Faith: " << this->faith << std::endl;
//	std::cout << "Luck: " << this->luck << std::endl;
//	std::cout << std::endl;
//	std::cout << "Health Points: " << this->healthPoints << "/" << this->maxHealthPoints << std::endl;
//	std::cout << "fatigue Points: " << this->fatiguePoints << "/" << this->maxfatiguePoints << std::endl;
//	std::cout << std::endl;
//	std::cout << "Speed: " << this->speed << std::endl;
//	std::cout << "Damage Reduction: " << this->damageReduction << "%" << std::endl;
//	std::cout << "Critical Chance: " << this->critChance << "%" << std::endl;
//	std::cout << "Dodge Chance: " << this->dodgeChance << "%" << std::endl;
//	std::cout << "Block Chance: " << this->blockChance << "%" << std::endl;
//	std::cout << "Block Amount: " << this->blockAmount << std::endl;
//	std::cout << std::endl;
//	std::cout << "Experience: " << this->experience << "/" << this->experienceToNextLevel << std::endl;
//	std::cout << "Gold: " << this->gold << std::endl;
//}
//
//void Character::checkCharacterIntro(Character player)
//{
//	//get all equipped items the character has access to
//	std::vector<Potion> potions = this->inventory.potions;
//	std::vector<Item> items = this->inventory.getEquippedItems();
//	Item mainHand1;
//	Item mainHand2;
//	Item offHand1;
//	Item offHand2;
//	Item amulet;
//	Item ring1;
//	Item ring2;
//	Item misc;
//
//	//until I figure out how to ensure this is set to false by default, we need this because its true 
//	//  by default 
//	mainHand1.hasBeenInitialized = false;
//	mainHand2.hasBeenInitialized = false;
//	offHand1.hasBeenInitialized = false;
//	offHand2.hasBeenInitialized = false;
//	amulet.hasBeenInitialized = false;
//	ring1.hasBeenInitialized = false;
//	ring2.hasBeenInitialized = false;
//	misc.hasBeenInitialized = false;
//	for (int i = 0; i < items.size(); i++)
//	{
//		if (items[i].slot == Item::MAINHAND1)
//		{
//			mainHand1 = items[i];
//		}
//		else if (items[i].slot == Item::MAINHAND2)
//		{
//			mainHand2 = items[i];
//		}
//		else if (items[i].slot == Item::OFFHAND1)
//		{
//			offHand1 = items[i];
//		}
//		else if (items[i].slot == Item::OFFHAND2)
//		{
//			offHand2 = items[i];
//		}
//		else if (items[i].slot == Item::AMULET)
//		{
//			amulet = items[i];
//		}
//		else if (items[i].slot == Item::RING1)
//		{
//			ring1 = items[i];
//		}
//		else if (items[i].slot == Item::RING2)
//		{
//			ring2 = items[i];
//		}
//		else if (items[i].slot == Item::MISC)
//		{
//			misc = items[i];
//		}
//	}
//
//	//Level difference text
//	float levelDifference = (player.level / this->level);
//
//	//should only print out when they're above 76% health to show that their stature is getting weaker as they take damage
//	//their level is 50% greater than the player's level
//	if (this->namedCharacter)
//	{
//		if (levelDifference < .66 && this->healthPoints > maxHealthPoints / 1.34)
//		{
//			std::cout << dye::light_yellow(this->name) << " has a foreboding presence. You should take care..." << std::endl;
//		}
//		//their level is 50% less than the player's level
//		else if (levelDifference > 1.5 && this->healthPoints > maxHealthPoints / 1.34)
//		{
//			std::cout << dye::light_yellow(this->name) << " shuffles about nervously. You can take them." << std::endl;
//		}
//		else if (levelDifference > .83 && levelDifference < 1.25 && this->healthPoints > maxHealthPoints / 1.34)
//		{
//			std::cout << dye::light_yellow(this->name) << " and you appear to be evenly matched." << std::endl;
//		}
//	}
//	else
//	{
//		if (levelDifference < .66 && this->healthPoints > maxHealthPoints / 1.34)
//		{
//			std::cout << "The " << dye::light_yellow(this->name) << " has a foreboding presence. You should take care..." << std::endl;
//		}
//		//their level is 50% less than the player's level
//		else if (levelDifference > 1.5 && this->healthPoints > maxHealthPoints / 1.34)
//		{
//			std::cout << "The " << dye::light_yellow(this->name) << " shuffles about nervously. You can take them." << std::endl;
//		}
//		else if (levelDifference > .83 && levelDifference < 1.25 && this->healthPoints > maxHealthPoints / 1.34)
//		{
//			std::cout << "The " << dye::light_yellow(this->name) << " and you appear to be evenly matched." << std::endl;
//		}
//	}
//	
//	//weapon specific
//	//what weapon(s) they are using?
//
//	std::string weaponTypes[] = { "nothing", "dagger", "straight sword", "great sword",
//		"fist weapon", "mace", "great mace", "hatchet", "axe", "great axe",
//		"thrusting sword", "spear", "great spear", "halberd", "polehammer", "parrying shield",
//		"average-sized shield", "great shield", "longbow", "compound bow",
//		"great bow", "miniature crossbow", "crossbow", "handheld ballista",
//		"talisman", "chime", "arcane tome", "magic wand", "magic staff", "magic orb" };
//
//	//if they have an item in each hand
//	if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == true)
//	{
//		std::cout << "They carry a "
//			<< weaponTypes[mainHand1.weaponType] << " in their main hand, ";
//		std::cout << "and a " << weaponTypes[offHand1.weaponType] << " in their off hand." << std::endl;
//	}
//	//if they have an item in both of their hands, plus weapons they can readily switch to
//	else if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == true
//		&& mainHand2.hasBeenInitialized == true && offHand2.hasBeenInitialized == true)
//	{
//		std::cout << "They carry a "
//			<< weaponTypes[mainHand1.weaponType] << " in their main hand, ";
//		std::cout << "and a " << weaponTypes[offHand1.weaponType] << " in their off hand." << std::endl;
//		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " and a "
//			<< weaponTypes[offHand2.weaponType] << " at the ready on their person." << std::endl;
//	}
//	//if they have an item in both of their hands, plus a twohanded weapon they can switch to
//	else if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == true
//		&& mainHand2.hasBeenInitialized == true && mainHand2.twoHanded == true)
//	{
//		std::cout << "They carry a "
//			<< weaponTypes[mainHand1.weaponType] << " in their main hand,";
//		std::cout << "and a " << weaponTypes[offHand1.weaponType] << " in their off hand." << std::endl;
//		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " at the ready on their person." << std::endl;
//	}
//	//if they only have one weapon equipped
//	else if (mainHand1.hasBeenInitialized == true && offHand1.hasBeenInitialized == false
//		&& offHand2.hasBeenInitialized == false && mainHand1.hasBeenInitialized == false)
//	{
//		std::cout << "They carry nothing but a "
//			<< weaponTypes[mainHand1.weaponType] << " in their main hand." << std::endl;
//	}
//	//if they have a two handed weapon and nothing else
//	else if (mainHand1.hasBeenInitialized == true && mainHand1.twoHanded == true
//		&& offHand1.hasBeenInitialized == false && offHand2.hasBeenInitialized == false
//		&& mainHand2.hasBeenInitialized == false)
//	{
//		std::cout << "They wield a " << weaponTypes[mainHand1.weaponType] << " with both hands." << std::endl;
//	}
//	//if they have a two handed weapon and another twohanded weapon to switch to
//	else if (mainHand1.hasBeenInitialized == true && mainHand1.twoHanded == true
//		&& mainHand2.hasBeenInitialized == true && mainHand2.twoHanded == true)
//	{
//		std::cout << "They wield a " << weaponTypes[mainHand1.weaponType] << " with both hands." << std::endl;
//		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " holstered on their back." << std::endl;
//	}
//	//if they have a two handed weapon and two more one handed items to switch to
//	else if (mainHand1.hasBeenInitialized == true && mainHand1.twoHanded == true
//		&& mainHand2.hasBeenInitialized == true && offHand2.hasBeenInitialized == true)
//	{
//		std::cout << "They wield a " << weaponTypes[mainHand1.weaponType] << " with both hands." << std::endl;
//		std::cout << "They also have a " << weaponTypes[mainHand2.weaponType] << " and a " << weaponTypes[offHand1.weaponType] << " at the ready on their person." << std::endl;
//	}
//	else {
//		std::cout << "They have the gall to approach you empty handed." << std::endl;
//	}
//
//	//what armor they are wearing?
//
//	std::string armorTypes[] = { "not armor", "leather", "padded leather",
//		"studded leather", "chainmail", "lamellar", "metal scale",
//		"ringmail", "chain-plate", "full plate" };
//
//	int numLight = 0;
//	int numMedium = 0;
//	int numHeavy = 0;
//
//	//count the number of light, medium, and heavy armor pieces they have equipped
//	for (int i = 0; i < items.size(); i++)
//	{
//		if (items[i].armorType == Item::LEATHER ||
//			items[i].armorType == Item::PADDED ||
//			items[i].armorType == Item::STUDDEDLEATHER)
//		{
//			numLight++;
//		}
//		else if (items[i].armorType == Item::CHAIN ||
//			items[i].armorType == Item::LAMELLAR ||
//			items[i].armorType == Item::SCALE)
//		{
//			numMedium++;
//		}
//		else if (items[i].armorType == Item::CHAINPLATE ||
//			items[i].armorType == Item::FULLPLATE ||
//			items[i].armorType == Item::BEASTSCALE)
//		{
//			numHeavy++;
//		}
//	}
//
//	//outputs the kind of armor they are wearing at a glance. More detailed descriptions
//	//  can be found in the check enemy menu
//	if (numLight > 0 && numMedium == 0 && numHeavy == 0)
//	{
//		std::cout << "They are wearing light armor." << std::endl;
//	}
//	else if (numLight == 0 && numMedium > 0 && numHeavy == 0)
//	{
//		std::cout << "They are wearing medium armor." << std::endl;
//	}
//	else if (numLight == 0 && numMedium == 0 && numHeavy > 0)
//	{
//		std::cout << "They are wearing heavy armor." << std::endl;
//	}
//
//	//mixed armor types
//	else if (numLight > 0 && numMedium > 0 && numHeavy == 0)
//	{
//		std::cout << "They are wearing a mixture of light and medium armor." << std::endl;
//	}
//	else if (numLight > 0 && numMedium == 0 && numHeavy > 0)
//	{
//		std::cout << "They are wearing a mixture of light and heavy armor." << std::endl;
//	}
//	else if (numLight == 0 && numMedium > 0 && numHeavy > 0)
//	{
//		std::cout << "They are wearing a mixture of medium and heavy armor." << std::endl;
//	}
//	else if (numLight > 0 && numMedium > 0 && numHeavy > 0)
//	{
//		std::cout << "They are wearing a mixture of light, medium, and heavy armor." << std::endl;
//	}
//
//	//if they have no armor equipped
//	else if (numLight == 0 && numMedium == 0 && numHeavy == 0)
//	{
//		std::cout << "They are daring not to wear any armor." << std::endl;
//	}
//}
//void Character::checkCharacter(Character player)
//{
//	//get all equipped items the character has access to
//	std::vector<Potion> potions = this->inventory.potions;
//	std::vector<Item> items = this->inventory.getEquippedItems();
//	Item mainHand1;
//	Item mainHand2;
//	Item offHand1;
//	Item offHand2;
//	Item amulet;
//	Item ring1;
//	Item ring2;
//	Item misc;
//
//	//until I figure out how to ensure this is set to false by default, we need this because its true 
//	//  by default 
//	mainHand1.hasBeenInitialized = false;
//	mainHand2.hasBeenInitialized = false;
//	offHand1.hasBeenInitialized = false;
//	offHand2.hasBeenInitialized = false;
//	amulet.hasBeenInitialized = false;
//	ring1.hasBeenInitialized = false;
//	ring2.hasBeenInitialized = false;
//	misc.hasBeenInitialized = false;
//	for (int i = 0; i < items.size(); i++)
//	{
//		if (items[i].slot == Item::MAINHAND1)
//		{
//			mainHand1 = items[i];
//		}
//		else if (items[i].slot == Item::MAINHAND2)
//		{
//			mainHand2 = items[i];
//		}
//		else if (items[i].slot == Item::OFFHAND1)
//		{
//			offHand1 = items[i];
//		}
//		else if (items[i].slot == Item::OFFHAND2)
//		{
//			offHand2 = items[i];
//		}
//		else if (items[i].slot == Item::AMULET)
//		{
//			amulet = items[i];
//		}
//		else if (items[i].slot == Item::RING1)
//		{
//			ring1 = items[i];
//		}
//		else if (items[i].slot == Item::RING2)
//		{
//			ring2 = items[i];
//		}
//		else if (items[i].slot == Item::MISC)
//		{
//			misc = items[i];
//		}
//	}
//
//	//Health based text
//
//	//100%
//	if (this->healthPoints == this->maxHealthPoints)
//	{
//		std::cout << "The " << this->name << " is completely healthy." << std::endl;
//	}
//
//	//75%
//	else if (this->healthPoints >= maxHealthPoints * .75 && this->healthPoints <= maxHealthPoints)
//	{
//		std::cout << "The " << this->name << " has taken a few hits. Are they bleeding?" << std::endl;
//	}
//
//	//50%
//	else if (this->healthPoints >= maxHealthPoints * .5 && this->healthPoints < maxHealthPoints * .75)
//	{
//		std::cout << "The " << this->name << " has a few large wounds. Best not to let them become scars." << std::endl;
//	}
//
//	//25%
//	else if (this->healthPoints >= maxHealthPoints * .25 && this->healthPoints < maxHealthPoints * .75)
//	{
//		std::cout << "The " << this->name << " is on their last legs. Show them no mercy!" << std::endl;
//	}
//
//	//10%
//	else if (this->healthPoints < maxHealthPoints * .25)
//	{
//		std::cout << "It's a marvel that the " << this->name << " is still standing after the punishment they've endured." << std::endl;
//	}
//
//	//fatigue based text
//
//	//100%
//	if (this->fatiguePoints == this->maxfatiguePoints)
//	{
//		std::cout << "They are alert and attentive. Their fatigue must be close to full." << std::endl;
//	}
//
//	//75%
//	else if (this->fatiguePoints >= maxfatiguePoints * .75 && this->fatiguePoints < maxfatiguePoints)
//	{
//		std::cout << "They look like they can keep the magic up for a while longer." << std::endl;
//	}
//
//	//50%
//	else if (this->fatiguePoints >= maxfatiguePoints * .5 && this->fatiguePoints <= maxfatiguePoints * .75)
//	{
//		std::cout << "They look somewhat disoriented. Are they running out of fatigue?" << std::endl;
//	}
//
//	//25%
//	else if (this->fatiguePoints >= maxfatiguePoints * .25&& this->fatiguePoints <= maxfatiguePoints * .5)
//	{
//		std::cout << "They look very disoriented. They must be running dry on fatigue." << std::endl;
//	}
//
//	//10%
//	else if (this->fatiguePoints <= maxfatiguePoints* .25)
//	{
//		std::cout << "They look like they don't have the magical energy to muster a spark." << std::endl;
//	}
//
//	checkCharacterIntro(player);
//
//	//if they are wearing jewelry
//
//	//if they have an item in each jewelry slot
//	if (amulet.hasBeenInitialized == true && ring1.hasBeenInitialized == true
//		&& ring2.hasBeenInitialized == true)
//	{
//		std::cout << "They are wearing a plethora of jewelry." << std::endl;
//	}
//
//	//if they have an amulet
//	else if (amulet.hasBeenInitialized == true && ring1.hasBeenInitialized == false
//		&& ring2.hasBeenInitialized == false)
//	{
//		std::cout << "An amulet gleams in the light upon " << this->name << "'s neck." << std::endl;
//	}
//
//	//if they have an amulet and a ring
//	else if (amulet.hasBeenInitialized == true && ring1.hasBeenInitialized == true
//		&& ring2.hasBeenInitialized == false)
//	{
//		std::cout << "An amulet gleams in the light upon " << this->name <<
//			"'s neck, and a ring glints on one of their fingers." << std::endl;
//	}
//
//	//if they are wearing just a ring
//	else if (amulet.hasBeenInitialized == false && ring1.hasBeenInitialized == true
//		&& ring2.hasBeenInitialized == false)
//	{
//		std::cout << "A ring glints on one of " << this->name << "'s fingers." << std::endl;
//	}
//
//	//if they are wearing two rings
//	else if (amulet.hasBeenInitialized == false && ring1.hasBeenInitialized == true
//		&& ring2.hasBeenInitialized == true)
//	{
//		std::cout << "Two rings glint in the light on " << this->name << "'s fingers." << std::endl;
//	}
//
//	//what potions do they have on them?
//
//	std::string effects[] = { "Restores Health", "Restores fatigue", "Cures Diseases" };
//	int healingPotionCount = 0;
//	int fatiguePotionCount = 0;
//	int cureDiseaseCount = 0;
//
//	for (int i = 0; i < potions.size(); i++)
//	{
//		if (potions[i].effects == Potion::HEALING)
//		{
//			healingPotionCount += 1;
//		}
//		else if (potions[i].effects == Potion::fatigue)
//		{
//			fatiguePotionCount += 1;
//		}
//		else if (potions[i].effects == Potion::CUREDISEASE)
//		{
//			cureDiseaseCount += 1;
//		}
//	}
//
//	//if they have all of one potion type
//	if (healingPotionCount > 0 && fatiguePotionCount == 0 && cureDiseaseCount == 0)
//	{
//		std::cout << "Healing potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//	else if (healingPotionCount == 0 && fatiguePotionCount > 0 && cureDiseaseCount == 0)
//	{
//		std::cout << "fatigue potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//	else if (healingPotionCount == 0 && fatiguePotionCount == 0 && cureDiseaseCount > 0)
//	{
//		std::cout << "Cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//
//	//if they have a mixture of types
//	else if (healingPotionCount > 0 && fatiguePotionCount > 0 && cureDiseaseCount == 0)
//	{
//		std::cout << "Healing and fatigue potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//	else if (healingPotionCount > 0 && fatiguePotionCount == 0 && cureDiseaseCount > 0)
//	{
//		std::cout << "Healing and cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//	else if (healingPotionCount == 0 && fatiguePotionCount > 0 && cureDiseaseCount > 0)
//	{
//		std::cout << "fatigue and cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//	else if (healingPotionCount > 0 && fatiguePotionCount > 0 && cureDiseaseCount > 0)
//	{
//		std::cout << "Healing, fatigue, and cure disease potions clink about on the " << this->name << "'s belt" << std::endl;
//	}
//
//	//do they have enough gold to be visible outside their pockets?
//	if (this->gold >= 50)
//	{
//		std::cout << "A coin purse hangs from the " << this->name << "'s belt." << std::endl;
//	}
//	else if (this->gold >= 100)
//	{
//		std::cout << "A heavy coin purse hangs from the " << this->name << "'s belt." << std::endl;
//	}
//	else if (this->gold >= 200)
//	{
//		std::cout << "A bulging coin purse hangs from the " << this->name << "'s belt." << std::endl;
//	}
//	else if (this->gold >= 500)
//	{
//		std::cout << "A sack of gold hangs from the " << this->name << "'s belt." << std::endl;
//	}
//	else if (this->gold >= 1000)
//	{
//		std::cout << "A small chest, clinking with gold as they move, hangs from the " << this->name << "'s back." << std::endl;
//	}
//}
//
//void Character::openPotionDialogue(bool& turnOver)
//{
//	if (this->isAlive == false)
//	{
//		std::cout << "Your enemy was too quick and you're dead before the potion can reach your lips..." << std::endl;
//	}
//	else
//	{
//		std::vector<Potion> healingPotions;
//		int potionQuantity = 0;
//		for (int i = 0; i < this->inventory.potions.size(); i++)
//		{
//			if (this->inventory.potions[i].effects == Potion::HEALING)
//			{
//				healingPotions.push_back(this->inventory.potions[i]);
//				potionQuantity += this->inventory.potions[i].quantity;
//			}
//		}
//		std::cout << "You have " << potionQuantity << " healing potions left." << std::endl;
//		std::cout << "Would you like to drink one? 1 = yes, 2 = no" << std::endl;
//		//input validation
//		int choice;
//		do
//		{
//			std::cout << ">> ";
//			std::cin >> choice;
//			if (std::cin.fail() || choice > 2 || choice == 0)
//			{
//				std::cout << "Enter a number from 1 - 2" << std::endl;
//			}
//			std::cin.clear();
//			std::cin.ignore(10000, '\n');
//		} while (std::cin.fail() || choice > 2 || choice == 0);
//
//		//yes
//		if (choice == 1)
//		{
//			std::cout << "Choose a potion.." << std::endl;
//			for (int i = 1; i < healingPotions.size() + 1; i++)
//			{
//				std::cout << i << ") " << healingPotions[i - 1].name << ", magnitude of "
//					<< healingPotions[i - 1].magnitude << ", quantity of " << healingPotions[i - 1].quantity << std::endl;
//			}
//			do
//			{
//				std::cout << ">> ";
//				std::cin >> choice;
//				if (std::cin.fail() || choice > healingPotions.size() || choice == 0)
//				{
//					std::cout << "Enter a number from 1 - " << healingPotions.size() << std::endl;
//				}
//				std::cin.clear();
//				std::cin.ignore(10000, '\n');
//			} while (std::cin.fail() || choice > healingPotions.size() || choice == 0);
//
//			this->drinkPotion(healingPotions[choice - 1]);
//		}
//		if (choice == 2)
//		{
//			turnOver = false;
//		}
//	}
//}
//
//void Character::drinkPotion(Potion& potion) {
//	if (this->isPlayer == true)
//	{
//		if (potion.effects == Potion::HEALING) {
//			if (this->healthPoints == this->maxHealthPoints) {
//				std::cout << dye::light_yellow("You are already at full health and did not consume the potion.") << std::endl;
//			}
//			else {
//				this->receiveHealing(potion.magnitude);
//				if (potion.quantity == 1) {
//					this->inventory.removePotion(potion);
//				}
//				else {
//					this->inventory.updatePotionQuantity(potion.name, potion.quantity - 1);
//				}
//				std::cout << potion.name << " consumed, " << potion.magnitude << " points of healing administered." << std::endl;
//			}
//		}
//		else
//		{
//			std::cout << "Invalid potion" << std::endl;
//		}
//	}
//	else
//	{
//		if (potion.effects == Potion::HEALING) {
//			if (this->healthPoints == this->maxHealthPoints) {
//				std::cout << dye::light_yellow(this->name) << dye::light_yellow(" tried to drink a potion, but they were already at full health and did not consume the potion.") << std::endl;
//			}
//			else {
//				this->receiveHealing(potion.magnitude);
//				if (potion.quantity == 1) {
//					this->inventory.removePotion(potion);
//				}
//				else {
//					this->inventory.updatePotionQuantity(potion.name, potion.quantity - 1);
//				}
//				std::cout << this->name << " consumed a " << potion.name << ", " << potion.magnitude << " points of healing administered." << std::endl;
//			}
//		}
//		else
//		{
//			std::cout << "Invalid potion" << std::endl;
//		}
//	}
//
//}
//
//void Character::sellItem(Item& item) {
//	std::cout << "Are you sure you want to sell this " << item.name << " for " << item.value << " gold pieces?" << std::endl;
//	std::cout << "1 = Yes, 2 = No" << std::endl;
//	int choice;
//	do
//	{
//		std::cout << ">> ";
//		std::cin >> choice;
//		if (std::cin.fail() || choice > 5 || choice == 0)
//		{
//			std::cout << "Enter a number from 1 - 2" << std::endl;
//		}
//		std::cin.clear();
//		std::cin.ignore(10000, '\n');
//	} while (std::cin.fail() || choice > 5 || choice == 0);
//	if (choice == 1)
//	{
//		if (item.quantity == 1)
//		{
//			this->inventory.removeItemFromBackpack(item);
//			this->gold += item.value;
//			std::cout << item.name << " sold for " << item.value << " gold pieces!" << std::endl;
//		}
//		else {
//			item.quantity -= 1;
//			this->gold += item.value;
//			std::cout << item.name << " sold for " << item.value << " gold pieces!" << std::endl;
//		}
//	}
//	else {
//		std::cout << "Item not sold" << std::endl;
//	}
//}