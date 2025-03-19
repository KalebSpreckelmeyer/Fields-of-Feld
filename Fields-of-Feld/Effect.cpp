#include "Effect.h"
#include <string>
#include <iostream>
#include "color.hpp"
#include "Character.h"
#include "vector"
#include "optional"
#include "Inventory.h"
#include "Human.h"
#include "Creature.h"
#include <algorithm>
#include "Armor.h"
#include "Weapon.h"
#include "MagicDamageType.h"
#include "PhysicalDamageType.h"

Effect::Effect()
{

}

Effect::Effect(bool doesDamage, bool applied, std::string name, std::string description, PhysicalDamageType physType,
	MagicDamageType magType, float duration,
	float magnitude, bool stackable, int stacks, int maxStacks, bool areaOfEffect)
	: name(name), description(description), duration(duration), magnitude(magnitude), stackable(stackable),
	stacks(stacks), maxStacks(maxStacks), areaOfEffect(areaOfEffect)
{
}

void Effect::setPhysicalDamage(PhysicalDamageType physType, float physDamage)
{
	physicalDamage[physType] = physDamage;
}

void Effect::setMagicDamage(MagicDamageType magType, float magDamage)
{
	magicDamage[magType] = magDamage;
}

float Effect::getPhysicalDamage(PhysicalDamageType physType)
{
	return physicalDamage[physType];
}

float Effect::getMagicDamage(MagicDamageType magType)
{
	return magicDamage[magType];
}

