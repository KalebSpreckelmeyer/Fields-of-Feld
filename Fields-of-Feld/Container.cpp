#include "Container.h"
#include <iostream>

//Constructors
Container::Container(std::string id, bool owned, bool locked, const std::vector<AccessCondition> accessConditions, const std::vector<std::shared_ptr<Trigger>>& triggers,
	const std::vector<std::shared_ptr<Item>>& items)

{
	this->id = id;
	this->owned = owned;
	this->locked = locked;
	this->accessConditions = accessConditions;
	this->triggers = triggers;
	this->items = items;
}

//JSON Serialization
nlohmann::json Container::toJson() const
{
	nlohmann::json j;
	j["id"] = id;
	j["owned"] = owned;
	j["locked"] = locked;
	for (const auto& cond : accessConditions) {
		nlohmann::json condJson;
		condJson["item"] = cond.item;
		condJson["value"] = cond.value;
		j["accessConditions"].push_back(condJson);
	}
	for (const auto& trigger : triggers)
	{
		j["triggers"].push_back(trigger->toJson());
	}
	for (const auto& item : items)
	{
		j["items"].push_back(item->toJson());
	}
	return j;
}

std::shared_ptr<Container> Container::fromJson(const nlohmann::json& j)
{
	//Create a new container
	std::shared_ptr<Container> container = std::make_shared<Container>();
	try
	{
		//Set the container's properties
		container->id = j.at("id").get<std::string>();
		container->owned = j.at("owned").get<bool>();
		container->locked = j.at("locked").get<bool>();
		//Add access conditions
		if (j.contains("accessConditions")) {
			for (const auto& condJson : j["accessConditions"]) {
				AccessCondition cond;
				cond.item = condJson["item"];
				cond.value = condJson["value"];
				container->accessConditions.push_back(cond);
			}
		}
		//Add triggers
		for (const auto& trigger : j.at("triggers"))
		{
			container->triggers.push_back(std::make_shared<Trigger>(Trigger::fromJson(trigger)));
		}
		//Add items
		for (const auto& item : j.at("items"))
		{
			container->items.push_back(Item::fromJson(item));
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing Container from JSON" << std::endl;
		return nullptr;
	}
	return container;
}

//Methods
void Container::unlockContainer()
{
	locked = false;
}

void Container::openContainer(GameState& state)
{
	//progress time
	state.advanceTime(5);
	//Trigger events
	//Display items
}

void Container::addItem(std::shared_ptr<Item> item)
{
	items.push_back(item);
}

void Container::addMultipleItems(std::vector<std::shared_ptr<Item>>& items)
{
	for (const auto& item : items)
	{
		this->items.push_back(item);
	}
}