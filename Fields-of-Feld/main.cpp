#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include "color.hpp"
#include "Item.h"
#include "Character.h"
#include "Creature.h"
#include "optional"
#include "Weapon.h"
#include "Armor.h"
#include "Trinket.h"
#include "Human.h"
#include "Consumable.h"
#include "ThrownConsumable.h"
#include "nlohmann/json.hpp"
#include "Enchantment.h"
#include "Effect.h"
#include "Spell.h"
#include "Potion.h"
#include "DefensiveEffect.h"
#include "OffensiveEffect.h"
#include "ConsumableEffect.h"
#include "PassiveEffect.h"
#include <fstream>
#include "Food.h"
#include "Drink.h"
#include "Book.h"
#include "HelperFunctions.h"
#include "LootItem.h"
#include "DialogueManager.h"
#include "GameState.h"
#include "Tools.h"

using namespace std;
using json = nlohmann::json;

#pragma region Function Declarations

//DESC: Saves player information to file based on slot
//PRE: Player should be a valid human object
//POST: Player information will be saved to a file
void savePlayerToSlot(shared_ptr<Human> player, int slot);
//DESC: Loads a player from a file based on the slot provided
//PRE: File should be checked with isSlotEmpty first before loading
//POST: Returns the player loaded from the file
shared_ptr<Human> loadPlayerFromSlot(int slot);
//DESC: Checks a file to see if it is empty
//PRE: File should exist
//POST: Returns true if empty or corrupted, false if filled
bool isSlotEmpty(const string& fileName);
//DESC:
//PRE:
//POST:
void openCombat(std::shared_ptr<Human> player, shared_ptr<Character> enemy);
//DESC: Checks the passed save file to see if it is a valid save slot
//PRE: None
//POST: Returns true if slot is filled and valid, false if not
bool isValidSaveSlot(const std::string& filename);
//DESC: Main menu interface for the game
//PRE: None
//POST: None
void mainMenu();
//DESC:
//PRE:
//POST:
void playerTurn(std::shared_ptr<Human> player, shared_ptr<Weapon> weaponChoice, std::shared_ptr<Ammunition> ammoChoice, shared_ptr<Spell> spellChoice, shared_ptr<Character> targetChoice, std::shared_ptr<ThrownConsumable> thrownConsumableChoice,
	std::shared_ptr<Consumable> consumableChoice, float playerMovement, bool onlyMove);
#pragma endregion Function Declarations

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::unordered_map<int, std::shared_ptr<Item>> itemRegistry;
	std::unordered_map<int, std::shared_ptr<Character>> characterRegistry;
	std::unordered_map<int, std::shared_ptr<Spell>> spellRegistry;
	std::unordered_map<int, std::shared_ptr<Effect>> effectRegistry;
	std::unordered_map<int, std::shared_ptr<Enchantment>> enchantRegistry;
	mainMenu();
	return 0;
}

//helper function to get weapon reach. If weapon is null, return 0
inline float getWeaponReach(std::shared_ptr<Weapon> weapon)
{
	if (weapon)
	{
		return weapon->reach;
	}
	else
	{
		return -1;
	}
}

//helper function to get weapon name. If weapon is null, return ""
inline string getWeaponName(std::shared_ptr<Weapon> weapon)
{
	return (weapon) ? weapon->name : "";
}
//Grab dialogue files from DialogueLines.cpp

string getConfidenceDescription(std::shared_ptr<Human> character)
{
	if (character->confidenceLevel >= 100)
		return "They're jovial, as if you aren't a threat at all.";
	else if (character->confidenceLevel >= 80 && character->confidenceLevel < 100)
		return "They seem confident, but there's something there. Are they starting to get scared?";
	else if (character->confidenceLevel >= 60 && character->confidenceLevel < 80)
		return "If you weren't mistaken, you'd think they're scared of you.";

	else if (character->confidenceLevel >= 40 && character->confidenceLevel < 60)
		return "They're eyeing you like a coinpurse. Is it fear in their eyes?";

	else if (character->confidenceLevel >= 20 && character->confidenceLevel < 40)
		return "They're looking around as if for an exit.";

	else if (character->confidenceLevel >= 0 && character->confidenceLevel < 20)
		return "You can feel the terror in their veins from here.";
	else
		return "You're not quite sure how confident they are.";

}

bool isSlotEmpty(const string& fileName)
{
	//If infile fails or is empty, return true
	ifstream inFile(fileName);
	if (!inFile || inFile.peek() == ifstream::traits_type::eof()) {
		return true;
	}

	//If the file is not empty, return false
	nlohmann::json j;
	try {
		inFile >> j;
		return j.empty();
	}
	//if there's an error parsing the information, return true
	catch (nlohmann::json::parse_error& e) {
		return true;
	}
}

void savePlayerToSlot(shared_ptr<Human> player, int slot)
{
	//Reads the file name based on the slot
	string fileName = "data/saves/playerSlot" + to_string(slot) + ".json";
	nlohmann::json j = player->toJson();

	//Writes the player information to the file
	ofstream outFile(fileName);
	outFile << j.dump(4);
}

