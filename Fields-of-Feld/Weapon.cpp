#include "Weapon.h"
#include <string>
#include "Human.h"
#include <algorithm>

Weapon::Weapon(bool specialDamage, std::string name, std::string description, float stability, float reach, 
	float attackSpeed, float weight, float value, bool twohanded, bool needsAmmo, 
	WeaponType weaponType, EquipSlots slot)
	: Item(true, name, description, value, weight, 1.0f, slot),
		specialDamage(specialDamage), reach(reach), 
		attackSpeed(attackSpeed), twoHanded(twohanded), needsAmmo(needsAmmo),
	weaponType(weaponType), stability(stability)
{
}

nlohmann::json Weapon::toJson() const
{
	return{
		{"id", id },
		{ "type", "Weapon"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "specialDamage", specialDamage },
		{ "reach", reach },
		{ "attackSpeed", attackSpeed },
		{ "twoHanded", twoHanded },
		{ "needsAmmo", needsAmmo },
		{ "stability", stability },
		{ "weaponType", weaponType }
	};
}

std::shared_ptr<Item> Weapon::fromJson(const nlohmann::json& j)
{
	auto weapon = std::make_shared<Weapon>(
		j.at("specialDamage"),
		j.at("name"),
		j.at("description"),
		j.at("stability"),
		j.at("reach"),
		j.at("attackSpeed"),
		j.at("weight"),
		j.at("value"),
		j.at("twoHanded"),
		j.at("needsAmmo"),
		j.at("weaponType"),
		j.at("slot"));
	weapon->id = j.at("id");
	return weapon;
}

float Weapon::getWeaponDamage(std::shared_ptr<Character> target, Weapon weapon)
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
		float cumulativeSlashDamage = weapon.getPhysicalDamage(PhysicalDamageType::SLASH) - (weapon.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = weapon.getPhysicalDamage(PhysicalDamageType::PIERCE) - (weapon.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = weapon.getPhysicalDamage(PhysicalDamageType::BLUNT) - (weapon.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = weapon.getPhysicalDamage(PhysicalDamageType::CHOP) - (weapon.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = weapon.getMagicDamage(MagicDamageType::MAGIC) - (weapon.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = weapon.getMagicDamage(MagicDamageType::FIRE) - (weapon.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = weapon.getMagicDamage(MagicDamageType::FROST) - (weapon.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = weapon.getMagicDamage(MagicDamageType::SHOCK) - (weapon.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = weapon.getMagicDamage(MagicDamageType::POISON) - (weapon.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = weapon.getMagicDamage(MagicDamageType::BLEED) - (weapon.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = weapon.getMagicDamage(MagicDamageType::SLEEP) - (weapon.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = weapon.getMagicDamage(MagicDamageType::DARK) - (weapon.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = weapon.getMagicDamage(MagicDamageType::HOLY) - (weapon.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = weapon.getMagicDamage(MagicDamageType::WIND) - (weapon.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float weaponDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
		weaponDamage = std::max(weaponDamage, 0.0f);

		return weaponDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}

float Weapon::getWeaponDefense(std::shared_ptr<Character> target)
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
		return 0;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}
void Weapon::setPhysicalDamage(PhysicalDamageType physType, float physDamage)
{
	physicalDamages[physType] = physDamage;
}

void Weapon::setMagicDamage(MagicDamageType magType, float magDamage)
{
	magicDamages[magType] = magDamage;
}

float Weapon::getPhysicalDamage(PhysicalDamageType physType)
{
	auto it = physicalDamages.find(physType);
	return (it != physicalDamages.end()) ? it->second : 0.0f;
}

float Weapon::getMagicDamage(MagicDamageType magType)
{
	auto it = magicDamages.find(magType);
	return (it != magicDamages.end()) ? it->second : 0.0f;
}

void Weapon::setPhysicalDefense(PhysicalDamageType physType, float physDefense)
{
	physicalResistance[physType] = physDefense;
}

void Weapon::setMagicDefense(MagicDamageType magType, float magDefense)
{
	magicResistance[magType] = magDefense;
}

float Weapon::getPhysicalDefense(PhysicalDamageType physType)
{
	auto it = physicalResistance.find(physType);
	return (it != physicalResistance.end()) ? it->second : 0.0f;
}

float Weapon::getMagicDefense(MagicDamageType magType)
{
	auto it = magicResistance.find(magType);
	return (it != magicResistance.end()) ? it->second : 0.0f;
}

float Weapon::getWeaponScalingValue(StatScaling)
{
	auto it = scalingStats.find(scalingStat);
	return (it != scalingStats.end()) ? it->second : 0.0f;
}

float Weapon::getWeaponRequirementValue(StatScaling)
{
	auto it = statRequirements.find(statRequirement);
	return (it != statRequirements.end()) ? it->second : 0.0f;
}

void Weapon::setWeaponScalingValue(StatScaling, float scalingValue)
{
	scalingStats[scalingStat] = scalingValue;
}

void Weapon::setWeaponRequirementValue(StatScaling, float requirementValue)
{
	statRequirements[statRequirement] = requirementValue;
}