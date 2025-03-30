#include "Location.h"
#include <iostream>
//Constructors
Location::Location(std::string name, std::string description, bool accessibleByDefault)
{
	this->name = name;
	this->description = description;
	this->accessibleByDefault = accessibleByDefault;
}

//JSON Serialization
nlohmann::json Location::toJson() const
{
	json j;
	for (const auto& [key, value] : nodes)
	{
		j["nodes"].push_back(key);
	}
	for (const auto& [key, value] : nodeTravelTimes)
	{
		j["nodeTravelTimes"][key] = value;
	}
	j["name"] = name;
	j["description"] = description;
	j["accessibleByDefault"] = accessibleByDefault;
	for (const auto& [key, value] : flavorText)
	{
		j["flavorText"][key] = value;
	}
	//Consider adding a helper function here if the JSON is too hard to read
	for (const auto& condition : accessConditions)
	{
		j["accessConditions"].push_back(static_cast<int>(condition));
	}
	nlohmann::json containerJSON;
	for (const auto& [key, value] : containers)
	{
		containerJSON[key] = value->toJson();
	}
	j["containers"] = containerJSON;

	nlohmann::json characterJSON;
	for (const auto& [key, value] : characters)
	{
		characterJSON[key] = value->toJson();
	}
	j["characters"] = characterJSON;

	//nlohmann::json dialogueJSON;
	//for (const auto& [key, value] : dialogues)
	//{
	//	dialogueJSON[key] = value->toJson();
	//}
	//j["dialogues"] = dialogueJSON;

	for (const auto& trigger : triggers)
	{
		j["triggers"].push_back(trigger->toJson());
	}
	for (const auto& condition : ambientConditions)
	{
		j["ambientConditions"].push_back(static_cast<int>(condition));
	}

	return j;
}

Location Location::fromJson(const nlohmann::json& j) 
{
	try
	{
		Location location;
		if (j.contains("nodes") && j["nodes"].is_array()) {
			for (const auto& nodeName : j["nodes"]) {
				// Placeholder null for now — we will resolve this after all locations are loaded
				location.nodes[nodeName] = nullptr;
			}
		}

		//call this after all locations are loaded
		//for (auto& [locationName, loc] : allLocations) {
		//	for (auto& [nodeName, nodePtr] : loc->nodes) {
		//		if (allLocations.count(nodeName)) {
		//			nodePtr = allLocations[nodeName]; // Fix null pointer to actual location
		//		}
		//	}
		//}

		if (j.contains("nodeTravelTimes"))
		{
			for (const auto& [key, value] : j["nodeTravelTimes"].items())
			{
				location.nodeTravelTimes[key] = value;
			}
		}
		if (j.contains("name")) location.name = j["name"];
		if (j.contains("description")) location.description = j["description"];
		if (j.contains("accessibleByDefault")) location.accessibleByDefault = j["accessibleByDefault"];
		if (j.contains("flavorText"))
		{
			for (const auto& [key, value] : j["flavorText"].items())
			{
				location.flavorText[key] = value;
			}
		}
		if (j.contains("accessConditions"))
		{
			for (const auto& condition : j["accessConditions"])
			{
				location.accessConditions.push_back(static_cast<Location::AccessCondition>(condition));
			}
		}
		if (j.contains("containers"))
		{
			for (const auto& [key, value] : j["containers"].items())
			{
				location.containers[key] = Container::fromJson(value);
			}
		}
		if (j.contains("characters"))
		{
			for (const auto& [key, value] : j["characters"].items())
			{
				for (const auto& character : value)
				{
					location.characters[key] = Character::fromJson(character);
				}
			}
		}
		//if (j.contains("dialogues"))
		//{
		//	for (const auto& [key, value] : j["dialogues"].items())
		//	{
		//		location.dialogues[key] = Dialogue::fromJson(value);
		//	}
		//}
		if (j.contains("triggers"))
		{
			for (const auto& trigger : j["triggers"])
			{
				location.triggers.push_back(std::make_shared<Trigger>(Trigger::fromJson(trigger)));
			}
		}
		if (j.contains("ambientConditions"))
		{
			for (const auto& condition : j["ambientConditions"])
			{
				location.ambientConditions.push_back(static_cast<Location::AmbientCondition>(condition));
			}
		}

		return location;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing Location from JSON" << std::endl;
	}

	return Location();
}
//Methods