shared_ptr<Human> loadPlayerFromSlot(int slot)
{
	string fileName = "data/saves/playerSlot" + to_string(slot) + ".json";
	ifstream inFile(fileName);
	//returns nullptr if file could not be found
	if (!inFile) return nullptr;

	nlohmann::json j;
	inFile >> j;
	std::shared_ptr<Human> character = dynamic_pointer_cast<Human>(Character::fromJson(j));
	return character;

}
void mainMenu()
{
	//populate files with placeholder values if empty 
	for (int i = 1; i <= 5; i++)
	{
		string fileName = "data/playerSlot" + to_string(i) + ".json";
		ifstream inFile(fileName);

		if (!inFile.good()) {
			ofstream outFile(fileName);
			outFile << "{}";
		}
	}

	//Load items from file -----------------------------------<
	std::vector<std::shared_ptr<Item>> allItems;

	// Load books from file
	std::ifstream bookFile("data/items/book.json");
	if (!bookFile) {
		std::cerr << "Failed to open book.json" << std::endl;
	}

	nlohmann::json bookJson;
	bookFile >> bookJson;

	// Check that the file contains an array
	if (!bookJson.is_array()) {
		std::cerr << "Expected an array of book in book.json" << std::endl;
	}
	else
	{
		// Parse each item and push into the vector
		for (const auto& j : bookJson) {
			shared_ptr<Book> item = std::dynamic_pointer_cast<Book>(Book::fromJson(j));
			if (item) {
				allItems.push_back(item);
			}
			else {
				std::cerr << "Failed to parse item from JSON." << std::endl;
			}
		}
	}

	// Load drinks from file
	std::ifstream drinkFile("data/items/drink.json");
	if (!drinkFile) {
		std::cerr << "Failed to open drink.json" << std::endl;
	}

	nlohmann::json drinkJson;
	drinkFile >> drinkJson;

	// Check that the file contains an array
	if (!drinkJson.is_array()) {
		std::cerr << "Expected an array of drink in drink.json" << std::endl;
	}
	else
	{
		// Parse each item and push into the vector
		for (const auto& j : drinkJson) {
			shared_ptr<Drink> item = std::dynamic_pointer_cast<Drink>(Drink::fromJson(j));
			if (item) {
				allItems.push_back(item);
			}
			else {
				std::cerr << "Failed to parse item from JSON." << std::endl;
			}
		}
	}

	// Load food from file
	std::ifstream foodFile("data/items/food.json");
	if (!foodFile) {
		std::cerr << "Failed to open food.json" << std::endl;
	}

	nlohmann::json foodJson;
	foodFile >> foodJson;

	// Check that the file contains an array
	if (!foodJson.is_array()) {
		std::cerr << "Expected an array of food in food.json" << std::endl;
	}
	else
	{
		// Parse each item and push into the vector
		for (const auto& j : foodJson) {
			shared_ptr<Food> item = std::dynamic_pointer_cast<Food>(Food::fromJson(j));
			if (item) {
				allItems.push_back(item);
			}
			else {
				std::cerr << "Failed to parse food from JSON." << std::endl;
			}
		}
	}

	// Load potion from file
	std::ifstream potionFile("data/items/potion.json");
	if (!potionFile) {
		std::cerr << "Failed to open potion.json" << std::endl;
	}

	nlohmann::json potionJson;
	potionFile >> potionJson;

	// Check that the file contains an array
	if (!potionJson.is_array()) {
		std::cerr << "Expected an array of potion in potion.json" << std::endl;
	}
	else
	{
		// Parse each item and push into the vector
		for (const auto& j : potionJson) {
			shared_ptr<Potion> item = std::dynamic_pointer_cast<Potion>(Potion::fromJson(j));
			if (item) {
				allItems.push_back(item);
			}
			else {
				std::cerr << "Failed to parse potion from JSON." << std::endl;
			}
		}
	}

	// Load weapons from file
	std::ifstream weaponFile("data/items/weapons.json");
	if (!weaponFile) {
		std::cerr << "Failed to open weapons.json" << std::endl;
	}

	nlohmann::json weaponJson;
	weaponFile >> weaponJson;

	// Check that the file contains an array
	if (!weaponJson.is_array()) {
		std::cerr << "Expected an array of weapon in weapons.json" << std::endl;
	}
	else
	{
		// Parse each item and push into the vector
		for (const auto& j : weaponJson) {
			shared_ptr<Weapon> item = std::dynamic_pointer_cast<Weapon>(Weapon::fromJson(j));
			if (item) {
				allItems.push_back(item);
			}
			else {
				std::cerr << "Failed to parse potion from JSON." << std::endl;
			}
		}
	}

	// Load armor from file
	std::ifstream armorFile("data/items/armor.json");
	if (!armorFile) {
		std::cerr << "Failed to open armor.json" << std::endl;
	}

	nlohmann::json armorJson;
	armorFile >> armorJson;

	// Check that the file contains an array
	if (!armorJson.is_array()) {
		std::cerr << "Expected an array of armor in armor.json" << std::endl;
	}
	else
	{
		// Parse each item and push into the vector
		for (const auto& j : armorJson) {
			shared_ptr<Armor> item = std::dynamic_pointer_cast<Armor>(Armor::fromJson(j));
			if (item) {
				allItems.push_back(item);
			}
			else {
				std::cerr << "Failed to parse armor from JSON." << std::endl;
			}
		}
	}

	//Load spells from file ----------------------------------<
	vector<shared_ptr<Spell>> allSpells;

	std::ifstream spellFile("data/spells/spells.json");
	if (!spellFile) {
		std::cerr << "Failed to open spells.json" << std::endl;
	}

	nlohmann::json spellJson;

	spellFile >> spellJson;
	if (!spellJson.is_array()) {
		std::cerr << "Expected an array of items in spells.json" << std::endl;
	}
	else
	{
		// Parse each spell and push into the vector
		for (const auto& j : spellJson)
		{
			shared_ptr<Spell> spell = Spell::fromJson(j);
			if (spell) allSpells.push_back(spell);
			else (std::cerr << "Failed to load spells from json" << std::endl);
		}
	}
	//Load enchantments from file ----------------------------<
	vector<shared_ptr<Enchantment>> allEnchants;
	std::ifstream enchantFile("data/enchantments/enchantments.json");
	if (!enchantFile) {
		std::cerr << "Failed to open enchantments.json" << std::endl;
	}

	nlohmann::json en;

	enchantFile >> en;
	if (!en.is_array()) std::cerr << "Expected an array of items in enchantments.json" << std::endl;
	else
	{
		for (const auto& j : en)
		{
			auto enchant = Enchantment::fromJson(j);
			if (enchant) allEnchants.push_back(enchant);
			else (std::cerr << "Failed to load enchantments from json" << std::endl);
		}
	}
	//Load effects from file --------------------------------<
	vector<shared_ptr<Effect>> allEffects;
	std::ifstream effectFile("data/effects/effects.json");
	if (!effectFile) {
		std::cerr << "Failed to open effects.json" << std::endl;
	}

	nlohmann::json ef;

	effectFile >> ef;
	if (!ef.is_array()) std::cerr << "Expected an array of items in effects.json" << std::endl;
	else
	{
		for (const auto& j : ef)
		{
			auto effect = Effect::fromJson(j);
			if (effect) allEffects.push_back(effect);
			else (std::cerr << "Failed to load effect from json" << std::endl);
		}
	}

	//Main menu loop
	bool exitGame = false;
	bool playerLoaded = false;
	shared_ptr<Human> player = make_shared<Human>();
	do
	{

		cout << "\n=--->\n";
		//check if any slots are filled
		int numSlots = 0;
		for (int i = 0; i < 4; i++)
		{
			if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json")) numSlots++;
		}
		if (numSlots > 0) cout << dye::light_yellow(" 1) Load Game") << endl;
		if (numSlots == 0) cout << dye::grey(" 1) Load Game (No Save File Found)") << endl;
		cout << dye::light_yellow(" 2) New Game") << endl;
		if (playerLoaded) cout << dye::light_yellow(" 3) Save Game") << endl;
		if (!playerLoaded) cout << dye::grey(" 3) Save Game (No Save File Found)") << endl;
		if (playerLoaded) cout << dye::light_yellow(" 4) View Character") << endl;
		if (!playerLoaded) cout << dye::grey(" 4) View Character (No Save File Found)") << endl;
		if (playerLoaded) cout << dye::light_yellow(" 5) View Inventory") << endl;
		if (!playerLoaded) cout << dye::grey(" 5) View Inventory (No Save File Found)") << endl;
		if (playerLoaded) cout << dye::light_yellow(" 6) View Spells") << endl;
		if (!playerLoaded) cout << dye::grey(" 6) View Spells (No Save File Found)") << endl;
		if (playerLoaded) cout << dye::light_yellow(" 7) View Party") << endl;
		if (!playerLoaded) cout << dye::grey(" 7) View Party (No Save File Found)") << endl;
		cout << dye::light_yellow(" 8) Debug Menu") << endl;
		cout << dye::light_yellow(" 9) Quit Game") << endl;

		int choice = validateInput(1, 9);

		switch (choice)
		{
		case 1: // LOAD GAME
		{
			//Load characters from file
			vector<shared_ptr<Human>> characters;
			//load all characters so their names can be printed in the menu
			for (int i = 1; i <= 5; i++)
			{
				if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json")) characters.push_back(dynamic_pointer_cast<Human>(loadPlayerFromSlot(i)));
			}

			//print out all slots 
			cout << "\n=--->\n";

			for (int i = 1; i <= 5; i++)
			{
				if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json"))
				{
					cout << dye::light_yellow(" Slot ") << dye::light_yellow(i) << dye::light_yellow(") ") << characters[i - 1]->name << endl;
				}
				else
				{
					cout << dye::grey(" Slot ") << dye::grey(i) << dye::grey(") EMPTY") << endl;
				}
			}

			int slotChoice = validateInput(1, 5);

			//If the slot is empty and the user selects it, ask if they want to start a new game on that slot
			if (isSlotEmpty("data/saves/playerSlot" + to_string(slotChoice) + ".json"))
			{
				cout << dye::light_red(" Slot is empty. Would you like to start a new game here?") << endl;
				cout << dye::light_yellow(" 1) Yes") << endl;
				cout << dye::light_yellow(" 2) No") << endl;
				int newGameChoice = validateInput(1, 2);
				if (newGameChoice == 1)
				{
					//Start a new game
					//Select a class
					player = player->setCharacterClass(allItems, allSpells);

					//Chose a name:
					string name = "";
					do {
						cout << dye::light_yellow(" Please enter your name: ");
						getline(cin, name);
					} while (name == "");

					player->name = name;

					//Save the player to the slot
					savePlayerToSlot(player, slotChoice);
					playerLoaded = true;
					//Temp break statement, game will start here
					break;
				}
				else
				{
					break; // Back to main menu
				}
			}
			else //Load the game
			{
				player = loadPlayerFromSlot(slotChoice);
				GameState game;
				game.playerCharacter = loadPlayerFromSlot(slotChoice);
				playerLoaded = true;
				DialogueManager dialogueManager;

				dialogueManager.loadDialogueNodesFromFolder("data/dialogues/allDialogues/Raw");
				dialogueManager.playDialogue("Inspect Surroundings", game);
			}
			break;
		}
		case 2: // NEW GAME
		{
			if (numSlots == 0)
			{
				cout << dye::light_red(" No save slots available. Please delete a save file to start a new game.") << endl;
				break;
			}
			else
			{
				//Select a class
				player = player->setCharacterClass(allItems, allSpells);
				//Chose a name:
				string name = "";
				do {
					cout << dye::light_yellow(" Please enter your name: ");
					getline(cin, name);
				} while (name == "");
				player->name = name;
				//Select a slot to save the game to
				cout << dye::light_yellow(" Please select a slot to save the game to: ");
				//print out all slots 
				cout << "\n=--->\n";
				//Load characters from file
				vector<shared_ptr<Human>> characters;
				//load all characters so their names can be printed in the menu
				for (int i = 1; i <= 5; i++)
				{
					if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json")) characters.push_back(dynamic_pointer_cast<Human>(loadPlayerFromSlot(i)));
				}
				for (int i = 1; i <= 5; i++)
				{
					if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json"))
					{
						cout << dye::light_yellow(" Slot ") << dye::light_yellow(i) << dye::light_yellow(") ") << characters[i - 1]->name << endl;
					}
					else
					{
						cout << dye::grey(" Slot ") << dye::grey(i) << dye::grey(") EMPTY") << endl;
					}
				}
				int slotChoice = validateInput(1, 5);
				if (!isSlotEmpty("data/saves/playerSlot" + to_string(slotChoice) + ".json"))
				{
					cout << dye::light_red(" Slot is not empty. Would you like to overwrite the save file?") << endl;
					cout << dye::light_yellow(" 1) Yes") << endl;
					cout << dye::light_yellow(" 2) No") << endl;
					int overwriteChoice = validateInput(1, 2);
					if (overwriteChoice == 2)
					{
						break;
					}
				}
				//Save the player to the slot
				savePlayerToSlot(player, slotChoice);
				playerLoaded = true;
				//Temp break statement, game will start here
				break;
			}
			break;
		}
		case 3: // SAVE GAME
		{
			//Select a slot to save the game to
			cout << dye::light_yellow(" Please select a slot to save the game to: ");
			//print out all slots 
			cout << "\n=--->\n";
			//Load characters from file
			vector<shared_ptr<Human>> characters;
			//load all characters so their names can be printed in the menu
			for (int i = 1; i <= 5; i++)
			{
				if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json")) characters.push_back(dynamic_pointer_cast<Human>(loadPlayerFromSlot(i)));
			}
			for (int i = 1; i <= 5; i++)
			{
				if (!isSlotEmpty("data/saves/playerSlot" + to_string(i) + ".json"))
				{
					cout << dye::light_yellow(" Slot ") << dye::light_yellow(i) << dye::light_yellow(") ") << characters[i - 1]->name << endl;
				}
				else
				{
					cout << dye::grey(" Slot ") << dye::grey(i) << dye::grey(") EMPTY") << endl;
				}
			}

			int slotChoice = validateInput(1, 5);
			if (!isSlotEmpty("data/saves/playerSlot" + to_string(slotChoice) + ".json"))
			{
				cout << dye::light_red(" Slot is not empty. Would you like to overwrite the save file?") << endl;
				cout << dye::light_yellow(" 1) Yes") << endl;
				cout << dye::light_yellow(" 2) No") << endl;
				int overwriteChoice = validateInput(1, 2);
				if (overwriteChoice == 2)
				{
					break;
				}
			}
			//Save the player to the slot
			savePlayerToSlot(player, slotChoice);
			playerLoaded = true;
			break;
		}
		case 4: // VIEW CHARACTER
		{
			//Load characters from file
			if (!playerLoaded) cout << dye::light_red(" No Player Character Loaded.") << endl;
			else
			{
				player->printHumanStats();
			}
			break;
		}
		case 5: // VIEW INVENTORY
		{
			if (!playerLoaded) cout << dye::light_red(" No Player Character Loaded.") << endl;
			else
			{
				player->inventory.printInventory();
			}
			break;
		}
		case 6: // VIEW SPELLS
		{
			if (!playerLoaded) cout << dye::light_red(" No Player Character Loaded.") << endl;
			else
			{
				player->printAttunedSpells();
			}
			break;
		}
		case 7: // VIEW PARTY
		{
			if (!playerLoaded) cout << dye::light_red(" No Player Character Loaded.") << endl;
			else
			{
				for (shared_ptr<Character> ally : player->allies) {
					shared_ptr<Human> humanAlly = dynamic_pointer_cast<Human>(ally);
					if (humanAlly) {
						humanAlly->printHumanStats();
					}
					else
					{
						shared_ptr<Creature> creatureAlly = dynamic_pointer_cast<Creature>(ally);
						if (creatureAlly) creatureAlly->printCreatureStats();
					}
				}
			}
			break;
		}
		case 8: // DEBUG MENU
		{
			shared_ptr<Weapon> sword = make_shared < Weapon>(true, "NAME", "DESC", 1, 1, 1, 1, 1, false, false, Weapon::WeaponType::STRAIGHTSWORD, Item::EquipSlots::MAINHAND);
			sword->setDamage(DamageTypes::BLUNT, 1);

			sword->setDefense(Defense::BLEED, 1);
			sword->setDefense(Defense::BLUNT, 1);

			sword->setWeaponRequirementValue(StatScaling::STRENGTH, 1);
			sword->setWeaponScalingValue(StatScaling::STRENGTH, 1);

			sword->enchantments.push_back(make_shared<Enchantment>("Enchantment", "Desc", false, false, false));
			sword->enchantments[0]->effects.push_back(make_shared<DamageEffect>(DamageTypes::BLEED, 1));

			json j;
			j = sword->toJson();
			ofstream outFile("templates/weaponTemplate.json");
			outFile << j.dump(4);

			//DialogueBuilder dialogueBuilder;
			//dialogueBuilder.processDialogueTree("data/dialogues/allDialogues/Raw/HunterCabin.json");
			int choice = 0;
			std::cin >> choice;
			break;
		}
		case 9: // QUIT GAME
		{
			cout << "Saving data..." << endl;
			exitGame = true;
			break;
		}
		default:
			cout << dye::light_red(" Please enter a number from 1 - 7") << endl;
			break;
		}
	} while (exitGame == false);

}



