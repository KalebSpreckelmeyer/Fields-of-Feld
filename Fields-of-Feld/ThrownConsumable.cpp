#include "ThrownConsumable.h"
#include "Item.h"
#include "Human.h"

ThrownConsumable::ThrownConsumable(bool specialDamage, std::string name, std::string description, float reach, float attackSpeed, float weight, float quantity, float value)
	: Item(hasBeenInitialized, name, description, value, weight, quantity, slot), 
	specialDamage(specialDamage), reach(reach), attackSpeed(attackSpeed)
{
}

nlohmann::json ThrownConsumable::toJson() const
{
	return{
		{"id", id },
		{ "type", "ThrownConsumable"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "specialDamage", specialDamage },
		{ "reach", reach },
		{ "attackSpeed", attackSpeed }
	};
}

std::shared_ptr<Item> ThrownConsumable::fromJson(const nlohmann::json& j)
{
	auto thrownConsumable = std::make_shared<ThrownConsumable>(
		j.at("specialDamage"),
		j.at("name"),
		j.at("description"),
		j.at("reach"),
		j.at("attackSpeed"),
		j.at("weight"),
		j.at("quantity"),
		j.at("value"));
	thrownConsumable->id = j.at("id");
	return thrownConsumable;
}

float ThrownConsumable::getThrownConsumableDamage(std::shared_ptr<Character> target, ThrownConsumable consumable)
{
	//Target is human
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
		float cumulativeSlashDamage = consumable.getPhysicalDamage(PhysicalDamageType::SLASH) - (consumable.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = consumable.getPhysicalDamage(PhysicalDamageType::PIERCE) - (consumable.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = consumable.getPhysicalDamage(PhysicalDamageType::BLUNT) - (consumable.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = consumable.getPhysicalDamage(PhysicalDamageType::CHOP) - (consumable.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = consumable.getMagicDamage(MagicDamageType::MAGIC) - (consumable.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = consumable.getMagicDamage(MagicDamageType::FIRE) - (consumable.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = consumable.getMagicDamage(MagicDamageType::FROST) - (consumable.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = consumable.getMagicDamage(MagicDamageType::SHOCK) - (consumable.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = consumable.getMagicDamage(MagicDamageType::POISON) - (consumable.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = consumable.getMagicDamage(MagicDamageType::BLEED) - (consumable.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = consumable.getMagicDamage(MagicDamageType::SLEEP) - (consumable.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = consumable.getMagicDamage(MagicDamageType::DARK) - (consumable.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = consumable.getMagicDamage(MagicDamageType::HOLY) - (consumable.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = consumable.getMagicDamage(MagicDamageType::WIND) - (consumable.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float consumableDamage = (cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage);
		consumableDamage = std::max(consumableDamage, 0.0f);

		return consumableDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}

void ThrownConsumable::setPhysicalDamage(PhysicalDamageType physType, float physDamage)
{
	physicalDamages[physType] = physDamage;
}

void ThrownConsumable::setMagicDamage(MagicDamageType magType, float magDamage)
{
	magicDamages[magType] = magDamage;
}

float ThrownConsumable::getPhysicalDamage(PhysicalDamageType physType)
{
	auto it = physicalDamages.find(physType);
	return (it != physicalDamages.end()) ? it->second : 0.0f;
}

float ThrownConsumable::getMagicDamage(MagicDamageType magType)
{
	auto it = magicDamages.find(magType);
	return (it != magicDamages.end()) ? it->second : 0.0f;
}

float ThrownConsumable::getThrownConsumableScalingValue(StatScaling)
{
	auto it = scalingStats.find(scalingStat);
	return (it != scalingStats.end()) ? it->second : 0.0f;
}

float ThrownConsumable::getThrownConsumableRequirementValue(StatScaling)
{
	auto it = statRequirements.find(statRequirement);
	return (it != statRequirements.end()) ? it->second : 0.0f;
}

void ThrownConsumable::setThrownConsumableScalingValue(StatScaling, float scalingValue)
{
	scalingStats[scalingStat] = scalingValue;
}

void ThrownConsumable::setThrownConsumableRequirementValue(StatScaling, float requirementValue)
{
	statRequirements[statRequirement] = requirementValue;
}