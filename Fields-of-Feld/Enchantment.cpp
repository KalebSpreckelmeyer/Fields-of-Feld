#include "Enchantment.h"
#include <string>
#include "Human.h"
#include <algorithm>

Enchantment::Enchantment(std::string name, std::string description, PhysicalDamageType physDmg, MagicDamageType magDmg, float duration, float magnitude, bool stackable,
	int stacks, int maxStacks, bool applied, bool doesDamage) :
	Effect(doesDamage, applied, name, description, physDmg, magDmg, duration, magnitude, stackable, stacks, maxStacks, areaOfEffect)
{

}

Enchantment::~Enchantment()
{
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

float Enchantment::getEnchantmentDamage(Character* target, Enchantment Enchantment)
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
			cumulativeBleedDamage + cumulativeSleepDamage + cumulativeDarkDamage + cumulativeHolyDamage + cumulativeWindDamage) - human->flatDefense * (human->flatDefense / 500);
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
void Enchantment::applyEnchantment()
{
	//WEAPONS -------------------------------------------------------------------------------------

	//magic causes bonus magical damage which penetrates physical armor and tough scales

	//Lightning does bonus damge and slows enemy movement speed

	//Bleeding does damage over time. 

	//Frost does bonus damage and slows movement speed and attack speed

	//Fire does damage over time and has a chance to cause low hp enemies to panic

	//Poison does damage over time and it can stack with itself.

	//Wind pushes enemies back a tiny bit each strike

	//Earthen coats the sword in jagged rocks that does bonus physical damage  

	//Sleep slows enemy movement and attack speed and drains mama

	//Holy does bonus damage to undead and demons

	//Dark does bonus damage to living creatures and drains confidence, but reduced damage to undead demons 

	//ARMOR ----------------------------------------------------------------------------------------

	//magic increases the magic defense of the wearer

	//Lightning causes arcs of electricity to strike nearby enemies

	//Blood increases the damage of blood loss 

	//Frost slows enemy movement speed and attack speed near the wearer

	//Fire causes enemies to take damage when they hit the wearer

	//Poison causes poison damage to increase

	//Wind causes enemies to be pushed back when they hit the wearer

	//Earthen gives a tiny passive health regen and increases physical defense 

	//Sleep causes enemies to remain asleep for longer

	//Holy gives a small passive health regeneration

	//Dark increases all defenses besides physical
}

void Enchantment::removeEnchantment()
{

}

void Enchantment::interactWith(Enchantment& otherEnchantment)
{
	//BOTH WEAPONS AND ARMOR
	
	//Fire and frost cancel each other out
	if (this->name == "Fire Weapon" && otherEnchantment.name == "Ice Weapon" || this->name == "Ice Armor" && otherEnchantment.name == "Fire Armor")
	{
		//this enchantment is removed
		this->removeEnchantment();
		//other enchantment is removed
		otherEnchantment.removeEnchantment();
	}
	if (this->name == "Fire Armor" && otherEnchantment.name == "Ice Armor" || this->name == "Ice Armor" && otherEnchantment.name == "Fire Armor")
	{
		//this enchantment is removed
		this->removeEnchantment();
		//other enchantment is removed
		otherEnchantment.removeEnchantment();
	}
	
	//WEAPONS
	
	//fire and lightning causes an explosion that does the remaining damage of the fire
	if (this->name == "Fire Weapon" && otherEnchantment.name == "Lightning Weapon" || this->name == "Lightning Weapon" &&
		otherEnchantment.name == "Fire Weapon")
	{
		//this enchantment is removed
		this->removeEnchantment(); 
		//other enchantment is removed
		otherEnchantment.removeEnchantment();
	}
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