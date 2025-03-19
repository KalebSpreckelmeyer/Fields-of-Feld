#include "Spell.h"
#include "Human.h"
#include "Character.h"
#include <algorithm>

Spell::Spell()
{
}

Spell::Spell(bool buff, bool useOnSelf , bool healing, bool useOnAlly, bool summon, bool areaOfEffect, bool applied, std::string name, std::string description,
	PhysicalDamageType physDmg, MagicDamageType magDmg, float range, float magnitude, bool stackable,
	int stacks, int maxStacks, float fatigueCost, float arcaneScaling, float intelligenceScaling,
	float faithScaling, float charismaScaling, float luckScaling, float attackSpeed, bool doesDamage)
	: Effect(doesDamage, applied, name, description, physDmg, magDmg, duration, magnitude, stackable, stacks, maxStacks, areaOfEffect),
	useOnSelf(useOnSelf),
	healing(healing),
	useOnAlly(useOnAlly),
	fatigueCost(fatigueCost),
	arcaneScaling(arcaneScaling),
	intelligenceScaling(intelligenceScaling),
	faithScaling(faithScaling),
	charismaScaling(charismaScaling),
	luckScaling(luckScaling),
	attackSpeed(attackSpeed),
	areaOfEffect(areaOfEffect),
	summon(summon),
	doesDamage(doesDamage),
	buff(buff),
	range(range)
{

}

Spell::~Spell()
{
}

