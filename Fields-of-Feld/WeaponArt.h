#pragma once
#include <string>
#include <vector>
#include "Effect.h"
#include "IDManager.h"
class WeaponArt
{
public:
	int id;

	std::vector<std::shared_ptr<Effect>> effects;
	std::string name;
	std::string description;
	float fatigueCost;
	float range;
	bool useOnSelf;
	bool useOnEnemy;
	bool useOnAlly;

	WeaponArt();
	WeaponArt(std::string name, std::string description, float fatigueCost, float range, bool useOnSelf, bool useOnEnemy, bool useOnAlly);
	~WeaponArt() = default;

	nlohmann::json toJson() const;
	static std::shared_ptr<WeaponArt> fromJson(const nlohmann::json& j);;

};
