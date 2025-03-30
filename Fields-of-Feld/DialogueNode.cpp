#include "DialogueNode.h"

//Constructor
DialogueNode::DialogueNode(std::string thisNodeName, std::string text, std::string speakerName, std::string listenerName, std::string conndition,
	bool playerBefore, bool playOnce, int weight, std::string eventName)


{
	this->thisNodeName = thisNodeName;
	this->text = text;
	this->speakerName = speakerName;
	this->listenerName = listenerName;
	this->condition = conndition;
	this->playedBefore = playerBefore;
	this->playOnce = playOnce;
	this->weight = weight;
	this->eventName = eventName;
}

//JSON Serialization
nlohmann::json DialogueNode::toJson() const
{
	json j;
	j["thisNodeName"] = thisNodeName;
	j["text"] = text;
	j["speakerName"] = speakerName;
	j["listenerName"] = listenerName;
	j["condition"] = condition;
	j["playedBefore"] = playedBefore;
	j["playOnce"] = playOnce;
	j["weight"] = weight;
	j["eventName"] = eventName;
	//Only save the key of the node to avoid infinite recursion 
	for (const auto& [key, value] : nodes)
	{
		j["nodes"].push_back(key);
	}
	return j;
}

std::shared_ptr<DialogueNode> DialogueNode::fromJson(const nlohmann::json& j)
{
	std::shared_ptr<DialogueNode> node = std::make_shared<DialogueNode>();
	try
	{
		if (j.contains("thisNodeName")) {
			node->thisNodeName = j["thisNodeName"];
		}

		if (j.contains("text")) {
			node->text = j["text"];
		}

		if (j.contains("speakerName")) {
			node->speakerName = j["speakerName"];
		}

		if (j.contains("listenerName")) {
			node->listenerName = j["listenerName"];
		}

		if (j.contains("condition")) {
			node->condition = j["condition"];
		}

		if (j.contains("playedBefore")) {
			node->playedBefore = j["playedBefore"];
		}

		if (j.contains("playOnce")) {
			node->playOnce = j["playOnce"];
		}

		if (j.contains("weight")) {
			node->weight = j["weight"];
		}

		if (j.contains("eventName")) {
			node->eventName = j["eventName"];
		}

		if (j.contains("nodes") && j["nodes"].is_array())
		{
			for (const auto& nodeName : j["nodes"])
			{
				node->nodes[nodeName] = nullptr; // Placeholder for stitching
			}
		}

	}
	catch (const std::exception& e)
	{
		std::cerr << "Error parsing dialogue node: " << e.what() << std::endl;
	}
	return node;
}

