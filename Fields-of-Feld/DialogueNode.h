#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "Character.h"

class DialogueNode
{
public:
	//Dialogue options in the tree
	std::unordered_map<std::string, std::shared_ptr<DialogueNode>> nodes;

	//Content
	std::string text;
	std::string thisNodeName;

	//Identifiers
	std::string speakerName;
	std::string listenerName;
	
	//Conditions and variables
	std::string condition;
	bool playedBefore = false;
	bool playOnce = false;
	int weight = 0;
	std::string eventName;

	//IMPLEMENT QUEST TRIGGERS WHEN QUESTS ARE IMPLEMENTED
	
	//Constructor
	DialogueNode() = default;
	DialogueNode(std::string thisNodeName, std::string text, std::string speakerName, std::string listenerName, std::string condition, 
		bool playerBefore, bool playOnce, int weight, std::string eventName);
	~DialogueNode() = default;

	//JSON Serialization
	nlohmann::json toJson() const;
	static std::shared_ptr<DialogueNode> fromJson(const nlohmann::json& j);
};
