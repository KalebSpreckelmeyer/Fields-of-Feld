#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Inventory.h"
#include "Container.h"
#include "Character.h"
#include "Trigger.h"

class Location
{
public:
	//Locations you can travel to from this location
	std::unordered_map<std::string, std::shared_ptr<Location>> nodes;

	//Time it takes to travel to those locations
	std::unordered_map<std::string, int> nodeTravelTimes;

	//Descriptors
	std::string name = "Location Name";
	std::string description = "Location Description";
	std::unordered_map<std::string, std::string> flavorText;

	//Accessing the location
	bool accessibleByDefault = true;

	enum class AccessCondition {
		NEEDS_KEY, 
		NEEDS_ITEM,
		NEEDS_QUEST_COMPLETED,
		NEEDS_QUEST_STARTED
	};

	std::vector<AccessCondition> accessConditions;

	//Containers in the location
	std::unordered_map<std::string, std::shared_ptr<Container>> containers;

	//Characters in the location
	std::unordered_map<std::string, std::shared_ptr<Character>> characters;

	//Dialogue starting nodes in this location
	//std::unordered_map<std::string, std::shared_ptr<Dialogue>> dialogues;

	//Events and Triggers
	//Triggers contain events which are triggered by certain conditions
	std::vector<std::shared_ptr<Trigger>> triggers;
	//Consider storing triggers globally if global events become a thing
	
	//Ambient Conditions
	enum class AmbientCondition {
		RAIN,
		SNOW,
		FOG,
		THUNDERSTORM,
		CLEAR,
		COLD,
		HOT, 
		WINDY
	};
	std::vector<AmbientCondition> ambientConditions;

	//Constructors

	Location() = default;
	Location(std::string name, std::string description, bool accessibleByDefault);
	~Location() = default;

	//JSON serialization
	nlohmann::json toJson() const;
	static Location fromJson(const nlohmann::json& j);

	//Methods
	// --- implement here later ---
};

