#include "Enchantment.h"
#include <string>

Enchantment::Enchantment(std::string name, std::string description, float duration, float magnitude, bool stackable,
	int stacks, int maxStacks, bool applied) :
	Effect(name, description, duration, magnitude, stackable, stacks, maxStacks)
{

}

Enchantment::~Enchantment()
{
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