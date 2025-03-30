#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DialogueManager.h"
#include "DialogueNode.h"
class Tools
{

};

class DialogueBuilder
{
public:
	void processDialogueTree(std::string folderPath);

	DialogueBuilder() = default;
	~DialogueBuilder() = default;
};