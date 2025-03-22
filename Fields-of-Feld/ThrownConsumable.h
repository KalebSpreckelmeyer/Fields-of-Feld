#ifndef THROWNCONSUMABLE_H
#define THROWNCONSUMABLE_H
#include <string>
#include "Item.h"
#include "Enchantment.h"
#include <vector>
#include <unordered_map>
#include "StatScaling.h"

class Enchantment;

class ThrownConsumable :
    public Item
{
public:
	std::unordered_map<PhysicalDamageType, float>physicalDamages;
	std::unordered_map<MagicDamageType, float> magicDamages;

	PhysicalDamageType physType = PhysicalDamageType::BLUNT;
	MagicDamageType magType = MagicDamageType::NONE;

	//Weapon Scaling Stats
	std::unordered_map<StatScaling, float> scalingStats;
	StatScaling scalingStat = StatScaling::NONE;

	//Weapon Requirements
	std::unordered_map<StatScaling, float> statRequirements;
	StatScaling statRequirement = StatScaling::NONE;

	bool specialDamage = false;
	float reach = 0.0f;
	float attackSpeed = 0.0f;
	float minRange = 0.0f;
	float maxRange = 0.0f;

	std::vector<std::shared_ptr<Enchantment>> enchantments;

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	float getThrownConsumableDamage(std::shared_ptr<Character> target, ThrownConsumable consumable);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getThrownConsumableScalingValue(StatScaling);

	float getThrownConsumableRequirementValue(StatScaling);

	void setThrownConsumableScalingValue(StatScaling, float scalingValue);

	void setThrownConsumableRequirementValue(StatScaling, float requirementValue);

	ThrownConsumable() = default;

	ThrownConsumable(bool specialDamage, std::string name, std::string description, float reach, float attackSpeed, float weight, float quantity, float value);

	~ThrownConsumable() = default;
};
#endif // !THROWNCONSUMABLE_H



