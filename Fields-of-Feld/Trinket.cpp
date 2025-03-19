#include "Trinket.h"
#include <string>


Trinket::Trinket()
{
}
Trinket::Trinket(Effect effect, TrinketType trinketType, PhysicalDamageType physType, MagicDamageType magType)
	: Item(true, name, description, physType, magType, value, weight, 1.0f, EquipSlots::BACKPACK),
	effect(effect), trinketType(trinketType)
{

}

Trinket::~Trinket()
{
}