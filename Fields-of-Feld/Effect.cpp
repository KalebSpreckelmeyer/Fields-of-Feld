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
#include "Defense.h"
#include "Spell.h"
#include "Enchantment.h"
#include "LootItem.h"
#include "OffensiveEffect.h"
#include "ConsumableEffect.h"
#include "DefensiveEffect.h"
#include "PassiveEffect.h"

Effect::Effect(bool doesDamage, bool applied, std::string name, std::string description, float range, float duration,
	float magnitude, bool stackable, int stacks, int maxStacks, bool areaOfEffect)
	: name(name), description(description), duration(duration), magnitude(magnitude), stackable(stackable),
	stacks(stacks), maxStacks(maxStacks), areaOfEffect(areaOfEffect), range(range), doesDamage(doesDamage), applied(applied)
{
}

std::shared_ptr<Effect> Effect::fromJson(const nlohmann::json& j) {
	std::string type = j.at("type");

	//Offensive effects 
	if (type == "Bleed") return BleedEffect::fromJson(j);
	if (type == "Burn") return BurnEffect::fromJson(j);
	if (type == "Poison") return PoisonEffect::fromJson(j);
	if (type == "FrostBurst") return FrostBurstEffect::fromJson(j);
	if (type == "Shock") return ShockEffect::fromJson(j);
	if (type == "Sleep") return SleepEffect::fromJson(j);
	if (type == "Stun") return StunEffect::fromJson(j);
	if (type == "Knockback") return KnockbackEffect::fromJson(j);
	if (type == "Fear") return FearEffect::fromJson(j);
	if (type == "ArmorPenetration") return ArmorPenetrationEffect::fromJson(j);
	if (type == "Explosion") return ExplosionEffect::fromJson(j);
	//Passive Effects
	if (type == "FatigueBuff") return FatigueBuff::fromJson(j);
	if (type == "HealthBuff") return HealthBuff::fromJson(j);
	if (type == "CastSpeed") return CastSpeed::fromJson(j);
	if (type == "Summon") return Summon::fromJson(j);
	if (type == "ArmorBuff") return ArmorBuff::fromJson(j);
	if (type == "Healing") return Healing::fromJson(j);
	//Consumable Effects
	if (type == "RestoreHealth") return RestoreHealthEffect::fromJson(j);
	if (type == "RestoreFatigue") return RestoreFatigueEffect::fromJson(j);
	if (type == "MaxHealth") return MaxHealthEffect::fromJson(j);
	if (type == "MaxFatigue") return MaxFatigueEffect::fromJson(j);
	if (type == "HealthRegen") return HealthRegenEffect::fromJson(j);
	if (type == "FatigueRegen") return FatigueRegenEffect::fromJson(j);
	if (type == "AttackSpeed") return AttackSpeedEffect::fromJson(j);
	if (type == "CastSpeed") return CastSpeedEffect::fromJson(j);
	if (type == "Speed") return SpeedEffect::fromJson(j);
	if (type == "BlockChance") return BlockChanceEffect::fromJson(j);
	if (type == "DodgeChance") return DodgeChanceEffect::fromJson(j);
	if (type == "CritChance") return CritChanceEffect::fromJson(j);
	if (type == "Resistance") return ResistanceEffect::fromJson(j);
	if (type == "Escape") return EscapeEffect::fromJson(j);
	if (type == "Resurrect") return ResurrectEffect::fromJson(j);
	if (type == "Attribute") return AttributeEffect::fromJson(j);
	if (type == "Random") return RandomEffect::fromJson(j);
	//Defensive Effects
	if (type == "Thorns") return ThornsEffect::fromJson(j);
	if (type == "Aura") return AuraEffect::fromJson(j);

	throw std::runtime_error("Unknown effect type: " + type);
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

float Effect::getEffectDamage(std::shared_ptr<Character> target, std::shared_ptr<Effect> effect)
{
	//Target is human
	if (std::dynamic_pointer_cast<Human>(target))
	{
		std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(target);
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

		for (std::shared_ptr<Item> item : target->inventory.equippedItems)
		{
			if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item))
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

		cumulativeSlashResist = max(cumulativeSlashResist, 0.0f);
		cumulativePierceResist = max(cumulativePierceResist, 0.0f);
		cumulativeBluntResist = max(cumulativeBluntResist, 0.0f);
		cumulativeChopResist = max(cumulativeChopResist, 0.0f);

		cumulativeMagicResist = max(cumulativeMagicResist, 0.0f);
		cumulativeFireResist = max(cumulativeFireResist, 0.0f);
		cumulativeIceResist = max(cumulativeIceResist, 0.0f);
		cumulativeShockResist = max(cumulativeShockResist, 0.0f);
		cumulativePoisonResist = max(cumulativePoisonResist, 0.0f);
		cumulativeBleedResist = max(cumulativeBleedResist, 0.0f);
		cumulativeSleepResist = max(cumulativeSleepResist, 0.0f);
		cumulativeDarkResist = max(cumulativeDarkResist, 0.0f);
		cumulativeHolyResist = max(cumulativeHolyResist, 0.0f);
		cumulativeWindResist = max(cumulativeWindResist, 0.0f);

		//damage = damage - (damage * (resistance / 500)) - max won't let it go below 0
		float cumulativeSlashDamage = effect->getPhysicalDamage(PhysicalDamageType::SLASH) - (effect->getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = effect->getPhysicalDamage(PhysicalDamageType::PIERCE) - (effect->getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = effect->getPhysicalDamage(PhysicalDamageType::BLUNT) - (effect->getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = effect->getPhysicalDamage(PhysicalDamageType::CHOP) - (effect->getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = effect->getMagicDamage(MagicDamageType::MAGIC) - (effect->getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = effect->getMagicDamage(MagicDamageType::FIRE) - (effect->getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = effect->getMagicDamage(MagicDamageType::FROST) - (effect->getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = effect->getMagicDamage(MagicDamageType::SHOCK) - (effect->getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = effect->getMagicDamage(MagicDamageType::POISON) - (effect->getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = effect->getMagicDamage(MagicDamageType::BLEED) - (effect->getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = effect->getMagicDamage(MagicDamageType::SLEEP) - (effect->getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = effect->getMagicDamage(MagicDamageType::DARK) - (effect->getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = effect->getMagicDamage(MagicDamageType::HOLY) - (effect->getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = effect->getMagicDamage(MagicDamageType::WIND) - (effect->getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float effectDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
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

//void Effect::refreshEffects(std::shared_ptr<Character> target)
//{
//	if (target->effects.empty()) return;
//	std::vector<std::shared_ptr<Effect>> effectsToRemove;
//
//	for (const auto& effect : target->effects)
//	{
//		if (effect == nullptr)
//		{
//			std::cout << "ERROR EFFECT IS NULL IN REFRESHEFFECTS" << std::endl;
//		}
//		else
//		{
//			if (effect->name == "Poison")
//			{
//				if (!target->isAlive) return;
//				for (int i = 0; i < effect->stacks; i++)
//				{
//					if (target->namedCharacter) std::cout << " " + target->name + " takes " << target->maxHealthPoints * 0.05 << dye::light_green(" poison ") << "damage!" << std::endl;
//					if (!target->namedCharacter) std::cout << " The " + target->name + " takes " << target->maxHealthPoints * 0.05 << dye::light_green(" poison ") << "damage!" << std::endl;
//					target->healthPoints -= target->maxHealthPoints * 0.05;
//					if (target->healthPoints <= 0)
//					{
//						target->healthPoints = 0;
//						target->killCharacter();
//						return;
//					}
//				}
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::POISONED)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Burn")
//			{
//				if (!target->isAlive) return;
//				float burnDamage = effect->getEffectDamage(target, effect);
//
//				if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " is " << dye::light_red("BURNED") <<
//					" for " << burnDamage << " points of damage!" << std::endl;
//				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_red("BURNED") <<
//					" for " << burnDamage << " points of damage!" << std::endl;
//				target->healthPoints -= burnDamage;
//				if (target->healthPoints <= 0)
//				{
//					target->healthPoints = 0;
//					target->killCharacter();
//					return;
//				}
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::BURNING)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Fear of Flames")
//			{
//				if (target->isAlive)
//				{
//					if (target->confidenceLevel <= 20 || target->healthPoints <= target->maxHealthPoints * 0.5 || target->level <= 5)
//					{
//						if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name + " is too terrified of the flames to attack!") << std::endl;
//						if (!target->namedCharacter) std::cout << " The " + target->name + " is too terrified of the flames to attack!" << std::endl;
//						target->combatFlag = Character::CombatFlags::FEAR;
//					}
//					else
//					{
//						std::cout << " " + target->name + " withstands the flames and attacks!" << std::endl;
//					}
//				}
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::FEAR)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Frost Burst")
//			{
//				if (target->isAlive)
//				{
//					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " suffers a" << dye::light_aqua(" FROST BURST!") <<
//						" and takes " << effect->getEffectDamage(target, effect) << " points of damage!" << std::endl;
//					if (!target->namedCharacter) std::cout << " The " << target->name << " suffers a" << dye::light_aqua(" FROST BURST!") <<
//						" and takes " << effect->getEffectDamage(target, effect) << " points of damage!" << std::endl;
//					target->healthPoints -= effect->getEffectDamage(target, effect);
//					if (target->healthPoints <= 0)
//					{
//						target->healthPoints = 0;
//						target->killCharacter();
//						return;
//					}
//				}
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::FROSTBITTEN)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Shock")
//			{
//				if (target->isAlive)
//				{
//					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " suffers an" << dye::light_purple(" ELECTROCUTION!") <<
//						" and takes " << effect->getEffectDamage(target, effect) << " points of damage!" << std::endl;
//					std::cout << dye::light_yellow(" " + target->name) << "'s movements are slowed!" << std::endl;
//					if (!target->namedCharacter) std::cout << " The " << target->name << " suffers an" << dye::light_purple(" ELECTROCUTION!") <<
//						" and takes " << effect->getEffectDamage(target, effect) << " points of damage!" << std::endl;
//					target->speed -= effect->getEffectDamage(target, effect);
//					if (target->speed < 0) target->speed = 0;
//					target->healthPoints -= effect->getEffectDamage(target, effect);
//					if (target->healthPoints <= 0)
//					{
//						target->healthPoints = 0;
//						target->killCharacter();
//						return;
//					}
//				}
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::SHOCKED)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Blood Loss")
//			{
//				
//			}
//			if (effect->name == "Sleep")
//			{
//				if (target->isAlive)
//				{
//					if (target->namedCharacter) std::cout << dye::light_yellow(" " + target->name) << " is" << dye::light_blue(" ASLEEP!") << std::endl;
//					if (!target->namedCharacter) std::cout << " The " << target->name << " is" << dye::light_blue(" ASLEEP!") << std::endl;
//					target->combatFlag = Character::CombatFlags::SLEEPY;
//				}
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::SLEEPY)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			//deal damage to all allies
//			if (effect->name == "Fiery Explosion")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//				}
//			}
//			//decrement duration of summoned animals, remove them if necessary
//			if (effect->name == "Summon Cooldown")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//					std::vector<std::shared_ptr<Character>> alliesToRemove;
//					for (int i = 0; i < target->allies.size(); i++)
//					{
//						if (target->allies[i]->name == "Bear" || target->allies[i]->name == "Vulture" || target->allies[i]->name == "Wolf")
//						{
//							std::cout << " " << target->allies[i]->name << " has left the battlefield!" << std::endl;
//							int j = i;
//							alliesToRemove.push_back(target->allies[i]);
//						}
//					}
//					for (int i = 0; i < alliesToRemove.size(); i++)
//					{
//						for (std::shared_ptr<Character> ally : target->allies)
//						{
//							if (ally->name == alliesToRemove[i]->name)
//							{
//								target->allies.erase(std::remove(target->allies.begin(), target->allies.end(), ally), target->allies.end());
//								ally = nullptr;
//								return;
//							}
//						}
//					}
//				}
//			}
//			if (effect->name == "Freeze 1" || effect->name == "Freeze 2" || effect->name == "Freeze 3")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::FROZEN)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Oaken Armor I")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					std::cout << " " << target->name << " loses their Oaken Armor I!" << std::endl;
//					target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) - 75);
//					target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) - 75);
//					target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) - 75);
//					target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) - 75);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::ENHANCEDARMOR)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Oaken Armor II")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					std::cout << " " << target->name << " loses their Oaken Armor II!" << std::endl;
//					target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT)  - 100);
//					target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE)  - 100);
//					target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH)  - 100);
//					target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP)  - 100);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::ENHANCEDARMOR)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Oaken Armor III")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					std::cout << " " << target->name << " loses their Oaken Armor III!" << std::endl;
//					target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) - 150);
//					target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) - 150);
//					target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) - 150);
//					target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) - 150);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::ENHANCEDARMOR)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Nature's Bounty I")
//			{
//				target->healthPoints += effect->magnitude;
//				std::cout << " " << target->name << " regains " << effect->magnitude << " health!" << std::endl;
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					std::cout << " " << target->name << " is no longer benefiting from Nature's Bounty I!" << std::endl;
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::HEALING)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Nature's Bounty II")
//			{
//				target->healthPoints += effect->magnitude;
//				std::cout << " " << target->name << " regains " << effect->magnitude << " health!" << std::endl;
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					std::cout << " " << target->name << " is no longer benefiting from Nature's Bounty II!" << std::endl;
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::HEALING)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Fruit of the Earth I" || effect->name == "Fruit of the Earth II" || effect->name == "Fruit of the Earth III")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effectsToRemove.push_back(effect);
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::HEALING)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//				}
//			}
//			if (effect->name == "Force Burst I" || effect->name == "Force Burst II" || effect->name == "Force Burst III")
//			{
//				effectsToRemove.push_back(effect);
//			}
//			if (effect->name == "Armor Penetration")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					for (int i = 0; i < target->inventory.equippedItems.size(); i++)
//					{
//						if (std::dynamic_pointer_cast<std::shared_ptr<Armor>>(target->inventory.equippedItems[i]))
//						{
//							std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(target->inventory.equippedItems[i]);
//							armor->setPhysicalResistance(PhysicalDamageType::BLUNT, armor->getPhysicalResistance(PhysicalDamageType::BLUNT) + effect->magnitude);
//							armor->setPhysicalResistance(PhysicalDamageType::PIERCE, armor->getPhysicalResistance(PhysicalDamageType::PIERCE) + effect->magnitude);
//							armor->setPhysicalResistance(PhysicalDamageType::SLASH, armor->getPhysicalResistance(PhysicalDamageType::SLASH) + effect->magnitude);
//							armor->setPhysicalResistance(PhysicalDamageType::CHOP, armor->getPhysicalResistance(PhysicalDamageType::CHOP) + effect->magnitude);
//						}
//					}
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Magic Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Fire Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Frost Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Shock Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Poison Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Bleed Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Sleep Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Wind Weapon")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Slowdown")
//			{
//				effect->duration -= 1;
//				if (effect->duration == 0)
//				{
//					target->speed += effect->magnitude;
//					std::cout << " " << target->name << " regains " << effect->magnitude << " speed!" << std::endl;
//					effect->applied = false;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Health Regen")
//			{
//				std::cout << " " << target->name << " regains " << effect->magnitude << " health!" << std::endl;
//				target->healthPoints += effect->magnitude;
//				duration -= 1;
//				if (duration == 0)
//				{
//					effect->applied = false;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Fatigue Regen")
//			{
//				std::cout << " " << target->name << " regains " << effect->magnitude << " fatigue!" << std::endl;
//				target->fatiguePoints += effect->magnitude;
//				duration -= 1;
//				if (duration == 0)
//				{
//					effect->applied = false;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Attack Speed")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					std::shared_ptr<Weapon> mainHand = nullptr;
//					std::shared_ptr<Weapon> offHand = nullptr;
//					std::shared_ptr<Weapon> reserve1 = nullptr;
//					std::shared_ptr<Weapon> reserve2 = nullptr;
//					target->inventory.getEquippedWeapons(mainHand, offHand, reserve1, reserve2);
//					if (mainHand != nullptr) mainHand->attackSpeed -= effect->magnitude;
//					if (offHand != nullptr) offHand->attackSpeed -= effect->magnitude;
//					if (reserve1 != nullptr) reserve1->attackSpeed -= effect->magnitude;
//					if (reserve2 != nullptr) reserve2->attackSpeed -= effect->magnitude;
//					effectsToRemove.push_back(effect);
//				}	
//			}
//			if (effect->name == "Cast Speed")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target))
//						std::dynamic_pointer_cast<Human>(target)->castSpeed -= effect->magnitude;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Speed")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->speed -= effect->magnitude;
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Physical Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->speed -= effect->magnitude;
//					target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) - effect->magnitude);
//					target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) - effect->magnitude);
//					target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) - effect->magnitude);
//					target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) - effect->magnitude);
//					effectsToRemove.push_back(effect);
//				}
//			}
//			if (effect->name == "Magic Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::MAGIC, target->getDefenseValue(Defense::MAGIC) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Fire Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::FIRE, target->getDefenseValue(Defense::FIRE) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Frost Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::FROST, target->getDefenseValue(Defense::FROST) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Shock Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::SHOCK, target->getDefenseValue(Defense::SHOCK) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Wind Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::WIND, target->getDefenseValue(Defense::WIND) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Poison Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::POISON, target->getDefenseValue(Defense::POISON) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Bleed Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::BLEED, target->getDefenseValue(Defense::BLEED) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Sleep Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::SLEEP, target->getDefenseValue(Defense::SLEEP) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Dark Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::DARK, target->getDefenseValue(Defense::DARK) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Holy Resistance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::HOLY, target->getDefenseValue(Defense::HOLY) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "All Resistances")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) - effect->magnitude);
//					target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) - effect->magnitude);
//					target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) - effect->magnitude);
//					target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) - effect->magnitude);
//					target->setDefenseValue(Defense::MAGIC, target->getDefenseValue(Defense::MAGIC) - effect->magnitude);
//					target->setDefenseValue(Defense::FIRE, target->getDefenseValue(Defense::FIRE) - effect->magnitude);
//					target->setDefenseValue(Defense::FROST, target->getDefenseValue(Defense::FROST) - effect->magnitude);
//					target->setDefenseValue(Defense::SHOCK, target->getDefenseValue(Defense::SHOCK) - effect->magnitude);
//					target->setDefenseValue(Defense::POISON, target->getDefenseValue(Defense::POISON) - effect->magnitude);
//					target->setDefenseValue(Defense::BLEED, target->getDefenseValue(Defense::BLEED) - effect->magnitude);
//					target->setDefenseValue(Defense::SLEEP, target->getDefenseValue(Defense::SLEEP) - effect->magnitude);
//					target->setDefenseValue(Defense::WIND, target->getDefenseValue(Defense::WIND) - effect->magnitude);
//					target->setDefenseValue(Defense::DARK, target->getDefenseValue(Defense::DARK) - effect->magnitude);
//					target->setDefenseValue(Defense::HOLY, target->getDefenseValue(Defense::HOLY) - effect->magnitude);
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Block Chance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->blockChance -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Dodge Chance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->dodgeChance -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Critical Chance")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->critChance -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Escape")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::CANESCAPE)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Strength")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->strength -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Agility")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->agility -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Intelligence")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->intelligence -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Faith")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->faith -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Arcane")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->arcane -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Charisma")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->charisma -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Luck")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->luck -= effect->magnitude;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Resurrect")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					for (int i = 0; i < target->combatFlags.size(); i++)
//					{
//						if (target->combatFlags[i] == Character::CombatFlags::RESURRECTED)
//						{
//							target->combatFlags.erase(target->combatFlags.begin() + i);
//						}
//					}
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Random I")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->healthPoints -= effect->magnitude;
//					if (target->healthPoints < 1) target->healthPoints = 1;
//					effect->removeEffect(target, *effect);
//				}
//			}
//			if (effect->name == "Random II")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//
//					target->fatiguePoints -= effect->magnitude;
//					if (target->fatiguePoints < 1) target->fatiguePoints = 1;
//					effect->removeEffect(target, *effect);
//				
//				}
//			}
//			if (effect->name == "Random III")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->fatiguePoints += effect->magnitude;
//					if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
//					effect->removeEffect(target, *effect);
//					break;
//				}
//			}
//			if (effect->name == "Random IV")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					target->healthPoints += effect->magnitude;
//					if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
//					effect->removeEffect(target, *effect);
//					break;
//				}
//			}
//			if (effect->name == "Random V")
//			{
//				duration -= 1;
//				if (duration == 0)
//				{
//					effect->removeEffect(target, *effect);
//					break;
//				}
//			}
//		}
//	}
//	for (std::shared_ptr<Effect> effect : effectsToRemove)
//	{
//		deleteEffect(target, *effect);
//	}
//}

