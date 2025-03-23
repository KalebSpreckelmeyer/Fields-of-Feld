#include "Enchantment.h"
#include <string>
#include "Human.h"
#include <algorithm>
#include "MagicDamageType.h"
#include "PhysicalDamageType.h"


Enchantment::Enchantment(std::string name, std::string description, bool areaOfEffect, bool summon, bool doesDamage,
	bool healing, bool useOnAlly, bool useOnSelf, bool buff, float duration, float magnitude, bool applied, bool stackable,
	int stacks, int maxStacks) :
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
	maxStacks(maxStacks)
{

}

Enchantment::~Enchantment()
{
}

nlohmann::json Enchantment::toJson() const
{
	nlohmann::json j;
	j["type"] = "Enchantment";
	j["name"] = name;
	j["description"] = description;
	j["areaOfEffect"] = areaOfEffect;
	j["summon"] = summon;
	j["doesDamage"] = doesDamage;
	j["healing"] = healing;
	j["useOnAlly"] = useOnAlly;
	j["useOnSelf"] = useOnSelf;
	j["buff"] = buff;
	j["duration"] = duration;
	j["magnitude"] = magnitude;
	j["applied"] = applied;
	j["stackable"] = stackable;
	j["stacks"] = stacks;
	j["maxStacks"] = maxStacks;
	for (const auto& effect : effects)
	{
		j["effects"].push_back(effect->toJson());
	}
	return j;
}

std::shared_ptr<Enchantment> Enchantment::fromJson(const nlohmann::json& j)
{
	auto ench = std::make_shared<Enchantment>(
		j.at("name"),
		j.at("description"),
		j.at("areaOfEffect"),
		j.at("summon"),
		j.at("doesDamage"),
		j.at("healing"),
		j.at("useOnAlly"),
		j.at("useOnSelf"),
		j.at("buff"),
		j.at("duration"),
		j.at("magnitude"),
		j.at("applied"),
		j.at("stackable"),
		j.at("stacks"),
		j.at("maxStacks"));
	for (const auto& effect : j.at("effects"))
	{
		ench->effects.push_back(Effect::fromJson(effect));
	}
	return ench;
}
void Enchantment::setPhysicalDamage(PhysicalDamageType physType, float physDamage)
{
	physicalDamage[physType] = physDamage;
}

void Enchantment::setMagicDamage(MagicDamageType magType, float magDamage)
{
	magicDamage[magType] = magDamage;
}

float Enchantment::getPhysicalDamage(PhysicalDamageType physType)
{
	return physicalDamage[physType];
}

float Enchantment::getMagicDamage(MagicDamageType magType)
{
	return magicDamage[magType];
}

