#pragma once
#include "Item.h"
#include <unordered_map>
#include "Defense.h"
#include "Enchantment.h"
#include <vector>
#include "Ammunition.h"
class Armor :
    public Item
{
public:
	int id;
    std::unordered_map<Defense, float> defenses;

	//PhysicalDamageType physType = PhysicalDamageType::BLUNT;
	//DamageTypes magType = DamageTypes::NONE;
	bool isHead = false;
	bool isChest = false;
	bool isArms = false;
	bool isLegs = false;
    bool isLight = false;
    bool isMedium = false;
	bool isHeavy = false;
    enum class ArmorDescriptor { CLOTH, LEATHER, PADDED, STUDDEDLEATHER, CHAIN, LAMELLAR, SCALE, CHAINPLATE, BEASTSCALE, FULLPLATE };
	ArmorDescriptor armorDescriptor = ArmorDescriptor::LEATHER;

	std::vector<std::shared_ptr<Enchantment>> enchantments;

	void setDefenses(Defense physType, float physResistance);

	//void setMagicResistance(Defense magType, float magResistance);

	float getDefenses(Defense physType);

	float getArmorDefenseBase(std::shared_ptr<Armor> armor);

	float getArmorDefenses(std::shared_ptr<Character> target, std::shared_ptr<Armor> armor);

	//float getMagicResistance(Defense magType);

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Armor();

	Armor(std::string name, std::string description, float weight, float value, bool isHead, bool isChest, bool isArms, bool isLegs, bool isLight, 
        bool isMedium, bool isHeavy, ArmorDescriptor armorDescriptor, Item::EquipSlots slot);

    ~Armor();
};

