#include "Ammunition.h"
#include <iostream>
#include "PhysicalDamageType.h"
#include "MagicDamageType.h"
#include "Human.h"

Ammunition::Ammunition()
{
}

Ammunition::Ammunition(bool specialDamage, bool hasBeenInitialized, std::string name, std::string description, 
	PhysicalDamageType physType, MagicDamageType magType, float value, float weight,
	float quantity, EquipSlots slot, float range, AmmoType ammoType)
	: Item(hasBeenInitialized, name, description, physType, magType, value, weight, quantity, slot), specialDamage(specialDamage), range(range), ammoType(ammoType)
{
}

Ammunition::~Ammunition()
{
}

void Ammunition::setPhysicalDamage(PhysicalDamageType physType, float physDamage)
{
	physicalDamage[physType] = physDamage;
}

void Ammunition::setMagicDamage(MagicDamageType magType, float magDamage)
{
	magicDamage[magType] = magDamage;
}

float Ammunition::getPhysicalDamage(PhysicalDamageType physType)
{
	return physicalDamage[physType];
}

float Ammunition::getMagicDamage(MagicDamageType magType)
{
	return magicDamage[magType];
}

float Ammunition::getAmmoDamage(Character* target, Ammunition ammo)
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
		float cumulativeSlashDamage = ammo.getPhysicalDamage(PhysicalDamageType::SLASH) - (ammo.getPhysicalDamage(PhysicalDamageType::SLASH) * (cumulativeSlashResist / 500));
		cumulativeSlashDamage = std::max(cumulativeSlashDamage, 0.0f);
		float cumulativePierceDamage = ammo.getPhysicalDamage(PhysicalDamageType::PIERCE) - (ammo.getPhysicalDamage(PhysicalDamageType::PIERCE) * (cumulativePierceResist / 500));
		cumulativePierceDamage = std::max(cumulativePierceDamage, 0.0f);
		float cumulativeBluntDamage = ammo.getPhysicalDamage(PhysicalDamageType::BLUNT) - (ammo.getPhysicalDamage(PhysicalDamageType::BLUNT) * (cumulativeBluntResist / 500));
		cumulativeBluntDamage = std::max(cumulativeBluntDamage, 0.0f);
		float cumulativeChopDamage = ammo.getPhysicalDamage(PhysicalDamageType::CHOP) - (ammo.getPhysicalDamage(PhysicalDamageType::CHOP) * (cumulativeChopResist / 500));
		cumulativeChopDamage = std::max(cumulativeChopDamage, 0.0f);

		float cumulativeMagicDamage = ammo.getMagicDamage(MagicDamageType::MAGIC) - (ammo.getMagicDamage(MagicDamageType::MAGIC) * (cumulativeMagicResist / 500));
		cumulativeMagicDamage = std::max(cumulativeMagicDamage, 0.0f);
		float cumulativeFireDamage = ammo.getMagicDamage(MagicDamageType::FIRE) - (ammo.getMagicDamage(MagicDamageType::FIRE) * (cumulativeFireResist / 500));
		cumulativeFireDamage = std::max(cumulativeFireDamage, 0.0f);
		float cumulativeIceDamage = ammo.getMagicDamage(MagicDamageType::FROST) - (ammo.getMagicDamage(MagicDamageType::FROST) * (cumulativeIceResist / 500));
		cumulativeIceDamage = std::max(cumulativeIceDamage, 0.0f);
		float cumulativeShockDamage = ammo.getMagicDamage(MagicDamageType::SHOCK) - (ammo.getMagicDamage(MagicDamageType::SHOCK) * (cumulativeShockResist / 500));
		cumulativeShockDamage = std::max(cumulativeShockDamage, 0.0f);
		float cumulativePoisonDamage = ammo.getMagicDamage(MagicDamageType::POISON) - (ammo.getMagicDamage(MagicDamageType::POISON) * (cumulativePoisonResist / 500));
		cumulativePoisonDamage = std::max(cumulativePoisonDamage, 0.0f);
		float cumulativeBleedDamage = ammo.getMagicDamage(MagicDamageType::BLEED) - (ammo.getMagicDamage(MagicDamageType::BLEED) * (cumulativeBleedResist / 500));
		cumulativeBleedDamage = std::max(cumulativeBleedDamage, 0.0f);
		float cumulativeSleepDamage = ammo.getMagicDamage(MagicDamageType::SLEEP) - (ammo.getMagicDamage(MagicDamageType::SLEEP) * (cumulativeSleepResist / 500));
		cumulativeSleepDamage = std::max(cumulativeSleepDamage, 0.0f);
		float cumulativeDarkDamage = ammo.getMagicDamage(MagicDamageType::DARK) - (ammo.getMagicDamage(MagicDamageType::DARK) * (cumulativeDarkResist / 500));
		cumulativeDarkDamage = std::max(cumulativeDarkDamage, 0.0f);
		float cumulativeHolyDamage = ammo.getMagicDamage(MagicDamageType::HOLY) - (ammo.getMagicDamage(MagicDamageType::HOLY) * (cumulativeHolyResist / 500));
		cumulativeHolyDamage = std::max(cumulativeHolyDamage, 0.0f);
		float cumulativeWindDamage = ammo.getMagicDamage(MagicDamageType::WIND) - (ammo.getMagicDamage(MagicDamageType::WIND) * (cumulativeWindResist / 500));
		cumulativeWindDamage = std::max(cumulativeWindDamage, 0.0f);

		//DAMAGE AFTER RESISTANCES = damage of all damages after resistances applied added together	
		float ammoDamage = cumulativeSlashDamage + cumulativePierceDamage + cumulativeBluntDamage + cumulativeChopDamage +
			cumulativeMagicDamage + cumulativeFireDamage + cumulativeIceDamage + cumulativeShockDamage + cumulativePoisonDamage +
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage;

		return ammoDamage;
	}
	//Target is creature
	else
	{
		//TODO
		return 0;
	}
}