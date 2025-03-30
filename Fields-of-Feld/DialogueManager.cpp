#include "DialogueManager.h"
#include <iostream>  
#include <filesystem>  
#include <fstream>  
#include "color.hpp"
#include "GameState.h"
#include "Spell.h"
#include "Human.h"

namespace fs = std::filesystem;

void DialogueManager::loadDialogueNodesFromFolder(const std::string& folderPath) {
	//Load all dialogues from master JSON file  
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_regular_file() && entry.path().extension() == ".json") {
			std::ifstream file(entry.path());
			if (!file.is_open()) {
				std::cerr << "Failed to open dialogue file: " << entry.path() << std::endl;
				continue;
			}
			try {
				nlohmann::json j;
				file >> j;
				for (const auto& [key, value] : j.items())
				{
					auto dialogueNode = DialogueNode::fromJson(value);
					if (dialogueNode && dialogueNode->thisNodeName.empty())
					{
						// Fallback if thisNodeName was not explicitly set
						dialogueNode->thisNodeName = key;
					}

					if (dialogueNode && !dialogueNode->thisNodeName.empty())
					{
						allDialogues[dialogueNode->thisNodeName] = dialogueNode;
					}
					else
					{
						std::cerr << "[ERROR] Skipping invalid dialogue node." << std::endl;
					}
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Error parsing dialogue file " << entry.path()
					<< ": " << e.what() << std::endl;
			}
		}
	}
	DialogueManager::resolveNodeReferences();
}

void DialogueManager::saveDialoguesToFile(const std::string& folderPath) const {
	nlohmann::json j;
	for (const auto& [name, dialoguePtr] : allDialogues) {
		if (dialoguePtr) {
			j[name] = dialoguePtr->toJson();
		}
	}
	std::ofstream outFile(folderPath);
	if (!outFile.is_open()) {
		std::cerr << "Failed to open file for writing: " << folderPath << "\n";
		return;
	}
	outFile << j.dump(4); // Pretty print with indent
	std::cout << "Dialogues saved successfully to " << folderPath << "\n";
}

void DialogueManager::resolveNodeReferences()
{
	for (auto& [dialogueName, dialoguePointer] : allDialogues)
	{
		if (!dialoguePointer) continue;
		for (auto& [nodeName, nodePointer] : dialoguePointer->nodes)
		{
			if (allDialogues.count(nodeName) && allDialogues[nodeName]) {
				nodePointer = allDialogues[nodeName];
			}
			else {
				std::cerr << "Could not resolve node: " << nodeName << " from dialogue: " << dialoguePointer->thisNodeName << "\n";
			}
		}
	}
}

std::shared_ptr<DialogueNode> DialogueManager::getDialogueByName(std::string name)
{
	auto it = allDialogues.find(name);
	if (it != allDialogues.end())
	{
		return it->second;
	}
	else
	{
		std::cerr << "Dialogue not found: " << name << std::endl;
		return std::shared_ptr<DialogueNode>();
	}
}

bool DialogueManager::evaluateCondition(const std::string& condition, GameState game)
{
	if (condition == " " || condition == "null" || condition.empty()) return true;
	std::shared_ptr<Human> player = game.playerCharacter;
	//Get player equipment
	std::shared_ptr<Weapon> mainHand, offHand, reserve1, reserve2;
	std::shared_ptr<Armor> head, chest, legs, arms;
	std::shared_ptr<Trinket> amulet, ring1, ring2, misc;
	player->inventory.getEquippedItems(mainHand, offHand, reserve1, reserve2, head, chest, legs, arms, amulet, ring1, ring2, misc);
	//Get player spells
	
	// WEAPON CHECKS
	if (condition == "hasChopWeapon")
	{
		if (mainHand && mainHand->getDamage(DamageTypes::CHOP) > 0) return true;
		if (offHand && offHand->getDamage(DamageTypes::CHOP) > 0) return true;
		if (reserve1 && reserve1->getDamage(DamageTypes::CHOP) > 0) return true;
		if (reserve2 && reserve2->getDamage(DamageTypes::CHOP) > 0) return true;
	}

	// SPELL CHECKS
	if (condition == "hasFireBoltSpell")
	{
		for (const auto& spell : player->attunedSpells)
		{
			if (spell && spell->name == "Fire Bolt") return true;
			if (spell && spell->name == "Fireball") return true;
			if (spell && spell->name == "Captive Sun") return true;
		}
	}
	if (condition == "hasForceBurstSpell")
	{
		for (const auto& spell : player->attunedSpells)
		{
			if (spell && spell->name == "Holy Gust") return true;
			if (spell && spell->name == "Holy Gale") return true;
			if (spell && spell->name == "Holy Burst") return true;
		}
	}
	if (condition == "hasThunderBoltSpell")
	{
		for (const auto& spell : player->attunedSpells)
		{
			if (spell && spell->name == "Lightning Bolt") return true;
			if (spell && spell->name == "Thunder Bolt") return true;
			if (spell && spell->name == "Plasma Bolt") return true;
		}
	}

	// STAT CHECKS
	std::string stat = "";
	std::string comparison = "";
	std::string value = "";
	for (char c : condition)
	{
		if (isalpha(c)) stat += c;
		if (c == '>' || c == '<' || c == '=') comparison += c;
		if (isdigit(c)) value += c;
	}
	if (stat == "strength")
	{
		if (comparison == ">") return player->strength > std::stoi(value);
		if (comparison == "<") return player->strength < std::stoi(value);
		if (comparison == "=") return player->strength == std::stoi(value);
		if (comparison == ">=") return player->strength >= std::stoi(value);
		if (comparison == "<=") return player->strength <= std::stoi(value);
	}
	if (stat == "agility")
	{
		if (comparison == ">") return player->agility > std::stoi(value);
		if (comparison == "<") return player->agility < std::stoi(value);
		if (comparison == "=") return player->agility == std::stoi(value);
		if (comparison == ">=") return player->agility >= std::stoi(value);
		if (comparison == "<=") return player->agility <= std::stoi(value);
	}
	if (stat == "intelligence")
	{
		if (comparison == ">") return player->intelligence > std::stoi(value);
		if (comparison == "<") return player->intelligence < std::stoi(value);
		if (comparison == "=") return player->intelligence == std::stoi(value);
		if (comparison == ">=") return player->intelligence >= std::stoi(value);
		if (comparison == "<=") return player->intelligence <= std::stoi(value);
	}
	if (stat == "charisma")
	{
		if (comparison == ">") return player->charisma > std::stoi(value);
		if (comparison == "<") return player->charisma < std::stoi(value);
		if (comparison == "=") return player->charisma == std::stoi(value);
		if (comparison == ">=") return player->charisma >= std::stoi(value);
		if (comparison == "<=") return player->charisma <= std::stoi(value);
	}
	if (stat == "faith")
	{
		if (comparison == ">") return player->faith > std::stoi(value);
		if (comparison == "<") return player->faith < std::stoi(value);
		if (comparison == "=") return player->faith == std::stoi(value);
		if (comparison == ">=") return player->faith >= std::stoi(value);
		if (comparison == "<=") return player->faith <= std::stoi(value);
	}
	if (stat == "arcane")
	{
		if (comparison == ">") return player->arcane > std::stoi(value);
		if (comparison == "<") return player->arcane < std::stoi(value);
		if (comparison == "=") return player->arcane == std::stoi(value);
		if (comparison == ">=") return player->arcane >= std::stoi(value);
		if (comparison == "<=") return player->arcane <= std::stoi(value);
	}
	if (stat == "health")
	{
		if (comparison == ">") return player->health > std::stoi(value);
		if (comparison == "<") return player->health < std::stoi(value);
		if (comparison == "=") return player->health == std::stoi(value);
		if (comparison == ">=") return player->health >= std::stoi(value);
		if (comparison == "<=") return player->health <= std::stoi(value);
	}
	if (stat == "fatigue")
	{
		if (comparison == ">") return player->fatigue > std::stoi(value);
		if (comparison == "<") return player->fatigue < std::stoi(value);
		if (comparison == "=") return player->fatigue == std::stoi(value);
		if (comparison == ">=") return player->fatigue >= std::stoi(value);
		if (comparison == "<=") return player->fatigue <= std::stoi(value);
	}
	return false;
}

