#include "PassiveEffect.h"
#include "Character.h"
#include "color.hpp"
#include <iostream>
#include "Spell.h"
#include "Human.h"
#include "OffensiveEffect.h"
#include "HelperFunctions.h"

FatigueBuff::FatigueBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FatigueBuff::getType() const
{
	return "FatigueBuff";
}

void FatigueBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->maxFatiguePoints += magnitude;
	target->fatiguePoints += magnitude;
	if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " gains " << magnitude << " points of maximum fatigue!" << std::endl;
	if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " gains " << magnitude << " points of maximum fatigue!" << std::endl;
	target->effects.push_back(shared_from_this());
}

void FatigueBuff::tick(std::shared_ptr<Character> wielder)
{
	duration -= 1;
	if (duration <= 0)
	{
		wielder->fatiguePoints = wielder->maxFatiguePoints;
		if (wielder->fatiguePoints >= 0) wielder->fatiguePoints = 1;
		wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
	}
}

void FatigueBuff::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json FatigueBuff::toJson() const {
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FatigueBuff::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<FatigueBuff>(
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize FatigueBuff: " << e.what() << std::endl;
		return nullptr;
	}
}


// ------------------------------------------ HEALTH BUFF ------------------------------------------ //

HealthBuff::HealthBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string HealthBuff::getType() const
{
	return "HealthBuff";
}

void HealthBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->maxHealthPoints += magnitude;
	target->healthPoints += magnitude;
	if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " gains " << magnitude << " points of maximum health!" << std::endl;
	if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " gains " << magnitude << " points of maximum health!" << std::endl;
	target->effects.push_back(shared_from_this());
}

void HealthBuff::tick(std::shared_ptr<Character> wielder)
{
	duration -= 1;
	if (duration <= 0)
	{
		wielder->healthPoints = wielder->maxHealthPoints;
		if (wielder->healthPoints >= 0) wielder->healthPoints = 1;
		wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
	}
}

void HealthBuff::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json HealthBuff::toJson() const {
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> HealthBuff::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<HealthBuff>(
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize HealthBuff: " << e.what() << std::endl;
		return nullptr;
	}
}

// ------------------------------------------ CAST SPEED ------------------------------------------ //

CastSpeed::CastSpeed(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string CastSpeed::getType() const
{
	return "CastSpeed";
}

void CastSpeed::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	if (std::dynamic_pointer_cast<Human>(target))
	{
		std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(target);
		human->castSpeed += magnitude;
		if (human->namedCharacter) std::cout << dye::light_yellow(" " + human->name) << " gains " << magnitude << " points of cast speed!" << std::endl;
		if (!human->namedCharacter) std::cout << " The " << dye::light_yellow(human->name) << " gains " << magnitude << " points of cast speed!" << std::endl;
		human->effects.push_back(shared_from_this());
	}
}

void CastSpeed::tick(std::shared_ptr<Character> wielder)
{
	duration -= 1;
	if (duration <= 0)
	{
		if (std::dynamic_pointer_cast<Human>(wielder))
		{
			std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(wielder);
			human->castSpeed -= magnitude;
			if (human->castSpeed < 0) human->castSpeed = 0;
			human->effects.erase(std::remove(human->effects.begin(), human->effects.end(), shared_from_this()), human->effects.end());

			if (human->namedCharacter) std::cout << dye::light_yellow(" " + human->name) << " loses " << magnitude << " points of cast speed!" << std::endl;
			if (!human->namedCharacter) std::cout << " The " << dye::light_yellow(human->name) << " loses " << magnitude << " points of cast speed!" << std::endl;
		}
	}
}

void CastSpeed::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json CastSpeed::toJson() const {
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> CastSpeed::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<CastSpeed>(
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize CastSpeed: " << e.what() << std::endl;
		return nullptr;
	}
}

// ------------------------------------------ SUMMON ------------------------------------------ //

Summon::Summon(std::shared_ptr<Character> summon, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->summon = summon;
}

void Summon::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->allies.push_back(summon);
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " summons " << summon->name << " to their aid!" << std::endl;
	if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " summons " << summon->name << " to their aid!" << std::endl;
	target->effects.push_back(shared_from_this());
}

void Summon::tick(std::shared_ptr<Character> wielder)
{
	duration -= 1;
	if (duration <= 0)
	{
		if (wielder->namedCharacter) std::cout << dye::light_yellow(" " + wielder->name) << "'s " << summon->name << " leaves the battlefield!" << std::endl;
		if (!wielder->namedCharacter) std::cout << " The " << dye::light_yellow(wielder->name) << "'s " << summon->name << " leaves the battlefield!" << std::endl;

		wielder->allies.erase(std::remove(wielder->allies.begin(), wielder->allies.end(), summon), wielder->allies.end());
	}
}

std::string Summon::getType() const
{
	return "Summon";
}