//WEAPONS
//std::shared_ptr<Enchantment> Enchantment::getMagicWeaponEffect(Character& wielder)
//{
//	float statInvestment = wielder.getIntelligence();
//	float damage = 50 + (statInvestment * 1.75) * (statInvestment / (statInvestment + 50));
//	std::shared_ptr<Enchantment> magicWeapon = std::make_shared<Enchantment>(true, false, "Magic Weapon", "Magical energy surrounds the weapon granting it additional damage and armor penetration", 1, false, 1, 1, false);
//
//	std::shared_ptr<Effect> magicDamage = std::make_shared<Effect>(true, false, "Magic Damage", "Turbulent Magical Energy Tears at its Target", 0.0f, 0.0f, damage, false, 1, 1, false);
//	magicDamage->setMagicDamage(MagicDamageType::MAGIC, damage);
//
//	std::shared_ptr<Effect> magicCleave = std::make_shared<Effect>(false, false, "Armor Penetration", "Magical energy cuts through steel and scale like butter bypassing defenses", 0.0f, 1, damage * 0.3f, false, 1, 1, false);
//
//	magicWeapon->effects.push_back(magicCleave);
//	magicWeapon->effects.push_back(magicDamage);
//	return magicWeapon;
//}
//
////ARMOR
//std::shared_ptr<Enchantment> Enchantment::getMagicArmorEffect(Character& wielder)
//{
//	float statInvestment = wielder.getIntelligence();
//	float speed = 50.0f + (statInvestment * 1.0f) * (statInvestment / (statInvestment + 50.0f));
//	std::shared_ptr<Enchantment> magicArmor = std::make_shared<Enchantment>(false, false, "Magic Armor", "Magical energy imbues the armor, increasing the wielder's cast speed", 1, false, 1, 1, false);
//	std::shared_ptr<Effect> castSpeed = std::make_shared<Effect>(false, false, "Cast Speed", "The wearer's cast speed is increased", 0.0f, 0.0f, speed, true, 1, 4, false);
//	magicArmor->effects.push_back(castSpeed);
//	return magicArmor;
//}
//std::shared_ptr<Enchantment> Enchantment::getLightningArmorEffect(Character& wielder)
//{
//	float statInvestment = wielder.getIntelligence();
//	float damage = 50.0f + (statInvestment * 0.5f) * (statInvestment / (statInvestment + 50.0f));
//	std::shared_ptr<Enchantment> lightningArmor = std::make_shared<Enchantment>(true, false, "Lightning Armor", 
//		"The armor crackles with electricity, damaging those in melee range", 1, false, 1, 1, false);
//	std::shared_ptr<Effect> shockDamage = std::make_shared<Effect>(true, false, "Shocking Thorns", "The target is shocked by the armor", 
//		 10.0f, 1.0f, damage, false, 1, 1, true);
//	shockDamage->setMagicDamage(MagicDamageType::SHOCK, damage);
//	lightningArmor->effects.push_back(shockDamage);
//	return lightningArmor;
//}
//std::shared_ptr<Enchantment> Enchantment::getBloodArmorEffect(Character& wielder)
//{
//	float statInvestment = wielder.getArcane();
//	float damage = 50.0f + (statInvestment * 0.5f) * (statInvestment / (statInvestment + 50.0f));
//	std::shared_ptr<Enchantment> bloodArmor = std::make_shared<Enchantment>(true, false, "Blood Armor",
//		"Accursed blood pours out from the cracks in the armor, coating enemies that strike it!", 
//		1, false, 1, 1, false);
//	std::shared_ptr<Effect> bleed = std::make_shared<Effect>(true, true, "Blood Splash", "Cursed blood splashes from the attacked armor, coating the attacker!",
//		0.0f, 1, damage, false, 1, 1, false);
//	bleed->setMagicDamage(MagicDamageType::BLEED, damage);
//	bloodArmor->effects.push_back(bleed);
//	return bloodArmor;
//}
//std::shared_ptr<Enchantment> Enchantment::getFrostArmorEffect(Character& wielder)
//{
//	float statInvestment = wielder.getIntelligence();
//	float damage = 50.0f + (statInvestment * 0.5f) * (statInvestment / (statInvestment + 50.0f));
//	std::shared_ptr<Enchantment> iceArmor = std::make_shared<Enchantment>(true, false, "Frost Armor", "Frigid air surrounds the armor, dealing frost burst buildup and slowing down enemies in melee range",
//		1.0f, false, 1, 1, true);
//	std::shared_ptr<Effect> frostDamage = std::make_shared<Effect>(true, false, "Frost Armor", "The target is affected by the frigid air seeping off of the armor", 
//		 10.0f, 1.0f, damage, false, 1, 1, true);
//	frostDamage->setMagicDamage(MagicDamageType::FROST, damage);
//	iceArmor->effects.push_back(frostDamage);
//	return iceArmor;
//}
//std::shared_ptr<Enchantment> Enchantment::getFireArmorEffect(Character& wielder)
//{
//
//}
//std::shared_ptr<Enchantment> Enchantment::getPoisonArmorEffect(Character& wielder)
//{
//
//}
//std::shared_ptr<Enchantment> Enchantment::getWindArmorEffect(Character& wielder)
//{
//
//}
//std::shared_ptr<Enchantment> Enchantment::getEarthenArmorEffect(Character& wielder)
//{
//
//}
//std::shared_ptr<Enchantment> Enchantment::getSleepArmorEffect(Character& wielder)
//{
//
//}
//std::shared_ptr<Enchantment> Enchantment::getHolyArmorEffect(Character& wielder)
//{
//
//}
//std::shared_ptr<Enchantment> Enchantment::getDarkArmorEffect(Character& wielder)
//{
//
//}

