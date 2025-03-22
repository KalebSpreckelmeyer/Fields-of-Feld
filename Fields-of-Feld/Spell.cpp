#include "Spell.h"
#include "Human.h"
#include "Character.h"
#include <algorithm>

Spell::Spell(bool areaOfEffect, bool summon, bool doesDamage, bool healing, bool useOnAlly, bool useOnSelf, bool buff, int duration,
	float magnitude, bool stackable, int stacks, int maxStacks, float intelligenceScaling, float faithScaling, float arcaneScaline,
	float luckScaling, float charismaScaling, float fatigueCost, float attackSpeed, float range) :
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
	if (std::dynamic_pointer_cast<std::shared_ptr<Human>>(target))
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

		cumulativeSlashResist = std::max(cumulativeSlashResist, 0.0f);
		cumulativePierceResist = std::max(cumulativePierceResist, 0.0f);
		cumulativeBluntResist = std::max(cumulativeBluntResist, 0.0f);
		cumulativeChopResist = std::max(cumulativeChopResist, 0.0f);

		cumulativeMagicResist = std::max(cumulativeMagicResist, 0.0f);
		cumulativeFireResist = std::max(cumulativeFireResist, 0.0f);
		cumulativeIceResist = std::max(cumulativeIceResist, 0.0f);
		cumulativeShockResist = std::max(cumulativeShockResist, 0.0f);
		cumulativePoisonResist = std::max(cumulativePoisonResist, 0.0f);
		cumulativeBleedResist = std::max(cumulativeBleedResist, 0.0f);
		cumulativeSleepResist = std::max(cumulativeSleepResist, 0.0f);
		cumulativeDarkResist = std::max(cumulativeDarkResist, 0.0f);
		cumulativeHolyResist = std::max(cumulativeHolyResist, 0.0f);
		cumulativeWindResist = std::max(cumulativeWindResist, 0.0f);

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

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float spellDamge = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
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
std::shared_ptr<Spell> Spell::getBonetrousleEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	float arcaneBonus = caster.getArcane() * 1.5f;  
	float bonetrousleDamage = (arcaneBonus * (arcaneBonus / (arcaneBonus + 50))) * 0.3;

	std::shared_ptr<Spell> bonetrousle;
	bonetrousle->range = 75;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		bonetrousle = std::make_shared<Spell>(false, false, false, false, false, false, false, "Bonetrousle I", "A flurry of tiny sharpened bone fragments pelt the target", 75, bonetrousleDamage, false, 1, 1, 25, 100, 0, 0, 0, 0, 66, true);
		bonetrousle->effects.push_back(std::make_shared<Effect>(true, false, "Blood Loss", "The target is bleeding. If attacks persist a hemmorrage will occur",
			bonetrousle->range, 1, 5, false, 1, 1, false));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);

		return bonetrousle;
	}
	else if (statInvestment < 60)
	{
		bonetrousle = std::make_shared<Spell>(false, false, false, false, false, false, false, "Bonetrousle II", "A flurry of sharpened bone fragments pelt the target", 75, bonetrousleDamage, false, 1, 1, 50, 100, 0, 0, 0, 0, 75, true);
		bonetrousle->effects.push_back(std::make_shared<Effect>(true, false, "Blood Loss", "The target is bleeding. If attacks persist a hemmorrage will occur",
			bonetrousle->range, 1, 7, false, 1, 1, false));
		bonetrousle->setPhysicalDamage(PhysicalDamageType::PIERCE, bonetrousleDamage * .8);
		bonetrousle->setMagicDamage(MagicDamageType::DARK, bonetrousleDamage * .2);
		return bonetrousle;
	}
	else
	{
		bonetrousle = std::make_shared<Spell>(false, false, false, false, false, false, false, "Bonetrousle III", "A flurry of sharpened bone chunks pelt the target", 75, bonetrousleDamage, false, 1, 1, 75, 100, 0, 0, 0, 0, 80, true);
		bonetrousle->effects.push_back(std::make_shared<Effect>(true, false, "Blood Loss", "The target is bleeding. If attacks persist a hemmorrage will occur",
			bonetrousle->range, 1, 10, false, 1, 1, false));
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
	animalAlly->range = 0;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		animalAlly = std::make_shared<Spell>(false, true, false, false, true, false, false, "Summon Vulture", "A large vulture will come to your aid in combat!", 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0, false);
		animalAlly->effects.push_back(std::make_shared<Effect>(false, false, "Summon Vulture", "A large vulture comes to aid you in combat!", animalAlly->range, 10, 0, false, 1, 1, false));
		return animalAlly;
	}
	else if (statInvestment < 60)
	{
		animalAlly = std::make_shared<Spell>(false, true, false, false, true, false, false, "Summon Wolf", "A rugged wolf will come to your aid in combat!", 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0, false);
		animalAlly->effects.push_back(std::make_shared<Effect>(false, false, "Summon Wolf", "A mountain bear will come to your aid in combat!", animalAlly->range, 10, 0, false, 1, 1, false));
		return animalAlly;
	}
	else
	{
		animalAlly = std::make_shared<Spell>(false, true, false, false, true, false, false, "Summon Bear", "A mountain bear will come to your aid in combat!", 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0, false);
		animalAlly->effects.push_back(std::make_shared<Effect>(false, false, "Summon Bear", "A mountain bear will come to your aid in combat!", animalAlly->range, 10, 0, false, 1, 1, false));
		return animalAlly;
	}
}
std::shared_ptr<Spell> Spell::getOakenArmorEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	std::shared_ptr<Spell> oakArmor;
	oakArmor->range = 0;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		oakArmor = std::make_shared<Spell>(true, true, false, false, false, false, false, "Oaken Armor I", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
			 0, 0, false, 1, 1, 50, 100, 0, 0, 0, 0, 0.1f, false);
		oakArmor->effects.push_back(std::make_shared<Effect>(false, false, "Oaken Armor I", "The target is protected by a thin layer of magically strengthened wood", oakArmor->range, 5, 100, false, 1, 1, false));
		return oakArmor;
	}
	else if (statInvestment < 60)
	{
		oakArmor = std::make_shared<Spell>(true, true, true, false, false, false, false, "Oaken Armor II", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
		 0, 0, false, 1, 1, 50, 150, 0, 0, 0, 0, 0.1f, false);
		oakArmor->effects.push_back(std::make_shared<Effect>(false, false, "Oaken Armor II", "The target is protected by a thin layer of magically strengthened wood", oakArmor->range, 5, 100, false, 1, 1, false));
		oakArmor->effects.push_back(std::make_shared<Effect>(false, false, "Nature's Bounty I", "The target is healed by the magic of the forest", oakArmor->range, 5, 50, false, 1, 1, false));
		return oakArmor;
	}
	else
	{
		oakArmor = std::make_shared<Spell>(true, true, true, false, false, false, false, "Oaken Armor III", "The trees give willingly when asked nicely. Project a thin layer of magically strengthened wood upon the surface of your body increasing physical damage negation for 3 turns. Investment in arcane causes the armor to gain a healing effect",
		 0, 0, false, 1, 1, 50, 200, 0, 0, 0, 0, 0.1f, false);
		oakArmor->effects.push_back(std::make_shared<Effect>(false, false, "Oaken Armor III", "The target is protected by a thin layer of magically strengthened wood", oakArmor->range, 5, 100, false, 1, 1, false));
		oakArmor->effects.push_back(std::make_shared<Effect>(false, false, "Nature's Bounty II", "The target is healed greatly by the magic of the forest", oakArmor->range, 5, 100, false, 1, 1, false));
		return oakArmor;
	}
}
std::shared_ptr<Spell> Spell::getFruitOfTheEarthEffect(Character& caster)
{
	float statInvestment = caster.getArcane();

	std::shared_ptr<Spell> fruit;
	fruit->range = 0;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		fruit = std::make_shared<Spell>(false, true, true, false, false, false, true, "Fruit of the Earth I", "Vegetation nearby grows a nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			 0, 150, false, 1, 1, 50, 100, 0, 0, 0, 0, 0.1f, false);
		fruit->effects.push_back(std::make_shared<Effect>(true, false, "Fruit of the Earth I", "The target consumes a fruit from the earth and regains health and fatigue",  fruit->range, 1, 175, false, 1, 1, false));
		return fruit;
	}
	else if (statInvestment < 60)
	{
		fruit = std::make_shared<Spell>(false, true, true, false, false, false, true, "Fruit of the Earth II", "Vegetation nearby grows a highly nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			 0, 150, false, 1, 1, 60, 100, 0, 0, 0, 0, 0.1f, false);
		fruit->effects.push_back(std::make_shared<Effect>(true, false, "Fruit of the Earth II", "The target consumes a fruit from the earth and regains health and fatigue",  fruit->range, 1, 200, false, 1, 1, false));
		return fruit;
	}
	else
	{
		fruit = std::make_shared<Spell>(false, true, true, false, false, false, true, "Fruit of the Earth III", "Vegetation nearby grows a unbelievably nutritious fruit. Consume it and regain health and fatigue. Investment in arcane increases the restorative effects of the fruit",
			 0, 150, false, 1, 1, 75, 100, 0, 0, 0, 0, 0.1f, false);
		fruit->effects.push_back(std::make_shared<Effect>(true, false, "Fruit of the Earth III", "The target consumes a fruit from the earth and regains health and fatigue",  fruit->range, 1, 300, false, 1, 1, false));
		return fruit;
	}
}
//CRYOMANCY
std::shared_ptr<Spell> Spell::getEndothermicGraspEffect(Character& caster)
{
	float statInvestment = caster.getIntelligence();

	std::shared_ptr<Spell> endothermicGrasp;
	endothermicGrasp->range = 10;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		endothermicGrasp = std::make_shared<Spell>(false, false, false, false, false, false, false, "Endorthermic Nudge",
			"A chilling touch that applies frost burst and freezes weaker targets solid!", 10, 1, false,
			1, 1, 25, 0, 100, 0, 0, 0, 1, false);
		endothermicGrasp->effects.push_back(std::make_shared<Effect>(false, false, "Frost Burst", "The target suffers a frost burst!", endothermicGrasp->range, 1, 5000, false, 1, 1, false));
		endothermicGrasp->effects.push_back(std::make_shared<Effect>(false, false, "Freeze 1", "The target is frozen solid and loses a turn!", endothermicGrasp->range, 1, 1, false, 1, 1, false));
		return endothermicGrasp;
	}
	else if (statInvestment < 60)
	{
		endothermicGrasp = std::make_shared<Spell>(false, false, false, false, false, false, false, "Endorthermic Touch",
			"A chilling touch that applies frost burst and freezes weaker targets solid!", 10, 1, false,
			1, 1, 40, 0, 100, 0, 0, 0, 1, false);
		endothermicGrasp->effects.push_back(std::make_shared<Effect>(false, false, "Frost Burst", "The target suffers a frost burst!", endothermicGrasp->range, 1, 5000, false, 1, 1, false));
		endothermicGrasp->effects.push_back(std::make_shared<Effect>(false, false, "Freeze 2", "The target is frozen solid and loses a turn!", endothermicGrasp->range, 1, 1, false, 1, 1, false));
		return endothermicGrasp;
	}
	else
	{
		endothermicGrasp = std::make_shared<Spell>(false, false, false, false, false, false, false, "Endorthermic Grasp",
			"A chilling touch that applies frost burst and freezes weaker targets solid!", 10, 1, false,
			1, 1, 50, 0, 100, 0, 0, 0, 1, false);
		endothermicGrasp->effects.push_back(std::make_shared<Effect>(false, false, "Frost Burst", "The target suffers a frost burst!", endothermicGrasp->range, 1, 5000, false, 1, 1, false));
		endothermicGrasp->effects.push_back(std::make_shared<Effect>(false, false, "Freeze 3", "The target is frozen solid and loses a turn!", endothermicGrasp->range, 1, 1, false, 1, 1, false));
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
	forceBurst->range = 20;
	if (statInvestment < 30)
	{
		forceBurst = std::make_shared<Spell>(false, false, false, false, false, true, false, "Force Burst I", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			 20, damage * 1, false, 1, 1, 20, 0, 0, 100, 0, 0, 0.1f, true);
		forceBurst->effects.push_back(std::make_shared<Effect>(true, false, "Knockback I", "The target is pushed back", forceBurst->range, 1, damage * 1, false, 1, 1, true));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 1);
		return forceBurst;
	}
	else if (statInvestment < 60)
	{
		forceBurst = std::make_shared<Spell>(false, false, false, false, false, true, false, "Force Burst II", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			 20, damage * 1.5, false, 1, 1, 20, 0, 0, 100, 0, 0, 0.1f, true);
		forceBurst->effects.push_back(std::make_shared<Effect>(true, false, "Knockback II", "The target is pushed back", forceBurst->range, 1, damage * 1.5, false, 1, 1, true));
		forceBurst->setMagicDamage(MagicDamageType::HOLY, damage * 2);
		return forceBurst;
	}
	else
	{
		forceBurst = std::make_shared<Spell>(false, false, false, false, false, true, false, "Force Burst III", "Create a small burst of holy energy dealing tiny amounts of damage and pushing enemies in melee range away from you. Investments in faith increase the damage and the knockback",
			 20, damage * 2.5, false, 1, 1, 20, 0, 0, 100, 0, 0, 0.1f, true);
		forceBurst->effects.push_back(std::make_shared<Effect>(true, false, "Knockback III", "The target is pushed back", forceBurst->range, 1, damage * 2.5, false, 1, 1, true));
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
	fireball->range = 100;
	//Determine which version of the spell is the one used by the player
	if (statInvestment < 30)
	{
		fireball = std::make_shared<Spell>(false, false, false, false, false, false, false, "Fire Bolt", "A bolt of holy fire that deals burning damage", 100, fireballDamage + 50 + caster.getFaith(), false, 1, 1, 20, 0, 0, 100, 0, 0, 1, true);
		fireball->effects.push_back(std::make_shared<Effect>(true, false, "Burn", "The target is engulfed in flames causing damage each turn",
			fireball->range, 3, caster.maxHealthPoints * 0.05f, false, 1, 1, false));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 75);
		return fireball;
	}
	else if (statInvestment < 60)
	{
		fireball = std::make_shared<Spell>(false, false, false, false, false, false, false, "Fire Ball", "A ball of holy fire that deals moderate burning damage", 100, fireballDamage + 75, false, 1, 1, 30, 0, 0, 100, 0, 0, 1, true);
		fireball->effects.push_back(std::make_shared<Effect>(true, false, "Burn", "The target is engulfed in flames causing damage each turn",
			fireball->range, 3, caster.maxHealthPoints * 0.1f, false, 1, 1, false));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 100);
		return fireball;
	}
	else
	{
		fireball = std::make_shared<Spell>(false, false, false, false, false, true, false, "Captive Sun", "A searing ball of holy plasma that does immense burning damage", 100, fireballDamage + 100, false, 1, 1, 50, 0, 0, 100, 0, 0, 1, true);
		fireball->effects.push_back(std::make_shared<Effect>(true, false, "Burn", "The target is engulfed in flames causing damage each turn",
			fireball->range, 3, caster.maxHealthPoints * 0.15f, false, 1, 1, false));
		fireball->effects[0]->setMagicDamage(MagicDamageType::FIRE, 25 + caster.getFaith() * 0.5);
		fireball->effects.push_back(std::make_shared<Effect>(true, false, "Fiery Explosion", "Enemies in close proximity to the target take splash damage", fireball->range * 0.5f, 1, 50, false, 1, 1, true));
		fireball->setMagicDamage(MagicDamageType::FIRE, fireballDamage + 125);
		return fireball;
	}
}
//AEROMANCY
//FULGURAMANCY
//VENOMANCY
