#include "Tools.h"
#include <regex>
#include <sstream>
#include "regex"

void DialogueBuilder::processDialogueTree(std::string folderPath)
{
	//Read from file
	std::ifstream file(folderPath, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file" << std::endl;
	}
	try
	{
		nlohmann::json j;
		file >> j;
		struct RawNode {
			std::vector<std::string> links;
			std::string text = "";
			std::string name = "";
			std::string speaker = "";
			std::string listener = "";
			std::string condition = "";
			std::string playOnce = "";
			std::string weight = "";
			std::string eventName = "";
		};

		std::vector<RawNode> rawNodes;

		if (j.contains("passages") && j["passages"].is_array())
		{
			for (auto& passage : j["passages"])
			{
				RawNode node;
				node.text = passage["text"];
				node.name = passage["name"];
				for (auto& link : passage["links"])
				{
					node.links.push_back(link["name"]);
				}
				rawNodes.push_back(node);
			}
		}
		
		//Split the text into useful chunks
		for (auto& node : rawNodes)
		{	
			//Raw text 
			std::string text = node.text;

			//separate the variable block from the rest of the text
			size_t start = node.text.find('{');
			size_t end = node.text.find('}');

			std::string betweenBraces = node.text.substr(start + 1, end - start - 1);
			
			//process the variable block
			std::vector<std::string> parts;
			char del = '-';
			std::stringstream ss(betweenBraces);
			std::string temp;

			//split the text into parts
			while (std::getline(ss, temp, del))
				parts.push_back(temp);

			//fallback in case a field was left empty by accident in Twine
			while (parts.size() < 6) parts.push_back("");

			//remove the processed text
			text.erase(start,end + 1);

			//remove the text in brackets
			size_t b1 = text.find('[');
			size_t b2;
			for (auto c = text.size(); c--;)
			{
				if (text[c] == ']')
				{
					b2 = c;
					break;
				}
			}

			if (b1 != std::string::npos && b1 < text.size() && b2 <= text.size() && b1 <= b2) {
				text.erase(b1, b2 - b1 + 1);
			}
			else {
			}
			//Erase leading new line characters

			text.erase(text.begin(), std::find_if(text.begin(), text.end(),
				[](int ch) { return !std::isspace(ch); }));

			//erase trailing whitespace
			text.erase(std::find_if(text.rbegin(), text.rend(),
				[](int ch) { return !std::isspace(ch); }).base(),
				text.end());

			//Assign values to final node object
			node.text = text;
			node.speaker = parts[0];
			node.listener = parts[1];
			node.condition = parts[2];
			node.playOnce = parts[3];
			node.weight = parts[4];
			node.eventName = parts[5];

			//Condition variable will be processed later in the play dialogue function
		}

		//Assemble the raw node into a dialogue tree
		std::unordered_map<std::string, std::shared_ptr<DialogueNode>> dialogueTree;
		for (const auto& raw : rawNodes) {
			auto node = std::make_shared<DialogueNode>();
			node->thisNodeName = raw.name;
			node->text = raw.text;
			node->speakerName = raw.speaker;
			node->listenerName = raw.listener;
			node->condition = raw.condition;
			node->playedBefore = false;
			if (raw.playOnce == "true") node->playOnce = true;
			if (raw.playOnce == "false") node->playOnce = false;
			node->weight = std::stoi(raw.weight);
			for (const auto& link : raw.links) {
				node->nodes[link] = nullptr; // placeholder for stitching
			}
			dialogueTree[node->thisNodeName] = node;
		}
		
		//Stitch the dialogue tree together
		for (auto& [dialogueName, dialoguePointer] : dialogueTree)
		{
			if (!dialoguePointer) continue;
			for (auto& [nodeName, nodePointer] : dialoguePointer->nodes)
			{
				if (dialogueTree.count(nodeName) && dialogueTree[nodeName]) {
					nodePointer = dialogueTree[nodeName];
				}
				else {
					std::cerr << "Could not resolve node: " << nodeName << " from dialogue: " << dialoguePointer->thisNodeName << "\n";
				}
			}
		}

		//Save the dialogue tree
		nlohmann::json i;
		for (const auto& [name, dialoguePtr] : dialogueTree) {
			if (dialoguePtr) {
				i[name] = dialoguePtr->toJson();
			}
		}
		std::ofstream outFile(folderPath);
		if (!outFile.is_open()) {
			std::cerr << "Failed to open file for writing: " << folderPath << "\n";
			return;
		}
		outFile << i.dump(4); // Pretty print with indent
		std::cout << "Dialogues saved successfully to " << folderPath << "\n";
	}
	catch (const nlohmann::json::exception& e)
	{
		std::cerr << "[ERROR] Failed to load DialogueNode from JSON: " << e.what() << std::endl;
	}
}