#include "Item.h"
#include <string>

Item::Item() {
}

Item::Item(bool hasBeenInitialized, std::string name, std::string description , float value, float weight, float quantity, Item::EquipSlots slot) :
	hasBeenInitialized(hasBeenInitialized), name(name), description(description)
	,value(value), weight(weight), quantity(quantity), slot(slot) {
}

Item::~Item() {
}

float Item::getScalingValue(float statValue, float scalingValue)
{
	
}