#include "Armor.h"
#include <vector>
#include <string>


Armor::Armor() {
}
Armor::Armor(std::string name, std::string description, float defense, float weight, float value, bool isLight, bool isMedium, 
	bool isHeavy, ArmorDescriptor armorDescriptor) : Item(true, name, description, value, weight, 1.0f, EquipSlots::BACKPACK),
	defense(defense), isLight(isLight), isMedium(isMedium), isHeavy(isHeavy), armorDescriptor(armorDescriptor)
{ 

}

Armor::~Armor() {
}