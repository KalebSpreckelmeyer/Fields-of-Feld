#include "Event.h"
#include "GameState.h"
#include <iostream>

Event::Event(std::string eventId, std::string eventName, std::string eventDescription, std::vector<std::shared_ptr<Character>> spawnedCharacters,
	std::vector<std::shared_ptr<Item>> spawnedItems, bool alreadyTriggered, std::string dialogueTriggerId)
{
	this->eventId = eventId;
	this->eventName = eventName;
	this->eventDescription = eventDescription;
	this->spawnedCharacters = spawnedCharacters;
	this->spawnedItems = spawnedItems;
	this->alreadyTriggered = alreadyTriggered;
	this->dialogueTriggerId = dialogueTriggerId;
}



//JSON Serialization
std::shared_ptr<Event> Event::fromJson(const nlohmann::json& j)
{
	std::string type = j.at("type").get<std::string>();
	if (type == "Ambush") return AmbushEvent::fromJson(j);

	std::cerr << "Unknown event type: " << type << std::endl;
	return nullptr;
}
// ------- AMBUSH -------- // 

AmbushEvent::AmbushEvent(std::string eventId, std::string eventName, std::string eventDescription,
	std::vector<std::shared_ptr<Character>> spawnedCharacters,
	std::vector<std::shared_ptr<Item>> spawnedItems,
	bool alreadyTriggered,
	std::string dialogueTriggerId)
	: Event(eventId, eventName, eventDescription, spawnedCharacters, spawnedItems, alreadyTriggered, dialogueTriggerId)
{
}

//JSON Serialization
nlohmann::json AmbushEvent::toJson() const
{
	nlohmann::json j;
	j["type"] = getType();
	j["eventId"] = eventId;
	j["eventName"] = eventName;
	j["eventDescription"] = eventDescription;
	j["alreadyTriggered"] = alreadyTriggered;
	for (const auto& character : spawnedCharacters)
	{
		j["spawnedCharacters"].push_back(character->toJson());
	}
	for (const auto& item : spawnedItems)
	{
		j["spawnedItems"].push_back(item->toJson());
	}
	j["dialogueTriggerId"] = dialogueTriggerId;
	return j;
}

std::shared_ptr<Event> AmbushEvent::fromJson(const nlohmann::json& j)
{
	std::string eventId = j.at("eventId").get<std::string>();
	std::string eventName = j.at("eventName").get<std::string>();
	std::string eventDescription = j.at("eventDescription").get<std::string>();
	bool alreadyTriggered = j.at("alreadyTriggered").get<bool>();
	std::string dialogueTriggerId = j.at("dialogueTriggerId").get<std::string>();
	std::vector<std::shared_ptr<Character>> spawnedCharacters;
	for (const auto& character : j.at("spawnedCharacters"))
	{
		spawnedCharacters.push_back(Character::fromJson(character));
	}
	std::vector<std::shared_ptr<Item>> spawnedItems;
	if (j.contains("spawnedItems")) {
		for (const auto& itemJson : j["spawnedItems"]) {
			spawnedItems.push_back(Item::fromJson(itemJson));
		}
	}
	return std::make_shared<AmbushEvent>(eventId, eventName, eventDescription, spawnedCharacters, spawnedItems ,alreadyTriggered, dialogueTriggerId);
}

std::string AmbushEvent::getType() const
{
	return "Ambush";
}

void AmbushEvent::executeEvent(GameState& state) const
{
	state.advanceTime(30);
	//Trigger dialogue
	//Spawn enemies
}