float Effect::getEffectDamage(Character* target, Effect effect)
{
	//Target is human
	if (dynamic_cast<Human*>(target))
	{
		Human* human = dynamic_cast<Human*>(target);
		//GET ARMOR RESISTANCES
		float cumulativeSlashResist = 0;
		float cumulativePierceResist = 0;
		float cumulativeBluntResist = 0;
		float cumulativeChopResist = 0;

		float cumulativeMagicResist = 0;
		float cumulativeFireResist = 0;
		float cumulativeIceResist = 0;
		float cumulativeShockResist = 0;
		float cumulativePoisonResist = 0;
		float cumulativeBleedResist = 0;
		float cumulativeSleepResist = 0;
		float cumulativeDarkResist = 0;
		float cumulativeHolyResist = 0;
		float cumulativeWindResist = 0;

		for (Item* item : target->inventory.equippedItems)
		{
			if (Armor* armor = dynamic_cast<Armor*>(item))
			{
				cumulativeSlashResist += armor->getPhysicalResistance(PhysicalDamageType::SLASH);
				cumulativePierceResist += armor->getPhysicalResistance(PhysicalDamageType::PIERCE);
				cumulativeBluntResist += armor->getPhysicalResistance(PhysicalDamageType::BLUNT);
				cumulativeChopResist += armor->getPhysicalResistance(PhysicalDamageType::CHOP);
				cumulativeMagicResist += armor->getMagicResistance(MagicDamageType::MAGIC);
				cumulativeFireResist += armor->getMagicResistance(MagicDamageType::FIRE);
				cumulativeIceResist += armor->getMagicResistance(MagicDamageType::FROST);
				cumulativeShockResist += armor->getMagicResistance(MagicDamageType::SHOCK);
				cumulativeWindResist += armor->getMagicResistance(MagicDamageType::WIND);
				cumulativePoisonResist += armor->getMagicResistance(MagicDamageType::POISON);
				cumulativeBleedResist += armor->getMagicResistance(MagicDamageType::BLEED);
				cumulativeSleepResist += armor->getMagicResistance(MagicDamageType::SLEEP);
				cumulativeDarkResist += armor->getMagicResistance(MagicDamageType::DARK);
				cumulativeHolyResist += armor->getMagicResistance(MagicDamageType::HOLY);
			}
		}

		//TODO: Implement enchanted item resistances

		//damage = damage - (damage * (resistance / 500)) - max won't let it go below 0
		float cumulativeSlashDamage = effect.getPhysicalDamage(PhysicalDamageType::SLASH) - (effect.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = effect.getPhysicalDamage(PhysicalDamageType::PIERCE) - (effect.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = effect.getPhysicalDamage(PhysicalDamageType::BLUNT) - (effect.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = effect.getPhysicalDamage(PhysicalDamageType::CHOP) - (effect.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = effect.getMagicDamage(MagicDamageType::MAGIC) - (effect.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = effect.getMagicDamage(MagicDamageType::FIRE) - (effect.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = effect.getMagicDamage(MagicDamageType::FROST) - (effect.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = effect.getMagicDamage(MagicDamageType::SHOCK) - (effect.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = effect.getMagicDamage(MagicDamageType::POISON) - (effect.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = effect.getMagicDamage(MagicDamageType::BLEED) - (effect.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = effect.getMagicDamage(MagicDamageType::SLEEP) - (effect.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = effect.getMagicDamage(MagicDamageType::DARK) - (effect.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = effect.getMagicDamage(MagicDamageType::HOLY) - (effect.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = effect.getMagicDamage(MagicDamageType::WIND) - (effect.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float effectDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage) - human->flatDefense * (human->flatDefense / 500);
		effectDamage = max(effectDamage, 0.0f);

		return effectDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}

void Effect::refreshEffects(Character* target)
{
	if (target->effects.empty()) return;
	std::vector<Effect*> effectsToRemove;
	for (const auto& effect : target->effects)
	{
		if (effect == nullptr)
		{
			std::cout << "ERROR EFFECT IS NULL IN REFRESHEFFECTS" << std::endl;
		}
		else
		{
			if (effect->name == "Poison")
			{
				if (!target->isAlive) return;
				for (int i = 0; i < effect->stacks; i++)
				{
					if (target->namedCharacter) std::cout << " " + target->name + " takes " << target->maxHealthPoints * 0.05 << dye::light_green(" poison ") << "damage!" << std::endl;
					if (!target->namedCharacter) std::cout << " The " + target->name + " takes " << target->maxHealthPoints * 0.05 << dye::light_green(" poison ") << "damage!" << std::endl;
					target->healthPoints -= target->maxHealthPoints * 0.05;
					if (target->healthPoints <= 0)
					{
						target->healthPoints = 0;
						target->killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::POISONED)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Burn")
			{
				if (!target->isAlive) return;
				float burnDamage = effect->getEffectDamage(target, *effect);

				if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " is " << dye::light_red("BURNED") <<
					" for " << burnDamage << " points of damage!" << std::endl;
				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_red("BURNED") <<
					" for " << burnDamage << " points of damage!" << std::endl;
				target->healthPoints -= burnDamage;
				if (target->healthPoints <= 0)
				{
					target->healthPoints = 0;
					target->killCharacter();
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::BURNING)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Fear of Flames")
			{
				if (target->isAlive)
				{
					if (target->confidenceLevel <= 20 || target->healthPoints <= target->maxHealthPoints * 0.5 || target->level <= 5)
					{
						if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name + " is too terrified of the flames to attack!") << std::endl;
						if (!target->namedCharacter) std::cout << " The " + target->name + " is too terrified of the flames to attack!" << std::endl;
						target->combatFlag = Character::CombatFlags::FEAR;
					}
					else
					{
						std::cout << " " + target->name + " withstands the flames and attacks!" << std::endl;
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::FEAR)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Frost Burst")
			{
				if (target->isAlive)
				{
					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " suffers a" << dye::light_aqua(" FROST BURST!") <<
						" and takes " << effect->getEffectDamage(target, *effect) << " points of damage!" << std::endl;
					if (!target->namedCharacter) std::cout << " The " << target->name << " suffers a" << dye::light_aqua(" FROST BURST!") <<
						" and takes " << effect->getEffectDamage(target, *effect) << " points of damage!" << std::endl;
					target->healthPoints -= effect->getEffectDamage(target, *effect);
					if (target->healthPoints <= 0)
					{
						target->healthPoints = 0;
						target->killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::FROSTBITTEN)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Shock")
			{
				if (target->isAlive)
				{
					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " suffers an" << dye::light_purple(" ELECTROCUTION!") <<
						" and takes " << effect->getEffectDamage(target, *effect) << " points of damage!" << std::endl;
					std::cout << dye::light_yellow(" " + target->name) << "'s movements are slowed!" << std::endl;
					if (!target->namedCharacter) std::cout << " The " << target->name << " suffers an" << dye::light_purple(" ELECTROCUTION!") <<
						" and takes " << effect->getEffectDamage(target, *effect) << " points of damage!" << std::endl;
					target->speed -= effect->getEffectDamage(target, *effect);
					if (target->speed < 0) target->speed = 0;
					target->healthPoints -= effect->getEffectDamage(target, *effect);
					if (target->healthPoints <= 0)
					{
						target->healthPoints = 0;
						target->killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::SHOCKED)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Blood Loss")
			{
				if (target->isAlive)
				{
					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " is" << dye::light_red(" BLEEDING!") <<
						" and takes " << effect->getEffectDamage(target, *effect) << " points of damage!" << std::endl;
					if (!target->namedCharacter) std::cout << " The " << target->name << " is" << dye::light_red(" BLEEDING!") <<
						" and takes " << effect->getEffectDamage(target, *effect) << " points of damage!" << std::endl;
					target->healthPoints -= effect->getEffectDamage(target, *effect);
					if (target->healthPoints <= 0)
					{
						target->healthPoints = 0;
						target->killCharacter();
					}
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::BLEEDING)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Sleep")
			{
				if (target->isAlive)
				{
					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " is" << dye::light_blue(" ASLEEP!") << std::endl;
					if (!target->namedCharacter) std::cout << " The " << target->name << " is" << dye::light_blue(" ASLEEP!") << std::endl;
					target->combatFlag = Character::CombatFlags::SLEEPY;
				}
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::SLEEPY)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			//deal damage to all allies
			if (effect->name == "Fiery Explosion")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
				}
			}
			//decrement duration of summoned animals, remove them if necessary
			if (effect->name == "Summon Cooldown")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effect->applied = false;
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->allies.size(); i++)
					{
						if (target->allies[i]->name == "Bear" || target->allies[i]->name == "Vulture" || target->allies[i]->name == "Wolf")
						{
							std::cout << " " << target->allies[i]->name << " has left the battlefield!" << std::endl;
							int j = i;
							target->allies.erase(target->allies.begin() + j);
							break;
						}
					}
				}
			}
			if (effect->name == "Freeze 1" || effect->name == "Freeze 2" || effect->name == "Freeze 3")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::FROZEN)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Oaken Armor I")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					std::cout << " " << target->name << " loses their Oaken Armor I!" << std::endl;
					dynamic_cast<Human*>(target)->flatDefense -= 75;
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::ENHANCEDARMOR)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Oaken Armor II")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					std::cout << " " << target->name << " loses their Oaken Armor II!" << std::endl;
					dynamic_cast<Human*>(target)->flatDefense -= 100;
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::ENHANCEDARMOR)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Oaken Armor III")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					std::cout << " " << target->name << " loses their Oaken Armor III!" << std::endl;
					dynamic_cast<Human*>(target)->flatDefense -= 125;
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::ENHANCEDARMOR)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Nature's Bounty I")
			{
				target->healthPoints += effect->magnitude;
				std::cout << " " << target->name << " regains " << effect->magnitude << " health!" << std::endl;
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					std::cout << " " << target->name << " is no longer benefiting from Nature's Bounty I!" << std::endl;
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::HEALING)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Nature's Bounty II")
			{
				target->healthPoints += effect->magnitude;
				std::cout << " " << target->name << " regains " << effect->magnitude << " health!" << std::endl;
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					std::cout << " " << target->name << " is no longer benefiting from Nature's Bounty II!" << std::endl;
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::HEALING)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Fruit of the Earth I" || effect->name == "Fruit of the Earth II" || effect->name == "Fruit of the Earth III")
			{
				effect->duration -= 1;
				if (effect->duration == 0)
				{
					effectsToRemove.push_back(effect);
					for (int i = 0; i < target->combatFlags.size(); i++)
					{
						if (target->combatFlags[i] == Character::CombatFlags::HEALING)
						{
							target->combatFlags.erase(target->combatFlags.begin() + i);
						}
					}
				}
			}
			if (effect->name == "Force Burst I" || effect->name == "Force Burst II" || effect->name == "Force Burst III")
			{
				effectsToRemove.push_back(effect);
			}
		}
	}
	for (Effect* effect : effectsToRemove)
	{
		removeEffect(*target, *effect);
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

bool hasEffect(const Character* target, const std::string& effectName) {
	for (const Effect* effect : target->effects) {
		if (effect->name == effectName) {
			return true;
		}
	}
	return false;
}

void Effect::applyEffect(Effect* effect, Character* attacker, Character* target)
{
	if (effect->name == "Burn") {
		target->burnPoints += effect->getEffectDamage(target, *effect) + attacker->getFaith();
		if (!hasEffect(target, "Burn")) {
			Effect* burn = new Effect(true, true, "Burn", "The target is engulfed in flames causing damage each turn", PhysicalDamageType::NONE, MagicDamageType::FIRE,
				3, target->maxHealthPoints * 0.05f, false, 1, 1, false);
			burn->setMagicDamage(MagicDamageType::FIRE, target->maxHealthPoints * 0.05);
			target->combatFlags.push_back(Character::CombatFlags::BURNING);
			target->effects.push_back(burn);
		}
		if (target->burnPoints >= target->maxBurnPoints) {
			target->burnPoints = 0;
			if (!hasEffect(target, "Fear of Flames")) {
				Effect* fear = new Effect(true, true, "Fear of Flames", "Weaker targets are too terrified of the inferno that engulfs them to attack", PhysicalDamageType::NONE, MagicDamageType::FIRE,
					1.0f, 1.0f, false, 1, 1, false);
				target->effects.push_back(fear);
			}
		}
		return;
	}
	else if (effect->name == "Fear of Flames")
	{
		if (target->confidenceLevel <= 20 || target->healthPoints <= target->maxHealthPoints * 0.5 || target->level <= 5)
		{
			std::cout << dye::light_yellow(" " + target->name + " is too terrified to attack!") << std::endl;
			target->combatFlags.push_back(Character::CombatFlags::FEAR);
			return;
		}
		else
		{
			std::cout << " " + target->name + " withstands the flames and attacks!" << std::endl;
			return;
		}
	}
	else if (effect->name == "Poison")
	{
		target->poisonPoints += effect->getEffectDamage(target, *effect);
		if (target->poisonPoints >= target->maxPoisonPoints)
		{
			std::cout << dye::light_yellow(" " + target->name) << dye::light_green(" POISONED") << std::endl;
			target->poisonPoints = 0;
			target->combatFlags.push_back(Character::CombatFlags::POISONED);

			Effect* poison = new Effect(true, true, "Poison", "Putrid venom courses through their veins", PhysicalDamageType::NONE, MagicDamageType::POISON, 5, 0, true, 1, 5, false);
			bool poisonApplied = false;
			poison->setMagicDamage(MagicDamageType::POISON, target->maxHealthPoints * 0.05);
			for (Effect* effect : target->effects)
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
				target->effects.push_back(poison);
			}
		}
		return;
	}
	else if (effect->name == "Frost Burst")
	{
		target->frostPoints += effect->getEffectDamage(target, *effect) + attacker->getIntelligence();
		if (target->frostPoints >= target->maxFrostPoints)
		{
			target->frostPoints = 0;
			target->combatFlags.push_back(Character::CombatFlags::FROSTBITTEN);
			Effect* frostBite = new Effect(true, true, "Frost Burst", "The ice accumulating on the target explodes in a burst of frost!", PhysicalDamageType::NONE, MagicDamageType::FROST,
				1, target->maxHealthPoints * 0.2, false, 1, 1, false);
			frostBite->setMagicDamage(MagicDamageType::FROST, target->maxHealthPoints * 0.2);
			target->effects.push_back(frostBite);
		}
		return;
	}
	else if (effect->name == "Shock")
	{
		target->shockPoints += effect->getEffectDamage(target, *effect) + attacker->getIntelligence();
		if (target->shockPoints >= target->maxShockPoints)
		{
			target->shockPoints = 0;
			target->combatFlags.push_back(Character::CombatFlags::SHOCKED);
			Effect* shock = new Effect(true, true, "Shock", "The target is paralyzed by the electrical current, slowing their movements!", PhysicalDamageType::NONE, MagicDamageType::SHOCK,
				1, effect->getEffectDamage(target, *effect), false, 1, 1, false);
			shock->setMagicDamage(MagicDamageType::SHOCK, 0);
			target->effects.push_back(shock);
		}
		return;
	}
	else if (effect->name == "Blood Loss")
	{
		target->bleedPoints += effect->getEffectDamage(target, *effect) + attacker->getArcane();
		if (target->bleedPoints >= target->maxBleedPoints)
		{
			target->bleedPoints = 0;
			target->combatFlags.push_back(Character::CombatFlags::BLEEDING);
			Effect* bleed = new Effect(true, true, "Blood Loss", "The target is bleeding profusely, losing a percentage of their maximum health!", PhysicalDamageType::NONE, MagicDamageType::BLEED,
				1, target->maxHealthPoints * 0.1, false, 1, 1, false);
			bleed->setMagicDamage(MagicDamageType::BLEED, target->maxHealthPoints * 0.1);
			target->effects.push_back(bleed);
		}
		return;
	}
	else if (effect->name == "Sleep")
	{
		target->sleepPoints += effect->getEffectDamage(target, *effect);
		if (target->sleepPoints >= target->maxSleepPoints)
		{
			target->sleepPoints = 0;
			target->combatFlags.push_back(Character::CombatFlags::SLEEPY);
			Effect* sleep = new Effect(true, true, "Sleep", "The target has dozen off, unable to attack for one turn!", PhysicalDamageType::NONE, MagicDamageType::SLEEP,
				1, 1, false, 1, 1, false);
			sleep->setMagicDamage(MagicDamageType::SLEEP, 0);
			target->effects.push_back(sleep);
		}
		return;
	}
	else if (effect->name == "Fiery Explosion")
	{
		effect->setMagicDamage(MagicDamageType::FIRE, 25 + attacker->getFaith() * 0.5);
		if (target->isAlive)
		{
			std::cout << dye::light_yellow(" " + target->name) << " takes " << effect->getEffectDamage(target, *effect) << " points of splash damage!" << std::endl;
			target->healthPoints -= effect->getEffectDamage(target, *effect);
			if (target->healthPoints <= 0)
			{
				target->healthPoints = 0;
				target->killCharacter();
				return;
			}
		}
	}
	else if (effect->name == "Summon Vulture" && effect->applied == false)
	{
		effect->applied = true;
		Inventory inventory;
		inventory.backpackItems.push_back(new Item(true, "Vulture Feather", "A feather from a vulture", PhysicalDamageType::NONE, MagicDamageType::NONE, 30.0f, 0.1f, 3.0f, Item::EquipSlots::BACKPACK));
		std::cout << " A large vulture comes to aid " << dye::light_yellow(attacker->name) << " in combat!" << std::endl;
		Creature* vulture = new Creature(false, true, true, true, false, "Vulture", "A large vulture", 100.0f, 10.0f, 100.0f, 200.0f, 200.0f, 200.0f, 5.0f, 20.0f, 1.0f, 0.0f, 0.0f, 100.0f,
			100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, inventory, 5, Character::CombatFlags::NEUTRAL);
		std::cout << "Before insertion: " << typeid(*vulture).name() << " at " << vulture << std::endl;
		attacker->allies.push_back(vulture);
		std::cout << "After insertion: " << typeid(*attacker->allies.back()).name() << " at " << attacker->allies.back() << std::endl;

		return;
	}
	else if (effect->name == "Summon Wolf" && effect->applied == false)
	{
		effect->applied = true;
		Inventory inventory;
		inventory.backpackItems.push_back(new Item(true, "Wolf Pelt", "A pelt from a wolf", PhysicalDamageType::NONE, MagicDamageType::NONE, 150.0f, 0.5f, 1.0f, Item::EquipSlots::BACKPACK));
		std::cout << " A rugged wolf comes to aid " << dye::light_yellow(attacker->name) << " in combat!" << std::endl;
		attacker->allies.push_back(new Creature(false, true, true, true, false, "Wolf", "A rugged wolf", 150.0f, 20.0f, 100.0f, 300.0f, 300.0f, 250.0f, 10.0f, 30.0f, 1.0f, 5.0f, 10.0f, 100.0f, 100.0f, 100.0f,
			100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, inventory, 5.0f, Character::CombatFlags::NEUTRAL));
		return;
	}
	else if (effect->name == "Summon Bear" && effect->applied == false)
	{
		effect->applied = true;
		Inventory inventory;
		inventory.backpackItems.push_back(new Item(true, "Bear Pelt", "A pelt from a bear", PhysicalDamageType::NONE, MagicDamageType::NONE, 300.0f, 5.0f, 1.0f, Item::EquipSlots::BACKPACK));
		std::cout << " A mountain bear comes to aid " << dye::light_yellow(attacker->name) << " in combat!" << std::endl;
		attacker->allies.push_back(new Creature(false, true, true, true, false, "Bear", "A mountain bear", 250.0f, 30.0f, 200.0f, 400.0f, 400.0f, 150.0f, 10.0f, 5.0f, 1.0f, 30.0f, 100.0f, 100.0f,
			100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, inventory, 5.0f, Character::CombatFlags::NEUTRAL));
		return;
	}
	else if (effect->name == "Freeze 1")
	{
		effect->applied = true;
		if (target->level <= 5)
		{
			if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
			if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
		}
		else
		{
			std::cout << " " << dye::light_yellow(target->name) << " endures the cold!" << std::endl;
		}

	}
	else if (effect->name == "Freeze 2")
	{
		effect->applied = true;
		if (target->level <= 10)
		{
			if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
			if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
		}
		else
		{
			std::cout << " " << dye::light_yellow(target->name) << " endures the cold!" << std::endl;
		}
	}
	else if (effect->name == "Freeze 2")
	{
		effect->applied = true;
		if (target->level <= 20)
		{
			if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
			if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
		}
		else
		{
			std::cout << " " << dye::light_yellow(target->name) << " endures the cold!" << std::endl;
		}
	}
	else if (effect->name == "Oaken Armor I")
	{
		effect->applied = true;
		dynamic_cast<Human*>(target)->flatDefense += 75;
		std::cout << " " << dye::light_yellow(target->name) << " is protected by " << dye::light_green("Oaken Armor I") << "!" << std::endl;
		target->combatFlags.push_back(Character::CombatFlags::ENHANCEDARMOR);
		target->effects.push_back(new Effect(false, true, "Oaken Armor I", "The target is protected by a thin layer of magically strengthened wood", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		return;
	}
	else if (effect->name == "Oaken Armor II")
	{
		effect->applied = true;
		dynamic_cast<Human*>(target)->flatDefense += 100;
		std::cout << " " << dye::light_yellow(target->name) << " is protected by " << dye::light_green("Oaken Armor II") << "!" << std::endl;
		target->combatFlags.push_back(Character::CombatFlags::ENHANCEDARMOR);
		target->effects.push_back(new Effect(false, true, "Oaken Armor II", "The target is protected by a thin layer of magically strengthened wood", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		return;

	}
	else if (effect->name == "Oaken Armor III")
	{
		effect->applied = true;
		dynamic_cast<Human*>(target)->flatDefense += 125;
		std::cout << " " << dye::light_yellow(target->name) << " is protected by " << dye::light_green("Oaken Armor III") << "!" << std::endl;
		target->effects.push_back(new Effect(false, true, "Oaken Armor III", "The target is protected by a thin layer of magically strengthened wood", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		target->combatFlags.push_back(Character::CombatFlags::ENHANCEDARMOR);
		return;

	}
	else if (effect->name == "Nature's Bounty I")
	{
		effect->applied = true;
		target->combatFlags.push_back(Character::CombatFlags::HEALING);
		target->effects.push_back(new Effect(false, true, "Nature's Bounty I", "The target is healed by the magic of the forest", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 50, false, 1, 1, false));
		return;

	}
	else if (effect->name == "Nature's Bounty II")
	{
		effect->applied = true;
		target->combatFlags.push_back(Character::CombatFlags::HEALING);
		target->effects.push_back(new Effect(false, true, "Nature's Bounty II", "The target is healed greatly by the magic of the forest", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		return;


	}
	else if (effect->name == "Fruit of the Earth I")
	{
		effect->applied = true;
		target->healthPoints += effect->magnitude;
		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
		target->fatiguePoints += effect->magnitude / 4;
		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
		std::cout << " " << target->name << " is healed by the magic of the forest!" << std::endl;
		std::cout << " " << target->name << " has gained " << effect->magnitude << " health!" << std::endl;
		std::cout << " " << target->name << " has gained " << effect->magnitude / 4 << " fatigue!" << std::endl;
		return;
	}
	else if (effect->name == "Fruit of the Earth II")
	{
		effect->applied = true;
		target->healthPoints += effect->magnitude;
		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
		target->fatiguePoints += effect->magnitude / 4;
		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
		std::cout << " " << target->name << " is healed by the magic of the forest!" << std::endl;
		std::cout << " " << target->name << " has gained " << effect->magnitude << " health!" << std::endl;
		std::cout << " " << target->name << " has gained " << effect->magnitude / 4 << " fatigue!" << std::endl;
		return;
	}
	else if (effect->name == "Fruit of the Earth III")
	{
		effect->applied = true;
		target->healthPoints += effect->magnitude;
		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
		target->fatiguePoints += effect->magnitude / 4;
		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
		std::cout << " " << target->name << " is healed by the magic of the forest!" << std::endl;
		std::cout << " " << target->name << " has gained " << effect->magnitude << " health!" << std::endl;
		std::cout << " " << target->name << " has gained " << effect->magnitude / 4 << " fatigue!" << std::endl;
		return;

	}
	else if (effect->name == "Knockback I" || effect->name == "Knockback II" || effect->name == "Knockback III")
	{
		effect->applied = true;
		for (int i = 0; i < target->allies.size() + 1; i++)
		{
			if (target->distanceFromPlayer <= 10)
			{
				float knockback = magnitude;
				target->distanceFromPlayer += knockback;
				if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is hit by a" << dye::yellow(" FORCE BURST!") << std::endl;
				if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is launched backwards by " << knockback << " units!" << std::endl;
				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is hit by a" << dye::yellow(" FORCE BURST!") << std::endl;
				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is launched backwards by " << knockback << " units!" << std::endl;
				target->healthPoints -= effect->getEffectDamage(target, *effect);
				if (target->healthPoints <= 0)
				{
					target->healthPoints = 0;
					target->killCharacter();
				}
			}
			else
			{
				std::cout << " " << dye::light_yellow(target->name) << " is too far away to be affected by the force burst!" << std::endl;
			}
		}
	}
	else if (effect->name == "None")
	{
		return;
	}
	else
	{
		std::cout << "Invalid effect name" << std::endl;
	}
}