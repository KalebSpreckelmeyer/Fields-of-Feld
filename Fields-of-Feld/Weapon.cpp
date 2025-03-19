#include "Weapon.h"
#include <string>
#include "Human.h"
#include <algorithm>

Weapon::Weapon()
{
}

Weapon::Weapon(bool specialDamage, std::string name, std::string description, float stability, float reach, float attackSpeed, float weight, float value,
	bool twohanded, bool needsAmmo, WeaponType weaponType, PhysicalDamageType physAttack, MagicDamageType magAttack, PhysicalDamageType physDefense, MagicDamageType magDefense, EquipSlots slot)
	: Item(true, name, description, physAttack, magAttack, value, weight, 1.0f, slot),
		specialDamage(specialDamage), reach(reach), 
		attackSpeed(attackSpeed), twoHanded(twohanded), needsAmmo(needsAmmo),
	weaponType(weaponType), stability(stability)
{
	//may beed to add mag and phys damage types to the last part of the constructor IDK
}

Weapon::~Weapon()
{
}

float Weapon::getWeaponDamage(Character* target, Weapon weapon)
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
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage) - human->flatDefense * (human->flatDefense / 500);;
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

float Weapon::getWeaponDefense(Character* target)
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