void Effect::deleteEffect(std::shared_ptr<Character> target, Effect& effectToDelete) {
	for (std::shared_ptr<Effect> effect : target->effects)
	{
		if (effect->name == effectToDelete.name)
		{
			target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), effect), target->effects.end());
			effect = nullptr;
			return;
		}
	}
}

void Effect::removeEffect(std::shared_ptr<Character> target, Effect& effectToRemove)
{
	for (std::shared_ptr<Effect> effect : target->effects)
	{
		if (effect == nullptr) return;
		if (effect->name == "Fatigue Buff")
		{
			target->fatiguePoints -= effect->magnitude;
			target->maxFatiguePoints -= effect->magnitude;
		}
		if (effect->name == "Cast Speed")
		{
			if (std::dynamic_pointer_cast<Human>(target))
				std::dynamic_pointer_cast<Human>(target)->castSpeed -= effect->magnitude;
		}
		if (effect->name == effectToRemove.name)
		{
			target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), effect), target->effects.end());
			effect = nullptr;
			return;
		}
	}
}
bool hasEffect(const std::shared_ptr<Character> target, const std::string& effectName) {
	for (const std::shared_ptr<Effect> effect : target->effects) {
		if (effect->name == effectName) {
			return true;
		}
	}
	return false;
}

//void Effect::applyDefensiveEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> wielder, std::shared_ptr<Character> attacker)
//{
//	if (effect == nullptr) return;
//	if (effect->name == "Shocking Thorns")
//	{
//		
//	}
//	if (effect->name == "Blood Splash")
//	{
//		if (attacker->position[wielder->getId()] <= effect->range)
//		{
//			attacker->bleedPoints += effect->getEffectDamage(attacker, effect);
//			if (attacker->namedCharacter) std::cout << dye::light_yellow(" " + attacker->name) << " is coated in " << dye::light_red("blood") <<
//				" from an enchantment on " << wielder->name << "'s armor and takes " << effect->getEffectDamage(attacker, effect) << " points of blood buildup!" << std::endl;
//			if (!attacker->namedCharacter) std::cout << dye::light_yellow(" The " + attacker->name) << " is coated in " << dye::light_red("blood") <<
//				" from an enchantment on " << wielder->name << "'s armor and takes " << effect->getEffectDamage(attacker, effect) << " points of blood buildup!" << std::endl;
//			effect->removeEffect(attacker, *effect);
//			if (attacker->bleedPoints >= attacker->maxBleedPoints)
//			{
//				attacker->bleedPoints = 0;
//				attacker->combatFlags.push_back(Character::CombatFlags::BLEEDING);
//				std::shared_ptr<Effect> bleed = std::make_shared<Effect>(true, true, "Blood Loss", "The attacker is bleeding profusely, losing a percentage of their maximum health!",
//					0.0f, 1, attacker->maxHealthPoints * 0.1, false, 1, 1, false);
//				bleed->setMagicDamage(MagicDamageType::BLEED, attacker->maxHealthPoints * 0.1);
//				attacker->effects.push_back(bleed);
//			}
//		}
//	}
//	if (effect->name == "Frost Armor")
//	{
//		if (attacker->position[wielder->getId()] <= effect->range)
//		{
//			attacker->frostPoints += effect->getEffectDamage(attacker, effect);
//			if (attacker->namedCharacter) std::cout << dye::light_yellow(" " + attacker->name) << " is affected by the" << dye::light_aqua(" frigid air") <<
//				" from an enchantment on " << wielder->name << "'s armor and takes " << effect->getEffectDamage(attacker, effect) << " points of frost buildup!" << std::endl;
//			if (attacker->namedCharacter) std::cout << dye::light_yellow(" " + attacker->name) << " is affected by the" << dye::light_aqua(" frigid air") <<
//				" from an enchantment on " << wielder->name << "'s armor and has their speed slowed by " << effect->magnitude / 2.0f << " points!" << std::endl;
//			if (!attacker->namedCharacter) std::cout << " The " << attacker->name << " is affected by the" << dye::light_aqua(" frigid air") <<
//				" from an enchantment on " << wielder->name << "'s armor and takes " << effect->getEffectDamage(attacker, effect) << " points of frost buildup!" << std::endl;
//			if (!attacker->namedCharacter) std::cout << " The " << attacker->name << " is affected by the" << dye::light_aqua(" frigid air") <<
//				" from an enchantment on " << wielder->name << "'s armor and has their speed slowed by " << effect->magnitude / 2.0f << " points!" << std::endl;
//			effect->removeEffect(attacker, *effect);
//			if (attacker->frostPoints >= attacker->maxFrostPoints)
//			{
//				attacker->frostPoints = 0;
//				attacker->combatFlags.push_back(Character::CombatFlags::FROSTBITTEN);
//				std::shared_ptr<Effect> frostBite = std::make_shared<Effect>(true, true, "Frost Burst", "The ice accumulating on the target explodes in a burst of frost!", 
//					0.0f, 1, attacker->maxHealthPoints * 0.2, false, 1, 1, false);
//				std::shared_ptr<Effect> slowdown = std::make_shared<Effect>(true, false, "Slowdown", "The target is slowed by the frost accumulating on them", 
//					0.0f, 3, effect->magnitude / 2.0f, false, 1, 1, false);
//				frostBite->setMagicDamage(MagicDamageType::FROST, attacker->maxHealthPoints * 0.2);
//				attacker->effects.push_back(frostBite);
//				attacker->effects.push_back(slowdown);
//			}
//		}
//	}
//}
//void Effect::applyOffensiveEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> attacker, std::shared_ptr<Character> target)
//{
//	if (effect == nullptr) return;
//
//	//SPELLS
//	if (effect->name == "Burn") {
//		effect->removeEffect(target, *effect);
//		target->burnPoints += effect->getEffectDamage(target, effect) + attacker->getFaith();
//		if (!hasEffect(target, "Burn")) {
//			std::shared_ptr<Effect> burn = std::make_shared<Effect>(true, true, "Burn", "The target is engulfed in flames causing damage each turn", 
//				0.0f, 3, target->maxHealthPoints * 0.05f, false, 1, 1, false);
//			burn->setMagicDamage(MagicDamageType::FIRE, target->maxHealthPoints * 0.05);
//			target->combatFlags.push_back(Character::CombatFlags::BURNING);
//			target->effects.push_back(burn);
//		}
//		if (target->burnPoints >= target->maxBurnPoints) {
//			target->burnPoints = 0;
//			if (!hasEffect(target, "Fear of Flames")) {
//				std::shared_ptr<Effect> fear = std::make_shared<Effect>(true, true, "Fear of Flames", "Weaker targets are too terrified of the inferno that engulfs them to attack", 
//					0.0f, 1.0f, 1.0f, false, 1, 1, false);
//				target->effects.push_back(fear);
//			}
//		}
//		return;
//	}
//	else if (effect->name == "Fear of Flames")
//	{
//		effect->removeEffect(target, *effect);
//		if (target->confidenceLevel <= 20 || target->healthPoints <= target->maxHealthPoints * 0.5 || target->level <= 5)
//		{
//			std::cout << dye::light_yellow(" " + target->name + " is too terrified to attack!") << std::endl;
//			target->combatFlags.push_back(Character::CombatFlags::FEAR);
//			return;
//		}
//		else
//		{
//			std::cout << " " + target->name + " withstands the flames and attacks!" << std::endl;
//			return;
//		}
//	}
//	else if (effect->name == "Poison")
//	{
//		target->poisonPoints += effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//		if (target->poisonPoints >= target->maxPoisonPoints)
//		{
//			std::cout << dye::light_yellow(" " + target->name) << dye::light_green(" POISONED") << std::endl;
//			target->poisonPoints = 0;
//			target->combatFlags.push_back(Character::CombatFlags::POISONED);
//
//			std::shared_ptr<Effect> poison = std::make_shared<Effect>(true, true, "Poison", "Putrid venom courses through their veins", 0.0f, 5, 0, true, 1, 5, false);
//			bool poisonApplied = false;
//			poison->setMagicDamage(MagicDamageType::POISON, target->maxHealthPoints * 0.05);
//			for (std::shared_ptr<Effect> effect : target->effects)
//			{
//				if (effect->name == "Poison")
//				{
//					effect->stacks = min(effect->stacks + 1, effect->maxStacks);
//					poisonApplied = true;
//					break;
//				}
//			}
//			if (!poisonApplied)
//			{
//				target->effects.push_back(poison);
//			}
//		}
//		return;
//	}
//	else if (effect->name == "Frost Burst")
//	{
//		target->frostPoints += effect->getEffectDamage(target, effect) + attacker->getIntelligence();
//		effect->removeEffect(target, *effect);
//		if (target->frostPoints >= target->maxFrostPoints)
//		{
//			target->frostPoints = 0;
//			target->combatFlags.push_back(Character::CombatFlags::FROSTBITTEN);
//			std::shared_ptr<Effect> frostBite = std::make_shared<Effect>(true, true, "Frost Burst", "The ice accumulating on the target explodes in a burst of frost!", 
//				0.0f, 1, target->maxHealthPoints * 0.2, false, 1, 1, false);
//			frostBite->setMagicDamage(MagicDamageType::FROST, target->maxHealthPoints * 0.2);
//			target->effects.push_back(frostBite);
//		}
//		return;
//	}
//	else if (effect->name == "Shock")
//	{
//		target->shockPoints += effect->getEffectDamage(target, effect) + attacker->getIntelligence();
//		effect->removeEffect(target, *effect);
//		if (target->shockPoints >= target->maxShockPoints)
//		{
//			target->shockPoints = 0;
//			target->combatFlags.push_back(Character::CombatFlags::SHOCKED);
//			std::shared_ptr<Effect> shock = std::make_shared<Effect>(true, true, "Shock", "The target is paralyzed by the electrical current, slowing their movements!", 
//				0.0f, 1, effect->getEffectDamage(target, effect), false, 1, 1, false);
//			shock->setMagicDamage(MagicDamageType::SHOCK, 0);
//			target->effects.push_back(shock);
//		}
//		return;
//	}
//	else if (effect->name == "Blood Loss")
//	{
//		target->bleedPoints += effect->getEffectDamage(target, effect) + attacker->getArcane();
//		effect->removeEffect(target, *effect);
//		if (target->bleedPoints >= target->maxBleedPoints)
//		{
//			target->bleedPoints = 0;
//			target->combatFlags.push_back(Character::CombatFlags::BLEEDING);
//			std::shared_ptr<Effect> bleed = std::make_shared<Effect>(true, true, "Blood Loss", "The target is bleeding profusely, losing a percentage of their maximum health!", 
//				0.0f, 1, target->maxHealthPoints * 0.1, false, 1, 1, false);
//			bleed->setMagicDamage(MagicDamageType::BLEED, target->maxHealthPoints * 0.1);
//			target->effects.push_back(bleed);
//		}
//		return;
//	}
//	else if (effect->name == "Sleep")
//	{
//		target->sleepPoints += effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//		if (target->sleepPoints >= target->maxSleepPoints)
//		{
//			target->sleepPoints = 0;
//			target->combatFlags.push_back(Character::CombatFlags::SLEEPY);
//			std::shared_ptr<Effect> sleep = std::make_shared<Effect>(true, true, "Sleep", "The target has dozen off, unable to attack for one turn!",
//				0.0f, 1, 1, false, 1, 1, false);
//			sleep->setMagicDamage(MagicDamageType::SLEEP, 0);
//			target->effects.push_back(sleep);
//		}
//		return;
//	}
//	else if (effect->name == "Fiery Explosion")
//	{
//		effect->setMagicDamage(MagicDamageType::FIRE, 25 + attacker->getFaith() * 0.5);
//		effect->removeEffect(target, *effect);
//		if (target->isAlive)
//		{
//			std::cout << dye::light_yellow(" " + target->name) << " takes " << effect->getEffectDamage(target, effect) << " points of splash damage!" << std::endl;
//			target->healthPoints -= effect->getEffectDamage(target, effect);
//			if (target->healthPoints <= 0)
//			{
//				target->healthPoints = 0;
//				target->killCharacter();
//				return;
//			}
//		}
//	}
//	else if (effect->name == "Freeze 1")
//	{
//		effect->applied = true;
//		effect->removeEffect(target, *effect);
//		if (target->level <= 5)
//		{
//			if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
//			if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
//			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
//		}
//		else
//		{
//			std::cout << " " << dye::light_yellow(target->name) << " endures the cold!" << std::endl;
//		}
//
//	}
//	else if (effect->name == "Freeze 2")
//	{
//		effect->applied = true;
//		effect->removeEffect(target, *effect);
//		if (target->level <= 10)
//		{
//			if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
//			if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
//			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
//		}
//		else
//		{
//			std::cout << " " << dye::light_yellow(target->name) << " endures the cold!" << std::endl;
//		}
//	}
//	else if (effect->name == "Freeze 2")
//	{
//		effect->applied = true;
//		effect->removeEffect(target, *effect);
//		if (target->level <= 20)
//		{
//			if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
//			if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is " << dye::light_aqua("frozen") << " solid!" << std::endl;
//			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
//		}
//		else
//		{
//			std::cout << " " << dye::light_yellow(target->name) << " endures the cold!" << std::endl;
//		}
//	}
//	else if (effect->name == "Knockback I" || effect->name == "Knockback II" || effect->name == "Knockback III")
//	{
//		effect->applied = true;
//		for (int i = 0; i < target->allies.size(); i++)
//		{
//			if (target->position[attacker->getId()] <= effect->range)
//			{
//				float knockback = magnitude;
//				target->position[attacker->getId()] += knockback;
//				if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is hit by a" << dye::yellow(" FORCE BURST!") << std::endl;
//				if (target->namedCharacter) std::cout << " " << dye::light_yellow(target->name) << " is launched backwards by " << knockback << " units!" << std::endl;
//				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is hit by a" << dye::yellow(" FORCE BURST!") << std::endl;
//				if (!target->namedCharacter) std::cout << " The " << dye::light_yellow(target->name) << " is launched backwards by " << knockback << " units!" << std::endl;
//				target->healthPoints -= effect->getEffectDamage(target, effect);
//				effect->removeEffect(target, *effect);
//				if (target->healthPoints <= 0)
//				{
//					target->healthPoints = 0;
//					target->killCharacter();
//					return;
//				}
//			}
//			else
//			{
//				std::cout << " " << dye::light_yellow(target->name) << " is too far away to be affected by the force burst!" << std::endl;
//				effect->removeEffect(target, *effect);
//			}
//		}
//	}
//	//WEAPONS
//	else if (effect->name == "Armor Penetration")
//	{
//		effect->applied = true;
//		for (int i = 0; i < target->inventory.equippedItems.size(); i++)
//		{
//			if (std::dynamic_pointer_cast<std::shared_ptr<Armor>>(target->inventory.equippedItems[i]))
//			{
//				std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(target->inventory.equippedItems[i]);
//				armor->setPhysicalResistance(PhysicalDamageType::BLUNT, armor->getPhysicalResistance(PhysicalDamageType::BLUNT) - effect->magnitude);
//				armor->setPhysicalResistance(PhysicalDamageType::PIERCE, armor->getPhysicalResistance(PhysicalDamageType::PIERCE) - effect->magnitude);
//				armor->setPhysicalResistance(PhysicalDamageType::SLASH, armor->getPhysicalResistance(PhysicalDamageType::SLASH) - effect->magnitude);
//				armor->setPhysicalResistance(PhysicalDamageType::CHOP, armor->getPhysicalResistance(PhysicalDamageType::CHOP) - effect->magnitude);
//				std::cout << " " << target->name << "'s armor is weakened by " << effect->magnitude << " points!" << std::endl;
//			}
//		}
//	}
//	else if (effect->name == "Magic Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of magic damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//	}
//	else if (effect->name == "Fire Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of fire damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//	}
//	else if (effect->name == "Frost Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of frost damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//		}
//	else if (effect->name == "Shock Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of shock damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//		}
//	else if (effect->name == "Poison Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of poison damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//		}
//	else if (effect->name == "Bleed Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of bleed damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//		}
//	else if (effect->name == "Sleep Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of sleep damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//	}
//	else if (effect->name == "Wind Damage")
//	{
//		effect->applied = true;
//		std::cout << " " << target->name << " takes " << effect->getEffectDamage(target, effect) << " points of wind damage!" << std::endl;
//		target->healthPoints -= effect->getEffectDamage(target, effect);
//		effect->removeEffect(target, *effect);
//	}
//	else if (effect->name == "None")
//	{
//		return;
//	}
//	else
//	{
//		std::cout << "Invalid effect name" << std::endl;
//	}
//}
//void Effect::applyPassiveEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> target)
//{
//	if (effect == nullptr) return;
//	if (effect->name == "Fatigue Buff")
//	{
//		effect->applied = true;
//		target->maxFatiguePoints += effect->magnitude;
//		target->fatiguePoints += effect->magnitude;
//		effect->removeEffect(target, *effect);
//	}
//	if (effect->name == "Cast Speed")
//	{
//		effect->applied = true;
//		if (std::dynamic_pointer_cast<Human>(target))
//		{
//			std::dynamic_pointer_cast<Human>(target)->castSpeed += effect->magnitude;
//		}
//		effect->removeEffect(target, *effect);
//	}
//	
//	else if (effect->name == "Oaken Armor I")
//	{
//		effect->applied = true;
//		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) + 75);
//		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) + 75);
//		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) + 75);
//		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) + 75);
//		std::cout << " " << dye::light_yellow(target->name) << " is protected by " << dye::light_green("Oaken Armor I") << "!" << std::endl;
//		target->combatFlags.push_back(Character::CombatFlags::ENHANCEDARMOR);
//		effect->removeEffect(target, *effect);
//		target->effects.push_back(std::make_shared<Effect>(false, true, "Oaken Armor I", "The target is protected by a thin layer of magically strengthened wood", 0.0f, 5, 100, false, 1, 1, false));
//		return;
//	}
//	if (effect->name == "Oaken Armor II")
//	{
//		effect->applied = true;
//		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) + 100);
//		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) + 100);
//		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) + 100);
//		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) + 100);
//		std::cout << " " << dye::light_yellow(target->name) << " is protected by " << dye::light_green("Oaken Armor II") << "!" << std::endl;
//		target->combatFlags.push_back(Character::CombatFlags::ENHANCEDARMOR);
//		effect->removeEffect(target, *effect);
//		target->effects.push_back(std::make_shared<Effect>(false, true, "Oaken Armor II", "The target is protected by a thin layer of magically strengthened wood", 0.0f, 5, 100, false, 1, 1, false));
//		return;
//
//	}
//	if (effect->name == "Oaken Armor III")
//	{
//		effect->applied = true;
//		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) + 150);
//		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) + 150);
//		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) + 150);
//		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) + 150);
//		std::cout << " " << dye::light_yellow(target->name) << " is protected by " << dye::light_green("Oaken Armor III") << "!" << std::endl;
//		effect->removeEffect(target, *effect);
//		target->effects.push_back(std::make_shared<Effect>(false, true, "Oaken Armor III", "The target is protected by a thin layer of magically strengthened wood", 0.0f, 5, 100, false, 1, 1, false));
//		target->combatFlags.push_back(Character::CombatFlags::ENHANCEDARMOR);
//		return;
//
//	}
//	if (effect->name == "Nature's Bounty I")
//	{
//		effect->applied = true;
//		target->combatFlags.push_back(Character::CombatFlags::HEALING);
//		effect->removeEffect(target, *effect);
//		target->effects.push_back(std::make_shared<Effect>(false, true, "Nature's Bounty I", "The target is healed by the magic of the forest", 0.0f, 5, 50, false, 1, 1, false));
//		return;
//
//	}
//	if (effect->name == "Nature's Bounty II")
//	{
//		effect->applied = true;
//		target->combatFlags.push_back(Character::CombatFlags::HEALING);
//		effect->removeEffect(target, *effect);
//		target->effects.push_back(std::make_shared<Effect>(false, true, "Nature's Bounty II", "The target is healed greatly by the magic of the forest", 0.0f, 5, 100, false, 1, 1, false));
//		return;
//	}
//	if (effect->name == "Fruit of the Earth I" || effect->name == "Fruit of the Earth II" || effect->name == "Fruit of the Earth III")
//	{
//		effect->applied = true;
//		target->healthPoints += effect->magnitude;
//		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
//		target->fatiguePoints += effect->magnitude / 4;
//		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
//		std::cout << " " << target->name << " is healed by the magic of the forest!" << std::endl;
//		std::cout << " " << target->name << " has gained " << effect->magnitude << " health!" << std::endl;
//		std::cout << " " << target->name << " has gained " << effect->magnitude / 4 << " fatigue!" << std::endl;
//		effect->removeEffect(target, *effect);
//		return;
//	}
//	if (effect->name == "None")
//	{
//		return;
//	}
//	else
//	{
//		std::cout << "Invalid effect name in applyPassiveEffect" << std::endl;
//	}
//}
//void Effect::applyConsumableEffect(std::shared_ptr<Effect> effect, std::shared_ptr<Character> target)
//{
//	if (effect == nullptr) return;
//	if (effect->name == "Restore Health")
//	{
//		target->healthPoints += effect->magnitude;
//		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
//		effect->removeEffect(target, *effect);
//	}
//	if (effect->name == "Restore Fatigue")
//	{
//		target->fatiguePoints += effect->magnitude;
//		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
//		effect->removeEffect(target, *effect);
//	}
//	if (effect->name == "Max Health")
//	{
//		target->maxHealthPoints += effect->magnitude;
//		effect->removeEffect(target, *effect);
//	}
//	if (effect->name == "Max Fatigue")
//	{
//		target->maxFatiguePoints += effect->magnitude;
//		effect->removeEffect(target, *effect);
//	}
//	if (effect->name == "Health Regen")
//	{
//		target->healthPoints += effect->magnitude;
//		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
//	}
//	if (effect->name == "Fatigue Regen")
//	{
//		target->fatiguePoints += effect->magnitude;
//		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
//	}
//	if (effect->name == "Attack Speed")
//	{
//		std::shared_ptr<Weapon> mainHand = nullptr;
//		std::shared_ptr<Weapon> offHand = nullptr;
//		std::shared_ptr<Weapon> reserve1 = nullptr;
//		std::shared_ptr<Weapon> reserve2 = nullptr;
//		target->inventory.getEquippedWeapons(mainHand, offHand, reserve1, reserve2);
//		if (mainHand != nullptr) mainHand->attackSpeed += effect->magnitude;
//		if (offHand != nullptr) offHand->attackSpeed += effect->magnitude;
//		if (reserve1 != nullptr) reserve1->attackSpeed += effect->magnitude;
//		if (reserve2 != nullptr) reserve2->attackSpeed += effect->magnitude;
//	}
//	if (effect->name == "Cast Speed")
//	{
//		if (std::dynamic_pointer_cast<Human>(target))
//		{
//			std::dynamic_pointer_cast<Human>(target)->castSpeed += effect->magnitude;
//		}
//	}
//	if (effect->name == "Speed")
//	{
//		if (target)	target->speed += effect->magnitude;
//	}
//	if (effect->name == "Physical Resistance")
//	{
//		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) + effect->magnitude);
//		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) + effect->magnitude);
//		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) + effect->magnitude);
//		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) + effect->magnitude);
//	}
//	if (effect->name == "Magic Resistance")
//	{
//		target->setDefenseValue(Defense::MAGIC, target->getDefenseValue(Defense::MAGIC) + effect->magnitude);
//	}
//	if (effect->name == "Fire Resistance")
//	{
//		target->setDefenseValue(Defense::FIRE, target->getDefenseValue(Defense::FIRE) + effect->magnitude);
//	}
//	if (effect->name == "Frost Resistance")
//	{
//		target->setDefenseValue(Defense::FROST, target->getDefenseValue(Defense::FROST) + effect->magnitude);
//	}
//	if (effect->name == "Shock Resistance")
//	{
//		target->setDefenseValue(Defense::SHOCK, target->getDefenseValue(Defense::SHOCK) + effect->magnitude);
//	}
//	if (effect->name == "Poison Resistance")
//	{
//		target->setDefenseValue(Defense::POISON, target->getDefenseValue(Defense::POISON) + effect->magnitude);
//	}
//	if (effect->name == "Bleed Resistance")
//	{
//		target->setDefenseValue(Defense::BLEED, target->getDefenseValue(Defense::BLEED) + effect->magnitude);
//	}
//	if (effect->name == "Sleep Resistance")
//	{
//		target->setDefenseValue(Defense::SLEEP, target->getDefenseValue(Defense::SLEEP) + effect->magnitude);
//	}
//	if (effect->name == "Wind Resistance")
//	{
//		target->setDefenseValue(Defense::WIND, target->getDefenseValue(Defense::WIND) + effect->magnitude);
//	}
//	if (effect->name == "Dark Resistance")
//	{
//		target->setDefenseValue(Defense::DARK, target->getDefenseValue(Defense::DARK) + effect->magnitude);
//	}
//	if (effect->name == "Holy Resistance")
//	{
//		target->setDefenseValue(Defense::HOLY, target->getDefenseValue(Defense::HOLY) + effect->magnitude);
//	}
//	if (effect->name == "All Resistances")
//	{
//		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) + effect->magnitude);
//		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) + effect->magnitude);
//		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) + effect->magnitude);
//		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) + effect->magnitude);
//		target->setDefenseValue(Defense::MAGIC, target->getDefenseValue(Defense::MAGIC) + effect->magnitude);
//		target->setDefenseValue(Defense::FIRE, target->getDefenseValue(Defense::FIRE) + effect->magnitude);
//		target->setDefenseValue(Defense::FROST, target->getDefenseValue(Defense::FROST) + effect->magnitude);
//		target->setDefenseValue(Defense::SHOCK, target->getDefenseValue(Defense::SHOCK) + effect->magnitude);
//		target->setDefenseValue(Defense::POISON, target->getDefenseValue(Defense::POISON) + effect->magnitude);
//		target->setDefenseValue(Defense::BLEED, target->getDefenseValue(Defense::BLEED) + effect->magnitude);
//		target->setDefenseValue(Defense::SLEEP, target->getDefenseValue(Defense::SLEEP) + effect->magnitude);
//		target->setDefenseValue(Defense::WIND, target->getDefenseValue(Defense::WIND) + effect->magnitude);
//		target->setDefenseValue(Defense::DARK, target->getDefenseValue(Defense::DARK) + effect->magnitude);
//		target->setDefenseValue(Defense::HOLY, target->getDefenseValue(Defense::HOLY) + effect->magnitude);
//	}
//	if (effect->name == "Block Chance")
//	{
//		target->blockChance += effect->magnitude;
//	}
//	if (effect->name == "Dodge Chance")
//	{
//		target->dodgeChance += effect->magnitude;
//	}
//	if (effect->name == "Critical Chance")
//	{
//		target->critChance += effect->magnitude;
//	}
//	if (effect->name == "Escape")
//	{
//		target->combatFlags.push_back(Character::CombatFlags::CANESCAPE);
//	}
//	if (effect->name == "Strength")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->strength += effect->magnitude;
//	}
//	if (effect->name == "Agility")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->agility += effect->magnitude;
//	}
//	if (effect->name == "Intelligence")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->intelligence += effect->magnitude;
//	}
//	if (effect->name == "Faith")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->faith += effect->magnitude;
//	}
//	if (effect->name == "Arcane")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->arcane += effect->magnitude;
//	}
//	if (effect->name == "Charisma")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->charisma += effect->magnitude;
//	}
//	if (effect->name == "Luck")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->luck += effect->magnitude;
//	}
//	if (effect->name == "Resurrect")
//	{
//		if (!target->isAlive)
//		{
//			target->isAlive = true;
//			target->healthPoints = target->maxHealthPoints * 0.1f;
//			target->combatFlags.push_back(Character::CombatFlags::RESURRECTED);
//		}
//	}
//	if (effect->name == "Random I")
//	{
//		target->healthPoints += effect->magnitude;
//		if (target->healthPoints > target->maxHealthPoints) target->healthPoints = target->maxHealthPoints;
//	}
//	if (effect->name == "Random II")
//	{
//		target->fatiguePoints += effect->magnitude;
//		if (target->fatiguePoints > target->maxFatiguePoints) target->fatiguePoints = target->maxFatiguePoints;
//	}
//	if (effect->name == "Random III")
//	{
//		target->fatiguePoints -= effect->magnitude;
//		if (target->fatiguePoints < target->maxFatiguePoints) target->fatiguePoints = 1.0f;
//	}
//	if (effect->name == "Random IV")
//	{
//		target->healthPoints -= effect->magnitude;
//		if (target->healthPoints < target->maxHealthPoints) target->healthPoints = 1.0f;
//	}
//	if (effect->name == "Random V")
//	{
//		if (std::dynamic_pointer_cast<Human>(target)) std::dynamic_pointer_cast<Human>(target)->gold += (rand() % 901) + 50;
//	}
//}