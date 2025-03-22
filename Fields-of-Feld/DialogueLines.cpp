#include "Dialogue.h"

void setupDialogue(std::vector<Dialogue>& dialogues, std::shared_ptr<Character> player, std::shared_ptr<Character> npc)
{
	//create dialogue nodes
	Dialogue greeting(npc, player, "What's up shitass", "Joking", 1, 1);

	Dialogue response(player, npc, "Fuck your life, BING BONG", "Joking", 1, 1);

	Dialogue farewell(npc, player, "I help anytime!", "Joking", 1, 1);

	//add responses 
	greeting.addResponse(response);
	response.addResponse(farewell);

	//store complete trees in a list

	dialogues.push_back(greeting);

}