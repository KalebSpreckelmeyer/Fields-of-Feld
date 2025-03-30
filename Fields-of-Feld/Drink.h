#pragma once
#include "Consumable.h"
class Drink :
    public Consumable
{
public:
	int id;
	std::vector<std::shared_ptr<Effect>> effects;

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Drink() = default;
	Drink(std::string name, std::string description,
		float magnitude, float weight, float quantity, float value);
	~Drink() = default;
	void use(std::shared_ptr<Character> consumer) override;
};

