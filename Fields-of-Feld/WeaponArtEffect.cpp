#include "WeaponArtEffect.h"
#include "Character.h"
#include <iostream>
#include "color.hpp"

// ------------------------------------------ PERSERVERANCE EFFECT ------------------------------------------ //

PerserveranceEffect::PerserveranceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string PerserveranceEffect::getType() const
{
	return "Perserverance";
}

void PerserveranceEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	wielder->effects.push_back(shared_from_this());
	if (wielder->namedCharacter) std::cout << " " << dye::light_yellow(wielder->name) << " braces themselves, increasing their defences by " << magnitude << std::endl;
	if (!wielder->namedCharacter) std::cout << " The " << dye::light_yellow(wielder->name) << " braces themselves, increasing their defences by " << magnitude << std::endl;
	wielder->setDefenseValue(Defense::BLUNT, wielder->getDefenseValue(Defense::BLUNT) + magnitude);
	wielder->setDefenseValue(Defense::CHOP, wielder->getDefenseValue(Defense::CHOP) + magnitude);
	wielder->setDefenseValue(Defense::PIERCE, wielder->getDefenseValue(Defense::PIERCE) + magnitude);
	wielder->setDefenseValue(Defense::SLASH, wielder->getDefenseValue(Defense::SLASH) + magnitude);
	wielder->setDefenseValue(Defense::MAGIC, wielder->getDefenseValue(Defense::MAGIC) + magnitude);
	wielder->setDefenseValue(Defense::FIRE, wielder->getDefenseValue(Defense::FIRE) + magnitude);
	wielder->setDefenseValue(Defense::FROST, wielder->getDefenseValue(Defense::FROST) + magnitude);
	wielder->setDefenseValue(Defense::SHOCK, wielder->getDefenseValue(Defense::SHOCK) + magnitude);
	wielder->setDefenseValue(Defense::POISON, wielder->getDefenseValue(Defense::POISON) + magnitude);
	wielder->setDefenseValue(Defense::BLEED, wielder->getDefenseValue(Defense::BLEED) + magnitude);
	wielder->setDefenseValue(Defense::DARK, wielder->getDefenseValue(Defense::DARK) + magnitude);
	wielder->setDefenseValue(Defense::HOLY, wielder->getDefenseValue(Defense::HOLY) + magnitude);
}


void PerserveranceEffect::tick(std::shared_ptr<Character> target)
{
	if (duration <= 0)
	{
		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) - magnitude);
		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) - magnitude);
		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) - magnitude);
		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) - magnitude);
		target->setDefenseValue(Defense::MAGIC, target->getDefenseValue(Defense::MAGIC) - magnitude);
		target->setDefenseValue(Defense::FIRE, target->getDefenseValue(Defense::FIRE) - magnitude);
		target->setDefenseValue(Defense::FROST, target->getDefenseValue(Defense::FROST) - magnitude);
		target->setDefenseValue(Defense::SHOCK, target->getDefenseValue(Defense::SHOCK) - magnitude);
		target->setDefenseValue(Defense::POISON, target->getDefenseValue(Defense::POISON) - magnitude);
		target->setDefenseValue(Defense::BLEED, target->getDefenseValue(Defense::BLEED) - magnitude);
		target->setDefenseValue(Defense::DARK, target->getDefenseValue(Defense::DARK) - magnitude);
		target->setDefenseValue(Defense::HOLY, target->getDefenseValue(Defense::HOLY) - magnitude);
		target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << "'s defences return to normal." << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << "'s defences return to normal." << std::endl;
	}
	if (duration > 0) --duration;
}

void PerserveranceEffect::burst(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

nlohmann::json PerserveranceEffect::toJson() const
{
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> PerserveranceEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<PerserveranceEffect>(duration, magnitude, stackable, stacks, maxStacks);
}