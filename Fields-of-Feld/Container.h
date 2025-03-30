#pragma once
#include <string>
#include <vector>
#include "memory"
#include "Trigger.h"
#include "Item.h"
#include "GameState.h"
class Container
{
public:
	//Accessing the container
	std::string id;
	bool owned = false;
	bool locked = false;
	struct AccessCondition {
		std::string item; //key, spell, etc...
		std::string value; //key name, spell name, etc...
	};

	std::vector<AccessCondition> accessConditions;

	//Events to happen when interacting with the container
	std::vector<std::shared_ptr<Trigger>> triggers;

	//Items in the container
	std::vector<std::shared_ptr<Item>> items;

	//Constructors
	Container() = default;
	Container(std::string id, bool owned, bool locked, const std::vector<AccessCondition> accessConditions, const std::vector<std::shared_ptr<Trigger>>& triggers, 
		const std::vector<std::shared_ptr<Item>>& items);
	~Container() = default;

	//JSON Serialization
	nlohmann::json toJson() const;
	static std::shared_ptr<Container> fromJson(const nlohmann::json& j);

	//Methods
	void unlockContainer();
	void openContainer(GameState& state);

	void addItem(std::shared_ptr<Item> item);
	void addMultipleItems(std::vector<std::shared_ptr<Item>>& items);
};