bool isValidSaveSlot(const std::string& filename)
{
	std::ifstream file(filename);
	//file couldn't open
	if (!file.is_open()) return false;
	try {
		nlohmann::json j;
		file >> j;
		//Check for expected values to be present
		if (j.contains("type") && j.contains("id") && j.contains("isPlayer"))
		{
			//file is valid and populated
			return true;
		}
		else
		{
			//file is corrupted or empty
			return false;
		}
	}
	catch (const std::exception& e) {
		//file is corrupted or empty
		return false;
	}
}

void openCombat(shared_ptr<Human> player, shared_ptr<Character> enemy)
{
	//set this condition to true if the fight ends for any reason
	bool exitFight = false;
	do
	{

		//SETS ALL NECESSARY VARIABLES FOR THE COMBAT LOOP

		//Get player equipment 
		shared_ptr<Weapon> mainHand, reserve1, offHand, reserve2;

		shared_ptr<Armor> headArmor, chestArmor, armArmor, legArmor;
		shared_ptr<Trinket> amulet, ring1, ring2, misc;
		player->inventory.getEquippedItems(mainHand, offHand, reserve1, reserve2, headArmor, chestArmor, armArmor, legArmor, amulet, ring1, ring2, misc);

		//create dummy items for if the item is nullptr for the purposes of checking ranges
		if (!mainHand) mainHand = make_shared<Weapon>(false, "Fists", "", 0, -1, 0, 0, 0, false, false, Weapon::WeaponType::STRAIGHTSWORD, Item::EquipSlots::MAINHAND);
		if (!offHand) offHand = make_shared<Weapon>(false, "Fists", "", 0, -1, 0, 0, 0, false, false, Weapon::WeaponType::STRAIGHTSWORD, Item::EquipSlots::MAINHAND);
		if (!reserve1) reserve1 = make_shared<Weapon>(false, "Fists", "", 0, -1, 0, 0, 0, false, false, Weapon::WeaponType::STRAIGHTSWORD, Item::EquipSlots::MAINHAND);
		if (!reserve2) reserve2 = make_shared<Weapon>(false, "Fists", "", 0, -1, 0, 0, 0, false, false, Weapon::WeaponType::STRAIGHTSWORD, Item::EquipSlots::MAINHAND);

		//check if player has equipment to swap to (changes menu color to represent this)
		bool hasStowedWeapons = false;

		if ((reserve2 && reserve2->reach > 0) || (reserve1 && reserve1->reach > 0))
		{
			hasStowedWeapons = true;
		}

		//Used to track the player's consumables and grey out the consumable option if they have none
		/*vector<std::shared_ptr<Item>> consumables = player->inventory.consumables();
		vector<std::shared_ptr<Item>> throwingWeapons = player->inventory.getThrownWeapons();*/

		//tracks the spent ammunition and throwing weapons to be returned at the end of the turn (based on luck and proficiency with item skill)
		vector<Item> spentProjectiles;

		//tracks the living/dead allies and enemies
		vector<shared_ptr<Character>> deadAllies;
		vector<shared_ptr<Character>> deadEnemies;

		vector<shared_ptr<Character>> livingAlliesPointers;
		vector<shared_ptr<Character>> livingEnemiesPointers;

		//checks if the allies and enemies are alive and adds them to the living/dead vectors
		if (player->allies.size() > 0)
		{
			for (shared_ptr<Character> ally : player->allies)
			{
				if (ally->isAlive)
				{
					livingAlliesPointers.push_back(ally);
				}
				else
				{
					deadAllies.push_back(ally);
				}
			}
		}
		if (enemy->allies.size() > 0)
		{
			for (shared_ptr<Character> enemy : enemy->allies)
			{
				if (enemy->isAlive)
				{
					livingEnemiesPointers.push_back(enemy);
				}
				else
				{
					deadEnemies.push_back(enemy);
				}
			}
		}
		//Add the enemy to the list of living enemies
		if (enemy->isAlive)	livingEnemiesPointers.push_back(enemy);

		//general variables for the combat loop
		int playerOptionChoice = 0;

		//finds the minimum distance from the player to an enemy from the group
		float minDistanceFromPlayer = 1000;
		for (int i = 0; i < livingEnemiesPointers.size(); i++)
		{
			if (livingEnemiesPointers[i]->position[player->getId()] <= minDistanceFromPlayer)
			{
				minDistanceFromPlayer = livingEnemiesPointers[i]->position[player->getId()];
			}
		}

		//used to determine the color of menu text in the attack option (gold for in range, grey for out of range)
		// they will not be able to select out of range options and this will help them intuit why
		// set to 1000 initially as range will never be this high in practice 
		bool inRange = false;
		//check if any spells attuned are in range
		int spellsInRange = 0;
		for (int i = 0; i < player->attunedSpells.size(); i++)
		{
			if (player->attunedSpells[i]->range >= minDistanceFromPlayer)
			{
				spellsInRange++;
			}
		}
		//check if any spells, mainhand, or offhand weapons are in range
		if (mainHand && minDistanceFromPlayer <= getWeaponReach(mainHand) || offHand && minDistanceFromPlayer <= getWeaponReach(offHand) || spellsInRange > 0)
		{
			inRange = true;
		}

		//INITIAL SANITY CHECKS


		//check if player is dead
		if (!player->isAlive)
		{
			cout << dye::light_red("You have fallen...") << endl;
			exitFight = true;
			int choiec;
			cin >> choiec;
		}
		if (player->isAlive && livingEnemiesPointers.size() == 0)
		{
			std::cout << "\n=--->\n" << std::endl;
			cout << "The battlefield is quiet once again..." << endl;
			int stop;
			cin >> stop;
		}
		//End of combat encounter rewards for player (repeated in case the loop terminates here)
		if (player->isAlive && livingEnemiesPointers.size() == 0)
		{
			for (int i = 0; i < deadEnemies.size(); i++)
			{
				int choiec;
				cin >> choiec;
				/*player->gainExperience(deadEnemies[i]);
				player->openLootInterface(deadEnemies[i]); ---------------------------------------------------------- < TODO */
			}
			exitFight = true;
		}

		//set to false initially, true once this has been played. Exists so this text only gets played once
		bool playedBefore = false;

		//INITIAL ENCOUNTER TEXT
		//Player is alive, at least one ally is alive, and at least one enemy is alive
		if (player->isAlive && livingEnemiesPointers.size() > 0 && livingAlliesPointers.size() > 0 && !playedBefore)
		{
			//Encounter text
			std::cout << "\n=--->\n" << std::endl;
			cout << "You encounter";
			for (int i = 0; i < livingEnemiesPointers.size(); i++)
			{
				if (livingEnemiesPointers.size() == 1 && !livingEnemiesPointers[i]->namedCharacter)
				{
					cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name) << "!" << endl;
				}
				else
				{
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << " and";
					}
					if (!livingEnemiesPointers[i]->namedCharacter)
					{
						cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					else
					{
						cout << " " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					if (i < livingEnemiesPointers.size() - 1)
					{
						cout << ",";
					}
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << "!" << endl;
					}
				}
			}
			//Allies text
			std::cout << "\n=--->\n" << std::endl;
			if (player->allies.size() > 1) cout << "Your allies,";
			if (player->allies.size() == 1) cout << "Your ally,";
			for (int i = 0; i < livingAlliesPointers.size(); i++)
			{
				if (livingAlliesPointers.size() == 1)
				{
					cout << " a " << dye::light_yellow(livingAlliesPointers[i]->name) << " joins you!" << endl;
				}
				else
				{
					if (i == livingAlliesPointers.size() - 1)
					{
						cout << " and";
					}
					if (!livingAlliesPointers[i]->namedCharacter)
					{
						cout << " a " << dye::light_yellow(livingAlliesPointers[i]->name);
					}
					else
					{
						cout << " " << dye::light_yellow(livingAlliesPointers[i]->name);
					}
					if (i < livingAlliesPointers.size() - 1)
					{
						cout << ",";
					}
					if (i == livingAlliesPointers.size() - 1)
					{
						cout << " joins you!" << endl;
					}
				}
			}
			playedBefore = true;
		}
		//Player is alive, all allies dead or nonexistant, and at least one enemy is alive
		if (player->isAlive == true && livingEnemiesPointers.size() > 0 && livingAlliesPointers.size() == 0 && !playedBefore)
		{
			//Encounter text
			std::cout << "\n=--->\n" << std::endl;
			cout << "You encounter";
			for (int i = 0; i < livingEnemiesPointers.size(); i++)
			{
				if (livingEnemiesPointers.size() == 1 && !livingEnemiesPointers[i]->namedCharacter)
				{
					cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name) << "!" << endl;
				}
				else
				{
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << " and";
					}
					if (!livingEnemiesPointers[i]->namedCharacter)
					{
						cout << " a " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					else
					{
						cout << " " << dye::light_yellow(livingEnemiesPointers[i]->name);
					}
					if (i < livingEnemiesPointers.size() - 1)
					{
						cout << ",";
					}
					if (i == livingEnemiesPointers.size() - 1)
					{
						cout << "!" << endl;
					}
				}
			}
			//Allies text
			std::cout << "\n=--->\n" << std::endl;
			cout << "You have no allies to assist you..." << endl;
			playedBefore = true;
		}

		//Intro Context Sensitive Text (repeated in check enemy option along with more details)
		/*for (int i = 0; i < livingEnemiesPointers.size(); i++) ----------------------------------------------------------< TODO
		{
			std::cout << "\n=--->\n" << std::endl;
			livingEnemiesPointers[i]->checkCharacterIntro(player);
		}*/

		//only play a round if exitFight = false (there are living enemies and the player is alive)
		if (exitFight == false)
		{

			//set this condition to true once the player has defeated all enemies or all allies have been defeated
			bool exitCombat = false;
			//COMBAT LOOP
			do
			{

				//set this condition to true once the player commits to an option all the way through their submenus
				bool inputChosen = false;

				//Option 1 variables
				float playerMovement = 0.0f;
				shared_ptr<Weapon> weaponChoice = nullptr;
				std::shared_ptr<Ammunition> ammoChoice = nullptr; //this will be a pointer to the ammo choice so that the quantity can be updated
				shared_ptr<Spell> spellChoice = make_shared<Spell>("", "", false, false, false, 0, 0, 0, 0, 0, 0, 0, -1);
				shared_ptr<Character> targetChoice = nullptr; //this is a pointer to the target choice so that the target's health can be updated

				//used to determine of the player only chose to move
				bool onlyMove = false;

				//Option 2 variables
				//NONE

				//Option 3 variables
				//NONE

				//Option 4 variables
				std::shared_ptr<Potion> potionChoice = nullptr; //this is a pointer to the potion choice so that the quantity can be updated
				shared_ptr<Character> potionTarget = nullptr; //this is a pointer to the target choice so that the target's health can be updated

				//Used to track the player's potions and grey out the potion option if they have none
				vector<std::shared_ptr<Potion>> potions;
				vector<std::shared_ptr<Consumable>> consumables;

				int numPotionCategories = 0;
				for (shared_ptr<Item> item : player->inventory.backpackItems)
				{
					if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
					{
						potions.push_back(potion);
					}
					if (std::shared_ptr<Food> food = std::dynamic_pointer_cast<Food>(item))
					{
						consumables.push_back(food);
					}
					if (std::shared_ptr<Drink> drink = std::dynamic_pointer_cast<Drink>(item))
					{
						consumables.push_back(drink);
					}
					if (std::shared_ptr<Book> book = std::dynamic_pointer_cast<Book>(item))
					{
						consumables.push_back(book);
					}
				}

				bool hasPotion = false;

				//EXPAND AS MORE POTIONS GET ADDED
				if (potions.size() > 0)
				{
					hasPotion = true;
				}

				//Option 5 variables
				shared_ptr<ThrownConsumable> thrownConsumableChoice;
				shared_ptr<Consumable> consumableChoice;
				shared_ptr<Character> consumableTarget;
				shared_ptr<Character> thrownConsumableTarget;
				vector<shared_ptr<ThrownConsumable>> throwingWeapons;

				for (shared_ptr<Item> item : player->inventory.backpackItems)
				{
					//gets throwing weapons and consumables
					if (shared_ptr<ThrownConsumable> consumable = std::dynamic_pointer_cast<ThrownConsumable>(item))
					{
						throwingWeapons.push_back(consumable);
					}
				}

				//Option 6 variables
				//NONE

				//Option 7 variables
				//NONE

				//Option 8 variables
				//NONE

				//Option 9 variables
				//NONE

				//Option 10 variables
				//NONE

				std::cout << "\n=--->\n" << std::endl;
				//print out the main combat menu

				//Option 1: Attack
				if (inRange)
				{
					cout << dye::light_yellow(" 1) Attack!") << endl;
				}
				else
				{
					cout << dye::grey(" 1) Attack") << endl;
				}

				//Option 2: Swap Weapons
				if (hasStowedWeapons)
				{
					cout << dye::light_yellow(" 2) Swap to Your Stored weapons") << endl;
				}
				else
				{
					cout << dye::grey(" 2) Swap to Your Stored weapons") << endl;
				}

				//Option 3: View Spells
				if (player->attunedSpells.size() > 0)
				{
					cout << dye::light_yellow(" 3) View Spells") << endl;
				}
				else
				{
					cout << dye::grey(" 3) View Spells") << endl;
				}

				//Option 4: Use Potion
				if (potions.size() > 0)
				{
					cout << dye::light_yellow(" 4) Use Potion") << endl;
				}
				else
				{
					cout << dye::grey(" 4) Use Potion") << endl;
				}

				//Option 5: Use Item
				if (consumables.size() > 0 || throwingWeapons.size() > 0)
				{
					cout << dye::light_yellow(" 5) Use Item") << endl;
				}
				else
				{
					cout << dye::grey(" 5) Use Item") << endl;
				}

				//Option 6: Taunt Enemy
				if (livingEnemiesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 6) Taunt Your Enemy") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 6) Taunt Your Enemies") << endl;
				}

				//Option 7: Check Enemy
				if (livingEnemiesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 7) Check Your Enemy") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 7) Check Your Enemies") << endl;
				}

				//Option 8: Check Ally/Self
				if (livingAlliesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 8) Check Self") << endl;
				}
				else if (livingAlliesPointers.size() == 1)
				{
					cout << dye::light_yellow(" 8) Check Self or Ally") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 8) Check Self or Allies") << endl;
				}

				//Option 9: Check Ally/Self Equipment
				if (livingAlliesPointers.size() == 0)
				{
					cout << dye::light_yellow(" 9) Check Equipment") << endl;
				}
				else if (livingAlliesPointers.size() == 1)
				{
					cout << dye::light_yellow(" 9) Check Equipment for Self or Ally") << endl;
				}
				else
				{
					cout << dye::light_yellow(" 9) Check Equipment for Self or Allies") << endl;
				}

				//Option 10: Flee
				cout << dye::light_yellow(" 10) Flee from Combat") << endl;

				//input validation
				int initialChoice = validateInput(1, 10);

				switch (initialChoice)
				{
				case 1: // ATTACK
				{

					if (!inRange || !spellsInRange)
					{
						cout << dye::white("\n You are out of range of any enemies!") << endl;
						break;
					}
					else
					{
						float distanceTraveled = player->speed / 15;
						int numEnemiesInRange = 0;
						int numEnemiesInRangeForward = 0;
						int numEnemiesInRangeBackward = 0;
						for (const auto& enemy : livingEnemiesPointers)
						{
							float distance = enemy->position[player->getId()];

							// Forward range: advancing reduces distance
							bool inRangeForward =
								(mainHand && distance - distanceTraveled <= getWeaponReach(mainHand)) ||
								(offHand && distance - distanceTraveled <= getWeaponReach(offHand));

							if (inRangeForward)
								numEnemiesInRangeForward++;

							// Backward range: retreating increases distance
							bool inRangeBackward =
								(mainHand && distance + distanceTraveled * 0.8 <= getWeaponReach(mainHand)) ||
								(offHand && distance + distanceTraveled * 0.8 <= getWeaponReach(offHand));

							if (inRangeBackward)
								numEnemiesInRangeBackward++;

							// Standing range: no movement
							bool inRange =
								(mainHand && distance <= getWeaponReach(mainHand)) ||
								(offHand && distance <= getWeaponReach(offHand));

							if (inRange)
								numEnemiesInRange++;
							std::cout << "Enemy " << enemy->name << " is at distance " << distance << std::endl;
							std::cout << "  Forward in range? " << inRangeForward << std::endl;
							std::cout << "  Backward in range? " << inRangeBackward << std::endl;
							std::cout << "  Standing in range? " << inRange << std::endl;
						}
						if (numEnemiesInRangeForward > 0 || spellsInRange > 0) cout << dye::light_yellow(" 1) Advance and Attack!") << endl;
						else cout << dye::grey(" 1) Advance and Attack!") << endl;
						if (numEnemiesInRange > 0 || spellsInRange > 0) cout << dye::light_yellow(" 2) Stand Your Ground and Attack!") << endl;
						else cout << dye::grey(" 2) Stand Your Ground and Attack!") << endl;
						if (numEnemiesInRangeBackward > 0 || spellsInRange > 0) cout << dye::light_yellow(" 3) Retreat and Attack!") << endl;
						else cout << dye::grey(" 3) Retreat and Attack!") << endl;
						cout << dye::light_yellow(" 4) Move Without Attacking!") << endl;
						cout << dye::light_yellow(" 5) Go back") << endl;

						//input validation
						int attackChoice = validateInput(1, 5);

						switch (attackChoice)
						{
						case 1: // ADVANCE AND ATTACK
						{
							float advanceMovement = 0 - player->speed / 20;

							if (numEnemiesInRangeForward > 0)
							{
								//get enemies in range of a spell if they move forward and attack and check if player has fatiuge to cast spell
								spellsInRange = 0;
								for (shared_ptr<Spell> spells : player->attunedSpells)
								{
									if (spells->range >= minDistanceFromPlayer - distanceTraveled && spells->fatigueCost <= player->fatiguePoints)
									{
										spellsInRange++;
									}
								}
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{

									//in range of both weapons and at least one spell
									if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand) &&
										livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(offHand) &&
										spellsInRange > 0)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< ", and " << offHand->name << ", and attuned spell(s)" << endl;
									}
									//in range of both weapons and no spells
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand) &&
										livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(offHand) &&
										spellsInRange == 0)
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< ", and " << offHand->name << endl;
									}
									//in range of mainhand and at least one spell
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand) &&
										spellsInRange > 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > getWeaponReach(offHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< ", and attuned spell(s)" << endl;
									}
									//in range of mainhand and no spells
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand) &&
										spellsInRange == 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > getWeaponReach(offHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name << endl;
									}
									//in range of offhand and at least one spell
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(offHand) &&
										spellsInRange > 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > getWeaponReach(mainHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name
											<< ", and attuned spell(s)" << endl;
									}
									//in range of offhand and no spells
									else if (livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled <= getWeaponReach(offHand) &&
										spellsInRange == 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > getWeaponReach(mainHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name << endl;
									}
									//in range of at least one spell
									else if (spellsInRange > 0 && livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > getWeaponReach(offHand)
										&& livingEnemiesPointers[i]->position[player->getId()] - distanceTraveled > getWeaponReach(mainHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of attuned spell(s)" << endl;
									}
									else
									{
										cout << dye::grey(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << endl;
									}
								}
								int advanceChoice = 0;
								advanceChoice = validateInput(1, livingEnemiesPointers.size());

								//check if the player is in range of the enemy they selected
								if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled > getWeaponReach(mainHand)
									&& livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled > getWeaponReach(offHand)
									&& spellsInRange == 0)
								{
									//They're not in range of choice, go back
									cout << "You are not in range of that enemy!" << endl;
									break;
								}
								else // they're in range and chose a target, ask which weapon to hit them with
								{
									//if they have two weapons to attack with, ask which one they want to use
									if (mainHand && offHand)
									{
										cout << "Which weapon would you like to attack with?" << endl;
										cout << dye::light_yellow(" 1) " + mainHand->name) << endl;
										cout << dye::light_yellow(" 2) " + offHand->name) << endl;
										cout << dye::light_yellow(" 3) Go back") << endl;
										int mainOrOffChoice = validateInput(1, 3);
										switch (mainOrOffChoice)
										{
										case 1: // MAINHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
												mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
												mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];
													weaponChoice = mainHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												break;
											}
											//PROJECTILE WEAPON
											else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												//print all enemies
												/*cout << " Which target do you pick?" << endl;
												for (int i = 0; i < livingEnemiesPointers.size(); i++)
												{
													cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												}
												cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

												bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = mainHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												else
												{
													break;
												}
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand))
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = mainHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}

										}
										case 2: // OFFHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
												offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
												offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = offHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												//print all enemies
												/*cout << " Which target do you pick?" << endl;
												for (int i = 0; i < livingEnemiesPointers.size(); i++)
												{
													cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												}
												cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

												bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = offHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand))
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = offHand;
													playerMovement = advanceMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}
										}
										case 3: // GO BACK
										{
											break;
										}
										default:
										{
											cout << dye::white("\n  Enter a number between 1 - 3") << endl;
											break;
										}
										}
									}
									//if only mainhand is available
									else if (mainHand && !offHand)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
											mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
											mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = mainHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = mainHand;
											playerMovement = advanceMovement;
											inputChosen = true;
											break;
										}
										else
										{
											if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] - distanceTraveled <= getWeaponReach(mainHand))
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
										}
									}
									//if only offhand is available
									else if (offHand && !mainHand)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
											offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
											offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = offHand;
												playerMovement = advanceMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

											bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = offHand;
											playerMovement = advanceMovement;
											inputChosen = true;
											break;
										}
										else
										{
											//print all enemies
											cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											int meleeAttackChoice = validateInput(1, livingEnemiesPointers.size());
											if (livingEnemiesPointers[meleeAttackChoice - 1]->position[player->getId()] - distanceTraveled <= getWeaponReach(offHand))
											{
												targetChoice = livingEnemiesPointers[meleeAttackChoice - 1];
												inputChosen = true;
												playerMovement = advanceMovement;
												weaponChoice = offHand;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
											break;
										}
									}
									else
									{
										cout << "ERROR: No weapons initialized!" << endl;
										break;
									}
									break;
								}
							}
							else
							{
								cout << "No enemies are in range of your advancing attack..." << endl;
								break;
							}
						}
						case 2: // STAND YOUR GROUND AND ATTACK
						{
							float standMovement = 0;
							if (numEnemiesInRange > 0)
							{
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									if (livingEnemiesPointers[i]->position[player->getId()] <= getWeaponReach(mainHand) &&
										livingEnemiesPointers[i]->position[player->getId()] <= getWeaponReach(offHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< " and " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] <= getWeaponReach(offHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] <= getWeaponReach(mainHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name << endl;
									}
									else
									{
										cout << dye::grey(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << endl;
									}
								}
								int advanceChoice = 0;
								advanceChoice = validateInput(1, livingEnemiesPointers.size());

								//check if the player is in range of the enemy they selected
								if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] > getWeaponReach(mainHand)
									&& livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] > getWeaponReach(offHand))
								{
									//They're not in range of choice, go back
									cout << "You are not in range of that enemy!" << endl;
									break;
								}
								else // they're in range and chose a target, ask which weapon to hit them with
								{
									//if they have two weapons to attack with, ask which one they want to use
									if (mainHand && offHand)
									{
										cout << "Which weapon would you like to attack with?" << endl;
										cout << dye::light_yellow(" 1) " + mainHand->name) << endl;
										cout << dye::light_yellow(" 2) " + offHand->name) << endl;
										cout << dye::light_yellow(" 3) Go back") << endl;
										int mainOrOffChoice = validateInput(1, 3);
										switch (mainOrOffChoice)
										{
										case 1: // MAINHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
												mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
												mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = mainHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

												bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												playerMovement = standMovement;
												weaponChoice = mainHand;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] <= getWeaponReach(mainHand))
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = mainHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}

										}
										case 2: // OFFHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
												offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
												offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = offHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												//print all enemies
												/*cout << " Which target do you pick?" << endl;
												for (int i = 0; i < livingEnemiesPointers.size(); i++)
												{
													cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												}
												cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

												bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = offHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] <= getWeaponReach(offHand))
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = offHand;
													playerMovement = standMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}
										}
										case 3: // GO BACK
										{
											break;
										}
										default:
										{
											cout << dye::white("\n  Enter a number between 1 - 3") << endl;
											break;
										}
										}
									}
									//if only mainhand is available
									else if (mainHand && !offHand)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
											mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
											mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = mainHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = mainHand;
											playerMovement = standMovement;
											inputChosen = true;
											break;
										}
										else
										{
											if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] <= getWeaponReach(mainHand))
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
										}
									}
									//if only offhand is available
									else if (offHand && !mainHand)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
											offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
											offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = offHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
										}
										//PROJECTILE WEAPON
										else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = offHand;
											playerMovement = standMovement;
											inputChosen = true;
											break;
										}
										else
										{
											//print all enemies
											cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											int meleeAttackChoice = validateInput(1, livingEnemiesPointers.size());
											if (livingEnemiesPointers[meleeAttackChoice - 1]->position[player->getId()] <= getWeaponReach(offHand))
											{
												targetChoice = livingEnemiesPointers[meleeAttackChoice - 1];
												weaponChoice = mainHand;
												playerMovement = standMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
											break;
										}
									}
									else
									{
										cout << "ERROR: No weapons initialized!" << endl;
										break;
									}
									break;
								}
							}
							else
							{
								cout << "No enemies are in range of your standing attack..." << endl;
								break;
							}
						}
						case 3: // RETREAT AND ATTACK
						{
							float retreatMovement = player->speed / 20;
							if (numEnemiesInRangeBackward > 0)
							{
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= getWeaponReach(mainHand) &&
										livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= getWeaponReach(offHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name
											<< " and " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= getWeaponReach(offHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << offHand->name << endl;
									}
									else if (livingEnemiesPointers[i]->position[player->getId()] + distanceTraveled <= getWeaponReach(mainHand))
									{
										cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << " in range of " << mainHand->name << endl;
									}
									else
									{
										cout << dye::grey(" " + to_string(i + 1) + ") " + livingEnemiesPointers[i]->name) << endl;
									}
								}
								int advanceChoice = 0;
								advanceChoice = validateInput(1, livingEnemiesPointers.size());

								//check if the player is in range of the enemy they selected
								if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled > getWeaponReach(mainHand)
									&& livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled > getWeaponReach(offHand))
								{
									//They're not in range of choice, go back
									cout << "You are not in range of that enemy!" << endl;
									break;
								}
								else // they're in range and chose a target, ask which weapon to hit them with
								{
									//if they have two weapons to attack with, ask which one they want to use
									if (mainHand && offHand)
									{
										cout << "Which weapon would you like to attack with?" << endl;
										cout << dye::light_yellow(" 1) " + mainHand->name) << endl;
										cout << dye::light_yellow(" 2) " + offHand->name) << endl;
										cout << dye::light_yellow(" 3) Go back") << endl;
										int mainOrOffChoice = validateInput(1, 3);
										switch (mainOrOffChoice)
										{
										case 1: // MAINHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
												mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
												mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = mainHand;
													playerMovement = retreatMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

												bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled <= getWeaponReach(mainHand))
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													inputChosen = true;
													playerMovement = retreatMovement;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}

										}
										case 2: // OFFHAND
										{
											//CAST SPELL
											std::cout << "\n=--->\n" << std::endl;
											if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
												offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
												offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
											{
												//check if player has enough fatigue to cast any spells
												int spellsPlayerCanCast = 0;
												for (shared_ptr<Spell> spell : player->attunedSpells)
												{
													if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
												}

												if (spellsPlayerCanCast == 0)
												{
													cout << "You don't have enough fatigue to cast any spells!" << endl;
													break;
												}

												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
												//if (spellAttackChoice > livingEnemiesPointers.size()) break;

												//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
												// choose to cast a spell
												bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
												if (spellAttackCommitted)
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

													weaponChoice = offHand;
													playerMovement = retreatMovement;
													inputChosen = true;
													break;
												}
											}
											//PROJECTILE WEAPON
											else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
												offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
												offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
											{
												////print all enemies
												//cout << " Which target do you pick?" << endl;
												//for (int i = 0; i < livingEnemiesPointers.size(); i++)
												//{
												//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
												//}
												//cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
												//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

												bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
												if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = offHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled <= getWeaponReach(offHand))
												{
													targetChoice = livingEnemiesPointers[advanceChoice - 1];
													weaponChoice = offHand;
													playerMovement = retreatMovement;
													inputChosen = true;
													break;
												}
												else
												{
													cout << "You are not in range of that enemy!" << endl;
													break;
												}
											}
										}
										case 3: // GO BACK
										{
											break;
										}
										default:
										{
											cout << dye::white("\n  Enter a number between 1 - 3") << endl;
											break;
										}
										}
									}
									//if only mainhand is available
									else if (mainHand && !offHand)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (mainHand->weaponType == Weapon::WeaponType::TALISMAN || mainHand->weaponType == Weapon::WeaponType::CHIME ||
											mainHand->weaponType == Weapon::WeaponType::TOME || mainHand->weaponType == Weapon::WeaponType::ORB ||
											mainHand->weaponType == Weapon::WeaponType::STAFF || mainHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*mainHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
											}
										}
										//PROJECTILE WEAPON
										else if (mainHand->weaponType == Weapon::WeaponType::LONGBOW || mainHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											mainHand->weaponType == Weapon::WeaponType::GREATBOW || mainHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											mainHand->weaponType == Weapon::WeaponType::CROSSBOW || mainHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											//print all enemies
											/*cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);*/

											bool projectileAttackCommitted = player->chooseAmmunition(mainHand, livingEnemiesPointers[advanceChoice - 1], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = mainHand;
											playerMovement = retreatMovement;
											inputChosen = true;
											break;
										}
										else
										{
											if (livingEnemiesPointers[advanceChoice - 1]->position[player->getId()] + distanceTraveled <= getWeaponReach(mainHand))
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1];
												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
										}
									}
									//if only offhand is available
									else if (offHand && !mainHand)
									{
										//CAST SPELL
										std::cout << "\n=--->\n" << std::endl;
										if (offHand->weaponType == Weapon::WeaponType::TALISMAN || offHand->weaponType == Weapon::WeaponType::CHIME ||
											offHand->weaponType == Weapon::WeaponType::TOME || offHand->weaponType == Weapon::WeaponType::ORB ||
											offHand->weaponType == Weapon::WeaponType::STAFF || offHand->weaponType == Weapon::WeaponType::WAND)
										{
											//check if player has enough fatigue to cast any spells
											int spellsPlayerCanCast = 0;
											for (shared_ptr<Spell> spell : player->attunedSpells)
											{
												if (spell->fatigueCost <= player->fatiguePoints) spellsPlayerCanCast++;
											}

											if (spellsPlayerCanCast == 0)
											{
												cout << "You don't have enough fatigue to cast any spells!" << endl;
												break;
											}

											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int spellAttackChoice = validateInput(1, livingEnemiesPointers.size());
											//if (spellAttackChoice > livingEnemiesPointers.size()) break;

											//returns false if they don't commit to a spell or can't cast the one they select, updates spellChoice if they 
											// choose to cast a spell
											bool spellAttackCommitted = player->chooseSpell(*offHand, livingEnemiesPointers[advanceChoice - 1], spellChoice);
											if (spellAttackCommitted)
											{
												targetChoice = livingEnemiesPointers[advanceChoice - 1.0f];

												weaponChoice = offHand;
												playerMovement = retreatMovement;
												inputChosen = true;
											}
										}
										//PROJECTILE WEAPON
										else if (offHand->weaponType == Weapon::WeaponType::LONGBOW || offHand->weaponType == Weapon::WeaponType::COMPOUNDBOW ||
											offHand->weaponType == Weapon::WeaponType::GREATBOW || offHand->weaponType == Weapon::WeaponType::MINICROSSBOW ||
											offHand->weaponType == Weapon::WeaponType::CROSSBOW || offHand->weaponType == Weapon::WeaponType::BALLISTA)
										{
											////print all enemies
											//cout << " Which target do you pick?" << endl;
											//for (int i = 0; i < livingEnemiesPointers.size(); i++)
											//{
											//	cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											//}
											////cout << " " << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") ") << "Go back..." << endl;
											//int projectileAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);

											bool projectileAttackCommitted = player->chooseAmmunition(offHand, livingEnemiesPointers[advanceChoice], ammoChoice);
											if (projectileAttackCommitted) targetChoice = livingEnemiesPointers[advanceChoice - 1];
											weaponChoice = offHand;
											playerMovement = retreatMovement;
											inputChosen = true;
											break;
										}
										else
										{
											//print all enemies
											cout << " Which target do you pick?" << endl;
											for (int i = 0; i < livingEnemiesPointers.size(); i++)
											{
												cout << " " << dye::light_yellow(i + 1) << " " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
											}
											int meleeAttackChoice = validateInput(1, livingEnemiesPointers.size());
											if (livingEnemiesPointers[meleeAttackChoice - 1]->position[player->getId()] + distanceTraveled <= getWeaponReach(offHand))
											{
												targetChoice = livingEnemiesPointers[meleeAttackChoice - 1];
												weaponChoice = mainHand;
												playerMovement = retreatMovement;
												inputChosen = true;
												break;
											}
											else
											{
												cout << "You are not in range of that enemy!" << endl;
												break;
											}
											break;
										}
									}
									else
									{
										cout << "ERROR: No weapons initialized!" << endl;
										break;
									}
									break;
								}
							}
							else
							{
								cout << "No enemies are in range of your retreating attack..." << endl;
								break;
							}
						}
						case 4://MOVE WITHOUT ATTACKING
						{
							std::cout << "\n=--->\n" << std::endl;
							cout << dye::light_yellow(" 1) Move Forward") << endl;
							cout << dye::light_yellow(" 2) Move Backward") << endl;
							cout << dye::light_yellow(" 3) Go back") << endl;

							int moveChoice = validateInput(1, 3);
							switch (moveChoice)
							{
							case 1: //ADVANCE
							{
								float advanceMovement = 0 - player->speed / 20;
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									cout << dye::light_yellow(" " + to_string(i + 1) + ") Advance on: " + livingEnemiesPointers[i]->name) << endl;
								}
								cout << dye::light_yellow(" " + to_string(livingEnemiesPointers.size() + 1) + ") ") << dye::light_yellow("Go back...") << endl;
								int advanceNoAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);
								if (advanceNoAttackChoice == livingEnemiesPointers.size() + 1) break;
								else
								{
									targetChoice = livingEnemiesPointers[advanceNoAttackChoice - 1];
									playerMovement = advanceMovement;
									onlyMove = true;
									inputChosen = true;
									break;
								}

								break;
							}
							case 2: //RETREAT
							{
								float retreatMovement = player->speed / 20;
								for (int i = 0; i < livingEnemiesPointers.size(); i++)
								{
									cout << dye::light_yellow(" " + to_string(i + 1) + ") Retreat from: " + livingEnemiesPointers[i]->name) << endl;
								}
								cout << dye::light_yellow(" " + to_string(livingEnemiesPointers.size() + 1) + ") ") << dye::light_yellow("Go back...") << endl;
								int advanceNoAttackChoice = validateInput(1, livingEnemiesPointers.size() + 1);
								if (advanceNoAttackChoice == livingEnemiesPointers.size() + 1) break;
								else
								{
									targetChoice = livingEnemiesPointers[advanceNoAttackChoice - 1];
									playerMovement = retreatMovement;
									onlyMove = true;
									inputChosen = true;
									break;
								}
								break;
							}
							case 3: //GO BACK
							{
								break;
							}
							default:
							{
								cout << dye::white("\n  Enter a number between 1 - 3") << endl;
								break;
							}
							}
							break;
						}
						case 5:// GO BACK
						{
							break;
						}
						default:
						{
							cout << dye::white("\n  Enter a number between 1 - 4") << endl;
							break;
						}
						}
						break;
					}
				}
				case 2: // SWAP WEAPONS
				{
					if (hasStowedWeapons)
					{
						//TODO
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::light_yellow(" 1) Swap to your reserves") << endl;
						cout << dye::light_yellow(" 2) Swap only your mainhand weapon") << endl;
						cout << dye::light_yellow(" 3) Swap only your offhand weapon") << endl;
						cout << dye::light_yellow(" 4) Go back") << endl;

						//input validation
						int swapWeaponChoice = validateInput(1, 4);

						switch (swapWeaponChoice)
						{
						case 1: // SWAP ALL WEAPONS TO RESERVED WEAPONS
						{
							player->inventory.swapEquippedItems(mainHand, offHand, reserve1, reserve2);
							if (mainHand->reach > 0 && offHand->reach > 0 && reserve1->reach > 0 && reserve2->reach > 0) cout << dye::light_yellow(" " + player->name)
								<< " swaps their " << mainHand->name << " and " << offHand->name << " for their " << reserve1->name << " and " << reserve2->name << endl;
							if (mainHand->reach > 0 && offHand->reach < 0 && reserve1->reach > 0 && reserve2->reach < 0) cout << dye::light_yellow(" " + player->name)
								<< " swaps their " << mainHand->name << " for " << reserve1->name << endl;
							break;
						}
						case 2: // SWAP ONLY MAINHAND
						{
							player->inventory.swapEquippedItems(mainHand, nullptr, reserve1, nullptr);
							if (mainHand->reach > 0 && offHand->reach < 0 && reserve1->reach > 0 && reserve2->reach < 0) cout << dye::light_yellow(" " + player->name)
								<< " swaps their " << mainHand->name << " for " << reserve1->name << endl;
							break;
						}
						case 3: // SWAP ONLY OFFHAND
						{
							player->inventory.swapEquippedItems(nullptr, offHand, nullptr, reserve2);
							if (mainHand->reach < 0 && offHand->reach > 0 && reserve1->reach < 0 && reserve2->reach > 0) cout << dye::light_yellow(" " + player->name)
								<< " swaps their " << offHand->name << " for " << reserve2->name << endl;
							break;
						}
						case 4: // GO BACK
						{
							break;
						}
						default:
						{
							cout << dye::white("\n  Enter a number between 1 - 4") << endl;
							break;
						}
						}
					}
					else //NO STOWED WEAPONS, GO BACK
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::white("\n You have no stowed weapons to swap to!") << endl;
						break;
					}
				}
				case 3: // VIEW SPELLS
				{
					if (player->attunedSpells.size() > 0)
					{
						std::cout << "\n=--->\n" << std::endl;
						player->viewSpells();
						break;
					}
					else //NO SPELLS, GO BACK
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::white("\n You have no spells to view!") << endl;
						break;
					}
				}
				case 4: // USE POTION
				{
					if (hasPotion)
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::light_yellow(" 1) Drink Potion") << endl;
						if (livingAlliesPointers.size() > 0)
						{
							cout << dye::light_yellow(" 2) Share with a Friend") << endl;
							cout << dye::light_yellow(" 3) Go back") << endl;
						}
						else
						{
							cout << dye::grey(" 2) Share with a Friend") << endl;
							cout << dye::light_yellow(" 3) Go back") << endl;
						}

						//input validation
						int potionChoice = validateInput(1, 3);

						switch (potionChoice)
						{
						case 1: // DRINK POTION
						{
							std::cout << "\n=--->\n" << std::endl;
							int index = 1;
							for (auto& potion : potions)
							{
								cout << dye::light_yellow(to_string(index) + ") " + potion->name) << ("; magnitude: " + to_string(potion->magnitude)) << endl;
								index++;
							}
							std::cout << dye::light_yellow(to_string(index) + ") Go back") << std::endl;
							int potionSubChoice = validateInput(1, index);

							if (potionSubChoice == index) break;
							else
							{
								inputChosen = true;
								consumableChoice = potions[potionSubChoice - 1];
								consumableTarget = player;
								break;
							}

						}
						case 2: // SHARE POTION
						{
							if (livingAlliesPointers.size() > 0)
							{
								//TODO
								std::cout << "\n=--->\n" << std::endl;
								std::cout << " Which ally do you want to share with?" << std::endl;
								for (int i = 0; i < livingAlliesPointers.size(); i++)
								{
									cout << dye::light_yellow(" " + to_string(i + 1) + ") " + livingAlliesPointers[i]->name) << endl;
								}
								cout << dye::light_yellow(" " + to_string(livingAlliesPointers.size() + 1) + ") ") << dye::light_yellow("Go back...") << endl;

								int shareChoice = validateInput(1, livingAlliesPointers.size() + 1);

								if (shareChoice == livingAlliesPointers.size() + 1) break;
								else std::cout << "\n=--->\n" << std::endl;

								int index = 1;
								for (auto& potion : potions)
								{
									cout << dye::light_yellow(to_string(index) + ") " + potion->name) << ("; magnitude: " + to_string(potion->magnitude)) << endl;
									index++;
								}
								std::cout << dye::light_yellow(to_string(index) + ") Go back") << std::endl;
								int potionSubChoice = validateInput(1, index);

								if (potionSubChoice == index) break;
								else
								{
									inputChosen = true;
									consumableChoice = potions[potionSubChoice - 1];
									consumableTarget = livingAlliesPointers[shareChoice - 1];
									break;
								}
								break;
							}
							else //NO ALLIES, GO BACK
							{
								std::cout << "\n=--->\n" << std::endl;
								cout << dye::white("\n You have no allies to share a potion with!") << endl;
								break;
							}
						}
						case 3: // GO BACK
						{
							break;
						}
						}
					}
					else //NO POTIONS, GO BACK
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::white("\n You have no potions to use!") << endl;
						break;
					}
					break;
				case 5: // USE ITEM
				{
					if (consumables.size() > 0 || throwingWeapons.size() > 0)
					{
						std::cout << "\n=--->\n" << std::endl;
						if (consumables.size() > 0)
						{
							cout << dye::light_yellow(" 1) Use Throwing Weapon") << endl;
						}
						else
						{
							cout << dye::grey(" 1) Use Throwing Weapon") << endl;
						}
						if (throwingWeapons.size() > 0)
						{
							cout << dye::light_yellow(" 2) Use Consumable") << endl;
						}
						else
						{
							cout << dye::grey(" 2) Use Consumable") << endl;
						}
						cout << dye::light_yellow(" 3) Go back") << endl;

						//input validation
						int itemChoice = validateInput(1, 3);

						switch (itemChoice)
						{
						case 1: // THROWING WEAPON
						{
							if (!throwingWeapons.empty())
							{
								for (int i = 0; i < throwingWeapons.size(); i++)
								{
									cout << dye::light_yellow(i + 1) << ") " << dye::light_yellow(throwingWeapons[i]->name) << "; quantity " + to_string(throwingWeapons[i]->quantity) << endl;
								}
								cout << dye::light_yellow(throwingWeapons.size() + 1) << ") Go back" << endl;

								int thrownWeaponChoice = validateInput(1, throwingWeapons.size() + 1);
								if (thrownWeaponChoice == throwingWeapons.size() + 1) break;
								else
								{
									std::cout << " Use " << throwingWeapons[thrownWeaponChoice - 1]->name << " on which enemy?" << std::endl;
									for (int i = 0; i < livingEnemiesPointers.size(); i++)
									{
										cout << dye::light_yellow(i + 1) << ") " << dye::light_yellow(livingEnemiesPointers[i]->name) << endl;
									}
									cout << dye::light_yellow(livingEnemiesPointers.size() + 1) << ") Go back" << endl;

									int thrownWeaponTargetChoice = validateInput(1, livingEnemiesPointers.size() + 1);
									if (thrownWeaponTargetChoice == livingEnemiesPointers.size() + 1) break;

									inputChosen = true;
									thrownConsumableChoice = throwingWeapons[thrownWeaponChoice - 1];
									thrownConsumableTarget = livingEnemiesPointers[thrownWeaponTargetChoice - 1];
									break;
								}
							}
							else //NO THROWING WEAPONS, GO BACK
							{
								std::cout << "\n=--->\n" << std::endl;
								cout << "\n You have no throwing weapons to use!" << endl;
								break;
							}
							break;
						}
						case 2: // CONSUMABLE
						{
							if (!consumables.empty())
							{
								// TODO
								for (int i = 0; i < consumables.size(); i++)
								{
									cout << dye::light_yellow(i + 1) << ") " << dye::light_yellow(consumables[i]->name) << "; quantity " + to_string(consumables[i]->quantity) << endl;
								}
								cout << dye::light_yellow(consumables.size() + 1) << ") Go back" << endl;

								int consumableUseChoice = validateInput(1, consumables.size() + 1);
								if (consumableUseChoice == consumables.size() + 1) break;
								else
								{
									inputChosen = true;
									consumableChoice = consumables[consumableUseChoice - 1];
									consumableTarget = player;
									break;
								}
							}
							else //NO CONSUMAMBLES, GO BACK
							{
								std::cout << "\n=--->\n" << std::endl;
								cout << "\n You have no consumables to use!" << endl;
								break;
							}
							break;
						}
						case 3: // GO BACK
						{
							break;
						}
						}
					}
					else
					{
						std::cout << "\n=--->\n" << std::endl;
						cout << "\n You have no items to use!" << endl;
					}
					break;
				}
				case 6: // TAUNT ENEMY
				{
					std::cout << "\n=--->\n" << std::endl;
					cout << dye::light_yellow("1) By the Book") << endl;
					cout << dye::light_yellow("2) Make Something Up") << endl;
					cout << dye::light_yellow("3) Go back") << endl;

					//input validation
					int tauntChoice = validateInput(1, 3);
					switch (tauntChoice)
					{
					case 1: // PRESELECTED TAUNT
					{
						//TODO TAUNT FUNCTION
						cout << dye::light_yellow("PLACEHOLDER TAUNT") << endl;
						break;
					}
					case 2: // USER INPUT TAUNT
					{
						string taunt;
						std::cout << "\n=--->\n" << std::endl;
						cout << dye::light_yellow(" Give them your best shot: ");
						cin.ignore(10000, '\n');
						getline(cin, taunt);

						//TODO TAUNT FUNCTION
						break;
					}
					case 3: // GO BACK
					{
						break;
					}
					}
					break;
				}
				case 7: // CHECK ENEMY
				{
					std::cout << "\n=--->\n" << std::endl;
					for (int i = 0; i < livingEnemiesPointers.size(); i++)
					{
						string confidenceDescription = getConfidenceDescription(std::dynamic_pointer_cast<Human>(livingEnemiesPointers[i]));
						cout << dye::light_yellow(i + 1) << ") " << dye::light_yellow(livingEnemiesPointers[i]->name) << dye::light_yellow("; ") << dye::white(confidenceDescription) << endl;
					}
					cout << dye::light_yellow(livingEnemiesPointers.size() + 1) << dye::light_yellow(") Go back") << endl;

					//input validation
					int checkEnemyChoice = validateInput(1, livingEnemiesPointers.size() + 1);

					if (checkEnemyChoice == livingEnemiesPointers.size() + 1) // GO BACK
					{
						break;
					}
					else // CHECK ENEMY
					{
						//TODO
						cout << dye::light_yellow("PLACEHOLDER CHECK ENEMY") << endl;
						break;
					}
					break;
				}
				case 8: // CHECK ALLY/SELF
				{
					std::cout << "\n=--->\n" << std::endl;
					if (!livingAlliesPointers.empty())
					{
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " " << dye::white(player->healthPoints) << "/" << dye::white(player->maxHealthPoints) << dye::light_yellow(" HP")
							<< " " << dye::white(player->fatiguePoints) << "/" << dye::white(player->maxFatiguePoints) << dye::light_yellow(" MP") << endl;
						for (int i = 0; i < livingAlliesPointers.size(); i++)
						{
							cout << dye::light_yellow(i + 2) << ") " << dye::white(livingAlliesPointers[i]->name) << " " << dye::white(livingAlliesPointers[i]->healthPoints) << "/" << dye::light_yellow(livingAlliesPointers[i]->maxHealthPoints) << " HP"
								<< " " << dye::white(livingAlliesPointers[i]->fatiguePoints) << "/" << dye::white(livingAlliesPointers[i]->maxFatiguePoints) << dye::light_yellow(" MP") << endl;
						}
						cout << dye::light_yellow(livingAlliesPointers.size() + 1) << dye::light_yellow(") Go back") << endl;

						//input validation
						int checkAllyChoice = validateInput(1, livingAlliesPointers.size() + 1);
						if (checkAllyChoice == livingAlliesPointers.size() + 1) // GO BACK
						{
							break;
						}
						else // CHECK ALLY
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK ALLY") << endl;
							break;
						}
					}
					else if (livingAlliesPointers.empty())
					{
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " " << dye::white(player->healthPoints) << "/" << dye::white(player->maxHealthPoints) << dye::light_yellow(" HP")
							<< " " << dye::white(player->fatiguePoints) << "/" << dye::white(player->maxFatiguePoints) << dye::light_yellow(" MP") << endl;
						cout << dye::light_yellow("2") << dye::light_yellow(") Go back") << endl;
						//input validation
						int checkAllyChoice = validateInput(1, 2);
						if (checkAllyChoice == 2) // GO BACK
						{
							break;
						}
						else // CHECK SELF
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK SELF") << endl;
							break;
						}
					}
					break;
				}
				case 9: // CHECK ALLY/SELF EQUIPMENT
				{
					//To be assigned to each character's equipment
					shared_ptr<Weapon> mainhand = nullptr;
					shared_ptr<Weapon> offhand = nullptr;
					shared_ptr<Weapon> mainhand2 = nullptr;
					shared_ptr<Weapon> offhand2 = nullptr;
					std::cout << "\n=--->\n" << std::endl;
					if (!livingAlliesPointers.empty())
					{
						player->inventory.getEquippedWeapons(mainhand, offhand, mainhand2, offhand2);
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " "
							<< dye::white(mainhand->name) << dye::light_yellow("; ") << dye::white(offhand->name) << endl;
						for (int i = 0; i < livingAlliesPointers.size(); i++)
						{
							livingAlliesPointers[i]->inventory.getEquippedWeapons(mainhand, offhand, mainhand2, offhand2);
							cout << dye::light_yellow(i + 2) << ") " << dye::light_yellow(livingAlliesPointers[i]->name) << " "
								<< dye::white(mainhand->name) << dye::light_yellow("; ") << dye::white(offhand->name) << endl;
						}
						cout << dye::light_yellow(livingAlliesPointers.size() + 1) << dye::light_yellow(") Go back") << endl;

						//input validation
						int checkAllyChoice = validateInput(1, livingAlliesPointers.size() + 1);
						if (checkAllyChoice == livingAlliesPointers.size() + 1) // GO BACK
						{
							break;
						}
						else // CHECK ALLY EQUIPMENT DETAILS
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK ALLY EQUIPMENT") << endl;
							break;
						}
					}
					else if (livingAlliesPointers.empty())
					{
						player->inventory.getEquippedWeapons(mainhand, offhand, mainhand2, offhand2);
						cout << dye::light_yellow("1") << ") " << dye::light_yellow(player->name) << " "
							<< dye::white(mainhand->name) << dye::light_yellow("; ") << dye::white(offhand->name) << endl;
						cout << dye::light_yellow("2") << dye::light_yellow(") Go back") << endl;

						//input validation
						int checkAllyChoice = validateInput(1, 2);
						if (checkAllyChoice == 2) // GO BACK
						{
							break;
						}
						else // CHECK SELF EQUIPMENT DETAILS
						{
							//TODO
							cout << dye::light_yellow("PLACEHOLDER CHECK SELF EQUIPMENT") << endl;
							break;
						}
					}
					break;
				}
				case 10: // FLEE
				{
					//TODO
					break;
				}
				}
				}
				//Only progress to taking turns once the player locks in a choice, denoted by the boolean inputChosen
				if (inputChosen)
				{
					/*static_assert(std::is_base_of<Character, Creature>::value, "Creature should inherit from Character!");
					static_assert(std::is_base_of<Character, Human>::value, "Human should inherit from Character!");
					std::cout << "Type of summoned creature: " << typeid(*player->allies.back()).name() << std::endl;*/
					vector<shared_ptr<Character>> combatants;
					combatants.push_back(player);
					combatants.insert(combatants.end(), livingAlliesPointers.begin(), livingAlliesPointers.end());
					combatants.insert(combatants.end(), livingEnemiesPointers.begin(), livingEnemiesPointers.end());

					//sorts combatants by speed
					sort(combatants.begin(), combatants.end(), [](shared_ptr<Character> a, shared_ptr<Character> b) {return a->speed > b->speed; });

					//dummy effect to call refresh effects
					std::shared_ptr<Effect> effect = nullptr;

					//variable to track size of player allies vector. used to detect if another ally was summoned
					int initialPlayerAlliesSize = player->allies.size();
					// Process turns
					for (int i = 0; i < combatants.size(); i++)
					{
						cout << combatants[i]->name << " bleed points: " << combatants[i]->bleedPoints << endl;
						cout << combatants[i]->name << " poison points " << combatants[i]->poisonPoints << endl;
						cout << combatants[i]->name << " burn points " << combatants[i]->burnPoints << endl;
						cout << combatants[i]->name << " frost points " << combatants[i]->frostPoints << endl;
						cout << combatants[i]->name << " shock points " << combatants[i]->shockPoints << endl;
						cout << combatants[i]->name << " sleep points " << combatants[i]->sleepPoints << endl;

						if (combatants[i]->isAlive && player->isAlive)
						{
							if (shared_ptr<Creature> creature = std::dynamic_pointer_cast<Creature>(combatants[i]))
							{
								if (creature->isAlly)
								{
									cout << "CREATURE ALLY TURN" << endl;
								}
								else
								{
									// Enemy Turn
									cout << "CREATURE ENEMY TURN" << endl;
								}
							}

							else if (shared_ptr<Human> human = dynamic_pointer_cast<Human>(combatants[i]); human && human->isPlayer)
							{
								// Player Turn
								playerTurn(human, weaponChoice, ammoChoice, spellChoice, targetChoice, thrownConsumableChoice, consumableChoice, playerMovement, onlyMove);

								//If player summoned an ally, add it to the living allies vector
								if (spellChoice)
								{
									if (player->allies.size() > initialPlayerAlliesSize)
									{
										shared_ptr<Character> summonedCreature = player->allies.back();
										livingAlliesPointers.push_back(summonedCreature);
									}
								}
							}

							else if (auto human = dynamic_pointer_cast<Human>(combatants[i]); human && human->isAlly)
							{
								// Ally Turn
								cout << "HUMAN ALLY TURN" << endl;
							}
							else
							{


								// Enemy Turn
								cout << "ENEMY TURN" << endl;
							}
						}
					}

					//refresh effects at the end of each round (Pokemon rules baby)
					for (shared_ptr<Character> combatant : combatants)
					{
						if (combatant)
						{
							for (shared_ptr<Effect> effect : combatant->effects)
							{
								if (effect)
								{
									effect->tick(combatant);
									if (combatant->healthPoints <= 0)
									{
										combatant->killCharacter();
										break;
									}
								}
							}
						}
					}
					// Remove dead combatants 
					auto removeDead = [](vector<shared_ptr<Character>>& vec) {
						vec.erase(remove_if(vec.begin(), vec.end(), [](shared_ptr<Character> c) { return !c->isAlive; }), vec.end());
						};

					removeDead(livingEnemiesPointers);
					removeDead(livingAlliesPointers);
				}
				if (livingEnemiesPointers.size() == 0 || player->isAlive == false)
				{
					exitCombat = true;
				}

			} while (exitCombat == false);
		}
		//input 1: attack target
		// -> present option to attack forward, attack in place, attack in retreat, or go back
		// -> 1) Advance and Attack!
		// -> 2) Stand your ground and Attack!
		// -> -> (sub menu) 1) normal attack
		// -> -> (sub menu) 2) grapple enemy (strength check; if success, enemy is grappled and loses their turn + damage; if fail, player wastes turn & chance to take damage)
		// -> 3) Retreat and Attack!
		// -> 4) Go back
		// -> -> display all targets, greying out targets not in range of selected attack option with longest weapon or go back
		// -> -> 1) _____; ten stage health descriptor: _____; ten stage fatigue descriptor: _____; ten stage confidence descriptor: _____; (always highest level enemy)
		// -> -> 2) _____; ten stage health descriptor: _____; ten stage fatigue descriptor: _____; ten stage confidence descriptor: _____; (lowest level enemy)
		// -> -> 3) Go back
		// -> -> -> display all attack options (mainhand, offhand, spells if either main or offhands are casting tools) 
		// -> -> -> -> 1) Mainhand: _____; Damage: _____; Reach: _____; Speed: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> 2) Offhand: _____; Damage: _____; Reach: _____; Speed: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> (sub menu) 1) Spell: _____; Damage: _____; Reach: _____; Speed: _____; Damgage Type: _____; (only if applicable) Magic Damage Type: _____ 
		// -> -> -> -> (sub menu) 2) Bash them with your catalyst (always second to last option)
		// -> -> -> -> (sub menu) 3) Go back
		// -> -> -> -> 3) Go back
		// -> -> -> -> -------------------------
		// -> -> -> -> (sub menu) 1) Arrow: _____; Damage: _____; Reach: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> (sub menu) 2) Bolt: _____; Damage: _____; Reach: _____; Damgage Type: _____; Magic Damage Type: _____ (only if applicable)
		// -> -> -> -> (sub menu) 3) Go back
		// -> -> -> -> grey out attack options not in range of specified target (ex: mainhand is spear offhand is dagger, offhand out of range but mainhand in range) or go back
		// -> -> -> -> -> 1) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> -> -> -> -> 2) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> -> -> -> -> 3) Go back
		// -> -> -> -> set values for player option choice, weapon choice, spell choice, and target choice

		//input 2: swap from mainhand and offhand to back items and vice versa
		// -> present option to swap mainhand and offhand with back items or go back
		// -> 1) Swap to your stowed weapons
		// -> -> - MAINHAND1 -> MAINHAND2
		// -> -> - OFFHAND1 -> OFFHAND2
		// -> 2) Go back
		// -> -> set values for player option choice (function will handle getting the quipped items and transferring them between slots)

		//input 3: view spells
		// -> present short list of all attuned spells (max of 10)
		// -> =---> Name: _____; Damage: _____; fatigue Cost: _____; Reach: _____; Speed: _____; Damage Type: _____; (if applicable) Magic Damage Type: _____
		// -> =---> Name: _____; Damage: _____; fatigue Cost: _____; Reach: _____; Speed: _____; Damage Type: _____; (if applicable) Magic Damage Type: _____

		//input 4: use potion
		// -> present short list of all potions
		// -> 1) _____ Potion; Magnitude: __; Quantity: __
		// -> 2) _____ Potion; Magnitude: __; Quantity: __
		// -> 3) Go back
		// -> -> present option to use on self, ally, or go back
		// -> -> -> self: set values for player option choice, potion choice, and target choice
		// -> -> -> ally: display all allies, greying out allies at full health
		// -> -> -> -> set values for player option choice, potion choice, and target choice

		//input 5: use item
		// -> present short list of all usable items in backpack (food, tools, etc)
		// -> 1) _____; Damage/Healing/Effect: __; Quantity: __
		// -> 2) _____; Damage/Healing/Effect: __; Quantity: __
		// -> 3) Go back
		// -> -> present option to use on self, ally, enemy, or go back
		// -> -> -> self: set values for player option choice, item choice, and target choice
		// -> -> -> ally: display all allies, greying out allies at full health
		// -> -> -> -> set values for player option choice, item choice, and target choice

		//input 6: check allies or self
		// -> display all allies and self
		// -> 1) _____; Health: __; fatigue: __; Confidence: __ (always player)
		// -> 2) _____; Health: __; fatigue: __; Confidence: __
		// -> 3) Go back
		// -> -> (self) display flavor text about your condition and equipped items
		// -> -> (ally) display flavor text about ally condition and equipped items

		//input 7: check enemies
		// -> display all enemies (sort by level)
		// -> 1) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 2) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 3) Go back

		//input 8: taunt enemies (confidence boost allies, makes enemy focus on you)
		// -> present all enemies
		// -> 1) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 2) _____; 10 stage level descriptor; 10 stage health descriptor; 10 stage fatigue descriptor; 10 stage confidence descriptor
		// -> 3) Go back
		// -> -> 1) Taunt _____;
		// -> -> 2) Make something up

		//input 9: check allies or self equipment
		// -> Display all allies or self brief equipment overview
		// -> 1) _____; HP: _____; Mainhand: __; Offhand: __; Backslot1: __; Backslot2: __;
		// -> 2) _____; HP: _____; Mainhand: __; Offhand: __; Backslot1: __; Backslot2: __;
		// -> 3) Go back
		// -> -> (self) display all equipped items and their stats
		// -> -> (ally) display all equipped items and their stats

		//input 10: attempt to flee
		// -> Display 10 stage descriptor at odds of getting away
		// -> 1) Attempt to flee
		// -> 2) Go back


	} while (exitFight == false);
}
void playerTurn(std::shared_ptr<Human> player, shared_ptr<Weapon> weaponChoice, std::shared_ptr<Ammunition> ammoChoice, shared_ptr<Spell> spellChoice, shared_ptr<Character> targetChoice, std::shared_ptr<ThrownConsumable> thrownConsumableChoice,
	std::shared_ptr<Consumable> consumableChoice, float playerMovement, bool onlyMove)
{
	//Check if player object is null
	if (!player)
	{
		cout << "ERROR: player is null!" << endl;
		return;
	}

	//move player

	if (playerMovement < 0) cout << "You advance by " << abs(playerMovement) << " units!" << endl;
	else if (playerMovement > 0) cout << "You retreat by " << abs(playerMovement) << " units!" << endl;
	else cout << "You stand your ground!" << endl;

	targetChoice->position[player->getId()] += playerMovement;

	//Printing if the player cannot move towards the enemy any closer
	if (targetChoice->position[player->getId()] <= 0)
	{
		targetChoice->position[player->getId()] = 0;
		cout << "You stand close enough to touch " << targetChoice->name << "!" << endl;
	}

	//Stop the turn if the player only chose to move
	if (playerMovement && onlyMove)
	{
		return;
	}

	//Applying Passive Armor Enchantments
	for (std::shared_ptr<Item> item : player->inventory.equippedItems)
	{
		if (dynamic_pointer_cast<std::shared_ptr<Armor>>(item))
		{
			std::shared_ptr<Armor> armor = dynamic_pointer_cast<Armor>(item);
			for (std::shared_ptr<Enchantment> enchant : armor->enchantments)
			{
				if (!enchant->useOnEnemy)
				{
					for (auto& eff : enchant->effects)
					{
						eff->apply(targetChoice, player);
					}
				}
			}
		}
	}
	//Player chose to cast a spell on an ally
	if (spellChoice && targetChoice->isAlly)
	{
		if (weaponChoice->weaponType != Weapon::WeaponType::TALISMAN && weaponChoice->weaponType != Weapon::WeaponType::CHIME &&
			weaponChoice->weaponType != Weapon::WeaponType::TOME && weaponChoice->weaponType != Weapon::WeaponType::ORB &&
			weaponChoice->weaponType != Weapon::WeaponType::STAFF && weaponChoice->weaponType != Weapon::WeaponType::WAND)
		{
			cout << "ERROR: weapon is not a casting tool!" << endl;
			return;
		}
		else
		{
			if (weaponChoice)
			{
				player->castSpell(*spellChoice, targetChoice, playerMovement);
			}
			else
			{
				cout << "ERROR: no weapon initialized!" << endl;
				return;
			}
		}
	}
	//Player chose to cast a spell on anything but an ally
	//range check because there is a dummy spellChoice created initially so this will always be true, though the dummy spell has a negative range 
	// which isn't normally possible so this will not fire if they haven't selected a spell
	else if (spellChoice && spellChoice->range >= 0)
	{
		if (weaponChoice->weaponType != Weapon::WeaponType::TALISMAN && weaponChoice->weaponType != Weapon::WeaponType::CHIME &&
			weaponChoice->weaponType != Weapon::WeaponType::TOME && weaponChoice->weaponType != Weapon::WeaponType::ORB &&
			weaponChoice->weaponType != Weapon::WeaponType::STAFF && weaponChoice->weaponType != Weapon::WeaponType::WAND)
		{
			cout << "ERROR: weapon is not a casting tool!" << endl;
			return;
		}
		else
		{
			if (weaponChoice)
			{
				player->castSpell(*spellChoice, targetChoice, playerMovement);
			}
			else
			{
				cout << "ERROR: no weapon initialized!" << endl;
				return;
			}
		}
	}
	//Player chose to attack an enemy with a melee weapon
	else if (weaponChoice && spellChoice->range < 0)
	{
		for (int i = 0; i < 99;)
		{
			if (player->isAlive)
			{
				player->attackWithMelee(weaponChoice, targetChoice);
				i += abs(weaponChoice->attackSpeed - 100);
			}
			else
			{
				return;
			}
		}
	}
	//Player chose to attack an enemy with a ranged weapon
	else if (weaponChoice && ammoChoice)
	{
		player->fireRangedWeapon(targetChoice, weaponChoice, ammoChoice);
	}
	//Player chose to attack an enemy with a thrown weapon
	else if (thrownConsumableChoice)
	{
		player->throwThrownConsumable(thrownConsumableChoice, targetChoice);
	}
	//Player chose to share a consumable with an ally
	else if (consumableChoice && targetChoice->isAlly)
	{
		consumableChoice->use(targetChoice);
	}
	//Player chose to consume a consumable
	else if (consumableChoice)
	{
		consumableChoice->use(player);
	}
	else
	{
		cout << "ERROR: NO VALID CHOICE WAS SENT TO PLAYERTURN" << endl;
	}
}