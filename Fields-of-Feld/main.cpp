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
#include "optional"


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
//DESC:
//PRE:
//POST:
void enemyTurn(Character& player, Character& enemy);
//DESC: Reprints the player turn menu and calls the player turn function with all necessary
// parameters to "restart" a players turn if they select an option that shouldn't consume it
//PRE: Attributes should be properly initialized with appropriate values
//POST: Player turn is "restarted" and it does not advance to enemy's turn
void continueTurn(int choice, bool exitFight, Character player, Character enemy, Item mainHand1 /*Item offHand1*/);
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
				Character easyEnemy;
				easyEnemy.isAlive = true;
				easyEnemy.health = 10;
				easyEnemy.mana = 5;
				easyEnemy.strength = 10;
				easyEnemy.agility = 18;
				easyEnemy.luck = 2;
				easyEnemy.level = 5;
				easyEnemy.name = "Bandit";
				easyEnemy.distanceFromPlayer = 50;
				easyEnemy.gold = 50;

				Item ironDagger = ironDagger.createWeapon("Iron Dagger", "A short blade stained brown with blood", 10,
					3, 60, 1, 1, false, false, Item::weapon_types::DAGGER, Item::physical_damage_types::SLASH,
					Item::magic_damage_types::NOMAGICDAMAGE);
				easyEnemy.inventory.equipItem(ironDagger, Item::MAINHAND1);
				Potion potion = potion.createPotion("Healing Potion", "Heals you", 40, 20, 1, 3, Potion::HEALING);
				Potion biggerPotion = potion.createPotion("Large Healing Potion", "Heals you better", 80, 40, 1, 2, Potion::HEALING);
				Item locket = locket.createLootItem("Silver locket", "A slightly tarnished locket, likely taken from its former owner", 40, 1, 1);
				Item bow = bow.createWeapon("Hunting Bow", "A worn bow once used to hunt game", 5, 20, 50, 4, 20, false, true, Item::weapon_types::LONGBOW, Item::physical_damage_types::PIERCE, Item::magic_damage_types::NOMAGICDAMAGE);
				easyEnemy.inventory.addItemToBackpack(bow);
				easyEnemy.inventory.addLootItems(locket);
				easyEnemy.inventory.addPotion(potion);
				character.inventory.addPotion(potion);
				character.inventory.addPotion(biggerPotion);
				vector<Item> items = {ironDagger};
				easyEnemy.refreshCharacterStats();
				easyEnemy.setArmorValues(items);
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
			cout << dye::yellow("Enter your name:") << endl;
			string playerName;
			getline(cin, playerName);
			character.name = playerName;

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
	//expand on this based on the characters level, archetype, etc...
	cout << "You encounter a " << enemy.name << "!" << endl;
	if (enemy.level <= player.level)
	{
		cout << "They shuffel about nervously" << endl;
	}
	if (enemy.level > player.level + 4)
	{
		cout << "They look tough..." << endl;
	}
	else if (enemy.level > player.level + 9)
	{
		cout << "You consider running away..." << endl;
	}
	vector<Item> charItems = player.inventory.getEquippedItems();
	Item mainHand;
	Item offHand;
	bool exitFight = false;

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
		int choice = 0;
		if (player.isAlive == true && enemy.isAlive == true)
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
		}
		//if player choses to check enemy (it shouldn't consume a turn)
		if (choice == 3 && player.isAlive == true && enemy.isAlive == true)
		{
			enemy.checkEnemy();
		}
		//if player killed enemy
		else if (player.isAlive == true && enemy.isAlive == false)
		{
			player.gainExperience(enemy);
			player.openLootInterface(enemy);
			exitFight = true;
		}
		//checks if they selected to attack when they are too far away, doesn't 
		//  progress loop if they can't attack
		else if (mainHand.reach < enemy.distanceFromPlayer && choice == 1 && player.isAlive == true && enemy.isAlive == true)
		{
			cout << dye::light_yellow("You are too far away to attack!") << endl;
			continue;
		}
		else
		{
			//turn order
			if (player.speed > enemy.speed && player.isAlive == true && enemy.isAlive == true)
			{
				playerTurn(choice, exitFight, player, enemy);
				if (exitFight == true) {
					cout << "The enemy's attack grazes the air of where you once stood!" << endl;
				}
				else
				{
					enemyTurn(player, enemy);
				}
				
			}
			else if (player.speed == enemy.speed && player.isAlive == true && enemy.isAlive == true)
			{
				mt19937 generator(time(nullptr));
				uniform_int_distribution<int> distribution(player.luck, 100);
				int randomSpeed = distribution(generator);

				if (randomSpeed >= 50)
				{
					playerTurn(choice, exitFight, player, enemy);
					if (exitFight == true) {
						cout << "The enemy's attack grazes the air of where you once stood!" << endl;
					}
					else
					{
						enemyTurn(player, enemy);
					}
				}
			}
			else if (player.speed < enemy.speed && player.isAlive == true && enemy.isAlive == true)
			{
				//if they chose to drink a potion their turn gets priority
				if (choice == 4)
				{
					playerTurn(choice, exitFight, player, enemy);
					enemyTurn(player, enemy);

				}
				else
				{
					enemyTurn(player, enemy);
					playerTurn(choice, exitFight, player, enemy);
				}
				
			}
			//player is dead
			else
			{
				cout << "Exiting game..." << endl;
				exitFight = true;
			}
		}

	} while (exitFight == false);

}

