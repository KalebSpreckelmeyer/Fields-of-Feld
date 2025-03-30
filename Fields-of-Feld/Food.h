#pragma once
#include "Consumable.h"
class Food :
    public Consumable
{
public:
	int id;

	std::vector<std::shared_ptr<Effect>> effects;

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Food() = default;
	Food(std::string name, std::string description, float magnitude, float weight, float quantity, float value);
	~Food() = default;
	void use(std::shared_ptr<Character> consumer) override;
};

