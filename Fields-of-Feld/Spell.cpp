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

Spell::Spell(std::string name, std::string description, bool areaOfEffect, bool summon, bool doesDamage, bool healing, bool useOnAlly, bool useOnSelf, bool buff, int duration,
	float magnitude, bool stackable, int stacks, int maxStacks, float intelligenceScaling, float faithScaling, float arcaneScaline,
	float luckScaling, float charismaScaling, float fatigueCost, float attackSpeed, float range) :
	name(name),
	description(description),
	areaOfEffect(areaOfEffect), 
	summon(summon), 
	doesDamage(doesDamage), 
	healing(healing), 
	useOnAlly(useOnAlly), 
	useOnSelf(useOnSelf), 
	buff(buff), 
	duration(duration),
	magnitude(magnitude),
	stackable(stackable),
	stacks(stacks),
	maxStacks(maxStacks),
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

nlohmann::json Spell::toJson() const {
	nlohmann::json j;
	j["type"] = "Spell";
	j["name"] = name;
	j["description"] = description;
	j["range"] = range;
	j["duration"] = duration;
	j["magnitude"] = magnitude;
	j["stackable"] = stackable;
	j["stacks"] = stacks;
	j["maxStacks"] = maxStacks;
	j["areaOfEffect"] = areaOfEffect;
	j["useOnSelf"] = useOnSelf;
	j["healing"] = healing;
	j["useOnAlly"] = useOnAlly;
	j["fatigueCost"] = fatigueCost;
	j["arcaneScaling"] = arcaneScaling;
	j["intelligenceScaling"] = intelligenceScaling;
	j["faithScaling"] = faithScaling;
	j["charismaScaling"] = charismaScaling;
	j["luckScaling"] = luckScaling;
	j["attackSpeed"] = attackSpeed;
	j["doesDamage"] = doesDamage;
	j["buff"] = buff;
	j["summon"] = summon;

	for (const auto& effect : effects)
		j["effects"].push_back(effect->toJson());
	return j;
}

std::shared_ptr<Spell> Spell::fromJson(const nlohmann::json& j) {
	auto spell = std::make_shared<Spell>(j.at("name"),
		j.at("description"),
		j.at("range"),
		j.at("duration"),
		j.at("magnitude"),
		j.at("stackable"),
		j.at("stacks"),	
		j.at("maxStacks"),
		j.at("areaOfEffect"),
		j.at("useOnSelf"),
		j.at("healing"),
		j.at("useOnAlly"),
		j.at("fatigueCost"),
		j.at("arcaneScaling"),
		j.at("intelligenceScaling"),
		j.at("faithScaling"),
		j.at("charismaScaling"),
		j.at("luckScaling"),
		j.at("attackSpeed"),
		j.at("doesDamage"),
		j.at("buff"),
		j.at("summon"));
	for (const auto& eff : j["effects"])
		spell->effects.push_back(Effect::fromJson(eff));
	return spell;
}