float Enchantment::getEnchantmentDamage(std::shared_ptr<Character> target, Enchantment Enchantment)
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
		float cumulativeSlashDamage = Enchantment.getPhysicalDamage(PhysicalDamageType::SLASH) - (Enchantment.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = Enchantment.getPhysicalDamage(PhysicalDamageType::PIERCE) - (Enchantment.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = Enchantment.getPhysicalDamage(PhysicalDamageType::BLUNT) - (Enchantment.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = Enchantment.getPhysicalDamage(PhysicalDamageType::CHOP) - (Enchantment.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = Enchantment.getMagicDamage(MagicDamageType::MAGIC) - (Enchantment.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = Enchantment.getMagicDamage(MagicDamageType::FIRE) - (Enchantment.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = Enchantment.getMagicDamage(MagicDamageType::FROST) - (Enchantment.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = Enchantment.getMagicDamage(MagicDamageType::SHOCK) - (Enchantment.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = Enchantment.getMagicDamage(MagicDamageType::POISON) - (Enchantment.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = Enchantment.getMagicDamage(MagicDamageType::BLEED) - (Enchantment.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = Enchantment.getMagicDamage(MagicDamageType::SLEEP) - (Enchantment.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = Enchantment.getMagicDamage(MagicDamageType::DARK) - (Enchantment.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = Enchantment.getMagicDamage(MagicDamageType::HOLY) - (Enchantment.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = Enchantment.getMagicDamage(MagicDamageType::WIND) - (Enchantment.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float EnchantmentDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
		EnchantmentDamage = std::max(EnchantmentDamage, 0.0f);

		return EnchantmentDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}

//void Enchantment::applyPassiveEnchantment(std::shared_ptr<Character> wielder)
//{
//	for (std::shared_ptr<Effect> effect : this->effects)
//	{
//		effect->applyPassiveEffect(effect, wielder);
//	}
//}
//void Enchantment::applyDefensiveEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Character> attacker)
//{
//	for (std::shared_ptr<Effect> effect : this->effects)
//	{
//		effect->applyDefensiveEffect(effect, wielder, attacker);
//	}
//}
//void Enchantment::applyOffensiveEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target)
//{
//	for (std::shared_ptr<Effect> effect : this->effects)
//	{
//		effect->applyOffensiveEffect(effect, wielder, target);
//	}
//	//WEAPONS -------------------------------------------------------------------------------------
//
//	//magic causes bonus magical damage which penetrates physical armor and tough scales
//
//	//Lightning does bonus damage and slows enemy movement speed
//
//	//Bleeding does damage over time. 
//
//	//Frost does bonus damage and slows movement speed and attack speed
//
//	//Fire does damage over time and has a chance to cause low hp enemies to panic
//
//	//Poison does damage over time and it can stack with itself.
//
//	//Wind pushes enemies back a tiny bit each strike
//
//	//Earthen coats the sword in jagged rocks that does bonus physical damage  
//
//	//Sleep slows enemy movement and attack speed and drains mama
//
//	//Holy does bonus damage to undead and demons
//
//	//Dark does bonus damage to living creatures and drains confidence, but reduced damage to undead demons 
//
//	//ARMOR ----------------------------------------------------------------------------------------
//
//	//magic increases the cast speed of the wearer
//
//	//Lightning causes arcs of electricity to strike enemies that hit the armor
//
//	//Blood causes a splash of blood to coat enemies that hit the armor
//
//	//Frost slows enemy movement speed and attack speed near the wearer
//
//	//Fire increases the wearer's strength
//
//	//Poison causes a splash of venom when enemies hit the wearer
//
//	//Wind increases the wearer's agility
//
//	//Earthen gives a tiny passive health regen and increases physical defense 
//
//	//Sleep increases the wearer's fatigue 
//
//	//Holy gives a small passive health regeneration
//
//	//Dark increases all defenses besides physical
//}

void Enchantment::removeEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Enchantment> enchant)
{
	for (std::shared_ptr<Effect> effect : enchant->effects)
	{
		effect->removeEffect(wielder, *effect);
	}
}

void Enchantment::interactWith(Enchantment& otherEnchantment)
{
	//BOTH WEAPONS AND ARMOR

	//Fire and frost cancel each other out

	//WEAPONS

	//fire and lightning causes an explosion that does the remaining damage of the fire
	//successive attacks with wind causes an airburst which knocks back enemies

	//successive attacks with bleed causes a hemmorage which does percentage based health damage (10% of max health)

	//successive attacks with sleep put an enemy to sleep for 1 turn and drain 30% of their mana

	//successive attacks with frost causes a frostbite which does percentage damage to health and leaves a lingering slow debuff

	//holy and fire causes a divine explosion that does damage to all creatures

	//dark and fire causes the damage over time effect to drain confidence and do double damage

	//dark and holy cancels each other out (removes buffs from holy armaments)

	//ARMOR

	//dark and holy cancel each other out

	//fire and frost cancel each other out

	//fire burns away earthen enchantments

	//holy and earthen create a healing aura that heals allies along with the wearer

	//dark and earthen create a miasma which does damage to enemies and reduces their confidence
}