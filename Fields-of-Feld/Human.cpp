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
#include "Effect.h"
#include "Enchantment.h"

Human::Human(bool isPlayer, bool isAlly, CharacterClass classChoice, Personality personality, float health, float fatigue, float strength, float agility, float charisma,
	float intelligence, float arcane, float faith, float luck, float weightBurden, float castSpeed, float maxWeightBurden,
	double experience, double experienceToNextLevel,
	int gold)
	: Character(isAlly, namedCharacter, true, true, false,
		"NAME", "DESC", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, inventory,
		1.0f, CombatFlags::NEUTRAL),
	isPlayer(isPlayer), classChoice(classChoice), health(health), fatigue(fatigue),
	strength(strength), agility(agility), charisma(charisma), intelligence(intelligence), 
	arcane(arcane), faith(faith), luck(luck), weightBurden(weightBurden), castSpeed(castSpeed),
	maxWeightBurden(maxWeightBurden), experience(experience), experienceToNextLevel(experienceToNextLevel),
	gold(gold)
{
	setInitialHumanStats();
}

nlohmann::json Human::toJson() const {
	nlohmann::json j;

	// Identity & state
	j["type"] = "Human"; // Required for proper deserialization
	j["id"] = id;
	j["isPlayer"] = isPlayer;
	j["isAlly"] = isAlly;

	// Enum values stored as integers
	j["classChoice"] = static_cast<int>(classChoice);
	j["personality"] = static_cast<int>(personality);

	// Core stats
	j["health"] = health;
	j["fatigue"] = fatigue;
	j["strength"] = strength;
	j["agility"] = agility;
	j["charisma"] = charisma;
	j["intelligence"] = intelligence;
	j["arcane"] = arcane;
	j["faith"] = faith;
	j["luck"] = luck;

	// Load-bearing stats
	j["weightBurden"] = weightBurden;
	j["maxWeightBurden"] = maxWeightBurden;
	j["castSpeed"] = castSpeed;

	// Progression
	j["experience"] = experience;
	j["experienceToNextLevel"] = experienceToNextLevel;
	j["gold"] = gold;

	// Inventory
	j["inventory"] = inventory.toJson();

	// Spells
	for (const auto& s : attunedSpells)
		j["attunedSpells"].push_back(s->toJson());

	for (const auto& s : knownSpells)
		j["knownSpells"].push_back(s->toJson());

	// Allies
	for (const auto& ally : allies)
		j["allies"].push_back(ally->toJson());

	// Tags
	for (const auto& tag : tags)
		j["tags"].push_back(*tag); // shared_ptr<std::string> ? string

	// Combat Flags (store as int)
	for (const auto& flag : combatFlags)
		j["combatFlags"].push_back(static_cast<int>(flag));

	// Effects
	for (const auto& eff : effects)
		j["effects"].push_back(eff->toJson());

	// Resistances / defenses
	j["defenseValues"] = defenseValues;

	return j;
}

std::shared_ptr<Character> Human::fromJson(const nlohmann::json& j) {
	auto c = std::make_shared<Human>();

	// Base values
	c->id = j.at("id");
	c->isPlayer = j.at("isPlayer");
	c->isAlly = j.at("isAlly");

	// Enums (cast from int stored in JSON)
	c->classChoice = static_cast<Human::CharacterClass>(j.at("classChoice"));
	c->personality = static_cast<Human::Personality>(j.at("personality"));

	// Core stats
	c->health = j.at("health");
	c->fatigue = j.at("fatigue");
	c->strength = j.at("strength");
	c->agility = j.at("agility");
	c->charisma = j.at("charisma");
	c->intelligence = j.at("intelligence");
	c->arcane = j.at("arcane");
	c->faith = j.at("faith");
	c->luck = j.at("luck");

	// Weight & combat mechanics
	c->weightBurden = j.at("weightBurden");
	c->maxWeightBurden = j.at("maxWeightBurden");
	c->castSpeed = j.at("castSpeed");

	// Progression
	c->experience = j.at("experience");
	c->experienceToNextLevel = j.at("experienceToNextLevel");
	c->gold = j.at("gold");

	// Inventory
	c->inventory.fromJson(j["inventory"]);

	// Known and attuned spells
	for (const auto& spell : j["attunedSpells"]) {
		auto s = std::dynamic_pointer_cast<Spell>(Effect::fromJson(spell));
		if (s) c->attunedSpells.push_back(s);
	}

	for (const auto& spell : j["knownSpells"]) {
		auto s = std::dynamic_pointer_cast<Spell>(Effect::fromJson(spell));
		if (s) c->knownSpells.push_back(s);
	}

	// Allies
	for (const auto& ally : j["allies"]) {
		c->allies.push_back(Character::fromJson(ally));
	}

	// Tags
	for (const auto& tag : j["tags"]) {
		c->tags.push_back(std::make_shared<std::string>(tag.get<std::string>()));
	}

	// Combat flags
	for (const auto& flag : j["combatFlags"]) {
		c->combatFlags.push_back(static_cast<CombatFlags>(flag.get<int>()));
	}

	// Active effects
	for (const auto& eff : j["effects"]) {
		c->effects.push_back(Effect::fromJson(eff));
	}

	// Resistances
	c->defenseValues = j.at("defenseValues");

	return c;
}
void Human::setInitialHumanStats() {

	//Get all equipped items
	std::shared_ptr<Weapon> mainHand,  offHand, reserve1, reserve2;
	std::shared_ptr<Armor> head, chest, legs, arms;
	std::shared_ptr<Trinket> amulet, ring1, ring2, misc;
	inventory.getEquippedItems(mainHand, offHand, reserve1, reserve2, head, chest, legs, arms, amulet, ring1, ring2, misc);

	float backPackWeight = 0;
	for (std::shared_ptr<Item> item : inventory.backpackItems)
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

	double baseXP = 100;
	experienceToNextLevel = baseXP * (std::pow(1.15, static_cast<double>(level)));

	//Max health calculation
	maxHealthPoints = (health * 10) + (strength * 2) + (fatigue / 3) + (agility / 3) + (charisma / 3) + (intelligence / 3) +
		(arcane / 3) + (faith / 3) + (luck / 3);
	healthPoints = maxHealthPoints;

	//Max Fatigue calculation
	maxFatiguePoints = (fatigue * 10) + (arcane * 2) + (intelligence * 2) + (faith * 2);
	fatiguePoints = maxFatiguePoints;

	//Status Resistances Calculation: ------------------------------------------------------------------- TO DO
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
std::shared_ptr<Human> Human::setCharacterClass(Human::CharacterClass classChoice)
{
	switch (classChoice)
	{
	case Human::WIZARD:
	{
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
		std::shared_ptr<Human> human = std::make_shared<Human>();
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
void Human::takeDamage(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target, std::shared_ptr<Weapon> weapon, std::shared_ptr<Ammunition> ammunition, 
	std::shared_ptr<ThrownConsumable> consumable, Spell* spell, std::optional<std::vector<std::shared_ptr<Character>>>& allies, 
	std::optional<std::vector<std::shared_ptr<Character>>>& enemyAllies)
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
	//if (std::shared_ptr<Human> humanAttacker = dynamic_cast<std::shared_ptr<Human>>(attacker))
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
	//			for (std::shared_ptr<Effect> effect : spell->effects)
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
	//			for (std::shared_ptr<Effect> effect : spell->effects)
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