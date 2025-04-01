#include "DefensiveEffect.h"
#include "Character.h"
#include "color.hpp"
#include <iostream>
#include "HelperFunctions.h"
// ------------------------------------------ THORNS EFFECT ------------------------------------------ //

ThornsEffect::ThornsEffect(DamageTypes damageType, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks) : TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->range = range;
	this->damageType = damageType;
	this->setDamage(damageType, magnitude);
}

void ThornsEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	if (target->position[wielder->getId()] <= this->range)
	{
		float damage = this->getEffectDamage(target, shared_from_this());
		target->healthPoints -= damage;

		if (target->namedCharacter)
			std::cout << dye::light_yellow(" " + target->name) << " is" << dye::light_purple(" SHOCKED")
			<< " from an enchantment on " << wielder->name << "'s armor and takes " << damage << " points of damage!" << std::endl;
		else
			std::cout << " The " << target->name << " is" << dye::light_purple(" SHOCKED")
			<< " from an enchantment on " << wielder->name << "'s armor and takes " << damage << " points of damage!" << std::endl;

		if (target->healthPoints <= 0)
		{
			target->healthPoints = 0;
			target->killCharacter();
			return;
		}
	}
}

void ThornsEffect::tick(std::shared_ptr<Character> wielder)
{
	if (duration > 0)
	{
		--duration;
		if (duration == 0)
		{
			wielder->effects.erase(std::remove(wielder->effects.begin(), wielder->effects.end(), shared_from_this()), wielder->effects.end());
		}
	}
}

void ThornsEffect::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}
nlohmann::json ThornsEffect::toJson() const
{
	return {
		{"type", getType()},
		{"damageType", damageTypesToString(damageType)},
		{"range", range},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ThornsEffect::fromJson(const nlohmann::json& j)
{
	return std::make_shared<ThornsEffect>(stringToDamageTypes(j["damageType"]),j["range"], j["duration"], j["magnitude"], j["stackable"], j["stacks"], j["maxStacks"]);
}

std::string ThornsEffect::getType() const
{
	return "Thorns";
}

// ------------------------------------------ AURA EFECT ------------------------------------------ //

AuraEffect::AuraEffect(DamageTypes damageType, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks) : TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->range = range;
	this->setDamage(damageType, magnitude);
}

void AuraEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	if (target->position[wielder->getId()] <= range)
	{
		float damage = this->getEffectDamage(target, shared_from_this());
		target->healthPoints -= damage;
		if (target->namedCharacter)
			std::cout << dye::light_yellow(" " + target->name) << " is" << dye::light_purple(" SHOCKED")
			<< " from an enchantment belonging to " << wielder->name << " and takes " << damage << " points of damage!" << std::endl;
		else
			std::cout << " The " << target->name << " is" << dye::light_purple(" SHOCKED")
			<< " from an enchantment belonging to " << wielder->name << " and takes " << damage << " points of damage!" << std::endl;
		if (target->healthPoints <= 0)
		{
			target->healthPoints = 0;
			target->killCharacter();
			return;
		}
	}
}

void AuraEffect::tick(std::shared_ptr<Character> wielder)
{	
	
}

void AuraEffect::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}
nlohmann::json AuraEffect::toJson() const
{
	return {
		{"type", getType()},
		{"damageType", damageTypesToString(damageType)},
		{"range", range},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> AuraEffect::fromJson(const nlohmann::json& j)
{
	return std::make_shared<AuraEffect>(stringToDamageTypes(j["damageType"]), j["range"], j["duration"], j["magnitude"], j["stackable"], j["stacks"], j["maxStacks"]);
}

std::string AuraEffect::getType() const
{
	return "Aura";
}