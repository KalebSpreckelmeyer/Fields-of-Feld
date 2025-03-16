#include "Trinket.h"
#include <string>


Trinket::Trinket()
{
}
Trinket::Trinket(Effect effect, TrinketType trinketType)
	: Item(true, name, description, value, weight, 1.0f, EquipSlots::BACKPACK),
	effect(effect), trinketType(trinketType)
{

}

Trinket::~Trinket()
{
}