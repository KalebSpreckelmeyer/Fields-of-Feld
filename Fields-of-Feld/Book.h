#pragma once
#include "Consumable.h"
class Book :
    public Consumable
{
public:
	int id;
	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	std::vector<std::shared_ptr<Effect>> effects;

	Book() = default;
	Book(std::string name, std::string description, float magnitude, float weight, float quantity, float value);
	~Book() = default;
	void use(std::shared_ptr<Character> consumer) override;
};

