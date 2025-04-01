#include "WeaponArt.h"
#include "IDManager.h"
#include <iostream>

WeaponArt::WeaponArt()
{
	this->id = IDManager::getNextId();
}

WeaponArt::WeaponArt(std::string name, std::string description, float fatigueCost, float range, bool useOnSelf, bool useOnEnemy, bool useOnAlly)
{
	this->id = IDManager::getNextId();
}

nlohmann::json WeaponArt::toJson() const
{
	nlohmann::json j;
	j["id"] = this->id;
	j["name"] = this->name;
	j["description"] = this->description;
	j["fatigueCost"] = this->fatigueCost;
	j["range"] = this->range;
	j["useOnSelf"] = this->useOnSelf;
	j["useOnAlly"] = this->useOnAlly;
	j["useOnEnemy"] = this->useOnEnemy;
	j["effects"] = nlohmann::json::array();
	for (auto& effect : this->effects)
	{
		j["effects"].push_back(effect->toJson());
	}
	return j;
}

std::shared_ptr<WeaponArt> WeaponArt::fromJson(const nlohmann::json& j)
{
	std::shared_ptr<WeaponArt> weaponArt = std::make_shared<WeaponArt>();
	try
	{
		if (j.contains("id")) weaponArt->id = j.at("id").get<int>();
		if (j.contains("name")) weaponArt->name = j.at("name").get<std::string>();
		if (j.contains("description")) weaponArt->description = j.at("description").get<std::string>();
		if (j.contains("fatigueCost")) weaponArt->fatigueCost = j.at("fatigueCost").get<float>();
		if (j.contains("range")) weaponArt->range = j.at("range").get<float>();
		if (j.contains("useOnSelf")) weaponArt->useOnSelf = j.at("useOnSelf").get<bool>();
		if (j.contains("useOnEnemy")) weaponArt->useOnEnemy = j.at("useOnEnemy").get<bool>();
		if (j.contains("useOnAlly")) weaponArt->useOnAlly = j.at("useOnAlly").get<bool>();
		if (j.contains("effects"))
		{
			for (auto& effect : j.at("effects"))
			{
				weaponArt->effects.push_back(Effect::fromJson(effect));
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return nullptr;
	}
}