float Spell::calculateSpellDamage(Character* target, Spell spell)
{
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
		float cumulativeSlashDamage = spell.getPhysicalDamage(PhysicalDamageType::SLASH) - (spell.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = spell.getPhysicalDamage(PhysicalDamageType::PIERCE) - (spell.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = spell.getPhysicalDamage(PhysicalDamageType::BLUNT) - (spell.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = spell.getPhysicalDamage(PhysicalDamageType::CHOP) - (spell.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = spell.getMagicDamage(MagicDamageType::MAGIC) - (spell.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = spell.getMagicDamage(MagicDamageType::FIRE) - (spell.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = spell.getMagicDamage(MagicDamageType::FROST) - (spell.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = spell.getMagicDamage(MagicDamageType::SHOCK) - (spell.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = spell.getMagicDamage(MagicDamageType::POISON) - (spell.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = spell.getMagicDamage(MagicDamageType::BLEED) - (spell.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = spell.getMagicDamage(MagicDamageType::SLEEP) - (spell.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = spell.getMagicDamage(MagicDamageType::DARK) - (spell.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = spell.getMagicDamage(MagicDamageType::HOLY) - (spell.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = spell.getMagicDamage(MagicDamageType::WIND) - (spell.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		float cumulativeFlatDefense = human->flatDefense / 500;

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float spellDamge = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage) - human->flatDefense * (human->flatDefense / 500);
		spellDamge = std::max(spellDamge, 0.0f);
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
Spell* Spell::getBonetrousleEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	float arcaneBonus = caster.getArcane() * 1.5f;  
	float bonetrousleDamage = (arcaneBonus * (arcaneBonus / (arcaneBonus + 50))) * 0.3;

	Spell* bonetrousle = nullptr;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		bonetrousle = new Spell(false, false, false, false, false, false, false, "Bonetrousle I", "A flurry of tiny sharpened bone fragments pelt the target", PhysicalDamageType::PIERCE, MagicDamageType::BLEED, 50, bonetrousleDamage, false, 1, 1, 25, 100, 0, 0, 0, 0, 66, true);
		bonetrousle->effects.push_back(new Effect(true, true, "Blood Loss", "The target is bleeding. If attacks persist a hemmorage will occur", PhysicalDamageType::NONE, MagicDamageType::BLEED,
			1, 5, false, 1, 1, false));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);

		return bonetrousle;
	}
	else if (statInvestment < 60)
	{
		bonetrousle = new Spell(false, false, false, false, false, false, false, "Bonetrousle II", "A flurry of sharpened bone fragments pelt the target", PhysicalDamageType::PIERCE, MagicDamageType::BLEED, 50, bonetrousleDamage, false, 1, 1, 50, 100, 0, 0, 0, 0, 75, true);
		bonetrousle->effects.push_back(new Effect(true, true, "Blood Loss", "The target is bleeding. If attacks persist a hemmorage will occur", PhysicalDamageType::NONE, MagicDamageType::BLEED,
			1, 7, false, 1, 1, false));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);
		return bonetrousle;
	}
	else
	{
		bonetrousle = new Spell(false, false, false, false, false, false, false, "Bonetrousle III", "A flurry of sharpened bone chunks pelt the target", PhysicalDamageType::PIERCE, MagicDamageType::BLEED, 50, bonetrousleDamage, false, 1, 1, 75, 100, 0, 0, 0, 0, 80, true);
		bonetrousle->effects.push_back(new Effect(true, true, "Blood Loss", "The target is bleeding. If attacks persist a hemmorage will occur", PhysicalDamageType::NONE, MagicDamageType::BLEED,
			1, 10, false, 1, 1, false));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);
		return bonetrousle;
	}
}
//GEOMANCY
Spell* Spell::getSummonAnimalAllyEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	Spell* animalAlly = nullptr;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		animalAlly = new Spell(false, true, false, false, true, false, false, "Summon Vulture", "A large vulture will come to your aid in combat!", PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0, false);
		animalAlly->effects.push_back(new Effect(false, true, "Summon Vulture", "A large vulture comes to aid you in combat!", PhysicalDamageType::NONE, MagicDamageType::NONE, 10, 0, false, 1, 1, false));
		return animalAlly;
	}
	else if (statInvestment < 60)
	{
		animalAlly = new Spell(false, true, false, false, true, false, false, "Summon Wolf", "A rugged wolf will come to your aid in combat!", PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0, false);
		animalAlly->effects.push_back(new Effect(false, true, "Summon Wolf", "A mountain bear will come to your aid in combat!", PhysicalDamageType::NONE, MagicDamageType::NONE, 10, 0, false, 1, 1, false));
		return animalAlly;
	}
	else
	{
		animalAlly = new Spell(false, true, false, false, true, false, false, "Summon Bear", "A mountain bear will come to your aid in combat!", PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0, false);
		animalAlly->effects.push_back(new Effect(false, true, "Summon Bear", "A mountain bear will come to your aid in combat!", PhysicalDamageType::NONE, MagicDamageType::NONE, 10, 0, false, 1, 1, false));
		return animalAlly;
	}
}
Spell* Spell::getOakenArmorEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	Spell* oakArmor = nullptr;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		oakArmor = new Spell(true, true, false, false, false, false, false, "Oaken Armor I", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 1, false);
		oakArmor->effects.push_back(new Effect(false, true, "Oaken Armor I", "The target is protected by a thin layer of magically strengthened wood", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		return oakArmor;
	}
	else if (statInvestment < 60)
	{
		oakArmor = new Spell(true, true, true, false, false, false, false, "Oaken Armor II", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 0, false, 1, 1, 50, 150, 0, 0, 0, 0, 1, false);
		oakArmor->effects.push_back(new Effect(false, true, "Oaken Armor II", "The target is protected by a thin layer of magically strengthened wood", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		oakArmor->effects.push_back(new Effect(false, true, "Nature's Bounty I", "The target is healed by the magic of the forest", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 50, false, 1, 1, false));
		return oakArmor;
	}
	else
	{
		oakArmor = new Spell(true, true, true, false, false, false, false, "Oaken Armor III", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 0, false, 1, 1, 50, 200, 0, 0, 0, 0, 1, false);
		oakArmor->effects.push_back(new Effect(false, true, "Oaken Armor III", "The target is protected by a thin layer of magically strengthened wood", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		oakArmor->effects.push_back(new Effect(false, true, "Nature's Bounty II", "The target is healed greatly by the magic of the forest", PhysicalDamageType::NONE, MagicDamageType::NONE, 5, 100, false, 1, 1, false));
		return oakArmor;
	}
}
Spell* Spell::getFruitOfTheEarthEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	Spell* fruit = nullptr;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		fruit = new Spell(false, true, true, false, false, false, true, "Fruit of the Earth I", "Vegetation nearby grows a nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 150, false, 1, 1, 50, 100, 0, 0, 0, 0, 1, false);
		fruit->effects.push_back(new Effect(true, true, "Fruit of the Earth I", "The target consumes a fruit from the earth and regains health and fatigue", PhysicalDamageType::NONE, MagicDamageType::NONE, 1, 175, false, 1, 1, false));
		return fruit;
	}
	else if (statInvestment < 60)
	{
		fruit = new Spell(false, true, true, false, false, false, true, "Fruit of the Earth II", "Vegetation nearby grows a highly nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 150, false, 1, 1, 60, 100, 0, 0, 0, 0, 1, false);
		fruit->effects.push_back(new Effect(true, true, "Fruit of the Earth II", "The target consumes a fruit from the earth and regains health and fatigue", PhysicalDamageType::NONE, MagicDamageType::NONE, 1, 200, false, 1, 1, false));
		return fruit;
	}
	else
	{
		fruit = new Spell(false, true, true, false, false, false, true, "Fruit of the Earth III", "Vegetation nearby grows a unbelievably nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			PhysicalDamageType::NONE, MagicDamageType::NONE, 0, 150, false, 1, 1, 75, 100, 0, 0, 0, 0, 1, false);
		fruit->effects.push_back(new Effect(true, true, "Fruit of the Earth III", "The target consumes a fruit from the earth and regains health and fatigue", PhysicalDamageType::NONE, MagicDamageType::NONE, 1, 300, false, 1, 1, false));
		return fruit;
	}
}
//CRYOMANCY
Spell* Spell::getEndothermicGraspEffect(Character& caster)
{
	float statInvestment = caster.getIntelligence();

	Spell* endothermicGrasp = nullptr;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		endothermicGrasp = new Spell(false, false, false, false, false, false, false, "Endorthermic Nudge",
			"A chilling touch that applies frost burst and freezes weaker targets solid!", PhysicalDamageType::NONE, MagicDamageType::FROST, 10, 0, false,
			1, 1, 25, 0, 100, 0, 0, 0, 1, false);
		endothermicGrasp->effects.push_back(new Effect(false, false, "Frost Burst", "The target suffers a frost burst!", PhysicalDamageType::NONE, MagicDamageType::FROST, 1, 5000, false, 1, 1, false));
		endothermicGrasp->effects.push_back(new Effect(false, false, "Freeze 1", "The target is frozen solid and loses a turn!", PhysicalDamageType::NONE, MagicDamageType::FROST, 1, 1, false, 1, 1, false));
		return endothermicGrasp;
	}
	else if (statInvestment < 60)
	{
		endothermicGrasp = new Spell(false, false, false, false, false, false, false, "Endorthermic Touch",
			"A chilling touch that applies frost burst and freezes weaker targets solid!", PhysicalDamageType::NONE, MagicDamageType::FROST, 10, 0, false,
			1, 1, 40, 0, 100, 0, 0, 0, 1, false);
		endothermicGrasp->effects.push_back(new Effect(false, false, "Frost Burst", "The target suffers a frost burst!", PhysicalDamageType::NONE, MagicDamageType::FROST, 1, 5000, false, 1, 1, false));
		endothermicGrasp->effects.push_back(new Effect(false, false, "Freeze 2", "The target is frozen solid and loses a turn!", PhysicalDamageType::NONE, MagicDamageType::FROST, 1, 1, false, 1, 1, false));
		return endothermicGrasp;
	}
	else
	{
		endothermicGrasp = new Spell(false, false, false, false, false, false, false, "Endorthermic Grasp",
			"A chilling touch that applies frost burst and freezes weaker targets solid!", PhysicalDamageType::NONE, MagicDamageType::FROST, 10, 0, false,
			1, 1, 50, 0, 100, 0, 0, 0, 1, false);
		endothermicGrasp->effects.push_back(new Effect(false, false, "Frost Burst", "The target suffers a frost burst!", PhysicalDamageType::NONE, MagicDamageType::FROST, 1, 5000, false, 1, 1, false));
		endothermicGrasp->effects.push_back(new Effect(false, false, "Freeze 3", "The target is frozen solid and loses a turn!", PhysicalDamageType::NONE, MagicDamageType::FROST, 1, 1, false, 1, 1, false));
		return endothermicGrasp;
	}
}
//MELODIC ARTS
//MIRACLES
Spell* Spell::getForceBurstEffect(Character& caster)
{
	float statInvestment = caster.getFaith();
	float faithBonus = caster.getFaith() * 1.5f;
	float damage = (faithBonus * (faithBonus / (faithBonus + 50))) * 0.3;

	Spell* forceBurst = nullptr;
	if (statInvestment < 30)
	{
		forceBurst = new Spell(false, false, false, false, false, true, false, "Force Burst I", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			PhysicalDamageType::BLUNT, MagicDamageType::HOLY, 10, damage * 1, false, 1, 1, 20, 0, 0, 100, 0, 0, 1, true);
		forceBurst->effects.push_back(new Effect(true, true, "Knockback I", "The target is pushed back", PhysicalDamageType::NONE, MagicDamageType::NONE, 1, damage * 1, false, 1, 1, true));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 1);
		return forceBurst;
	}
	else if (statInvestment < 60)
	{
		forceBurst = new Spell(false, false, false, false, false, true, false, "Force Burst II", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			PhysicalDamageType::BLUNT, MagicDamageType::HOLY, 10, damage * 1.5, false, 1, 1, 20, 0, 0, 100, 0, 0, 1, true);
		forceBurst->effects.push_back(new Effect(true, true, "Knockback II", "The target is pushed back", PhysicalDamageType::NONE, MagicDamageType::NONE, 1, damage * 1.5, false, 1, 1, true));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 2);
		return forceBurst;
	}
	else
	{
		forceBurst = new Spell(false, false, false, false, false, true, false, "Force Burst III", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			PhysicalDamageType::BLUNT, MagicDamageType::HOLY, 10, damage * 2.5, false, 1, 1, 20, 0, 0, 100, 0, 0, 1, true);
		forceBurst->effects.push_back(new Effect(true, true, "Knockback III", "The target is pushed back", PhysicalDamageType::NONE, MagicDamageType::NONE, 1, damage * 2.5, false, 1, 1, true));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 3);
		return forceBurst;
	}
}
//PYROMANCY
Spell* Spell::getFireBallEffect(Character& caster)
{
	float statInvestment = caster.getFaith();

	float faithBonus = caster.getFaith() * 1.5f;
	float fireballDamage = faithBonus * (faithBonus / (faithBonus + 50));

	Spell* fireball = nullptr;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		fireball = new Spell(false, false, false, false, false, false, false, "Fire Bolt", "A bolt of holy fire that deals burning damage", PhysicalDamageType::NONE, MagicDamageType::FIRE, 100, fireballDamage + 100 + caster.getFaith(), false, 1, 1, 20, 0, 0, 100, 0, 0, 1, true);
		fireball->effects.push_back(new Effect(true, true, "Burn", "The target is engulfed in flames causing damage each turn", PhysicalDamageType::NONE, MagicDamageType::FIRE,
			3, caster.maxHealthPoints * 0.05f, false, 1, 1, false));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 100);
		return fireball;
	}
	else if (statInvestment < 60)
	{
		fireball = new Spell(false, false, false, false, false, false, false, "Fire Ball", "A ball of holy fire that deals moderate burning damage", PhysicalDamageType::NONE, MagicDamageType::FIRE, 100, fireballDamage + 150, false, 1, 1, 30, 0, 0, 100, 0, 0, 1, true);
		fireball->effects.push_back(new Effect(true, true, "Burn", "The target is engulfed in flames causing damage each turn", PhysicalDamageType::NONE, MagicDamageType::FIRE,
			3, caster.maxHealthPoints * 0.1f, false, 1, 1, false));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 150);
		return fireball;
	}
	else
	{
		fireball = new Spell(false, false, false, false, false, true, false, "Captive Sun", "A searing ball of holy plasma that does immense burning damage", PhysicalDamageType::NONE, MagicDamageType::FIRE, 100, fireballDamage + 250, false, 1, 1, 50, 0, 0, 100, 0, 0, 1, true);
		fireball->effects.push_back(new Effect(true, true, "Burn", "The target is engulfed in flames causing damage each turn", PhysicalDamageType::NONE, MagicDamageType::FIRE,
			3, caster.maxHealthPoints * 0.15f, false, 1, 1, false));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->effects.push_back(new Effect(true, true, "Fiery Explosion", "Enemies in close proximity to the target take splash damage", PhysicalDamageType::NONE, MagicDamageType::FIRE, 1, 50, false, 1, 1, true));
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 250);
		return fireball;
	}
}
//AEROMANCY
//FULGURAMANCY
//VENOMANCY