float Spell::calculateSpellDamage(std::shared_ptr<Character> target, Spell spell)
{
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
			std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
			if (!armor) continue;
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
		float cumulativeSlashDamage = spell.getPhysicalDamage(PhysicalDamageType::SLASH) - (spell.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = spell.getPhysicalDamage(PhysicalDamageType::PIERCE) - (spell.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = spell.getPhysicalDamage(PhysicalDamageType::BLUNT) - (spell.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = spell.getPhysicalDamage(PhysicalDamageType::CHOP) - (spell.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = spell.getMagicDamage(MagicDamageType::MAGIC) - (spell.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = spell.getMagicDamage(MagicDamageType::FIRE) - (spell.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = spell.getMagicDamage(MagicDamageType::FROST) - (spell.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = spell.getMagicDamage(MagicDamageType::SHOCK) - (spell.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = spell.getMagicDamage(MagicDamageType::POISON) - (spell.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = spell.getMagicDamage(MagicDamageType::BLEED) - (spell.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = spell.getMagicDamage(MagicDamageType::SLEEP) - (spell.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = spell.getMagicDamage(MagicDamageType::DARK) - (spell.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = spell.getMagicDamage(MagicDamageType::HOLY) - (spell.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = spell.getMagicDamage(MagicDamageType::WIND) - (spell.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float spellDamge = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
		spellDamge = max(spellDamge, 0.0f);
		return spellDamge;
	}
	else
	{
		//UNDER CONSTRUCTION
		return 0;
	}

}

void Spell::setPhysicalDamage(PhysicalDamageType physType, float physDamage)
{
	physicalDamages[physType] = physDamage;
}

void Spell::setMagicDamage(MagicDamageType magType, float magDamage)
{
	magicDamages[magType] = magDamage;
}

float Spell::getPhysicalDamage(PhysicalDamageType physType)
{
	auto it = physicalDamages.find(physType);
	return (it != physicalDamages.end()) ? it->second : 0.0f;
}

float Spell::getMagicDamage(MagicDamageType magType)
{
	auto it = magicDamages.find(magType);
	return (it != magicDamages.end()) ? it->second : 0.0f;
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
	float bonetrousleDamage = (arcaneBonus * (arcaneBonus / (arcaneBonus + 50))) * 0.3;
	float bonetrousleBleed = (arcaneBonus * (arcaneBonus / (arcaneBonus + 50))) * 3;

	std::shared_ptr<Spell> bonetrousle;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		bonetrousle = std::make_shared<Spell>("Bonetrousle I", "A flurry of sharpened bone fragments pelt the target",
			false, false, true, false, false, false, false, 1, bonetrousleDamage, false, 1, 1, 0, 0, 100, 0, 0, 50, 70, 75);
		bonetrousle->effects.push_back(std::make_shared<BleedEffect>(1, bonetrousleBleed, false, 1, 1));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);

		return bonetrousle;
	}
	else if (statInvestment < 60)
	{
		bonetrousle = std::make_shared<Spell>("Bonetrousle II", "A flurry of sharpened bone pieces pelt the target", 
			false, false, true, false, false, false, false, 1, bonetrousleDamage, false, 1, 1, 0, 0, 100, 0, 0, 60, 80, 75);
		bonetrousle->effects.push_back(std::make_shared<BleedEffect>(1, bonetrousleBleed, false, 1, 1));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);
		return bonetrousle;
	}
	else
	{
		bonetrousle = std::make_shared<Spell>("Bonetrousle III", "A flurry of sharpened bone chunks pelt the target", 
			false, false, true, false, false, false, false, 1, bonetrousleDamage, false, 1, 1, 0, 0, 100, 0, 0, 70, 90, 75);
		bonetrousle->effects.push_back(std::make_shared<BleedEffect>(1, bonetrousleBleed, false, 1, 1));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);
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
		animalAlly = std::make_shared<Spell>("Summon Vulture", "A large vulture will come to your aid in combat!", false, true, false, false, false, true, false, 10, 1, false, 1, 1, 0, 0, 100, 0, 0, 100, 1, 0);
		animalAlly->effects.push_back(std::make_shared<Summon>(vulture, 10, 1, false, 1, 1));
		return animalAlly;
	}
	else if (statInvestment < 60)
	{
		Inventory inventory;
		inventory.addToBackpack(std::make_shared<LootItem>("Wolf Pelt", "A pelt from a wolf", 150.0f, 0.5f, 1.0f));
		std::shared_ptr<Creature> wolf = std::make_shared<Creature>(false, true, true, true, false, "Wolf", "A rugged wolf", 150, 20, 100, 300, 300, 250, 5, 20, 0, 200, 200, 200, 2000,
			200, 200, 200, 200, 200, 200, 200, 200, inventory, Character::CombatFlags::NEUTRAL);
		animalAlly = std::make_shared<Spell>("Summon Wolf", "A rugged wolf will come to your aid in combat!", false, true, false, false, false, true, false, 10, 1, false, 1, 1, 0, 0, 125, 0, 0, 100, 1, 0);
		animalAlly->effects.push_back(std::make_shared<Summon>(wolf, 10, 1, false, 1, 1));
		return animalAlly;
	}
	else
	{
		Inventory inventory;
		inventory.addToBackpack(std::make_shared<LootItem>("Bear Pelt", "A pelt from a bear", 300.0f, 5.0f, 1.0f));
		std::shared_ptr<Creature> bear = std::make_shared<Creature>(false, true, true, true, false, "Bear", "A mountain bear", 250, 20, 100, 400, 400, 200, 5, 20, 0, 200, 200, 200, 2000,
			200, 200, 200, 200, 200, 200, 200, 200, inventory, Character::CombatFlags::NEUTRAL);
		animalAlly = std::make_shared<Spell>("Summon Bear", "A mountain bear will come to your aid in combat!", false, true, false, false, false, true, false, 10, 1, false, 1, 1, 0, 0, 150, 0, 0, 100, 1, 0);
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
			false, false, false, false, false, true, true, 3, 100, false, 1, 1, 0, 0, 100, 0, 0, 75, 1, 0);
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::BLUNT, 3, 75, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::CHOP, 3, 75, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::PIERCE, 3, 75, false, 1, 1));
		oakArmor->effects.push_back(std::make_shared<ArmorBuff>(Defense::SLASH, 3, 75, false, 1, 1));
		return oakArmor;
	}
	else if (statInvestment < 60)
	{
		oakArmor = std::make_shared<Spell>("Oaken Armor II", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			false, false, false, false, false, true, true, 3, 100, false, 1, 1, 0, 0, 100, 0, 0, 100, 1, 0);
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
			false, false, false, false, false, true, true, 3, 100, false, 1, 1, 0, 0, 100, 0, 0, 125, 1, 0);
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
			false, false, false, true, false, true, false, 1, 1, false, 1, 1, 0, 0, 100, 0, 0, 50, 1, 0);
		fruit->effects.push_back(std::make_shared<Healing>(1, 100, false, 1, 1));
		fruit->effects.push_back(std::make_shared<FatigueRestore>(1, 50, false, 1, 1));
		return fruit;
	}
	else if (statInvestment < 60)
	{
		fruit = std::make_shared<Spell>("Fruit of the Earth II", "Vegetation nearby grows a highly nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			false, false, false, true, false, true, false, 1, 1, false, 1, 1, 0, 0, 100, 0, 0, 60, 1, 0);
		fruit->effects.push_back(std::make_shared<Healing>(1, 150, false, 1, 1));
		fruit->effects.push_back(std::make_shared<FatigueRestore>(1, 75, false, 1, 1));
		return fruit;
	}
	else
	{
		fruit = std::make_shared<Spell>("Fruit of the Earth III", "Vegetation nearby grows a unbelievably nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			false, false, false, true, false, true, false, 1, 1, false, 1, 1, 0, 0, 100, 0, 0, 70, 1, 0);
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
			false, false, true, false, false, false, false, 1, 1, false, 1, 1, 100, 0, 0, 0, 0, 50, 1, 10);
		endothermicGrasp->effects.push_back(std::make_shared<FrostBurstEffect>(1, 5000, false, 1, 1));
		endothermicGrasp->effects.push_back(std::make_shared<FreezeEffect>(1, 1, false, 1, 1));
		return endothermicGrasp;
	}
	else if (statInvestment < 60)
	{
		endothermicGrasp = std::make_shared<Spell>("Endorthermic Touch",
			"A chilling touch that applies frost burst and freezes weaker targets solid! Investment in intelligence causes the range of the spell to increase.",
			false, false, true, false, false, false, false, 1, 1, false, 1, 1, 100, 0, 0, 0, 0, 60, 1, 15);
		endothermicGrasp->effects.push_back(std::make_shared<FrostBurstEffect>(1, 5000, false, 1, 1));
		endothermicGrasp->effects.push_back(std::make_shared<FreezeEffect>(1, 1, false, 1, 1));
		return endothermicGrasp;
	}
	else
	{
		endothermicGrasp = std::make_shared<Spell>("Endorthermic Grasp",
			"A chilling touch that applies frost burst and freezes weaker targets solid! Investment in intelligence causes the range of the spell to increase.",
			false, false, true, false, false, false, false, 1, 1, false, 1, 1, 100, 0, 0, 0, 0, 70, 1, 20);
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
	float faithBonus = caster.getFaith() * 1.5f;
	float damage = (faithBonus * (faithBonus / (faithBonus + 50))) * 0.3;
	
	std::shared_ptr<Spell> forceBurst;
	if (statInvestment < 30)
	{
		forceBurst = std::make_shared<Spell>("Force Burst I", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			true, false, true, false, false, false, false, 1, 1, false, 1, 1, 0, 100, 0, 0, 0, 30, 1, 10);
		forceBurst->effects.push_back(std::make_shared<KnockbackEffect>(1, damage * 1.5f, false, 1, 1));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 1);
		return forceBurst;
	}
	else if (statInvestment < 60)
	{
		forceBurst = std::make_shared<Spell>("Force Burst II", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			true, false, true, false, false, false, false, 1, 1, false, 1, 1, 0, 100, 0, 0, 0, 40, 1, 10);
		forceBurst->effects.push_back(std::make_shared<KnockbackEffect>(1, damage * 1.6, false, 1, 1));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 2);
		return forceBurst;
	}
	else
	{
		forceBurst = std::make_shared<Spell>("Force Burst III", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			true, false, true, false, false, false, false, 1, 1, false, 1, 1, 0, 100, 0, 0, 0, 50, 1, 10);
		forceBurst->effects.push_back(std::make_shared<KnockbackEffect>(1, damage * 1.7f, false, 1, 1));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 3);
		return forceBurst;
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
		fireball = std::make_shared<Spell>("Fire Bolt", "A bolt of holy fire that deals burning damage", false, false, true, false, false, false, false, 1, fireballDamage + 50 + caster.getFaith(), false, 1, 1, 0, 100, 0, 0, 0, 50, 1, 100);
		fireball->effects.push_back(std::make_shared<BurnEffect>(1, fireballDamage, false, 1, 1));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 75);
		return fireball;
	}
	else if (statInvestment < 60)
	{
		fireball = std::make_shared<Spell>("Fire Ball", "A ball of holy fire that deals moderate burning damage", false, false, true, false, false, false, false, 1, fireballDamage + 75 + caster.getFaith(), false, 1, 1, 0, 100, 0, 0, 0, 75, 1, 100);
		fireball->effects.push_back(std::make_shared<BurnEffect>(1, fireballDamage, false, 1, 1));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 100);
		return fireball;
	}
	else
	{
		fireball = std::make_shared<Spell>("Captive Sun", "A searing ball of holy plasma that does immense burning damage", false, false, true, false, false, false, false, 1, fireballDamage + 100 + caster.getFaith(), false, 1, 1, 0, 100, 0, 0, 0, 100, 1, 100);
		fireball->effects.push_back(std::make_shared<BurnEffect>(1, fireballDamage, false, 1, 1));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->effects.push_back(std::make_shared<FieryExplosionEffect>(fireball->range * 0.3f, fireballDamage * 0.5f, false, 1, 1));
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 125);
		return fireball;
	}
}
//AEROMANCY
//FULGURAMANCY
//VENOMANCY
