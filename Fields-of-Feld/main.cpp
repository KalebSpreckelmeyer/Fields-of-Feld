#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include "color.hpp"
#include "Item.h"
#include "Potion.h"
#include "Character.h"


using namespace std;

#pragma region Function Declarations
//DESC: Prints the main menu and takes in user input to determine what to do next
// PRE: None
// POST: Returns a character object with the selected class
void printMainMenu(Character character);
//DESC: Starts a combat encounter and prints the relevant menus
//PRE: Player and Enemy Characters must be initialized
//POST: Player values will be updated depending on the results of the battle
void printMainCombatMenu(Character player, Character enemy);
//DESC: Takes in a character and prints their health, stamina, or mana respectively as a bar
//PRE: Character object must be initialized first with setCharacterClass() in order to have a health/mana/stamina value
//POST: Prints health, stamina, or mana bar to console
void printHealthBar(Character player);
void printStaminaBar(Character player);
void printManaBar(Character player);
//DESC: Calls all 3 bar functions 
//PRE: None
//POST: All 3 will be printed to console
void printAllBars(Character character);
//DESC: Opens up the shop interface 
//PRE: Character should be initialized first
//POST: Modifies the character's inventory or gold value based on interactions within the shop
void openShop(Character& character);

#pragma endregion Function Declarations

int main()
{
	Character player;;
	printMainMenu(player);

	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> distribution(1, 100);
	int randomNum = distribution(generator);
	return 0;
}

