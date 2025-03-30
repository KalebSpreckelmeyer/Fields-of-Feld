#include "LocationManager.h"  
#include <iostream>  
#include <filesystem>  
#include <fstream>  

namespace fs = std::filesystem;

void LocationManager::loadAllLocationsFromJson(const std::string& folderPath)
{
	//Load all locations from master JSON file  
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_regular_file() && entry.path().extension() == ".json") {
			std::ifstream file(entry.path());
			if (!file.is_open()) {
				std::cerr << "Failed to open location file: " << entry.path() << std::endl;
				continue;
			}

			try {
				nlohmann::json j;
				file >> j;

				for (const auto& locJson : j) {
					Location loc = Location::fromJson(locJson);
					allLocations[loc.name] = std::make_shared<Location>(std::move(loc));
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Error parsing location file " << entry.path()
					<< ": " << e.what() << std::endl;
			}
		}
	}
	//After all are loaded:  
	resolveNodeReferences();
}

void LocationManager::saveLocationsToFile(const std::string& filePath) const {
	nlohmann::json j;
	for (const auto& [name, locationPtr] : allLocations) {
		if (locationPtr) {
			j[name] = locationPtr->toJson();
		}
	}

	std::ofstream outFile(filePath);
	if (!outFile.is_open()) {
		std::cerr << "Failed to open file for writing: " << filePath << "\n";
		return;
	}

	outFile << j.dump(4); // Pretty print with indent
	std::cout << "Locations saved successfully to " << filePath << "\n";
}

void LocationManager::resolveNodeReferences()
{
	for (auto& [locationName, locationPointer] : allLocations)
	{
		for (auto& [nodeName, nodePointer] : locationPointer->nodes)
		{
			auto it = allLocations.find(nodeName);
			if (it != allLocations.end())
			{
				nodePointer = it->second;
			}
			else
			{
				std::cerr << "Error: Node " << nodeName << " not found in allLocations" << std::endl;
			}
		}
	}
}

Location LocationManager::getLocationByName(std::string name)
{
	auto it = allLocations.find(name);
	if (it != allLocations.end())
	{
		return *it->second;
	}
	else
	{
		std::cerr << "Error: Location " << name << " not found in allLocations" << std::endl;
		return Location();
	}
}