void Summon::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json Summon::toJson() const {
	return {
		{"type", getType()},
		{"summon", summon->toJson()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> Summon::fromJson(const nlohmann::json& j) {
	try {
		auto summoned = Character::fromJson(j.at("summon"));
		return std::make_shared<Summon>(
			summoned,
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize Summon: " << e.what() << std::endl;
		return nullptr;
	}
}

// ------------------------------------------ ARMOR BUFF ------------------------------------------ //

ArmorBuff::ArmorBuff(Defense defense, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), defense(defense)
{
}

std::string ArmorBuff::getType() const
{
	return "ArmorBuff";
}

void ArmorBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	std::string defenseTypes[] {"None", "Slash", "Pierce", "Blunt", "Chop", "Magic", "Fire", "Frost", "Shock", "Wind", "Poison", "Bleed", "Sleep", "Dark", "Holy"};
	target->setDefenseValue(defense, target->getDefenseValue(defense) + magnitude);
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " gains " << magnitude << " points of " << defenseTypes[static_cast<int>(defense)] << " defense!" << std::endl;
	
	//Apply effect to target so it can be removed later
	target->effects.push_back(shared_from_this());
}

void ArmorBuff::tick(std::shared_ptr<Character> wielder)
{
	duration -= 1;
	if (duration <= 0)
	{
		wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
		wielder->setDefenseValue(defense, wielder->getDefenseValue(defense) - magnitude);
		if (wielder->getDefenseValue(defense) < 0) wielder->setDefenseValue(defense, 0);
	}
}

void ArmorBuff::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json ArmorBuff::toJson() const {
	return {
		{"type", getType()},
		{"defense", defenseToString(defense)},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ArmorBuff::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<ArmorBuff>(
			stringToDefense(j.at("defense")),
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize ArmorBuff: " << e.what() << std::endl;
		return nullptr;
	}
}

// ------------------------------------------ HEALING ------------------------------------------ //

Healing::Healing(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string Healing::getType() const
{
	return "Healing";
}

void Healing::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->effects.push_back(shared_from_this());
}

void Healing::tick(std::shared_ptr<Character> wielder)
{
	if (duration > 0)
	{
		wielder->healthPoints += magnitude;
		if (wielder->healthPoints > wielder->maxHealthPoints) wielder->healthPoints = wielder->maxHealthPoints;
		if (wielder->namedCharacter) std::cout << dye::light_yellow(" " + wielder->name) << " restores " << magnitude << " points of health!" << std::endl;
		if (!wielder->namedCharacter) std::cout << " The " << dye::light_yellow(wielder->name) << " restores " << magnitude << " points of health!" << std::endl;
	}
	if (duration <= 0)
	{
		wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
	}
	duration -= 1;
}

void Healing::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json Healing::toJson() const {
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> Healing::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<Healing>(
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize Healing: " << e.what() << std::endl;
		return nullptr;
	}
}
// ------------------------------------------ AOE HEALING RESTORE ------------------------------------------ //

AreaOfEffectHealing::AreaOfEffectHealing(float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), range(range)
{
}

std::string AreaOfEffectHealing::getType() const
{
	return "AreaOfEffectHealing";
}

void AreaOfEffectHealing::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->effects.push_back(shared_from_this());
	target->healthPoints += magnitude;
	if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " restores " << magnitude << " points of health!" << std::endl;
	if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " restores " << magnitude << " points of health!" << std::endl;

	for (auto& ally : target->allies)
	{
		if (target->position[ally->getId()] <= range)
		{
			ally->healthPoints += magnitude;
			if (ally->healthPoints > ally->maxHealthPoints) ally->healthPoints = ally->maxHealthPoints;
			if (ally->namedCharacter) std::cout << dye::light_yellow(" " + ally->name) << " restores " << magnitude << " points of health!" << std::endl;
			if (!ally->namedCharacter) std::cout << " The " << dye::light_yellow(ally->name) << " restores " << magnitude << " points of health!" << std::endl;
		}
	}
}

void AreaOfEffectHealing::tick(std::shared_ptr<Character> wielder)
{
	if (duration > 0)
	{
		wielder->healthPoints += magnitude;
		if (wielder->healthPoints > wielder->maxHealthPoints) wielder->healthPoints = wielder->maxHealthPoints;
		if (wielder->namedCharacter) std::cout << dye::light_yellow(" " + wielder->name) << " restores " << magnitude << " points of health!" << std::endl;
		if (!wielder->namedCharacter) std::cout << " The " << dye::light_yellow(wielder->name) << " restores " << magnitude << " points of health!" << std::endl;
		for (auto& ally : wielder->allies)
		{
			if (wielder->position[ally->getId()] <= range)
			{
				ally->healthPoints += magnitude;
				if (ally->healthPoints > ally->maxHealthPoints) ally->healthPoints = ally->maxHealthPoints;
				if (ally->namedCharacter) std::cout << dye::light_yellow(" " + ally->name) << " restores " << magnitude << " points of health!" << std::endl;
				if (!ally->namedCharacter) std::cout << " The " << dye::light_yellow(ally->name) << " restores " << magnitude << " points of health!" << std::endl;
			}
		}
	}
	if (duration <= 0)
	{
		wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
	}
	duration -= 1;
}

void AreaOfEffectHealing::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json AreaOfEffectHealing::toJson() const {
	return {
		{"type", getType()},
		{"range", range},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> AreaOfEffectHealing::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<AreaOfEffectHealing>(
			j.at("range"),
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize AreaOfEffectHealing: " << e.what() << std::endl;
		return nullptr;
	}
}

// ------------------------------------------ FATIGUE RESTORE ------------------------------------------ //

FatigueRestore::FatigueRestore(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FatigueRestore::getType() const
{
	return "FatigueRestore";
}

void FatigueRestore::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->fatiguePoints += magnitude;
	if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " restores " << magnitude << " points of fatigue!" << std::endl;
	if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " restores " << magnitude << " points of fatigue!" << std::endl;
}

void FatigueRestore::tick(std::shared_ptr<Character> wielder)
{
	// Default implementation does nothing
}

void FatigueRestore::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json FatigueRestore::toJson() const {
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FatigueRestore::fromJson(const nlohmann::json& j) {
	try {
		return std::make_shared<FatigueRestore>(
			j.at("duration"),
			j.at("magnitude"),
			j.at("stackable"),
			j.at("stacks"),
			j.at("maxStacks")
		);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize FatigueRestore: " << e.what() << std::endl;
		return nullptr;
	}
}

// ------------------------------------------ ARMAMENT BUFF ------------------------------------------ //

ArmamentBuff::ArmamentBuff(DamageTypes damageType, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), damageType(damageType)
{
	this->setDamage(damageType, magnitude);
}

std::string ArmamentBuff::getType() const
{
	return "ArmamentBuff";
}

void ArmamentBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	std::string DamageTypess[]{ "None", "Magic", "Fire", "Frost", "Shock", "Wind", "Poison", "Bleed", "Sleep", "Dark", "Holy" };
	// add incoming effect
	target->effects.push_back(shared_from_this());

	// Get equipped weapons
	std::shared_ptr<Weapon> mainHand, offHand, reserve1, reserve2;
	target->inventory.getEquippedWeapons(mainHand, offHand, reserve1, reserve2);

	//return if mainhand is empty
	if (!mainHand) return;
	//add magic damage to weapon
	mainHand->setDamage(damageType, mainHand->getDamage(damageType) + magnitude);
	if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << "'s " << mainHand->name << " gains " << magnitude << " points of " << DamageTypess[static_cast<int>(damageType)] << " damage!" << std::endl;
	if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << "'s " << mainHand->name << " gains " << magnitude << " points of " << DamageTypess[static_cast<int>(damageType)] << " damage!" << std::endl;
}

void ArmamentBuff::tick(std::shared_ptr<Character> wielder)
{
	std::string DamageTypess[]{ "None", "Magic", "Fire", "Frost", "Shock", "Wind", "Poison", "Bleed", "Sleep", "Dark", "Holy" };
	if (duration <= 0)
	{
		// Get equipped weapons
		std::shared_ptr<Weapon> mainHand, offHand, reserve1, reserve2;
		wielder->inventory.getEquippedWeapons(mainHand, offHand, reserve1, reserve2);

		//return if mainhand is empty
		if (!mainHand) return;

		//remove magic damage from weapon
		float current = mainHand->getDamage(damageType);
		mainHand->setDamage(damageType, max(0.0f, current - magnitude));
		wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
		if (wielder->namedCharacter) std::cout << dye::light_yellow(" " + wielder->name) << "'s " << mainHand->name << " loses " << magnitude << " points of " << DamageTypess[static_cast<int>(damageType)] << " damage!" << std::endl;
		if (!wielder->namedCharacter) std::cout << " The " << dye::light_yellow(wielder->name) << "'s " << mainHand->name << " loses " << magnitude << " points of " << DamageTypess[static_cast<int>(damageType)] << " damage!" << std::endl;
	}
	if (duration > 0) duration -= 1;
}

void ArmamentBuff::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json ArmamentBuff::toJson() const
{
	return {
		{"type", getType()},
		{"magicDamage", damageTypesToString(damageType)},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ArmamentBuff::fromJson(const nlohmann::json& j)
{
	try {
		DamageTypes magicDamage = stringToDamageTypes(j.at("magicDamage").get<std::string>());
		int duration = j.at("duration");
		float magnitude = j.at("magnitude");
		bool stackable = j.at("stackable");
		int stacks = j.at("stacks");
		int maxStacks = j.at("maxStacks");

		return std::make_shared<ArmamentBuff>(magicDamage, duration, magnitude, stackable, stacks, maxStacks);
	}
	catch (const std::exception& e) {
		std::cerr << "[ERROR] Failed to deserialize ArmamentBuff: " << e.what() << std::endl;
		return nullptr;
	}
}