void printMainMenu(Character character)
{
	//Initialize all classes so they can be printed 
	Character wizard;
	wizard.setCharacterClass(Character::WIZARD);
	Character battleMage;
	battleMage.setCharacterClass(Character::BATTLEMAGE);
	Character knight;
	knight.setCharacterClass(Character::KNIGHT);
	Character cleric;
	cleric.setCharacterClass(Character::CLERIC);
	Character hunter;
	hunter.setCharacterClass(Character::HUNTER);
	Character highlander;
	highlander.setCharacterClass(Character::HIGHLANDER);
	Character wretch;
	wretch.setCharacterClass(Character::WRETCH);
	//TODO: Make the buttons grey out if unselectable
	int choice;
	do
	{
		cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
			<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
			<< dye::bright_white(" |   1) Continue     |   |   2) New Game     |   | 3) View Inventory |   | 4) View Character |   |      5) Exit      |  ") << endl
			<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
			<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;


		//input validation
		do
		{
			cout << ">> ";
			cin >> choice;
			if (cin.fail() || choice > 5 || choice == 0)
			{
				cout << "Enter a number from 1 - 5" << endl;
			}
			cin.clear();
			cin.ignore(10000, '\n');
		} while (cin.fail() || choice > 5 || choice == 0);
		switch (choice)
		{
		case 1:
		{
			//Continue
			if (character.active == true)
			{
				//for now this adds items to the selected character for testing		
				Item goblet = goblet.createLootItem("Fine Gold Goblet", "A golden goblet inlaid with emeralds. Will fetch a nice price.", 100, 1, 1);
				character.inventory.addItemToBackpack(goblet);
				
				openShop(character);
				/*Potion potion = potion.createPotion("Healing Potion", "Heals you for 50 points", 50, 20, 1, 3, Potion::HEALING);
				character.inventory.addPotion(potion);
				character.takeDamage(50);
				cout << "Your health is " << character.healthPoints << endl;
				Potion potionToDrink = character.inventory.findPotion("Healing Potion");
				character.drinkPotion(potionToDrink);
				cout << "Your health is " << character.healthPoints << endl;*/
				break;
			}
			else
			{
				cout << "  No save file found" << endl;
				break;
			}
		}
		case 2:
		{
			//New Game
			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |  6) The Wizard    |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;

			wizard.printCharacterStats(wizard);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" | 5) The Battlemage |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			battleMage.printCharacterStats(battleMage);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |   4) The Knight   |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			knight.printCharacterStats(knight);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |   3) The Cleric   |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			cleric.printCharacterStats(cleric);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" |   2) The Hunter   |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			hunter.printCharacterStats(hunter);
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

			cout << dye::light_yellow(" =-------------------=") << endl
				<< dye::bright_white(" | 1) The Highlander |") << endl
				<< dye::light_yellow(" =-------------------=") << endl;
			highlander.printCharacterStats(highlander);

			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::light_yellow(" =-------------------=---=-------------------=---=-------------------=---=-------------------=---=-------------------=  ") << endl
				<< dye::bright_white(" |                                                 Select Your Class                                                 |  ") << endl
				<< dye::light_yellow(" =-------------------=---=-------------------=---=-------------------=---=-------------------=---=-------------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;


			int classChoice;
			//input validation
			do
			{
				cout << ">> ";
				cin >> classChoice;
				if (cin.fail() || classChoice > 7 || classChoice == 0)
				{
					cout << "Enter a number from 1 - 7" << endl;
				}
				cin.clear();
				cin.ignore(10000, '\n');
			} while (cin.fail() || classChoice > 7 || classChoice == 0);

			switch (classChoice)
			{
			case 1:
				character.setCharacterClass(Character::HIGHLANDER);
				break;
			case 2:
				character.setCharacterClass(Character::HUNTER);
				break;
			case 3:
				character.setCharacterClass(Character::CLERIC);
				break;
			case 4:
				character.setCharacterClass(Character::KNIGHT);
				break;
			case 5:
				character.setCharacterClass(Character::BATTLEMAGE);

				break;
			case 6:
				character.setCharacterClass(Character::WIZARD);
				break;
			case 7:
				character.setCharacterClass(Character::WRETCH);
				//Return to main menu for now
				break;
			case 8:
				//Return to main menu for now
				break;
			}
			break;
		}
		case 3:
			if (character.active == true)
			{
				cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
					<< dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
					<< dye::bright_white(" |   1) View Equipped Items   |              |   2) View Backpack Items  |              |         3) Go back         |  ") << endl
					<< dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
					<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

				int inventoryChoice;
				do
				{
					cout << ">> ";
					cin >> inventoryChoice;
					if (cin.fail() || inventoryChoice > 3 || inventoryChoice == 0)
					{
						cout << "Enter a number from 1 - 3" << endl;
					}
					cin.clear();
					cin.ignore(10000, '\n');
				} while (cin.fail() || inventoryChoice > 3 || inventoryChoice == 0);
				switch (inventoryChoice)
				{
				case 1:
				{
					character.inventory.printEquippedItems();
					break;
				}
				case 2:
				{
					character.inventory.printBackpack();
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					cout << "  Enter a number between 1 - 3" << endl;
					break;
				}
				}
			}
			else
			{
				cout << "  No save file found" << endl;
				break;
			}
			break;
		case 4:
			//Inspect Character Stats
			if (character.active == true)
			{
				character.printCharacterStats(character);
			}
			else
			{
				cout << "  No save file found" << endl;
				break;
			}
			break;
			break;
		case 5:
		{
			//Exit
			break;
		}
		}
	} while (choice != 5);
}

