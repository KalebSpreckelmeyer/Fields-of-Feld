#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DialogueNode.h"
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "GameState.h"
#include "fstream"
class DialogueManager
{
public:
	//Central storage for all dialogue trees
	std::unordered_map<std::string, std::shared_ptr<DialogueNode>> allDialogues;

	//Populate all dialogues with data from JSON
	void loadDialogueNodesFromFolder(const std::string& folderPath);

	//Save dialogue data to JSON so dialogue flags can be set (e.g. playedBefore)
	void saveDialoguesToFile(const std::string& folderPath) const;

	//Stitch all the dialogue nodes together
	void resolveNodeReferences();

	//Get the start of a dialogue tree by name
	std::shared_ptr<DialogueNode> getDialogueByName(std::string name);

	//Parse the string condition into a usable value and evaluate it
	bool evaluateCondition(const std::string& condition, GameState game);

	//Start a conversation
	void playDialogue(const std::string& startingName, GameState& game);
};

//while (current)
//{
//	//Player is the one speaking
//	if (current->speakerName == "PLAYERNAME")
//	{
//		std::cout << dye::light_yellow(" " + playerName + ": ") << current->text << std::endl;
//
//		current->playedBefore = true;
//
//		if (current->nodes.empty())
//		{
//			std::cout << "\n [End of dialogue]\n";
//			break;
//		}
//
//		std::cout << "=--->" << std::endl;
//		std::cout << dye::light_yellow(" Options: ") << std::endl;
//		int index = 1;
//		std::vector<std::string> keys;
//		for (const auto& [key, node] : current->nodes)
//		{
//			std::cout << " " << dye::light_yellow(std::to_string(index) + ") ") << key << std::endl;
//			keys.push_back(key);
//			index++;
//		}
//		std::cout << "=--->" << std::endl;
//		std::cout << ">> ";
//		int choice;
//		std::cin >> choice;
//
//		if (choice > 0 && choice <= keys.size())
//		{
//			std::string selectedKey = keys[choice - 1];
//			current = current->nodes[selectedKey];
//		}
//		else
//		{
//			std::cout << "Invalid choice. Please try again.\n";
//		}
//	}
//	//NPC is the one speaking
//	else
//	{
//		std::cout << dye::light_yellow(" " + current->speakerName + ": ") << current->text << std::endl;
//	}
//
//	current->playedBefore = true;
//
//	if (current->nodes.empty())
//	{
//		std::cout << "\n [End of dialogue]\n";
//		break;
//	}
//	std::cout << "=--->" << std::endl;
//	auto start = current->nodes.begin();
//	current = start->second;
//}