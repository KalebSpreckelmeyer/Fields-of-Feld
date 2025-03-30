#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Character.h"

class GameState
{
//Time is stored in minutes and accessed to get hours, days, etc.
//Time is passed by traveling, interacting with objects, enemy encounters, entering/exiting locations, etc.
//Time is used to determine when events happen, when characters are available, etc.
private:
	int minutesPassed = 0;
public:
	void advanceTime(int minutes);
	int getMinutes() const;
	int getHours() const;
	int getDays() const;
	std::string getDayOfTheWeek() const;
	std::string getTime() const;

	//Player state:
	std::string currentLocation;
	std::shared_ptr<Human> playerCharacter;

	//Global states in relation to the player:
public:
	struct LocationState
	{
		std::string locationName = "";
		bool visited = false;
		bool enemiesCleared = false;
		bool itemsLooted = false;
		std::vector<std::string> customFlags;
		std::unordered_map<std::string, std::shared_ptr<Character>> defeatedEnemies;

		//Json serialization
		nlohmann::json toJson() const;
		static LocationState fromJson(const nlohmann::json& j);
	};
public:
	struct DialogueState
	{
		std::string dialogueId;
		bool played;
		std::vector<std::string> customFlags;

		//Json serialization
		nlohmann::json toJson() const;
		static DialogueState fromJson(const nlohmann::json& j);
	};
public:
	struct QuestState
	{
		std::string questId;
		bool started;
		bool completed;
		std::vector<std::string> customFlags;

		//Json serialization
		nlohmann::json toJson() const;
		static QuestState fromJson(const nlohmann::json& j);
	};
	std::unordered_map<std::string, LocationState> locationStates;
	std::unordered_map<std::string, DialogueState> dialogueStates;
	std::unordered_map<std::string, QuestState> questStates;

	//Constructors
	GameState() = default;
	GameState(std::string currentLocation, std::shared_ptr<Human> playerCharacter);
	~GameState() = default;

	//Json serialization
	nlohmann::json toJson() const;
	static GameState fromJson(const nlohmann::json& j);
};