void DialogueManager::playDialogue(const std::string& startingName, GameState& game) {
	std::shared_ptr<DialogueNode> current = getDialogueByName(startingName);
	if (!current) {
		std::cerr << "Dialogue not found: " << startingName << std::endl;
		return;
	}
	
	if (current->playedBefore && current->playOnce) return;
	
	//Get the player character's name
	std::string playerName = game.playerCharacter->name;

	while (current)
	{
		//Dynamically insert player name into conversation
		if (current->speakerName == "Player") current->speakerName = playerName;
		if (current->listenerName == "Player") current->listenerName = playerName;
		
		//Print dialogue of this node
		std::cout << "=--->" << std::endl;
		std::cout << dye::light_yellow(" " + current->speakerName + ": ") << current->text << std::endl;

		//If there are no more nodes, end the dialogue
		if (current->nodes.empty())
		{
			std::cout << dye::light_yellow("\n [End of dialogue]\n");
			break;
		}

		//For now, progress the dialogue automatically if the player is the speaker. 
		if (current->speakerName == playerName)
		{
			current->playedBefore = true;
			current = current->nodes.begin()->second;
		}
		//NPC or Narrator is the speaker: present the player with response options but favor the one with higher weight
		else
		{
			int choice = 0;
			std::vector<std::string> keys;
			do
			{
				std::cout << "=--->" << std::endl;
				std::cout << dye::light_yellow(" Options: ") << std::endl;
				int weight = 1;
				int index = 1;
				std::unordered_map<std::string, std::shared_ptr<DialogueNode>> validNodes;
				std::unordered_map<std::string, std::shared_ptr<DialogueNode>> heaviestNode; // Placeholder for the heaviest node
				for (const auto& [key, node] : current->nodes)
				{
					//Dont display nodes that don't meed the condition
					if (!evaluateCondition((node->condition), game)) continue;
					//Skip nodes that have played before and can only be played once
					if (current->playedBefore && current->playOnce) continue;
					//find if any nodes have a higher weight
					if (node->weight > weight)
					{
						weight = node->weight;
						heaviestNode[key] = node;
					}
					validNodes[key] = node;
				}
				if (weight > 1)
				{
					for (const auto& [key, node] : heaviestNode)
					{
						std::cout << " " << dye::light_yellow(std::to_string(index) + ") ") << key << std::endl;
						keys.push_back(key);
						index++;
					}

				}
				else
				{
					for (const auto& [key, node] : validNodes)
					{
						std::cout << " " << dye::light_yellow(std::to_string(index) + ") ") << key << std::endl;
						keys.push_back(key);
						index++;
					}
				}
				std::cout << "=--->" << std::endl;
				std::cout << ">> ";
				std::cin >> choice;
				if (choice < 1 || choice > keys.size())
				{
					std::cout << dye::red("Invalid choice. Try again.") << std::endl;
				}
			} while (choice < 1 || choice > keys.size());
			current->playedBefore = true;
			current = current->nodes[keys[choice - 1]];
		}
	}
}