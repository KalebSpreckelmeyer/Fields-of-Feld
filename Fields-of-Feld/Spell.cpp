#include "Spell.h"
#include "Human.h"
#include "Character.h"
#include "OffensiveEffect.h"
#include "DefensiveEffect.h"
#include "PassiveEffect.h"
#include "ConsumableEffect.h"
#include <algorithm>
#include <iostream>
#include "color.hpp"
#include "LootItem.h"
#include "Creature.h"

Spell::Spell(std::string name, std::string description, bool useOnAlly, bool useOnSelf, bool useOnEnemy, float intelligenceScaling, 
	float faithScaling, float arcaneScaline, float luckScaling, float charismaScaling, float fatigueCost, float attackSpeed, float range) :
	id(IDManager::getNextId()),
	name(name),
	description(description),
	useOnAlly(useOnAlly), 
	useOnSelf(useOnSelf), 
	useOnEnemy(useOnEnemy),
	intelligenceScaling(intelligenceScaling),
	faithScaling(faithScaling),
	arcaneScaling(arcaneScaline),
	luckScaling(luckScaling),
	charismaScaling(charismaScaling),
	fatigueCost(fatigueCost),
	attackSpeed(attackSpeed),
	range(range)
{

}

Spell::Spell() 
{
	id = IDManager::getNextId();
}
nlohmann::json Spell::toJson() const {
	nlohmann::json j = {
		{"type", "Spell"},
		{"id", id},
		{"name", name},
		{"description", description},
		{"range", range},
		{"useOnSelf", useOnSelf},
		{"useOnAlly", useOnAlly},
		{"useOnEnemy", useOnEnemy},
		{"fatigueCost", fatigueCost},
		{"arcaneScaling", arcaneScaling},
		{"intelligenceScaling", intelligenceScaling},
		{"faithScaling", faithScaling},
		{"charismaScaling", charismaScaling},
		{"luckScaling", luckScaling},
		{"attackSpeed", attackSpeed},
		{"effects", nlohmann::json::array()}
	};

	for (const auto& effect : effects) {
		j["effects"].push_back(effect->toJson());
	}

	return j;
}


std::shared_ptr<Spell> Spell::fromJson(const nlohmann::json& j) {
	auto spell = std::make_shared<Spell>();

	try {
		if (j.contains("id")) spell->id = j.at("id");
		if (j.contains("name")) spell->name = j.at("name");
		if (j.contains("description")) spell->description = j.at("description");
		if (j.contains("range")) spell->range = j.at("range");
		if (j.contains("useOnSelf")) spell->useOnSelf = j.at("useOnSelf");
		if (j.contains("useOnAlly")) spell->useOnAlly = j.at("useOnAlly");
		if (j.contains("useOnEnemy")) spell->useOnEnemy = j.at("useOnEnemy");
		if (j.contains("fatigueCost")) spell->fatigueCost = j.at("fatigueCost");
		if (j.contains("arcaneScaling")) spell->arcaneScaling = j.at("arcaneScaling");
		if (j.contains("intelligenceScaling")) spell->intelligenceScaling = j.at("intelligenceScaling");
		if (j.contains("faithScaling")) spell->faithScaling = j.at("faithScaling");
		if (j.contains("charismaScaling")) spell->charismaScaling = j.at("charismaScaling");
		if (j.contains("luckScaling")) spell->luckScaling = j.at("luckScaling");
		if (j.contains("attackSpeed")) spell->attackSpeed = j.at("attackSpeed");

		if (j.contains("effects") && j["effects"].is_array()) {
			for (const auto& eff : j["effects"]) {
				spell->effects.push_back(Effect::fromJson(eff));
			}
		}
	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "[ERROR] Failed to load Spell from JSON: " << e.what() << std::endl;
		return nullptr;
	}

	return spell;
}

void Spell::setStatRequirements(StatScaling stat, int value)
{
	statRequirements[stat] = value;
}

