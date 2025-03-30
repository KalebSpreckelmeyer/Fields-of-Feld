#pragma once
#include <unordered_map>
#include <string>
#include "Location.h"
class LocationManager
{
public:
	//Central storage for all locations
	std::unordered_map<std::string, std::shared_ptr<Location>> allLocations;

	//Populate allLocations with data from JSON
	void loadAllLocationsFromJson(const std::string& folderPath);

	//Save location data to JSON so player can impact the world
	void saveLocationsToFile(const std::string& folderPath) const;

	//Stitch all the nodes together
	// Necessary as you can't do this while loading each location from JSON as the nodes they connect to may not have been loaded yet
	void resolveNodeReferences();

	//Get a location by name
	Location getLocationByName(std::string name);
};

