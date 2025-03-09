#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
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
//DESC:
//PRE:
//POST:
void openCombat(Character& player, Character& enemy1);
void openCombat(Character& player, Character& enemy1, Character& enemy2);
void openCombat(Character& player, Character& enemy1, Character& enemy2, Character& enemy3);
void openCombat(Character& player, Character& enemy1, Character& enemy2, Character& enemy3, Character& enemy4);
void openCombat(Character& player, Character& enemy1, Character& enemy2, Character& enemy3, Character& enemy4, Character& enemy5);
//DESC:
//PRE:
//POST:
void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy1);
void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy1, Character& enemy2);
void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy1, Character& enemy2, Character& enemy3);
void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy1, Character& enemy2, Character& enemy3, Character& enemy4);
void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy1, Character& enemy2, Character& enemy3, Character& enemy4, Character& enemy5);
//DESC:
//PRE:
//POST:
void enemyTurn(Character& player, Character& enemy);
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
				Character hardEnemy = hardEnemy.createEnemy("Bandit Warlord", 300, 150, 50, 250, 10, 5, 5, 5, 40, 80, 20, 20);
				Character easyEnemy = easyEnemy.createEnemy("Bandit", 150, 100, 50, 200, 10, 5, 5, 5, 20, 20, 5, 15);
				openCombat(character, easyEnemy);
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

void openCombat(Character& player, Character& enemy)
{
	vector<Item> charItems = player.inventory.getEquippedItems();
	Item mainHand;
	Item offHand;
	bool exitFight = false;
	bool optionPicked = false;

	for (int i = 0; i < charItems.size(); i++)
	{
		if (charItems[i].slot == Item::MAINHAND1)
		{
			mainHand = charItems[i];
		}
		if (charItems[i].slot == Item::OFFHAND1)
		{
			offHand = charItems[i];
		}
	}
	//main fight loop
	do
	{
		cout << "Select an option: " << endl;
		if (mainHand.reach >= enemy.distanceFromPlayer)
		{
			cout << dye::light_yellow("1. Attack!") << endl;
		}
		else {
			cout << dye::grey("1. Attack!") << endl;
		}
		cout << "2. Move" << endl;
		cout << "3. Check Enemy" << endl;
		cout << "4. Use Potion" << endl;
		cout << "5. Check Inventory" << endl;
		cout << "6. Attempt to Flee" << endl;
		int choice;
		//input validation
		do
		{
			cout << ">> ";
			std::cin >> choice;
			if (std::cin.fail() || choice > 6 || choice == 0)
			{
				cout << "Enter a number from 1 - 6" << endl;
			}
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		} while (std::cin.fail() || choice > 6 || choice == 0);

		//checks if they selected to attack when they are too far away, doesn't 
		//  progress loop if they can't attack
		if (mainHand.reach < enemy.distanceFromPlayer && choice == 1)
		{
			cout << dye::light_yellow("You are too far away to attack!") << endl;
			break;
		}
		else
		{
			if (player.speed > enemy.speed)
			{
				playerTurn(choice, exitFight, player, enemy);
			}
			else if (player.speed == enemy.speed)
			{
				mt19937 generator(time(nullptr));
				uniform_int_distribution<int> distribution(player.luck, 100);
				int randomSpeed = distribution(generator);

				if (randomSpeed >= 50)
				{
					playerTurn(choice, exitFight, player, enemy);
				}
			}
			else
			{
				enemyTurn(player, enemy);
			}
		}

	} while (exitFight == false);

}

void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy)
{
	vector<Item> charItems = player.inventory.getEquippedItems();
	Item mainHand;
	Item offHand;

	for (int i = 0; i < charItems.size(); i++)
	{
		if (charItems[i].slot == Item::MAINHAND1)
		{
			mainHand = charItems[i];
		}
		if (charItems[i].slot == Item::OFFHAND1)
		{
			offHand = charItems[i];
		}
	}

	switch (choice)
	{
	case 1:
	{
		if (mainHand.reach >= enemy.distanceFromPlayer)
		{

		}
		//attack
		break;
	}
	case 2:
	{
		//Move
		break;
	}
	case 3:
	{
		//Check Enemy
		break;
	}
	case 4:
	{
		//Potion
		break;
	}
	case 5:
	{
		//check inventory
		break;
	}
	case 6:
	{
		//run

		//sets up random number for the calculations on whether or not running is successful
		mt19937 generator(time(nullptr));
		uniform_int_distribution<int> distribution(enemy.speed / 2, enemy.speed);
		int randomSpeed = distribution(generator);
		if (player.speed >= enemy.speed)
		{
			exitFight = true;
			cout << "Your superior speed allowed you to slip away!" << endl;
		}
		else if (player.speed >= randomSpeed)
		{
			exitFight = true;
			cout << "In spite of your enemy's superior speed you managed to slip away!" << endl;
		}
		else {
			cout << "The enemy is too fast for you to slip away!" << endl;
		}
		break;
	}
	}
}

void enemyTurn(Character& player, Character& enemy)
{
	//add more here if more potion types get implemented
	Potion healingPotion = enemy.inventory.getHealingPotion();
	//Drinks a potion if health is below 1/3
	if (enemy.healthPoints <= enemy.maxHealthPoints / 3 && healingPotion.magnitude >= 1)
	{
		enemy.drinkPotion(healingPotion);
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