void playerTurn(int choice, bool& exitFight, Character& player, Character& enemy)
{
	Item mainHand1;
	Item mainHand2;
	Item offHand1;
	Item offHand2;
	player.inventory.getEquippedWeapons(mainHand1, mainHand2, offHand1, offHand2);

	for (int i = 0; i < 1; i++)
	{
		switch (choice)
		{
		case 1:
		{
			if (player.isAlive == true)
			{
				for (int i = 0; i < 101;)
				{
					cout << dye::light_yellow("You strike forth with your ") << dye::light_yellow(mainHand1.name) << endl;
					enemy.takeDamage(player);
					i += (100 - mainHand1.attackSpeed);
				}
				break;
			}
			//attack
			break;
		}
		case 2:
		{
			//Move
			if (enemy.distanceFromPlayer <= 0)
			{
				cout << "You stand close enough to reach out and touch your enemy, you can't move forward anymore!" << endl;
				continueTurn(choice, exitFight, player, enemy, mainHand1 /*Item offHand1*/);
				break;
			}
			else
			{
				float distanceClosed;
				if ((player.speed / 10) < 0)
				{
					distanceClosed = 1;
				}
				else
				{
					distanceClosed = player.speed / 10;
				}
				enemy.distanceFromPlayer -= distanceClosed;
				std::cout << player.name << " closes the distance by " << distanceClosed << " units!" << endl;
				break;
			}
			break;
		}
		case 3:
		{
			//Check Enemy
			enemy.checkEnemy();
			continueTurn(choice, exitFight, player, enemy, mainHand1 /*Item offHand1*/);
			break;
		}
		case 4:
		{
			//Potion
			bool turnOver = true;
			player.openPotionDialogue(turnOver);

			if (turnOver == false)
			{
				continueTurn(choice, exitFight, player, enemy, mainHand1 /*Item offHand1*/);
			}
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
			if (player.speed >= enemy.speed && player.isAlive == true)
			{
				exitFight = true;
				cout << "Your superior speed allowed you to slip away!" << endl;
			}
			else if (player.speed >= randomSpeed && player.isAlive == true)
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
}

void enemyTurn(Character& player, Character& enemy)
{
	bool turnOver = false;

	Item mainHand1;
	Item mainHand2;
	Item offHand1;
	Item offHand2;
	enemy.inventory.getEquippedWeapons(mainHand1, mainHand2, offHand1, offHand2);

	//add more here if more potion types get implemented  
	std::optional<Potion> healingPotionOpt = enemy.inventory.getHealingPotion();
	if (healingPotionOpt.has_value())
	{
		//random num generation
		Potion healingPotion = healingPotionOpt.value();
		mt19937 generator(time(nullptr));
		uniform_int_distribution<int> distribution(player.luck, 100);
		int potionChance = distribution(generator);

		//potentially game breaking depending on where we cap luck values, adjust if needed
		//Can drink a potion if health is below 1/3
		float thirdHealth = enemy.maxHealthPoints / 3;
		if (enemy.healthPoints < thirdHealth && potionChance < 50 && turnOver == false && enemy.isAlive == true)
		{
			enemy.drinkPotion(healingPotion);
			turnOver = true;
		}
	}
	//if they're in range of the player with their weapon
	if (mainHand1.reach >= enemy.distanceFromPlayer && turnOver == false && enemy.isAlive == true)
	{
		for (int i = 0; i < 101;)
		{
			cout << dye::light_yellow("The ") << dye::light_yellow(enemy.name) << dye::light_yellow(" strikes forward with their ") 
				<< dye::light_yellow(mainHand1.name) << endl;
			player.takeDamage(enemy);
			i += (100 - mainHand1.attackSpeed);
			turnOver = true;
		}
	}
	//move closer
	else if (mainHand1.reach < enemy.distanceFromPlayer && turnOver == false && enemy.isAlive == true)
	{
		float distanceClosed;
		if ((enemy.speed / 10) < 0)
		{
			distanceClosed = 1;
			turnOver = true;
		}
		else
		{
			distanceClosed = enemy.speed / 10;
			turnOver = true;
		}
		enemy.distanceFromPlayer -= distanceClosed;
		std::cout << "The " << enemy.name << " closes the distance by " << distanceClosed << " units!" << endl;
	}
}

void printAllBars(Character character)
{
	printHealthBar(character);
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

void continueTurn(int choice, bool exitFight, Character player, Character enemy, Item mainHand1 /*Item offHand1*/)
{
	cout << "Select an option: " << endl;
	if (mainHand1.reach >= enemy.distanceFromPlayer)
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
	playerTurn(choice, exitFight, player, enemy);
}