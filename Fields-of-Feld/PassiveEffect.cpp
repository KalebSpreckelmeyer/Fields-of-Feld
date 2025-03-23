#include "PassiveEffect.h"
#include "Character.h"
#include "color.hpp"
#include <iostream>
#include "Spell.h"
#include "Human.h"

FatigueBuff::FatigueBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FatigueBuff::getType() const
{
	return "FatigueBuff";
}

void FatigueBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json FatigueBuff::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FatigueBuff::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FatigueBuff>(duration, magnitude, stackable, stacks, maxStacks);
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

void HealthBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json HealthBuff::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> HealthBuff::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<HealthBuff>(duration, magnitude, stackable, stacks, maxStacks);
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

void CastSpeed::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json CastSpeed::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> CastSpeed::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<CastSpeed>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ SUMMON ------------------------------------------ //

Summon::Summon(std::shared_ptr<Character> summon, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->summon = summon;
}

void Summon::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json Summon::toJson() const
{
	return{
		{"type", getType()},
		{"summon", summon->toJson()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> Summon::fromJson(const nlohmann::json& j)
{
	std::shared_ptr<Character> summon = Character::fromJson(j.at("summon"));
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<Summon>(summon, duration, magnitude, stackable, stacks, maxStacks);

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

void ArmorBuff::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json ArmorBuff::toJson() const
{
	return{
		{"type", getType()},
		{"defense", static_cast<int>(defense)},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ArmorBuff::fromJson(const nlohmann::json& j)
{
	Defense defense = static_cast<Defense>(j.at("defense").get<int>());
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ArmorBuff>(defense, duration, magnitude, stackable, stacks, maxStacks);
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

void Healing::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json Healing::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> Healing::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<Healing>(duration, magnitude, stackable, stacks, maxStacks);
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

void FatigueRestore::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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

nlohmann::json FatigueRestore::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FatigueRestore::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FatigueRestore>(duration, magnitude, stackable, stacks, maxStacks);
}