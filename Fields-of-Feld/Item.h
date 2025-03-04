#pragma once

#include <string>
#include <sstream>

enum item_types { LOOT = 0, WEAPON = 1, ARMOR = 2, CONSUMABLE = 3};
enum item_rarity { COMMON = 0, UNCOMMON = 1, RARE = 2, EPIC = 3, LEGENDARY = 4};

class Item
{
private:
	std::string name;
	unsigned type;
	unsigned rarity;
	unsigned value;
	unsigned reach;

	void generate();
public:
	Item(std::string name,
		unsigned type,
		unsigned rarity,
		unsigned value,
		unsigned reach);
	virtual ~Item();

	//Accessors

	const std::string& getName();
	const unsigned& getType();
	const unsigned& getRarity();
	const unsigned& getValue();

	//Functions
	const std::string toString() const;
};

