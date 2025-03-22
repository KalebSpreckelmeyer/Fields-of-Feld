#include "Armor.h"
#include <vector>
#include <string>
#include "Item.h"

Armor::Armor() {
}
Armor::Armor(std::string name, std::string description, float weight, float value, bool isLight, bool isMedium,
	bool isHeavy, ArmorDescriptor armorDescriptor) : 
	Item(true, name, description, value, weight, 1.0f, EquipSlots::BACKPACK),
	isLight(isLight), isMedium(isMedium), isHeavy(isHeavy), armorDescriptor(armorDescriptor)
{ 
	//sets physical resistances to the map to default values
	for (PhysicalDamageType type : {PhysicalDamageType::BLUNT, PhysicalDamageType::PIERCE,
		PhysicalDamageType::SLASH, PhysicalDamageType::CHOP})
	{
		physicalResistance[type] = 0.0f;
	}
	//sets magic resistances to the map to default values
	for (MagicDamageType type : { MagicDamageType::MAGIC, MagicDamageType::FIRE, MagicDamageType::FROST, 
		MagicDamageType::SHOCK, MagicDamageType::WIND, MagicDamageType::POISON, MagicDamageType::BLEED, 
		MagicDamageType::SLEEP, MagicDamageType::DARK, MagicDamageType::HOLY})
	{
		magicResistance[type] = 0.0f;
	}
}

Armor::~Armor() {
}

nlohmann::json Armor::toJson() const
{
	return {
		{"id", id},
		{ "type", "Armor"},
		{ "name", name },
		{ "description", description },
		{ "value", value },
		{ "weight", weight },
		{ "quantity", quantity },
		{ "slot", static_cast<int>(slot) },
		{ "isLight", isLight },
		{ "isMedium", isMedium },
		{ "isHeavy", isHeavy },
		{ "armorDescriptor", static_cast<int>(armorDescriptor) },
		{ "physicalResistance", physicalResistance },
		{ "magicResistance", magicResistance }
	};
}

std::shared_ptr<Item> Armor::fromJson(const nlohmann::json& j)
{
	auto armor = std::make_shared<Armor>(
		j.at("name"),
		j.at("description"),
		j.at("weight"),
		j.at("value"),
		j.at("isLight"),
		j.at("isMedium"),
		j.at("isHeavy"),
		static_cast<Armor::ArmorDescriptor>(j.at("armorDescriptor")));
	armor->id = j.at("id");
	armor->quantity = j.at("quantity");
	armor->physicalResistance = j.at("physicalResistance").get<std::unordered_map<PhysicalDamageType, float>>();
	armor->magicResistance = j.at("magicResistance").get<std::unordered_map<MagicDamageType, float>>();
	return armor;
}

void Armor::setPhysicalResistance(PhysicalDamageType physType, float physResistance)
{
	physicalResistance[physType] = physResistance;
}

void Armor::setMagicResistance(MagicDamageType magType, float magResistance)
{
	magicResistance[magType] = magResistance;
}

float Armor::getPhysicalResistance(PhysicalDamageType physType)
{
	auto it = physicalResistance.find(physType);
	return (it != physicalResistance.end()) ? it->second : 0.0f;
}

float Armor::Armor::getMagicResistance(MagicDamageType magType)
{
	auto it = magicResistance.find(magType);
	return (it != magicResistance.end()) ? it->second : 0.0f;
}