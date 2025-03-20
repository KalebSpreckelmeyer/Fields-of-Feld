#include "Trinket.h"
#include <string>


Trinket::Trinket()
{
}
Trinket::Trinket(TrinketType trinketType)
	: Item(true, name, description, value, weight, 1.0f, EquipSlots::BACKPACK),
	 trinketType(trinketType)
{

}

Trinket::~Trinket()
{
}