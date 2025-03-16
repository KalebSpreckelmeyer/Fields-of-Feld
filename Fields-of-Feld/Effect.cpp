#include "Effect.h"
#include <string>
#include <iostream>
#include "color.hpp"

Effect::Effect(std::string name, std::string description, float duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: name(name), description(description), duration(duration), magnitude(magnitude), stackable(stackable), stacks(stacks), maxStacks(maxStacks)
{
}

Effect::~Effect()
{
}

void Effect::refreshEffects(Character& target)
{
	if (target.effects.empty()) return;
	std::vector<Effect*> effectsToRemove;
	for(const auto& effect : target.effects)
	{	
		if (effect == nullptr)
		{
			std::cout << "ERROR EFFECT IS NULL IN REFRESHEFFECTS" << std::endl;
		}
		else
		{
			if (effect->name == "Poison")
			{
				for (int i = 0; i < effect->stacks; i++)
				{
					std::cout << " " + target.name + " takes " << target.maxHealthPoints * 0.05 << " poison damage!" << std::endl;
					target.healthPoints -= target.maxHealthPoints * 0.05;
					if (target.healthPoints <= 0)
					{
						target.healthPoints = 0;
						target.killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::POISONED)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Burn")
			{
				float burnDamage = effect->magnitude;

				std::cout << dye::light_yellow(" " + target.name) << dye::light_red(" BURNED") <<
					" for " << burnDamage << " points of damage!" << std::endl;
				target.healthPoints -= burnDamage;
				if (target.healthPoints <= 0)
				{
					target.healthPoints = 0;
					target.killCharacter();
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::BURNING)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Fear of Flames")
			{
				if (target.isAlive)
				{
					if (target.confidenceLevel <= 20 || target.healthPoints <= target.maxHealthPoints * 0.5 || target.level <= 5)
					{
						std::cout << dye::light_yellow(" " + target.name + " is too terrified of the flames to attack!") << std::endl;
						target.combatFlag = Character::CombatFlags::FEAR;
					}
					else
					{
						std::cout << " " + target.name + " withstands the flames and attacks!" << std::endl;
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::FEAR)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Frost Burst")
			{
				if (target.isAlive)
				{
					std::cout << dye::light_yellow(" " + target.name) << " suffers a" << dye::light_blue(" FROST BURST!") << 
						" and takes " << effect->magnitude << " points of damage!" << std::endl;
					target.healthPoints -= effect->magnitude;
					if (target.healthPoints <= 0)
					{
						target.healthPoints = 0;
						target.killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::FROSTBITTEN)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Shock")
			{
				if (target.isAlive)
				{
					std::cout << dye::light_yellow(" " + target.name) << " suffers a" << dye::light_purple(" ELECTROCUTION!") <<
						" and takes " << effect->magnitude << " points of damage!" << std::endl;
					std::cout << dye::light_yellow(" " + target.name) << "'s movements are slowed!" << std::endl;
					target.speed -= effect->magnitude;
					if (target.speed < 0) target.speed = 0;
					target.healthPoints -= effect->magnitude;
					if (target.healthPoints <= 0)
					{
						target.healthPoints = 0;
						target.killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::SHOCKED)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Blood Loss")
			{
				if (target.isAlive)
				{
					std::cout << dye::light_yellow(" " + target.name) << " is" << dye::light_red(" BLEEDING!") <<
						" and takes " << effect->magnitude << " points of damage!" << std::endl;
					target.healthPoints -= effect->magnitude;
					if (target.healthPoints <= 0)
					{
						target.healthPoints = 0;
						target.killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::BLEEDING)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Sleep")
			{
				if (target.isAlive)
				{
					std::cout << dye::light_yellow(" " + target.name) << " is" << dye::light_blue(" ASLEEP!") << std::endl;
					target.combatFlag = Character::CombatFlags::SLEEPY;
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target.combatFlags.size(); i++)
					{
						if (target.combatFlags[i] == Character::CombatFlags::SLEEPY)
						{
							target.combatFlags.erase(target.combatFlags.begin() + i);
						}
					}
				}
			}
		}
	}
	for (Effect* effect : effectsToRemove)
	{
		removeEffect(target, *effect);
	}
}

void Effect::removeEffect(Character& target, Effect& effectToDelete) {
	for (Effect* effect : target.effects)
	{
		if (effect->name == effectToDelete.name)
		{
			target.effects.erase(std::remove(target.effects.begin(), target.effects.end(), effect), target.effects.end());
			delete effect;
			effect = nullptr;
			return;
		}
	}
}

bool hasEffect(const Character& target, const std::string& effectName) {
	for (const Effect* effect : target.effects) {
		if (effect->name == effectName) {
			return true;
		}
	}
	return false;
}

void Effect::applyEffect(Character& attacker, Character& target, Effect& effect)
{
	if (effect.name == "Burn") {
		target.burnPoints += effect.magnitude + attacker.getFaith();
		if (!hasEffect(target, "Burn")) {
			Effect* burn = new Effect("Burn", "The target is engulfed in flames causing damage each turn",
				3, target.maxHealthPoints * 0.1f, false, 1, 1);
			target.combatFlags.push_back(Character::CombatFlags::BURNING);
			target.effects.push_back(burn);
		}
		if (target.burnPoints >= target.maxBurnPoints) {
			if (!hasEffect(target, "Fear of Flames")) {
				Effect* fear = new Effect("Fear of Flames", "Weaker targets are too terrified of the inferno that engulfs them to attack", 1.0f, 1.0f, false, 1, 1);
				target.effects.push_back(fear);
			}
		}
		return;
	}
	else if (effect.name == "Fear of Flames")
	{
		if (target.confidenceLevel <= 20 || target.healthPoints <= target.maxHealthPoints * 0.5 || target.level <= 5)
		{
			std::cout << dye::light_yellow(" " + target.name + " is too terrified to attack!") << std::endl;
			target.combatFlags.push_back(Character::CombatFlags::FEAR);
			return;
		}
		else
		{
			std::cout << " " + target.name + " withstands the flames and attacks!" << std::endl;
			return;
		}
	}
	else if (effect.name == "Poison")
	{
		target.poisonPoints += effect.magnitude;
		if (target.poisonPoints >= target.maxPoisonPoints)
		{
			std::cout << dye::light_yellow(" " + target.name) << dye::light_green(" POISONED") << std::endl;
			target.poisonPoints = 0;
			target.combatFlags.push_back(Character::CombatFlags::POISONED);
			
			Effect* poison = new Effect("Poison", "Putrid venom courses through their veins", 5, 0, true, 1, 5);
			bool poisonApplied = false;
			for (Effect* effect : target.effects)
			{
				if (effect->name == "Poison")
				{
					effect->stacks = min(effect->stacks + 1, effect->maxStacks);
					poisonApplied = true;
					break;  
				}
			}
			if (!poisonApplied)
			{
				target.effects.push_back(poison);
			}
		}
		return;
	}
	else if (effect.name == "Frost Burst")
	{
		target.frostPoints += effect.magnitude + attacker.getIntelligence();
		if (target.frostPoints >= target.maxFrostPoints)
		{
			target.frostPoints = 0;
			target.combatFlags.push_back(Character::CombatFlags::FROSTBITTEN);
			Effect* frostBite = new Effect("Frost Burst", "The ice accumulating on the target explodes in a burst of frost!",
				1, target.maxHealthPoints * 0.2, false, 1, 1);
			target.effects.push_back(frostBite);
		}
		return;
	}
	else if (effect.name == "Shock")
	{
		target.shockPoints += effect.magnitude + attacker.getIntelligence();
		if (target.shockPoints >= target.maxShockPoints)
		{
			target.shockPoints = 0;
			target.combatFlags.push_back(Character::CombatFlags::SHOCKED);
			Effect* shock = new Effect("Shock", "The target is paralyzed by the electrical current, slowing their movements!"
				,1 , effect.magnitude, false, 1, 1);
			target.effects.push_back(shock);
		}
		return;
	}
	else if (effect.name == "Blood Loss")
	{
		target.bleedPoints += effect.magnitude + attacker.getArcane();
		if (target.bleedPoints >= target.maxBleedPoints)
		{
			target.bleedPoints = 0;
			target.combatFlags.push_back(Character::CombatFlags::BLEEDING);
			Effect* bleed = new Effect("Blood Loss", "The target is bleeding profusely, losing a percentage of their maximum health!",
				1, target.maxHealthPoints * 0.1, false, 1, 1);
			target.effects.push_back(bleed);
		}
		return;
	}
	else if (effect.name == "Sleep")
	{
		target.sleepPoints += effect.magnitude;
		if (target.sleepPoints >= target.maxSleepPoints)
		{
			target.sleepPoints = 0;
			target.combatFlags.push_back(Character::CombatFlags::SLEEPY);
			Effect* sleep = new Effect("Sleep", "The target has dozen off, unable to attack for one turn!",
				1, 1, false, 1, 1);
			target.effects.push_back(sleep);
		}
		return;
	}
	else if (effect.name == "None")
	{
		return;
	}
	else
	{
		std::cout << "Invalid effect name" << std::endl;
	}
}