std::unordered_map<std::string, int> Spell::getStatRequirements()
{
	std::string statArray[] = { "None", "Strength", "Agility", "Charisma", "Intelligence", "Arcane", "Faith", "Luck" };
	std::unordered_map<std::string, int> statRequirementsStrings;
	for (const auto& [stat, value] : statRequirements)
	{
		statRequirementsStrings[statArray[static_cast<int>(stat)]] = value;
	}
	return statRequirementsStrings;
}
bool Spell::checkSpellRequirements(std::shared_ptr<Spell> spell, std::shared_ptr<Character> caster)
{
	bool hasRequirements = true;
	std::unordered_map<std::string, int> requirements;
	requirements = spell->getStatRequirements();
	for (auto& [stat, value] : requirements)
	{
		if (stat == "Strength" && value < caster->getStrength()) hasRequirements = false;
		if (stat == "Agility" && value < caster->getAgility()) hasRequirements = false;
		if (stat == "Intelligence" && value < caster->getIntelligence()) hasRequirements = false;
		if (stat == "Faith" && value < caster->getFaith()) hasRequirements = false;
		if (stat == "Luck" && value < caster->getLuck()) hasRequirements = false;
		if (stat == "Arcane" && value < caster->getArcane()) hasRequirements = false;
		if (stat == "Charisma" && value < caster->getCharisma()) hasRequirements = false;
	}
	return hasRequirements;
}


