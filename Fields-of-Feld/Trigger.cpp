#include "Trigger.h"
#include "Event.h"
#include <iostream>

//Constructors
Trigger::Trigger(TriggerType type, std::string locationName, std::string conditionName, bool oneTimeOnly, std::shared_ptr<Event> event)
{
	this->type = type;
	this->locationName = locationName;
	this->conditionName = conditionName;
	this->event = event;
	this->oneTimeOnly = oneTimeOnly;
}

//JSON Serialization
nlohmann::json Trigger::toJson() const
{
	nlohmann::json j;
	j["type"] = static_cast<int>(type);
	j["locationName"] = locationName;
	j["conditionName"] = conditionName;
	j["oneTimeOnly"] = oneTimeOnly;
	if (event) {
		j["event"] = event->toJson();
	}
	return j;
}
Trigger Trigger::fromJson(const nlohmann::json& j)
{
	Trigger trigger;
	try
	{
		if (j.contains("type")) trigger.type = static_cast<TriggerType>(j["type"]);
		if (j.contains("locationName")) trigger.locationName = j["locationName"];
		if (j.contains("conditionName")) trigger.conditionName = j["conditionName"];
		if (j.contains("oneTimeOnly")) trigger.oneTimeOnly = j["oneTimeOnly"];
		if (j.contains("event")) trigger.event = Event::fromJson(j["event"]);
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing Trigger from JSON" << std::endl;
	}
	return trigger;
}
//Methods

void Trigger::triggerEvent(GameState& state) {
	if (event && (!oneTimeOnly || !event->alreadyTriggered)) {
		event->executeEvent(state);
		event->alreadyTriggered = true; 
	}
}