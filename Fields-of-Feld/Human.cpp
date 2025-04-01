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
#include "HelperFunctions.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include "Food.h"
#include "Drink.h"
#include "IDManager.h"

Human::Human(bool isPlayer, bool isAlly, std::string classChoice, Personality personality, float health, float fatigue, float strength, float agility, float charisma,
	float intelligence, float arcane, float faith, float luck, float weightBurden, float maxWeightBurden, float castSpeed,
	double experience, double experienceToNextLevel,
	int gold)
	: Character(isAlly, namedCharacter, isAlive, active, alert, name, description, confidenceLevel, healthPoints, maxHealthPoints, fatiguePoints, maxFatiguePoints, speed,
		critChance, dodgeChance, blockChance, bleedPoints, maxBleedPoints, burnPoints, maxBurnPoints, poisonPoints, maxPoisonPoints, frostPoints, maxFrostPoints, shockPoints,
		maxShockPoints, sleepPoints, maxSleepPoints, inventory, level, combatFlag),
	isPlayer(isPlayer), classChoice(classChoice), health(health), fatigue(fatigue),
	strength(strength), agility(agility), charisma(charisma), intelligence(intelligence), 
	arcane(arcane), faith(faith), luck(luck), weightBurden(weightBurden), maxWeightBurden(maxWeightBurden), 
	castSpeed(castSpeed), experience(experience), experienceToNextLevel(experienceToNextLevel),
	gold(gold), id(IDManager::getNextId())
{
	setInitialHumanStats();
}



Human::Human()
	: Character()
{
	id = IDManager::getNextId();
}
nlohmann::json Human::toJson() const {
	nlohmann::json j;

	// Identity & classification
	j["type"] = "Human";
	j["id"] = id;
	j["isPlayer"] = isPlayer;
	j["isAlive"] = isAlive;
	j["alert"] = alert;
	j["isAlly"] = isAlly;
	j["classChoice"] = (classChoice);
	j["personality"] = personalityToString(personality);
	j["name"] = name;
	j["description"] = description;


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
	j["weightBurden"] = weightBurden;
	j["maxWeightBurden"] = maxWeightBurden;
	j["castSpeed"] = castSpeed;

	// Status Values
	j["bleedPoints"] = bleedPoints;
	j["maxBleedPoints"] = maxBleedPoints;
	j["burnPoints"] = burnPoints;
	j["maxBurnPoints"] = maxBurnPoints;
	j["poisonPoints"] = poisonPoints;
	j["maxPoisonPoints"] = maxPoisonPoints;
	j["frostPoints"] = frostPoints;
	j["maxFrostPoints"] = maxFrostPoints;
	j["shockPoints"] = shockPoints;
	j["maxShockPoints"] = maxShockPoints;
	j["sleepPoints"] = sleepPoints;
	j["maxSleepPoints"] = maxSleepPoints;

	// Progression
	j["experience"] = experience;
	j["experienceToNextLevel"] = experienceToNextLevel;
	j["level"] = level;
	j["gold"] = gold;

	// Combat values
	j["confidenceLevel"] = confidenceLevel;
	j["fatiguePoints"] = fatiguePoints;
	j["maxFatiguePoints"] = maxFatiguePoints;
	j["healthPoints"] = healthPoints;
	j["maxHealthPoints"] = maxHealthPoints;
	j["critChance"] = critChance;
	j["blockChance"] = blockChance;
	j["dodgeChance"] = dodgeChance;
	j["namedCharacter"] = namedCharacter;
	j["isAlive"] = isAlive;
	j["active"] = active;
	j["alert"] = alert;
	j["speed"] = speed;

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
		j["tags"].push_back(*tag);

	// Combat Flags
	for (const auto& flag : combatFlags)
		j["combatFlags"].push_back(combatFlagToString(flag));

	// Effects
	for (const auto& eff : effects)
		j["effects"].push_back(eff->toJson());

	// Resistances / defenses
	nlohmann::json defenseJson;
	for (const auto& [key, value] : defenseValues) {
		defenseJson[defenseToString(key)] = value;
	}
	j["defenseValues"] = defenseJson;

	// Position map
	j["position"] = positionToJson(position);

	return j;
}

