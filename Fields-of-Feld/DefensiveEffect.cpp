#include "DefensiveEffect.h"
#include "Character.h"
#include "color.hpp"
#include <iostream>
// ------------------------------------------ FATIGUE BUFF ------------------------------------------ //

ThornsEffect::ThornsEffect(MagicDamageType damageType, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks) : TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->range = range;
	this->damageType = damageType;
	this->setMagicDamage(damageType, magnitude);
}

void ThornsEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
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
		{"damageType", damageType},
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
	return std::make_shared<ThornsEffect>(j["damageType"],j["range"], j["duration"], j["magnitude"], j["stackable"], j["stacks"], j["maxStacks"]);
}

std::string ThornsEffect::getType() const
{
	return "Thorns";
}

// ------------------------------------------ AURA EFECT ------------------------------------------ //

AuraEffect::AuraEffect(MagicDamageType magicDamage, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks) : TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->range = range;
	this->setMagicDamage(magicDamage, magnitude);
}

void AuraEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
{
	// Default implementation does nothing

}

void AuraEffect::tick(std::shared_ptr<Character> wielder)
{	
	// Default implementation does nothing
}

void AuraEffect::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}
nlohmann::json AuraEffect::toJson() const
{
	return {
		{"type", getType()},
		{"magicDamage", magicDamage},
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
	return std::make_shared<AuraEffect>(j["range"], j["magicDamage"], j["duration"], j["magnitude"], j["stackable"], j["stacks"], j["maxStacks"]);
}

std::string AuraEffect::getType() const
{
	return "Aura";
}