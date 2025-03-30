#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Character.h"
#include "Item.h"
#include "GameState.h"

class Event
{
public:
	std::string eventId;
	std::string eventName;
	std::string eventDescription;
	std::vector<std::shared_ptr<Character>> spawnedCharacters;
	std::vector<std::shared_ptr<Item>> spawnedItems;
	std::string dialogueTriggerId;
	bool alreadyTriggered = false;

	//Constructor
	Event(std::string eventId , std::string eventName, std::string eventDescription, std::vector<std::shared_ptr<Character>> spawnedCharacters,
		std::vector<std::shared_ptr<Item>> spawnedItems, bool alreadyTriggered, std::string dialogueTriggerId);

	//JSON serialization
	virtual nlohmann::json toJson() const = 0;
	static std::shared_ptr<Event> fromJson(const nlohmann::json& j);
	virtual void executeEvent(GameState& state) const = 0;
};

class AmbushEvent : public Event
{
public:
	std::vector<std::shared_ptr<Character>> enemies;

	//Constructor
	AmbushEvent(std::string eventId, std::string eventName, std::string eventDescription,
		std::vector<std::shared_ptr<Character>> spawnedCharacters,
		std::vector<std::shared_ptr<Item>> spawnedItems,
		bool alreadyTriggered,
		std::string dialogueTriggerId);
	//JSON serialization
	nlohmann::json toJson() const;
	static std::shared_ptr<Event> fromJson(const nlohmann::json& j);

	//Methods
	std::string getType() const;
	void executeEvent(GameState& state) const override;
};


