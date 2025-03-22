#pragma once
#include "Consumable.h"
class Book :
    public Consumable
{
public:

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);


	Book() = default;
	Book(std::string name, std::string description, float magnitude, float weight, float quantity, float value);
	~Book() = default;
	void use() override;
};

