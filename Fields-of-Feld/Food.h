#pragma once
#include "Consumable.h"
class Food :
    public Consumable
{
public:

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Food() = default;
	Food(std::string name, std::string description, float magnitude, float weight, float quantity, float value);
	~Food() = default;
	void use() override;
};

