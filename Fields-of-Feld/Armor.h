#pragma once
#include "Item.h"
class Armor :
    public Item
{
public:
    float defense = 0.0f;
    bool isLight = false;
    bool isMedium = false;
	bool isHeavy = false;
    enum class ArmorDescriptor { LEATHER, PADDED, STUDDEDLEATHER, CHAIN, LAMELLAR, SCALE, CHAINPLATE, BEASTSCALE, FULLPLATE };
	ArmorDescriptor armorDescriptor = ArmorDescriptor::LEATHER;

	Armor();

	Armor(std::string name, std::string description, float defense, float weight, float value, bool isLight, 
        bool isMedium, bool isHeavy, ArmorDescriptor armorDescriptor);

    ~Armor();
};

