#pragma once
#include <vector>
#include "Event.h"
#include "string"
#include <memory>
#include "GameState.h"

class Trigger
{
public:
	enum class TriggerType {
		ON_ENTER,
		ON_EXIT,
		ON_INTERACT,
		ON_LOOT,
		ON_TIME_OF_DAY,
		ON_KILL_NPC,
		ON_FIRST_VISIT
	};

	TriggerType type;
	std::string locationName;
	std::string conditionName;
	bool oneTimeOnly = false;

	std::shared_ptr<Event> event;

	//Constructors

	Trigger() = default;
	Trigger(TriggerType type, std::string locationName, std::string conditionName, bool oneTimeOnly, std::shared_ptr<Event> event);
	~Trigger() = default;

	//JSON serialization
	nlohmann::json toJson() const;
	static Trigger fromJson(const nlohmann::json& j);

	//Methods
	void triggerEvent(GameState& state);
};