std::shared_ptr<Character> Human::fromJson(const nlohmann::json& j) {
	auto c = std::make_shared<Human>();

	try {
		// Identity & classification
		if (j.contains("id")) c->id = j["id"];
		if (j.contains("isPlayer")) c->isPlayer = j["isPlayer"];
		if (j.contains("isAlive")) c->isAlive = j["isAlive"];
		if (j.contains("isAlly")) c->isAlly = j["isAlly"];
		if (j.contains("alert")) c->alert = j["alert"];
		if (j.contains("name")) c->name = j["name"];
		if (j.contains("description")) c->description = j["description"];
		if (j.contains("classChoice")) c->classChoice = (j["classChoice"]);
		if (j.contains("personality")) c->personality = stringToPersonality(j["personality"]);

		// Core stats
		if (j.contains("health")) c->health = j["health"];
		if (j.contains("fatigue")) c->fatigue = j["fatigue"];
		if (j.contains("strength")) c->strength = j["strength"];
		if (j.contains("agility")) c->agility = j["agility"];
		if (j.contains("charisma")) c->charisma = j["charisma"];
		if (j.contains("intelligence")) c->intelligence = j["intelligence"];
		if (j.contains("arcane")) c->arcane = j["arcane"];
		if (j.contains("faith")) c->faith = j["faith"];
		if (j.contains("luck")) c->luck = j["luck"];
		if (j.contains("weightBurden")) c->weightBurden = j["weightBurden"];
		if (j.contains("maxWeightBurden")) c->maxWeightBurden = j["maxWeightBurden"];
		if (j.contains("castSpeed")) c->castSpeed = j["castSpeed"];

		// Status values
		if (j.contains("bleedPoints")) c->bleedPoints = j["bleedPoints"];
		if (j.contains("maxBleedPoints")) c->maxBleedPoints = j["maxBleedPoints"];
		if (j.contains("burnPoints")) c->burnPoints = j["burnPoints"];
		if (j.contains("maxBurnPoints")) c->maxBurnPoints = j["maxBurnPoints"];
		if (j.contains("poisonPoints")) c->poisonPoints = j["poisonPoints"];
		if (j.contains("maxPoisonPoints")) c->maxPoisonPoints = j["maxPoisonPoints"];
		if (j.contains("frostPoints")) c->frostPoints = j["frostPoints"];
		if (j.contains("maxFrostPoints")) c->maxFrostPoints = j["maxFrostPoints"];
		if (j.contains("shockPoints")) c->shockPoints = j["shockPoints"];
		if (j.contains("maxShockPoints")) c->maxShockPoints = j["maxShockPoints"];
		if (j.contains("sleepPoints")) c->sleepPoints = j["sleepPoints"];
		if (j.contains("maxSleepPoints")) c->maxSleepPoints = j["maxSleepPoints"];

		// Progression
		if (j.contains("experience")) c->experience = j["experience"];
		if (j.contains("experienceToNextLevel")) c->experienceToNextLevel = j["experienceToNextLevel"];
		if (j.contains("level")) c->level = j["level"];
		if (j.contains("gold")) c->gold = j["gold"];

		// Combat values
		if (j.contains("confidenceLevel")) c->confidenceLevel = j["confidenceLevel"];
		if (j.contains("fatiguePoints")) c->fatiguePoints = j["fatiguePoints"];
		if (j.contains("maxFatiguePoints")) c->maxFatiguePoints = j["maxFatiguePoints"];
		if (j.contains("healthPoints")) c->healthPoints = j["healthPoints"];
		if (j.contains("maxHealthPoints")) c->maxHealthPoints = j["maxHealthPoints"];
		if (j.contains("critChance")) c->critChance = j["critChance"];
		if (j.contains("blockChance")) c->blockChance = j["blockChance"];
		if (j.contains("dodgeChance")) c->dodgeChance = j["dodgeChance"];
		if (j.contains("namedCharacter")) c->namedCharacter = j["namedCharacter"];
		if (j.contains("active")) c->active = j["active"];
		if (j.contains("speed")) c->speed = j["speed"];

		// Inventory
		if (j.contains("inventory")) {
			c->inventory.fromJson(j["inventory"]);
		}

		// Spells
		if (j.contains("attunedSpells")) {
			for (const auto& spell : j["attunedSpells"]) {
				auto s = Spell::fromJson(spell);
				if (s) c->attunedSpells.push_back(s);
			}
		}
		if (j.contains("knownSpells")) {
			for (const auto& spell : j["knownSpells"]) {
				auto s = Spell::fromJson(spell);
				if (s) c->knownSpells.push_back(s);
			}
		}

		// Allies
		if (j.contains("allies")) {
			for (const auto& ally : j["allies"]) {
				auto s = std::dynamic_pointer_cast<Character>(Character::fromJson(ally));
				if (s) c->allies.push_back(s);
			}
		}

		// Tags
		if (j.contains("tags")) {
			for (const auto& tag : j["tags"]) {
				c->tags.push_back(std::make_shared<std::string>(tag.get<std::string>()));
			}
		}

		// Combat flags
		if (j.contains("combatFlags")) {
			for (const auto& flag : j["combatFlags"]) {
				c->combatFlags.push_back(stringToCombatFlag(flag.get<std::string>()));
			}
		}

		// Effects
		if (j.contains("effects")) {
			for (const auto& eff : j["effects"]) {
				c->effects.push_back(Effect::fromJson(eff));
			}
		}

		// Resistances
		if (j.contains("defenseValues")) {
			for (const auto& [key, value] : j["defenseValues"].items()) {
				c->defenseValues[stringToDefense(key)] = value.get<float>();
			}
		}

		// Position
		if (j.contains("position")) {
			c->position = positionFromJson(j["position"]);
		}
	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "[ERROR] Failed to load Human from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return c;
}

void Human::printHumanStats()
{
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Name: ") << this->name << std::endl;
	std::cout << dye::light_yellow(" Class: ") << classChoice << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Health Points: ") << healthPoints << " / " << maxHealthPoints << std::endl;
	std::cout << dye::light_yellow(" Fatigue Points: ") << fatiguePoints << " / " << maxFatiguePoints << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Bleed Points: ") << bleedPoints << " / " << maxBleedPoints << std::endl;
	std::cout << dye::light_yellow(" Burn Points: ") << burnPoints << " / " << maxBurnPoints << std::endl;
	std::cout << dye::light_yellow(" Poison Points: ") << poisonPoints << " / " << maxPoisonPoints << std::endl;
	std::cout << dye::light_yellow(" Frost Points: ") << frostPoints << " / " << maxFrostPoints << std::endl;
	std::cout << dye::light_yellow(" Shock Points: ") << shockPoints << " / " << maxShockPoints << std::endl;
	std::cout << dye::light_yellow(" Sleep Points: ") << sleepPoints << " / " << maxSleepPoints << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Health: ") << health << std::endl;
	std::cout << dye::light_yellow(" Fatigue: ") << fatigue << std::endl;
	std::cout << dye::light_yellow(" Strength: ") << strength << std::endl;
	std::cout << dye::light_yellow(" Agility: ") << agility << std::endl;
	std::cout << dye::light_yellow(" Charisma: ") << charisma << std::endl;
	std::cout << dye::light_yellow(" Intelligence: ") << intelligence << std::endl;
	std::cout << dye::light_yellow(" Arcane: ") << arcane << std::endl;
	std::cout << dye::light_yellow(" Faith: ") << faith << std::endl;
	std::cout << dye::light_yellow(" Luck: ") << luck << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Weight: ") << weightBurden << " / " << maxWeightBurden << std::endl;
	std::cout << dye::light_yellow(" Cast Speed: ") << castSpeed << std::endl;
	std::cout << "=---->" << std::endl;
	std::cout << dye::light_yellow(" Experience: ") << experience << " / " << experienceToNextLevel << std::endl;
	std::cout << dye::light_yellow(" Gold: ") << gold << std::endl;
}

void Human::printAttunedSpells()
{
	std::cout << dye::light_yellow(" Attuned Spells: ") << std::endl;
	for (const auto& spell : attunedSpells)
	{
		std::cout << "=---->" << std::endl;
		std::cout << dye::light_yellow(" Name: ") << spell->name << std::endl;
		std::cout << dye::light_yellow(" Description: ") << spell->description << std::endl;
		std::cout << dye::light_yellow(" Fatiuge Cost") << spell->fatigueCost << std::endl;
		std::unordered_map<std::string, int> requirements = spell->getStatRequirements();
		std::cout << "=---->" << std::endl;
		std::cout << dye::light_yellow(" Stat Requirements: ") << std::endl;
		for (const auto& [key, value] : requirements)
		{
			std::cout << dye::light_yellow(" Stat: ") << key << " Requires: " << value << std::endl;
		}
		std::cout << dye::light_yellow(" Scaling: ") << std::endl;
		std::cout << dye::light_yellow(" Intelligence: ") << spell->getScalingGrade(spell->intelligenceScaling) << std::endl;
		std::cout << dye::light_yellow(" Faith: ") << spell->getScalingGrade(spell->faithScaling) << std::endl;
		std::cout << dye::light_yellow(" Arcane: ") << spell->getScalingGrade(spell->arcaneScaling) << std::endl;
		std::cout << dye::light_yellow(" Luck: ") << spell->getScalingGrade(spell->luckScaling) << std::endl;
		std::cout << dye::light_yellow(" Charisma: ") << spell->getScalingGrade(spell->charismaScaling) << std::endl;
	}
}
std::shared_ptr<Human> Human::setCharacterClass(std::vector<std::shared_ptr<Item>> allItems, std::vector<std::shared_ptr<Spell>> allSpells)
{
	//Create vector of character classes
	std::vector<std::shared_ptr<Human>> classes;
	std::unordered_map<std::string, std::string> classDescriptions;

	//Grab the various item types from the main vector
	std::vector<std::shared_ptr<Weapon>> weapons;
	std::vector<std::shared_ptr<Armor>> armors;
	std::vector<std::shared_ptr<Trinket>> trinkets;
	std::vector<std::shared_ptr<Potion>> potions;
	std::vector<std::shared_ptr<Food>> foods;
	std::vector<std::shared_ptr<Drink>> drinks;
	std::vector<std::shared_ptr<Spell>> spells;
	std::vector<std::shared_ptr<Ammunition>> ammunition;
	for (const auto& item : allItems)
	{
		if (auto weapon = std::dynamic_pointer_cast<Weapon>(item))
		{
			weapons.push_back(weapon);
		}
		if (auto armor = std::dynamic_pointer_cast<Armor>(item))
		{
			armors.push_back(armor);
		}
		if (auto ammo = std::dynamic_pointer_cast<Ammunition>(item))
		{
			ammunition.push_back(ammo);
		}
		if (auto trinket = std::dynamic_pointer_cast<Trinket>(item))
		{
			trinkets.push_back(trinket);
		}
		if (auto potion = std::dynamic_pointer_cast<Potion>(item))
		{
			potions.push_back(potion);
		}
		if (auto food = std::dynamic_pointer_cast<Food>(item))
		{
			foods.push_back(food);
		}
		if (auto drink = std::dynamic_pointer_cast<Drink>(item))
		{
			drinks.push_back(drink);
		}
	}
	for (const auto& spell : allSpells)
	{
		spells.push_back(spell);
	}

	////SORCERER
	//std::shared_ptr<Human> sorcerer;
	//sorcerer->health = 10.0f;
	//sorcerer->fatigue = 10.0f;
	//sorcerer->strength = 10.0f;
	//sorcerer->agility = 10.0f;
	//sorcerer->charisma = 10.0f;
	//sorcerer->intelligence = 10.0f;
	//sorcerer->arcane = 10.0f;
	//sorcerer->faith = 10.0f;
	//sorcerer->luck = 10.0f;

	//classes.push_back(sorcerer);

	////NECROMANCER
	//std::shared_ptr<Human> necromancer;
	//necromancer->health = 10.0f;
	//necromancer->fatigue = 10.0f;
	//necromancer->strength = 10.0f;
	//necromancer->agility = 10.0f;
	//necromancer->charisma = 10.0f;
	//necromancer->intelligence = 10.0f;
	//necromancer->arcane = 10.0f;
	//necromancer->faith = 10.0f;
	//necromancer->luck = 10.0f;

	//classes.push_back(necromancer);

	//GEOMANCER
	std::shared_ptr<Human> geomancer = std::make_shared<Human>();
	geomancer->health = 16.0f;
	geomancer->fatigue = 20.0f;
	geomancer->strength = 8.0f;
	geomancer->agility = 6.0f;
	geomancer->charisma = 8.0f;
	geomancer->intelligence = 10.0f;
	geomancer->arcane = 35.0f;
	geomancer->faith = 7.0f;
	geomancer->luck = 10.0f;
	geomancer->classChoice = "Geomancer";
	geomancer->level = 10;

	//Get the starting gear
	for (auto weapon : weapons)
	{
		if (weapon->name == "Iron Hatchet")
		{
			weapon->slot = Weapon::EquipSlots::MAINHAND;
			geomancer->inventory.equippedItems.push_back(weapon);
		}
		if (weapon->name == "Wooden Staff")
		{
			weapon->slot = Weapon::EquipSlots::OFFHAND;
			geomancer->inventory.equippedItems.push_back(weapon);
		}
	}
	for (auto armor : armors)
	{
		if (armor->name == "Leather Vest")
		{
			armor->slot = Armor::EquipSlots::CHEST;
			geomancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Leather Gloves")
		{
			armor->slot = Armor::EquipSlots::ARMS;
			geomancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Leather Boots")
		{
			armor->slot = Armor::EquipSlots::LEGS;
			geomancer->inventory.equippedItems.push_back(armor);
		}
	}
	for (auto food : foods)
	{
		if (food->name == "Baked Potato")
		{
			food->quantity = 3;
			geomancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Apple")
		{
			food->quantity = 2;
			geomancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Deer Jerky")
		{
			food->quantity = 3;
			geomancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Handfull of Nuts")
		{
			food->quantity = 4;
			geomancer->inventory.backpackItems.push_back(food);
		}
	}
	for (auto drink : drinks)
	{
		if (drink->name == "Water Flask")
		{
			drink->quantity = 3;
			geomancer->inventory.backpackItems.push_back(drink);
		}
	}
	for (auto potion : potions)
	{
		if (potion->name == "Minor Healing Potion")
		{
			potion->quantity = 5;
			geomancer->inventory.backpackItems.push_back(potion);
		}
	}
	geomancer->setInitialHumanStats();
	classes.push_back(geomancer);

	////CRYOMANCER
	//std::shared_ptr<Human> cryomancer;
	//cryomancer->health = 10.0f;
	//cryomancer->fatigue = 10.0f;
	//cryomancer->strength = 10.0f;
	//cryomancer->agility = 10.0f;
	//cryomancer->charisma = 10.0f;
	//cryomancer->intelligence = 10.0f;
	//cryomancer->arcane = 10.0f;
	//cryomancer->faith = 10.0f;
	//cryomancer->luck = 10.0f;

	//classes.push_back(cryomancer);

	////BARD
	//std::shared_ptr<Human> bard;
	//bard->health = 10.0f;
	//bard->fatigue = 10.0f;
	//bard->strength = 10.0f;
	//bard->agility = 10.0f;
	//bard->charisma = 10.0f;
	//bard->intelligence = 10.0f;
	//bard->arcane = 10.0f;
	//bard->faith = 10.0f;
	//bard->luck = 10.0f;

	/*classes.push_back(bard);*/

	//CLERIC
	std::shared_ptr<Human> cleric = std::make_shared<Human>();;
	cleric->health = 16.0f;
	cleric->fatigue = 20.0f;
	cleric->strength = 12.0f;
	cleric->agility = 5.0f;
	cleric->charisma = 14.0f;
	cleric->intelligence = 8.0f;
	cleric->arcane = 2.0f;
	cleric->faith = 30.0f;
	cleric->luck = 10.0f;
	cleric->classChoice = "Cleric";
	cleric->level = 10;

	//Get the starting gear
	for (auto weapon : weapons)
	{
		if (weapon->name == "Iron Morningstar")
		{
			weapon->slot = Weapon::EquipSlots::MAINHAND;
			cleric->inventory.equippedItems.push_back(weapon);
		}
		if (weapon->name == "Wooden Wand")
		{
			weapon->slot = Weapon::EquipSlots::OFFHAND;
			cleric->inventory.equippedItems.push_back(weapon);
		}
	}
	for (auto armor : armors)
	{
		if (armor->name == "Cleric's Aventail")
		{
			armor->slot = Armor::EquipSlots::HEAD;
			cleric->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Cleric's Cloak")
		{
			armor->slot = Armor::EquipSlots::CHEST;
			cleric->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Cleric's Gauntlets")
		{
			armor->slot = Armor::EquipSlots::ARMS;
			cleric->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Cleric's Leggings")
		{
			armor->slot = Armor::EquipSlots::LEGS;
			cleric->inventory.equippedItems.push_back(armor);
		}
	}
	for (auto food : foods)
	{
		if (food->name == "Bread Loaf")
		{
			food->quantity = 3;
			cleric->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Wedge of Cheese")
		{
			food->quantity = 3;
			cleric->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Bundle of Spinach")
		{
			food->quantity = 3;
			cleric->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Raw Garlic")
		{
			food->quantity = 1;
			cleric->inventory.backpackItems.push_back(food);
		}
	}
	for (auto drink : drinks)
	{
		if (drink->name == "Water Flask")
		{
			drink->quantity = 3;
			cleric->inventory.backpackItems.push_back(drink);
		}
	}
	for (auto potion : potions)
	{
		if (potion->name == "Minor Healing Potion")
		{
			potion->quantity = 5;
			cleric->inventory.backpackItems.push_back(potion);
		}
	}

	cleric->setInitialHumanStats();
	classes.push_back(cleric);

	//PYROMANCER
	std::shared_ptr<Human> pyromancer = std::make_shared<Human>();;
	pyromancer->health = 15.0f;
	pyromancer->fatigue = 20.0f;
	pyromancer->strength = 7.0f;
	pyromancer->agility = 14.0f;
	pyromancer->charisma = 12.0f;
	pyromancer->intelligence = 8.0f;
	pyromancer->arcane = 7.0f;
	pyromancer->faith = 25.0f;
	pyromancer->luck = 10.0f;
	pyromancer->classChoice = "Pyromancer";
	pyromancer->level = 10;

	//Get the starting gear
	for (auto weapon : weapons)
	{
		if (weapon->name == "Wooden Wand")
		{
			weapon->slot = Weapon::EquipSlots::MAINHAND;
			pyromancer->inventory.equippedItems.push_back(weapon);
		}
		if (weapon->name == "Faded Cloth Talisman")
		{
			weapon->slot = Weapon::EquipSlots::OFFHAND;
			pyromancer->inventory.equippedItems.push_back(weapon);
		}
	}
	for (auto armor : armors)
	{
		if (armor->name == "Traveler's Hood")
		{
			armor->slot = Armor::EquipSlots::HEAD;
			pyromancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Traveler's Cloak")
		{
			armor->slot = Armor::EquipSlots::CHEST;
			pyromancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Leather Gloves")
		{
			armor->slot = Armor::EquipSlots::ARMS;
			pyromancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Leather Boots")
		{
			armor->slot = Armor::EquipSlots::LEGS;
			pyromancer->inventory.equippedItems.push_back(armor);
		}
	}
	for (auto food : foods)
	{
		if (food->name == "Bread Loaf")
		{
			food->quantity = 3;
			pyromancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Wedge of Cheese")
		{
			food->quantity = 3;
			pyromancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Bundle of Turnips")
		{
			food->quantity = 3;
			pyromancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Orange")
		{
			food->quantity = 2;
			pyromancer->inventory.backpackItems.push_back(food);
		}
	}
	for (auto drink : drinks)
	{
		if (drink->name == "Water Flask")
		{
			drink->quantity = 3;
			pyromancer->inventory.backpackItems.push_back(drink);
		}
	}
	for (auto potion : potions)
	{
		if (potion->name == "Minor Healing Potion")
		{
			potion->quantity = 5;
			pyromancer->inventory.backpackItems.push_back(potion);
		}
	}

	pyromancer->setInitialHumanStats();
	classes.push_back(pyromancer);

	////AEROMANCER
	//std::shared_ptr<Human> aeromancer;
	//aeromancer->health = 10.0f;
	//aeromancer->fatigue = 10.0f;
	//aeromancer->strength = 10.0f;
	//aeromancer->agility = 10.0f;
	//aeromancer->charisma = 10.0f;
	//aeromancer->intelligence = 10.0f;
	//aeromancer->arcane = 10.0f;
	//aeromancer->faith = 10.0f;
	//aeromancer->luck = 10.0f;

	//classes.push_back(aeromancer);

	//FULGURAMANCER
	std::shared_ptr<Human> fulguramancer = std::make_shared<Human>();;
	fulguramancer->health = 15.0f;
	fulguramancer->fatigue = 20.0f;
	fulguramancer->strength = 7.0f;
	fulguramancer->agility = 14.0f;
	fulguramancer->charisma = 9.0f;
	fulguramancer->intelligence = 25.0f;
	fulguramancer->arcane = 7.0f;
	fulguramancer->faith = 10.0f;
	fulguramancer->luck = 10.0f;
	fulguramancer->classChoice = "Fulguramancer";
	fulguramancer->level = 10;

	//Get the starting gear
	for (auto weapon : weapons)
	{
		if (weapon->name == "Iron Estoc")
		{
			weapon->slot = Weapon::EquipSlots::MAINHAND;
			fulguramancer->inventory.equippedItems.push_back(weapon);
		}
		if (weapon->name == "Wooden Staff")
		{
			weapon->slot = Weapon::EquipSlots::OFFHAND;
			fulguramancer->inventory.equippedItems.push_back(weapon);
		}
	}
	for (auto armor : armors)
	{
		if (armor->name == "Traveler's Hood")
		{
			armor->slot = Armor::EquipSlots::HEAD;
			fulguramancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Traveler's Cloak")
		{
			armor->slot = Armor::EquipSlots::CHEST;
			fulguramancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Leather Gloves")
		{
			armor->slot = Armor::EquipSlots::ARMS;
			fulguramancer->inventory.equippedItems.push_back(armor);
		}
		if (armor->name == "Leather Boots")
		{
			armor->slot = Armor::EquipSlots::LEGS;
			fulguramancer->inventory.equippedItems.push_back(armor);
		}
	}
	for (auto food : foods)
	{
		if (food->name == "Bread Loaf")
		{
			food->quantity = 3;
			fulguramancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Wedge of Cheese")
		{
			food->quantity = 3;
			fulguramancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Bundle of Leeks")
		{
			food->quantity = 3;
			fulguramancer->inventory.backpackItems.push_back(food);
		}
		if (food->name == "Apple")
		{
			food->quantity = 2;
			fulguramancer->inventory.backpackItems.push_back(food);
		}
	}
	for (auto drink : drinks)
	{
		if (drink->name == "Water Flask")
		{
			drink->quantity = 3;
			fulguramancer->inventory.backpackItems.push_back(drink);
		}
	}
	for (auto potion : potions)
	{
		if (potion->name == "Minor Healing Potion")
		{
			potion->quantity = 5;
			fulguramancer->inventory.backpackItems.push_back(potion);
		}
	}

	fulguramancer->setInitialHumanStats();
	classes.push_back(fulguramancer);

	////VENOMANCER
	//std::shared_ptr<Human> venomancer;
	//venomancer->health = 10.0f;
	//venomancer->fatigue = 10.0f;
	//venomancer->strength = 10.0f;
	//venomancer->agility = 10.0f;
	//venomancer->charisma = 10.0f;
	//venomancer->intelligence = 10.0f;
	//venomancer->arcane = 10.0f;
	//venomancer->faith = 10.0f;
	//venomancer->luck = 10.0f;

	//classes.push_back(venomancer);

	////DORMIMANCER
	//std::shared_ptr<Human> dormimancer;
	//dormimancer->health = 10.0f;
	//dormimancer->fatigue = 10.0f;
	//dormimancer->strength = 10.0f;
	//dormimancer->agility = 10.0f;
	//dormimancer->charisma = 10.0f;
	//dormimancer->intelligence = 10.0f;
	//dormimancer->arcane = 10.0f;
	//dormimancer->faith = 10.0f;
	//dormimancer->luck = 10.0f;

	//classes.push_back(dormimancer);

	////BANDIT
	//std::shared_ptr<Human> bandit;
	//bandit->health = 10.0f;
	//bandit->fatigue = 10.0f;
	//bandit->strength = 10.0f;
	//bandit->agility = 10.0f;
	//bandit->charisma = 10.0f;
	//bandit->intelligence = 10.0f;
	//bandit->arcane = 10.0f;
	//bandit->faith = 10.0f;
	//bandit->luck = 10.0f;

	//classes.push_back(bandit);

	//KNIGHT
	std::shared_ptr<Human> knight = std::make_shared<Human>();;
	knight->health = 20.0f;
	knight->fatigue = 15.0f;
	knight->strength = 18.0f;
	knight->agility = 18.0f;
	knight->charisma = 14.0f;
	knight->intelligence = 8.0f;
	knight->arcane = 4.0f;
	knight->faith = 10.0f;
	knight->luck = 10.0f;
	knight->classChoice = "Knight";
	knight->level = 10;

	//Get the starting gear
	for (auto weapon : weapons)
	{
		if (weapon->name == "Iron Longsword")
		{
			weapon->slot = Weapon::EquipSlots::MAINHAND;
			knight->inventory.equippedItems.push_back(weapon);
		}
		if (weapon->name == "Wooden Towershield")
		{
			weapon->slot = Weapon::EquipSlots::OFFHAND;
			knight->inventory.equippedItems.push_back(weapon);
		}
		if (weapon->name == "Wooden Crossbow")
		{
			weapon->slot = Weapon::EquipSlots::RESERVE1;
			knight->inventory.equippedItems.push_back(weapon);
		}
	}
	for (auto ammo : ammunition)
	{
		if (ammo->name == "Iron Bolt")
		{
			ammo->quantity = 30;
			ammo->slot = Weapon::EquipSlots::QUIVER1;
			knight->inventory.backpackItems.push_back(ammo);
		}
		for (auto armor : armors)
		{
			if (armor->name == "Iron Knight's Helmet")
			{
				armor->slot = Armor::EquipSlots::HEAD;
				knight->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Iron Knight's Cuirass")
			{
				armor->slot = Armor::EquipSlots::CHEST;
				knight->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Iron Knight's Gauntlets")
			{
				armor->slot = Armor::EquipSlots::ARMS;
				knight->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Iron Knight's Greaves")
			{
				armor->slot = Armor::EquipSlots::LEGS;
				knight->inventory.equippedItems.push_back(armor);
			}
		}
		for (auto food : foods)
		{
			if (food->name == "Bread Loaf")
			{
				food->quantity = 3;
				knight->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Wedge of Cheese")
			{
				food->quantity = 3;
				knight->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Raw Garlic")
			{
				food->quantity = 3;
				knight->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Hard-Boiled Egg")
			{
				food->quantity = 3;
				knight->inventory.backpackItems.push_back(food);
			}
		}
		for (auto drink : drinks)
		{
			if (drink->name == "Water Flask")
			{
				drink->quantity = 3;
				knight->inventory.backpackItems.push_back(drink);
			}
		}
		for (auto potion : potions)
		{
			if (potion->name == "Minor Healing Potion")
			{
				potion->quantity = 5;
				knight->inventory.backpackItems.push_back(potion);
			}
		}

		knight->setInitialHumanStats();
		classes.push_back(knight);

		//HUNTER
		std::shared_ptr<Human> hunter = std::make_shared<Human>();;
		hunter->health = 20.0f;
		hunter->fatigue = 15.0f;
		hunter->strength = 14.0f;
		hunter->agility = 25.0f;
		hunter->charisma = 12.0f;
		hunter->intelligence = 8.0f;
		hunter->arcane = 8.0f;
		hunter->faith = 5.0f;
		hunter->luck = 10.0f;
		hunter->classChoice = "Hunter";
		hunter->level = 10;

		//Get the starting gear
		for (auto weapon : weapons)
		{
			if (weapon->name == "Hunting Bow")
			{
				weapon->slot = Weapon::EquipSlots::MAINHAND;
				hunter->inventory.equippedItems.push_back(weapon);
			}
			if (weapon->name == "Iron Dagger")
			{
				weapon->slot = Weapon::EquipSlots::RESERVE1;
				hunter->inventory.equippedItems.push_back(weapon);
			}
		}
		for (auto ammo : ammunition)
		{
			if (ammo->name == "Iron Arrow")
			{
				ammo->quantity = 30;
				ammo->slot = Weapon::EquipSlots::QUIVER1;
				hunter->inventory.backpackItems.push_back(ammo);
			}
		}
		for (auto armor : armors)
		{
			if (armor->name == "Leather Vest")
			{
				armor->slot = Armor::EquipSlots::CHEST;
				hunter->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Leather Gloves")
			{
				armor->slot = Armor::EquipSlots::ARMS;
				hunter->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Leather Boots")
			{
				armor->slot = Armor::EquipSlots::LEGS;
				hunter->inventory.equippedItems.push_back(armor);
			}
		}
		for (auto food : foods)
		{
			if (food->name == "Bread Loaf")
			{
				food->quantity = 3;
				hunter->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Deer Jerky")
			{
				food->quantity = 3;
				hunter->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Duck Leg")
			{
				food->quantity = 1;
				hunter->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Hard-Boiled Egg")
			{
				food->quantity = 3;
				hunter->inventory.backpackItems.push_back(food);
			}
		}
		for (auto drink : drinks)
		{
			if (drink->name == "Water Flask")
			{
				drink->quantity = 3;
				hunter->inventory.backpackItems.push_back(drink);
			}
		}
		for (auto potion : potions)
		{
			if (potion->name == "Minor Healing Potion")
			{
				potion->quantity = 5;
				hunter->inventory.backpackItems.push_back(potion);
			}
		}

		hunter->setInitialHumanStats();
		classes.push_back(hunter);

		////HIGHLANDER
		//std::shared_ptr<Human> highlander;
		//highlander->health = 10.0f;
		//highlander->fatigue = 10.0f;
		//highlander->strength = 10.0f;
		//highlander->agility = 10.0f;
		//highlander->charisma = 10.0f;
		//highlander->intelligence = 10.0f;
		//highlander->arcane = 10.0f;
		//highlander->faith = 10.0f;
		//highlander->luck = 10.0f;

		//classes.push_back(highlander);

		//BARBARIAN
		std::shared_ptr<Human> barbarian = std::make_shared<Human>();;
		barbarian->health = 30.0f;
		barbarian->fatigue = 15.0f;
		barbarian->strength = 25.0f;
		barbarian->agility = 10.0f;
		barbarian->charisma = 4.0f;
		barbarian->intelligence = 4.0f;
		barbarian->arcane = 9.0f;
		barbarian->faith = 10.0f;
		barbarian->luck = 10.0f;
		barbarian->classChoice = "Barbarian";
		barbarian->level = 10;

		for (auto weapon : weapons)
		{
			if (weapon->name == "Crude War Axe")
			{
				weapon->slot = Weapon::EquipSlots::MAINHAND;
				barbarian->inventory.equippedItems.push_back(weapon);
			}
			if (weapon->name == "Wooden Round Shield")
			{
				weapon->slot = Weapon::EquipSlots::OFFHAND;
				barbarian->inventory.equippedItems.push_back(weapon);
			}
		}
		for (auto armor : armors)
		{
			if (armor->name == "Leather Barbarian's Helmet")
			{
				armor->slot = Armor::EquipSlots::HEAD;
				barbarian->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Reinforced Bandolier")
			{
				armor->slot = Armor::EquipSlots::CHEST;
				barbarian->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Leather Barbarian's Bracers")
			{
				armor->slot = Armor::EquipSlots::ARMS;
				barbarian->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Leather Barbarian's Boots")
			{
				armor->slot = Armor::EquipSlots::LEGS;
				barbarian->inventory.equippedItems.push_back(armor);
			}
		}
		for (auto food : foods)
		{
			if (food->name == "Duck Leg")
			{
				food->quantity = 2;
				barbarian->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Chicken Leg")
			{
				food->quantity = 2;
				barbarian->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Beef Steak")
			{
				food->quantity = 1;
				barbarian->inventory.backpackItems.push_back(food);
			}
		}
		for (auto drink : drinks)
		{
			if (drink->name == "Cheap Beer")
			{
				drink->quantity = 3;
				barbarian->inventory.backpackItems.push_back(drink);
			}
		}
		for (auto potion : potions)
		{
			if (potion->name == "Minor Healing Potion")
			{
				potion->quantity = 5;
				barbarian->inventory.backpackItems.push_back(potion);
			}
		}

		barbarian->setInitialHumanStats();
		classes.push_back(barbarian);

		//SAMURAI
		std::shared_ptr<Human> samurai = std::make_shared<Human>();;
		samurai->health = 20.0f;
		samurai->fatigue = 16.0f;
		samurai->strength = 14.0f;
		samurai->agility = 25.0f;
		samurai->charisma = 12.0f;
		samurai->intelligence = 8.0f;
		samurai->arcane = 6.0f;
		samurai->faith = 6.0f;
		samurai->luck = 10.0f;
		samurai->classChoice = "Samurai";
		samurai->level = 10;

		for (auto weapon : weapons)
		{
			if (weapon->name == "Iron Odachi")
			{
				weapon->slot = Weapon::EquipSlots::MAINHAND;
				samurai->inventory.equippedItems.push_back(weapon);
			}
		}
		for (auto armor : armors)
		{
			if (armor->name == "Samurai's Iron Kabuto Helmet")
			{
				armor->slot = Armor::EquipSlots::HEAD;
				samurai->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Samurai's Iron Lamellar Armor")
			{
				armor->slot = Armor::EquipSlots::CHEST;
				samurai->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Samurai's Iron Scaled Gauntlets")
			{
				armor->slot = Armor::EquipSlots::ARMS;
				samurai->inventory.equippedItems.push_back(armor);
			}
			if (armor->name == "Samurai's Iron Greaves")
			{
				armor->slot = Armor::EquipSlots::LEGS;
				samurai->inventory.equippedItems.push_back(armor);
			}
		}
		for (auto food : foods)
		{
			if (food->name == "Duck Leg")
			{
				food->quantity = 1;
				samurai->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Rice Ball")
			{
				food->quantity = 4;
				samurai->inventory.backpackItems.push_back(food);
			}
			if (food->name == "Smoked Fish")
			{
				food->quantity = 2;
				samurai->inventory.backpackItems.push_back(food);
			}
		}
		for (auto drink : drinks)
		{
			if (drink->name == "Water Flask")
			{
				drink->quantity = 3;
				samurai->inventory.backpackItems.push_back(drink);
			}
		}
		for (auto potion : potions)
		{
			if (potion->name == "Minor Healing Potion")
			{
				potion->quantity = 5;
				samurai->inventory.backpackItems.push_back(potion);
			}
		}

		samurai->setInitialHumanStats();
		classes.push_back(samurai);

		//Display the classes:
		for (int i = 0; i < classes.size(); i++)
		{
			std::cout << "=--->" << std::endl;
			std::cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(classes[i]->classChoice + ": ") << std::endl;
			std::cout << "=--->" << std::endl;
			std::cout << " Health: " << classes[i]->health << std::endl;
			std::cout << " Fatigue: " << classes[i]->fatigue << std::endl;
			std::cout << " Strength: " << classes[i]->strength << std::endl;
			std::cout << " Agility: " << classes[i]->agility << std::endl;
			std::cout << " Charisma: " << classes[i]->charisma << std::endl;
			std::cout << " Intelligence: " << classes[i]->intelligence << std::endl;
			std::cout << " Arcane: " << classes[i]->arcane << std::endl;
			std::cout << " Faith: " << classes[i]->faith << std::endl;
			std::cout << " Luck: " << classes[i]->luck << std::endl;
			std::cout << "=--->" << std::endl;
			std::cout << " Speed: " << classes[i]->speed << std::endl;
			std::cout << " Crit Chance: " << classes[i]->critChance << std::endl;
			std::cout << " Dodge Chance: " << classes[i]->dodgeChance << std::endl;
			std::cout << " Block Chance: " << classes[i]->blockChance << std::endl;
			std::cout << " Weight Burden: " << classes[i]->weightBurden << "/" << classes[i]->maxWeightBurden << std::endl;
			std::cout << "=--->" << std::endl;
			std::cout << " Health Points: " << classes[i]->healthPoints << "/" << classes[i]->maxHealthPoints << std::endl;
			std::cout << " Fatigue Points: " << classes[i]->fatiguePoints << "/" << classes[i]->maxFatiguePoints << std::endl;
			std::cout << " Level: " << classes[i]->level << std::endl;
			std::cout << "=--->" << std::endl;
			for (const auto& spell : classes[i]->attunedSpells)
			{
				std::cout << " Attuned Spell: " << spell->name << std::endl;
			}
			if (classes[i]->attunedSpells.size() > 0) std::cout << "=--->" << std::endl;
			for (const auto& item : classes[i]->inventory.equippedItems)
			{
				std::cout << " Equipped Item: " << item->name << std::endl;
			}
		}
		std::cout << "=--->\n" << std::endl;
		std::cout << " Please choose a class: ";

		int choice = validateInput(1, classes.size());

		return(classes[choice - 1]);
	}
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
	maxHealthPoints = (health * 10) + (strength * 3) + (fatigue / 3) + (agility / 3) + (charisma / 3) + (intelligence / 3) +
		(arcane / 3) + (faith / 3) + (luck / 3);
	healthPoints = maxHealthPoints;

	//Max Fatigue calculation
	maxFatiguePoints = (fatigue * 10) + (arcane * 2) + (intelligence * 2) + (faith * 2);
	fatiguePoints = maxFatiguePoints;

	//Status Resistances Calculation: ------------------------------------------------------------------- TO DO
	//crit chance calculation
	critChance = luck * 0.5f + arcane * 0.25f + agility * 0.1f + strength * 0.1f;
	//Caps crit chance to 50
	critChance = std::min<float>(critChance, 50.0f);
	//weight burden calculation
	weightBurden = equipmentWeight + (backPackWeight / 3);

	//max weight burden calculation
	maxWeightBurden = (strength * 10) + (agility * 5) + (fatigue * 5);

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
	if (offHand) stability = max(offHand->stability, 0);
	blockChance = (strength * 0.25) + (speed / 100) + ( stability / 10);
	blockChance = 75 * (blockChance / (blockChance + 50));  // Soft cap at 75%
}

void Human::updateHumanStats() {

}

float Human::softCapMultiplier(float statValue) {
	if (statValue < 30) return statValue;             // Full scaling below 30
	if (statValue < 60) return 30 + (statValue - 30) * 0.75f;  // 75% scaling from 30-60
	return 52.5f + (statValue - 60) * 0.5f;           // 50% scaling beyond 60
}