std::string Spell::getScalingGrade(float scalingValue)
{
	if (scalingValue >= 90) return "S";
	else if (scalingValue >= 75) return "A";
	else if (scalingValue >= 60) return "B";
	else if (scalingValue >= 45) return "C";
	else if (scalingValue >= 30) return "D";
	else return "F";
}
//SORCERIES
//NECROMANCY
std::shared_ptr<Spell> Spell::getBonetrousleEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	float arcaneBonus = caster.getArcane() * 1.5f;  
	float bonetrousleDamage = (arcaneBonus * (arcaneBonus / (arcaneBonus + 50))) * 3;
	float bonetrousleBleed = (arcaneBonus * (arcaneBonus / (arcaneBonus + 50))) * 3;

	std::shared_ptr<Spell> bonetrousle;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		bonetrousle = std::make_shared<Spell>("Bonetrousle I", "A flurry of sharpened bone fragments pelt the target",
			false, false, true, 0, 0, 100, 0, 0, 50, 70, 75);
		bonetrousle->effects.push_back(std::make_shared<BleedEffect>(1, bonetrousleBleed, false, 1, 1));
		bonetrousle->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::BLUNT, bonetrousleDamage * 0.8));
		bonetrousle->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::DARK, bonetrousleDamage * 0.2));


		return bonetrousle;
	}
	else if (statInvestment < 60)
	{
		bonetrousle = std::make_shared<Spell>("Bonetrousle II", "A flurry of sharpened bone pieces pelt the target", 
			false, false, true, 0, 0, 100, 0, 0, 60, 80, 75);
		bonetrousle->effects.push_back(std::make_shared<BleedEffect>(1, bonetrousleBleed, false, 1, 1));
		bonetrousle->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::BLUNT, bonetrousleDamage * 0.8));
		bonetrousle->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::DARK, bonetrousleDamage * 0.2));
		return bonetrousle;
	}
	else
	{
		bonetrousle = std::make_shared<Spell>("Bonetrousle III", "A flurry of sharpened bone chunks pelt the target", 
			false, false, true, 0, 0, 100, 0, 0, 70, 90, 75);
		bonetrousle->effects.push_back(std::make_shared<BleedEffect>(1, bonetrousleBleed, false, 1, 1));
		bonetrousle->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::BLUNT, bonetrousleDamage * 0.8));
		bonetrousle->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::DARK, bonetrousleDamage * 0.2));
		return bonetrousle;
	}
}
//GEOMANCY
std::shared_ptr<Spell> Spell::getSummonAnimalAllyEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	std::shared_ptr<Spell> animalAlly;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		Inventory inventory;
		inventory.addToBackpack(std::make_shared<LootItem>("Vulture Feather", "A feather from a vulture", 40, 0.1, 5));
		std::shared_ptr<Creature> vulture = std::make_shared<Creature>(false, true, true, true, true, "Vulture", "A large vulture", 100, 20, 100, 200, 200, 200, 5, 20, 0, 200, 200, 200, 2000, 200, 200, 200, 200, 200, 200, 200, 200, inventory, Character::CombatFlags::NEUTRAL);
		animalAlly = std::make_shared<Spell>("Summon Vulture", "A large vulture will come to your aid in combat!",
			false, true, false, 0, 0, 100, 0, 0, 100, 1, 0);
		animalAlly->effects.push_back(std::make_shared<Summon>(vulture, 10, 1, false, 1, 1));
		return animalAlly;
	}
	else if (statInvestment < 60)
	{
		Inventory inventory;
		inventory.addToBackpack(std::make_shared<LootItem>("Wolf Pelt", "A pelt from a wolf", 150.0f, 0.5f, 1.0f));
		std::shared_ptr<Creature> wolf = std::make_shared<Creature>(false, true, true, true, false, "Wolf", "A rugged wolf", 150, 20, 100, 300, 300, 250, 5, 20, 0, 200, 200, 200, 2000,
			200, 200, 200, 200, 200, 200, 200, 200, inventory, Character::CombatFlags::NEUTRAL);
		animalAlly = std::make_shared<Spell>("Summon Wolf", "A rugged wolf will come to your aid in combat!", 
			false, true, false, 0, 0, 100, 0, 0, 125, 1, 0);
		animalAlly->effects.push_back(std::make_shared<Summon>(wolf, 10, 1, false, 1, 1));
		return animalAlly;
	}
	else
	{
		Inventory inventory;
		inventory.addToBackpack(std::make_shared<LootItem>("Bear Pelt", "A pelt from a bear", 300.0f, 5.0f, 1.0f));
		std::shared_ptr<Creature> bear = std::make_shared<Creature>(false, true, true, true, false, "Bear", "A mountain bear", 250, 20, 100, 400, 400, 200, 5, 20, 0, 200, 200, 200, 2000,
			200, 200, 200, 200, 200, 200, 200, 200, inventory, Character::CombatFlags::NEUTRAL);
		animalAlly = std::make_shared<Spell>("Summon Bear", "A mountain bear will come to your aid in combat!",
			false, true, false, 0, 0, 100, 0, 0, 150, 1, 0);
		animalAlly->effects.push_back(std::make_shared<Summon>(bear, 10, 1, false, 1, 1));
		return animalAlly;
	}
}
std::shared_ptr<Spell> Spell::getOakenArmorEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	std::shared_ptr<Spell> oakArmor;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		oakArmor = std::make_shared<Spell>("Oaken Armor I", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			false, true, false, 0, 0, 100, 0, 0, 75, 1, 0);
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::BLUNT, 3, 75, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::CHOP, 3, 75, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::PIERCE, 3, 75, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::SLASH, 3, 75, false, 1, 1));
		return oakArmor;
	}
	else if (statInvestment < 60)
	{
		oakArmor = std::make_shared<Spell>("Oaken Armor II", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			false, true, false, 0, 0, 100, 0, 0, 100, 1, 0);
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::BLUNT, 3, 115, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::CHOP, 3, 115, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::PIERCE, 3, 115, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::SLASH, 3, 115, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<Healing>(3, 50, false, 1, 1));
		return oakArmor;
	}
	else
	{
		oakArmor = std::make_shared<Spell>("Oaken Armor III", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			false, true, false, 0, 0, 100, 0, 0, 125, 1, 0);
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::BLUNT, 3, 150, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::CHOP, 3, 150, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::PIERCE, 3, 150, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::SLASH, 3, 150, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<Healing>(3, 75, false, 1, 1));
		return oakArmor;
	}
}
std::shared_ptr<Spell> Spell::getFruitOfTheEarthEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	std::shared_ptr<Spell> fruit;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		fruit = std::make_shared<Spell>("Fruit of the Earth I", "Vegetation nearby grows a nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			false, true, false, 0, 0, 100, 0, 0, 50, 1, 0);
		fruit->effects.push_back(std::make_shared<Healing>(1, 100, false, 1, 1));
		fruit->effects.push_back(std::make_shared<FatigueRestore>(1, 50, false, 1, 1));
		return fruit;
	}
	else if (statInvestment < 60)
	{
		fruit = std::make_shared<Spell>("Fruit of the Earth II", "Vegetation nearby grows a highly nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			false, true, false, 0, 0, 100, 0, 0, 75, 1, 0);
		fruit->effects.push_back(std::make_shared<Healing>(1, 150, false, 1, 1));
		fruit->effects.push_back(std::make_shared<FatigueRestore>(1, 75, false, 1, 1));
		return fruit;
	}
	else
	{
		fruit = std::make_shared<Spell>("Fruit of the Earth III", "Vegetation nearby grows a unbelievably nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			false, true, false, 0, 0, 100, 0, 0, 100, 1, 0);
		fruit->effects.push_back(std::make_shared<Healing>(1, 200, false, 1, 1));
		fruit->effects.push_back(std::make_shared<FatigueRestore>(1, 100, false, 1, 1));
		return fruit;
	}
}
//CRYOMANCY
std::shared_ptr<Spell> Spell::getEndothermicGraspEffect(Character& caster)
{
	float statInvestment = caster.getIntelligence();

	std::shared_ptr<Spell> endothermicGrasp;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		endothermicGrasp = std::make_shared<Spell>("Endorthermic Nudge",
			"A chilling touch that applies frost burst and freezes weaker targets solid! Investment in intelligence causes the range of the spell to increase.",
			false, false, true, 100, 0, 0, 0, 0, 30, 1, 10);
		endothermicGrasp->effects.push_back(std::make_shared<FrostBurstEffect>(1, 5000, false, 1, 1));
		endothermicGrasp->effects.push_back(std::make_shared<FreezeEffect>(1, 1, false, 1, 1));
		return endothermicGrasp;
	}
	else if (statInvestment < 60)
	{
		endothermicGrasp = std::make_shared<Spell>("Endorthermic Touch",
			"A chilling touch that applies frost burst and freezes weaker targets solid! Investment in intelligence causes the range of the spell to increase.",
			false, false, true, 100, 0, 0, 0, 0, 40, 1, 15);
		endothermicGrasp->effects.push_back(std::make_shared<FrostBurstEffect>(1, 5000, false, 1, 1));
		endothermicGrasp->effects.push_back(std::make_shared<FreezeEffect>(1, 1, false, 1, 1));
		return endothermicGrasp;
	}
	else
	{
		endothermicGrasp = std::make_shared<Spell>("Endorthermic Grasp",
			"A chilling touch that applies frost burst and freezes weaker targets solid! Investment in intelligence causes the range of the spell to increase.",
			false, false, true, 100, 0, 0, 0, 0, 50, 1, 20);
		endothermicGrasp->effects.push_back(std::make_shared<FrostBurstEffect>(1, 5000, false, 1, 1));
		endothermicGrasp->effects.push_back(std::make_shared<FreezeEffect>(1, 1, false, 1, 1));
		return endothermicGrasp;
	}
}
//MELODIC ARTS
//MIRACLES
std::shared_ptr<Spell> Spell::getForceBurstEffect(Character& caster)
{
	float statInvestment = caster.getFaith();
	float faithBonus = caster.getFaith() * 1.0f;
	float damage = (faithBonus * (faithBonus / (faithBonus + 50))) * 1.0f;
	
	std::shared_ptr<Spell> forceBurst;
	if (statInvestment < 30)
	{
		forceBurst = std::make_shared<Spell>("Holy Gust", "Create a small gust of holy wind dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith causes holy fire to accompany the explosion.",
			false, false, true, 0, 100, 0, 0, 0, 30, 1, 10);
		forceBurst->effects.push_back(std::make_shared<KnockbackEffect>(1, max(damage * 1.5f, 20), false, 1, 1));
		forceBurst->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::BLUNT, damage * .5));
		forceBurst->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::HOLY, damage * .5));
		return forceBurst;
	}
	else if (statInvestment < 60)
	{
		forceBurst = std::make_shared<Spell>("Holy Gale", "Create a burst of holy wind dealing small amounts of damage and pushing enemies in melee range away from you. Investments in faith causes holy fire to accompany the explosion.",
			false, false, true, 0, 100, 0, 0, 0, 40, 1, 15);
		forceBurst->effects.push_back(std::make_shared<KnockbackEffect>(1, max(damage * 1.6f, 20), false, 1, 1));
		forceBurst->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::BLUNT, damage * .5));
		forceBurst->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::HOLY, damage * .5));
		forceBurst->effects.push_back(std::make_shared<BurnEffect>(4, damage * 0.5, false, 1, 1));
		return forceBurst;
	}
	else
	{
		forceBurst = std::make_shared<Spell>("Holy Burst", "Create a great burst of holy wind dealing moderate amounts of damage and pushing enemies in melee range away from you. Investments in faith causes holy fire to accompany the explosion.",
			false, false, true, 0, 100, 0, 0, 0, 50, 1, 20);
		forceBurst->effects.push_back(std::make_shared<KnockbackEffect>(1, max(damage * 1.7f, 20), false, 1, 1));
		forceBurst->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::BLUNT, damage * .5));
		forceBurst->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::HOLY, damage * .5));
		forceBurst->effects.push_back(std::make_shared<BurnEffect>(4, damage * 0.5, false, 1, 1));
		return forceBurst;
	}
}
std::shared_ptr<Spell> Spell::getWarmthOfTheGodsEffect(Character& caster)
{
	float statInvestment = caster.getFaith();
	float faithBonus = caster.getFaith() * 2.0f;
	float healing = (faithBonus * (faithBonus / (faithBonus + 10))) * 1.5f;

	std::shared_ptr<Spell> warmth;
	if (statInvestment < 30)
	{
		warmth = std::make_shared<Spell>("Hearth of the Home", "Cast a holy sigil of warmth upon the ground that heals you and your allies. Investment in faith increases the range, healing, and adds a healing over time effect.",
			true, true, false, 0, 100, 0, 0, 0, 60, 1, 10);
		warmth->effects.push_back(std::make_shared<AreaOfEffectHealing>(10, 0, healing * 0.8f, false, 1, 1));
		return warmth;
	}
	else if (statInvestment < 60)
	{
		warmth = std::make_shared<Spell>("Hearth of the Church", "Cast a holy sigil of warmth upon the ground that heals you and your allies. Investment in faith increases the range, healing, and adds a healing over time effect.",
			true, true, false, 0, 100, 0, 0, 0, 70, 1, 15);
		warmth->effects.push_back(std::make_shared<AreaOfEffectHealing>(15, 0, healing, false, 1, 1));
		return warmth;
	}
	else
	{
		warmth = std::make_shared<Spell>("Hearth of the Gods", "Cast a holy sigil of warmth upon the ground that heals you and your allies. Investment in faith increases the range, healing, and adds a healing over time effect.",
			true, true, false, 0, 100, 0, 0, 0, 80, 1, 20);
		warmth->effects.push_back(std::make_shared<AreaOfEffectHealing>(20, 0, healing * 1.1, false, 1, 1));
		warmth->effects.push_back(std::make_shared<AreaOfEffectHealing>(20, 3, healing * 0.3, false, 1, 1));
		return warmth;
	}
}
//PYROMANCY
std::shared_ptr<Spell> Spell::getFireBallEffect(Character& caster)
{
	float statInvestment = caster.getFaith();

	float faithBonus = caster.getFaith() * 1.5f;
	float fireballDamage = faithBonus * (faithBonus / (faithBonus + 50));

	std::shared_ptr<Spell> fireball;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		fireball = std::make_shared<Spell>("Fire Bolt", "A bolt of holy fire that deals burning damage",
			false, false, true, 0, 100, 0, 0, 0, 50, 50, 100);
		fireball->effects.push_back(std::make_shared<BurnEffect>(1, fireballDamage * 2, false, 1, 1));
		fireball->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::FIRE, fireballDamage + 50));
		return fireball;
	}
	else if (statInvestment < 60)
	{
		fireball = std::make_shared<Spell>("Fire Ball", "A ball of holy fire that deals moderate burning damage",
			false, false, true, 0, 100, 0, 0, 0, 60, 50, 100);
		fireball->effects.push_back(std::make_shared<BurnEffect>(1, fireballDamage * 2, false, 1, 1));
		fireball->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::FIRE, fireballDamage + 75));

		return fireball;
	}
	else
	{
		fireball = std::make_shared<Spell>("Captive Sun", "A searing ball of holy plasma that does immense burning damage",
			false, false, true, 0, 100, 0, 0, 0, 70, 50, 100);
		fireball->effects.push_back(std::make_shared<BurnEffect>(1, fireballDamage * 2, false, 1, 1));
		fireball->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::FIRE, fireballDamage + 100));
		fireball->effects.push_back(std::make_shared<FieryExplosionEffect>(fireball->range * 0.3f, fireballDamage * 0.5f, false, 1, 1));
		return fireball;
	}
}
//AEROMANCY
//FULGURAMANCY
std::shared_ptr<Spell> Spell::getThunderboltEffect(Character& caster)
{
	float statInvestment = caster.getIntelligence();
	float intBonus = caster.getIntelligence() * 1.5f;
	float thunderboltDamage = (intBonus * (intBonus / (intBonus + 50))) * 1.5;

	std::shared_ptr<Spell> thunderbolt;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		thunderbolt = std::make_shared<Spell>("Lightning Bolt", "Emit an arc of electricity from your fingertips that seeks out its target and applies moderate shock damage. Investments in intelligence give the spell the chance to arc between enemies.",
			false, false, true, 100, 0, 0, 0, 0, 50, 50, 150);
		thunderbolt->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::SHOCK, thunderboltDamage));
		thunderbolt->effects.push_back(std::make_shared<ShockEffect>(false, 3, thunderboltDamage, false, 1, 1));
		return thunderbolt;
	}
	else if (statInvestment < 60)
	{
		thunderbolt = std::make_shared<Spell>("Thunder Bolt", "Emit an arc of electricity from your fingertips that seeks out its target and applies moderate shock damage. Investments in intelligence give the spell the chance to arc between enemies.", 
			false, false, true, 100, 0, 0, 0, 0, 60, 50, 150);
		thunderbolt->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::SHOCK, thunderboltDamage));
		thunderbolt->effects.push_back(std::make_shared<ShockEffect>(false, 3, thunderboltDamage, false, 1, 1));
		thunderbolt->effects.push_back(std::make_shared<LightningArcEffect>(thunderboltDamage * 0.5, 150, 10, 30));
		return thunderbolt;
	}
	else
	{
		thunderbolt = std::make_shared<Spell>("Plasma Bolt", "Emit an arc of electricity from your fingertips that seeks out its target and applies moderate shock damage. Investments in intelligence give the spell the chance to arc between enemies.", 
			false, false, true, 100, 0, 0, 0, 0, 70, 50, 150);
		thunderbolt->effects.push_back(std::make_shared<DamageEffect>(DamageTypes::SHOCK, thunderboltDamage));
		thunderbolt->effects.push_back(std::make_shared<ShockEffect>(false, 3, thunderboltDamage, false, 1, 1));
		thunderbolt->effects.push_back(std::make_shared<LightningArcEffect>(thunderboltDamage * 0.5, 150, 20, 50));
		return thunderbolt;
	}
}
std::shared_ptr<Spell> Spell::getLightningArmamentEffect(Character& caster)
{
	float statInvestment = caster.getIntelligence();
	float intBonus = caster.getIntelligence() * 1.5f;
	float lightningArmamentDamage = (intBonus * (intBonus / (intBonus + 50))) * 1;
	std::shared_ptr<Spell> lightningArmament;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		lightningArmament = std::make_shared<Spell>("Electrify Armament I", "Use your weapon as a magical lightning rod, absorbing a falling bolt of lightning. For the next 5 turns your weapon deals additional shock damage. Investments in intelligence increase the potency of the enchantment and cause nearby targets to be shocked when applying the spell.",
			false, true, false, 100, 0, 0, 0, 0, 50, 1, 0);
		lightningArmament->effects.push_back(std::make_shared<ArmamentBuff>(DamageTypes::SHOCK, 5, lightningArmamentDamage, false, 1, 1));
		return lightningArmament;
	}
	else if (statInvestment < 60)
	{
		lightningArmament = std::make_shared<Spell>("Electrify Armament II", "Use your weapon as a magical lightning rod, absorbing a falling bolt of lightning. For the next 5 turns your weapon deals additional shock damage. Investments in intelligence increase the potency of the enchantment and cause nearby targets to be shocked when applying the spell.",
			false, true, false, 100, 0, 0, 0, 0, 70, 1, 0);
		lightningArmament->effects.push_back(std::make_shared<ArmamentBuff>(DamageTypes::SHOCK, 5, lightningArmamentDamage * 1.1f, false, 1, 1));
		lightningArmament->effects.push_back(std::make_shared<AuraEffect>(DamageTypes::SHOCK, 10, 1, lightningArmamentDamage * 2, false, 1, 1));
		return lightningArmament;
	}
	else
	{
		lightningArmament = std::make_shared<Spell>("Electrify Armament III", "Use your weapon as a magical lightning rod, absorbing a falling bolt of lightning. For the next 5 turns your weapon deals additional shock damage. Investments in intelligence increase the potency of the enchantment and cause nearby targets to be shocked when applying the spell.",
			false, true, false, 100, 0, 0, 0, 0, 80, 1, 0);
		lightningArmament->effects.push_back(std::make_shared<ArmamentBuff>(DamageTypes::SHOCK, 5, lightningArmamentDamage * 1.2f, false, 1, 1));
		lightningArmament->effects.push_back(std::make_shared<AuraEffect>(DamageTypes::SHOCK, 15, 1, lightningArmamentDamage * 4, false, 1, 1));

		return lightningArmament;
	}
}
//VENOMANCY