void openShop(Character& character)
{
	cout << dye::yellow(" Shopkeep:") << endl;
	cout << dye::light_yellow("  Welcome to my shop traveler. Take a look around. I'm sure we've got what you're looking for.") << endl;
	cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
		 << dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
		 << dye::bright_white(" |       1) View Wares        |              |     2) Sell your Items    |              |         3) Go back         |  ") << endl
		 << dye::light_yellow(" =----------------------------=              =---------------------------=              =----------------------------=  ") << endl
		 << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
	int choice;
	do {
		cout << ">> ";
		cin >> choice;
		if (cin.fail() || choice > 3 || choice == 0)
		{
			cout << "Enter a number from 1 - 3" << endl;
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || choice > 3 || choice == 0);
	switch (choice)
	{
	case 1:
	{
		//buy items
		break;
	}
	case 2:
	{
		Item itemToSell = character.inventory.findItem("Fine Gold Goblet");
		character.sellItem(itemToSell);
		//sell items
		break;
	}
	case 3:
	{
		//go back
		break;
	}
	}
}

void printMainCombatMenu(Character player, Character enemy)
{

	cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
		<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		<< dye::bright_white(" |     1) Move       |   |    2) Attack      |   |   3) Use Item     |   |  4) Check Enemy   |   | 5) Attempt to Run |  ") << endl
		<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

	//input validation
	printAllBars(player);
	int choice;
	do {
		cout << ">> ";
		cin >> choice;
		if (cin.fail() || choice > 5 || choice == 0)
		{
			cout << "Enter a number from 1 - 5" << endl;
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || choice > 5 || choice == 0);
	switch (choice)
	{
	case 1:
		if (player.getMainWeapon1(player).reach >= enemy.distanceFromPlayer ||
			player.getOffhandWeapon1(player).reach >= enemy.distanceFromPlayer)
		{
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				<< dye::bright_white(" |    1) Attack      |   |  2) Move Forward  |   | 3) Move Backward  |   | 4) Retreat & Attack |   |    5) Return    |  ") << endl
				<< dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
			printAllBars(player);
		}
		else
		{
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::grey(" |    1) Attack      |   ") << dye::bright_white("|  2) Move Forward  |   | 3) Move Backward  |   | 4) Move Back & Attack |   |   5) Return   |  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
			printAllBars(player);


			//Scuffed color pallet lmao
			/*cout << dye::light_yellow("  This is a ") << dye::yellow("legendary") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  This is an ") << dye::light_blue("epic") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  This is an ") << dye::light_green("uncommon") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  This is a ") << dye::bright_white("common") << dye::light_yellow(" item.") << endl;
			cout << dye::light_yellow("  It's wizard time motherfucker, ") << dye::light_red("FIREBALL") << endl;
			cout << dye::light_yellow("  It's wizard time motherfucker, ") << dye::aqua("ICE SPEAR") << endl;
			cout << dye::light_yellow("  It's wizard time motherfucker, ") << dye::purple("THUNDERBOLT") << endl;
			cout << dye::light_yellow("  It's sword time motherfucker, ") << dye::white("SLASH") << endl;
			cout << dye::light_yellow("  You recieve 10 points of ") << dye::green("healing") << endl;
			cout << dye::light_yellow("  You take 10 points of ") << dye::red("damage") << endl;
			cout << dye::light_yellow("  You have been ") << dye::light_green("buffed") << endl;
			cout << dye::light_yellow("  You have been ") << dye::light_purple("debuffed") << endl;*/

		}
		break;
	case 2:

		break;
	case 3:

		break;

	case 4:

		break;
	case 5:

		break;
	}

}

void printAllBars(Character character)
{
	printHealthBar(character);
	printStaminaBar(character);
	printManaBar(character);
}

void printHealthBar(Character player) {
	//red portion of health bar (health remaining)
	int healthRemainingSegments = player.healthPoints / 10;
	//white portion of health bar (health missing)
	int numHealthSegments = player.maxHealthPoints / 10;
	string healthBarText = " Health Remaining:  ";
	cout << healthBarText;
	for (int i = 0; i < healthRemainingSegments; i++)
	{
		cout << dye::red("[]");
	}
	for (int i = 0; i < (player.maxHealthPoints - player.healthPoints) / 10; i++) {
		cout << dye::light_yellow("[]");
	}
	cout << endl;
	cout << endl;
}

void printStaminaBar(Character player) {
	//green portion of stamina bar (stamina remaining)
	int staminaRemainingSegments = player.staminaPoints / 10;
	//white portion of stamina bar (stamina missing)
	int numStaminaSegments = player.maxStaminaPoints / 10;
	string staminaBarText = " Stamina Remaining: ";
	cout << staminaBarText;
	for (int i = 0; i < staminaRemainingSegments; i++)
	{
		cout << dye::green("[]");
	}
	for (int i = 0; i < (player.maxStaminaPoints - player.staminaPoints) / 10; i++) {
		cout << dye::light_yellow("[]");
	}
	cout << endl;
	cout << endl;
}

void printManaBar(Character player)
{
	//green portion of mana bar (mana remaining)
	int manaRemainingSegments = player.manaPoints / 10;
	//white portion of mana bar (mana missing)
	int nummanaSegments = player.maxManaPoints / 10;
	string manaBarText = " Mana Remaining:    ";
	cout << manaBarText;
	for (int i = 0; i < manaRemainingSegments; i++)
	{
		cout << dye::blue("[]");
	}
	for (int i = 0; i < (player.maxManaPoints - player.manaPoints) / 10; i++) {
		cout << dye::light_yellow("[]");
	}
	cout << endl;
	cout << endl;
}