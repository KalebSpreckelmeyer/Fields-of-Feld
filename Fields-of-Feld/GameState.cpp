#include "GameState.h"
#include <iostream>
#include "Human.h"
#include "Character.h"
//Constructors
GameState::GameState(std::string currentLocation, std::shared_ptr<Human> playerCharacter)
	: currentLocation(currentLocation), playerCharacter(playerCharacter)
{
}


//Json serialization

//LocationState ----------------------------------------------------------------------------------------------------------------------------------------- < LocationState
nlohmann::json GameState::LocationState::toJson() const
{
	nlohmann::json j;
	j["locationName"] = locationName;
	j["visited"] = visited;
	j["enemiesCleared"] = enemiesCleared;
	j["itemsLooted"] = itemsLooted;
	for (const auto& flag : customFlags)
	{
		j["customFlags"].push_back(flag);
	}
	//Consider creating a helper function if this is too hard to read in JSON format
	for (const auto& [key, value] : defeatedEnemies)
	{
		j["defeatedEnemies"][key] = value->toJson();
	}

	return j;
}
GameState::LocationState GameState::LocationState::fromJson(const nlohmann::json& j)
{
	try
	{
		LocationState state;
		if (j.contains("locationName"))   state.locationName = j["locationName"];
		if (j.contains("visited"))        state.visited = j["visited"];
		if (j.contains("enemiesCleared")) state.enemiesCleared = j["enemiesCleared"];
		if (j.contains("itemsLooted"))    state.itemsLooted = j["itemsLooted"];
		if (j.contains("customFlags"))
		{
			for (const auto& flag : j["customFlags"])
			{
				state.customFlags.push_back(flag);
			}
		}
		if (j.contains("defeatedEnemies"))
		{
			for (const auto& [key, value] : j["defeatedEnemies"].items())
			{
				state.defeatedEnemies[key] = Character::fromJson(value);
			}
		}
		return state;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing LocationState from JSON" << std::endl;
	}

	return LocationState();
}

//DialogueStat ------------------------------------------------------------------------------------------------------------------------------------------ < DialogueState
nlohmann::json GameState::DialogueState::toJson() const
{
	nlohmann::json j;
	j["dialogueId"] = dialogueId;
	j["played"] = played;

	for (const auto& flag : customFlags)
	{
		j["customFlags"].push_back(flag);
	}


	return j;
}
GameState::DialogueState GameState::DialogueState::fromJson(const nlohmann::json& j)
{
	try
	{
		DialogueState state;
		if (j.contains("dialogueId"))  state.dialogueId = j["dialogueId"];
		if (j.contains("played"))      state.played = j["played"];
		if (j.contains("customFlags"))
		{
			for (const auto& flag : j["customFlags"])
			{
				state.customFlags.push_back(flag);
			}
		}
		return state;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing DialogueState from JSON" << std::endl;
	}

	return DialogueState();
}
//QuestState ---------------------------------------------------------------------------------------------------------------------------------------------- < QuestState
nlohmann::json GameState::QuestState::toJson() const
{
	nlohmann::json j;
	j["questId"] = questId;
	j["started"] = started;
	j["completed"] = completed;

	for (const auto& flag : customFlags)
	{
		j["customFlags"].push_back(flag);
	}


	return j;
}
GameState::QuestState GameState::QuestState::fromJson(const nlohmann::json& j)
{
	try
	{
		QuestState state;
		if (j.contains("questId"))   state.questId = j["questId"];
		if (j.contains("started"))   state.started = j["started"];
		if (j.contains("completed")) state.completed = j["completed"];
		if (j.contains("customFlags"))
		{
			for (const auto& flag : j["customFlags"])
			{
				state.customFlags.push_back(flag);
			}
		}
		return state;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing QuestState from JSON" << std::endl;
	}

	return QuestState();
}

//GameState ---------------------------------------------------------------------------------------------------------------------------------------------- < GameState
nlohmann::json GameState::toJson() const
{
	nlohmann::json j;
	j["minutesPassed"] = minutesPassed;
	j["currentLocation"] = currentLocation;
	j["playerCharacter"] = playerCharacter->toJson();
	for (const auto& [key, value] : locationStates)
	{
		j["locationStates"][key] = value.toJson();
	}
	for (const auto& [key, value] : dialogueStates)
	{
		j["dialogueStates"][key] = value.toJson();
	}
	for (const auto& [key, value] : questStates)
	{
		j["questStates"][key] = value.toJson();
	}
	return j;
}

GameState GameState::fromJson(const nlohmann::json& j)  
{  
try  
{  
	GameState state;  
	if (j.contains("minutesPassed"))   state.minutesPassed = j["minutesPassed"];  
	if (j.contains("currentLocation")) state.currentLocation = j["currentLocation"];  
	if (j.contains("playerCharacter")) state.playerCharacter = std::dynamic_pointer_cast<Human>(Character::fromJson(j["playerCharacter"]));  
	if (j.contains("locationStates"))  
	{  
		for (const auto& [key, value] : j["locationStates"].items())  
		{  
			state.locationStates[key] = LocationState::fromJson(value);  
		}  
	}  
	if (j.contains("dialogueStates"))  
	{  
		for (const auto& [key, value] : j["dialogueStates"].items())  
		{  
			state.dialogueStates[key] = DialogueState::fromJson(value);  
		}  
	}  
	if (j.contains("questStates"))  
	{  
		for (const auto& [key, value] : j["questStates"].items())  
		{  
			state.questStates[key] = QuestState::fromJson(value);  
		}  
	}  
	return state;  
}  
catch (const std::exception&)  
{  
	std::cerr << "Error parsing GameState from JSON" << std::endl;  
}  

return GameState();  
}
void GameState::advanceTime(int minutes)
{
	minutesPassed += minutes;
}

int GameState::getMinutes() const
{
	return minutesPassed % 60;
}

int GameState::getHours() const
{
	return minutesPassed / 60 % 24;
}

int GameState::getDays() const
{
	return minutesPassed / 60 / 24 % 7;
}

std::string GameState::getDayOfTheWeek() const
{
	int day = getDays() % 7;
	if (day == 0) return "Sunday";
	if (day == 1) return "Monday";
	if (day == 2) return "Tuesday";
	if (day == 3) return "Wednesday";
	if (day == 4) return "Thursday";
	if (day == 5) return "Friday";
	if (day == 6) return "Saturday";
}

std::string GameState::getTime() const
{
	//Cleanly formatted clock time
	return std::to_string(getHours()) + ":" + (getMinutes() < 10 ? "0" : "") + std::to_string(getMinutes());
}