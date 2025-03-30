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
	int id;
	std::unordered_map<DamageTypes, float>damageTypes;

	DamageTypes damage = DamageTypes::NONE;

	//Weapon Scaling Stats
	std::unordered_map<StatScaling, float> scalingStats;
	StatScaling scalingStat = StatScaling::NONE;

	//Weapon Requirements
	std::unordered_map<StatScaling, float> statRequirements;
	StatScaling statRequirement = StatScaling::NONE;

	bool specialDamage = false;
	float reach = 0.0f;
	float attackSpeed = 0.0f;

	std::vector<std::shared_ptr<Enchantment>> enchantments;

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	float getThrownConsumableDamage(std::shared_ptr<Character> target, ThrownConsumable consumable);

	void setDamage(DamageTypes damageType, float damageValue);

	float getDamage(DamageTypes damageType);

	float getThrownConsumableScalingValue(StatScaling);

	float getThrownConsumableRequirementValue(StatScaling);

	void setThrownConsumableScalingValue(StatScaling, float scalingValue);

	void setThrownConsumableRequirementValue(StatScaling, float requirementValue);

	ThrownConsumable();

	ThrownConsumable(bool specialDamage, std::string name, std::string description, float reach, float attackSpeed, float weight, float quantity, float value);

	~ThrownConsumable() = default;
};
#endif // !THROWNCONSUMABLE_H



