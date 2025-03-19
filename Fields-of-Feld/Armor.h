#pragma once
#include "Item.h"
#include <unordered_map>

class Armor :
    public Item
{
public:

    std::unordered_map<PhysicalDamageType, float> physicalResistance;
	std::unordered_map<MagicDamageType, float> magicResistance;

    bool isLight = false;
    bool isMedium = false;
	bool isHeavy = false;
    enum class ArmorDescriptor { LEATHER, PADDED, STUDDEDLEATHER, CHAIN, LAMELLAR, SCALE, CHAINPLATE, BEASTSCALE, FULLPLATE };
	ArmorDescriptor armorDescriptor = ArmorDescriptor::LEATHER;

	void setPhysicalResistance(PhysicalDamageType physType, float physResistance);

	void setMagicResistance(MagicDamageType magType, float magResistance);

	float getPhysicalResistance(PhysicalDamageType physType);

	float getMagicResistance(MagicDamageType magType);

	Armor();

	Armor(std::string name, std::string description, float weight, float value, bool isLight, 
        bool isMedium, bool isHeavy, ArmorDescriptor armorDescriptor, PhysicalDamageType physType, MagicDamageType magType);

    ~Armor();
};

