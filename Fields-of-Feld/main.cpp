#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include "color.hpp"

void printMainCombatMenu();

using namespace std;

int main()
{
	//case 1:
	//{
	//	character.characterClass = "Wizard";
	//	character.health = 10;
	//	character.mana = 20;
	//	character.stamina = 7;
	//	character.strength = 7;
	//	character.agility = 7;
	//	character.arcane = 20;
	//	character.faith = 1;
	//	character.luck = 10;
	//	// placeholder values for armor inside function
	//	character.setCharacterAttributes(5);
	//	break;
	//}
	//case 2:
	//{
	//	character.characterClass = "Knight";
	//	character.health = 16;
	//	character.mana = 5;
	//	character.stamina = 15;
	//	character.strength = 16;
	//	character.agility = 10;
	//	character.arcane = 5;
	//	character.faith = 5;
	//	character.luck = 10;
	//	// placeholder values for armor inside function
	//	character.setCharacterAttributes(40);
	//	break;
	//}
	//case 3:
	//{
	//	character.characterClass = "Cleric";
	//	character.health = 10;
	//	character.mana = 15;
	//	character.stamina = 10;
	//	character.strength = 10;
	//	character.agility = 5;
	//	character.arcane = 2;
	//	character.faith = 20;
	//	character.luck = 10;
	//	// placeholder values for armor inside function
	//	character.setCharacterAttributes(15);
	//	break;
	//}
	//case 4:
	//{
	//	character.characterClass = "Archer";
	//	character.health = 10;
	//	character.mana = 5;
	//	character.stamina = 15;
	//	character.strength = 7;
	//	character.agility = 20;
	//	character.arcane = 10;
	//	character.faith = 5;
	//	character.luck = 10;
	//	// placeholder values for armor inside function
	//	character.setCharacterAttributes(25);
	//	break;
	//}
	//default:

		
	int choice;
	printMainCombatMenu(); 
	cin >> choice;
	return 0;
}

void printMainCombatMenu() 
{
	//temp hardcoded values
	int enemyDistance = 10;
	int range = 5;
	cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
		 << dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
		 << dye::light_yellow(" |     1) Move       |   |    2) Attack      |   |   3) Use Item     |   |  4) Check Enemy   |   | 5) Attempt to Run |  ") << endl
         << dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =-------------------=   =-------------------=  ") << endl
         << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
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
		if (range >= enemyDistance)
		{
			cout       << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				 << dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				 << dye::light_yellow(" |    1) Attack      |   |  2) Move Forward  |   | 3) Move Backward  |   | 4) Retreat & Attack |   |    5) Return    |  ") << endl
				 << dye::light_yellow(" =-------------------=   =-------------------=   =-------------------=   =---------------------=   =-----------------=  ") << endl
				       << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;

		}
		else
		{
			cout << dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::grey(" |    1) Attack      |   ") << dye::light_yellow("|  2) Move Forward  |   | 3) Move Backward  |   | 4) Move Back & Attack |   |   5) Return   |  ") << endl
				<< dye::grey(" =-------------------=   ") << dye::light_yellow("=-------------------=   =-------------------=   =-----------------------=   =---------------=  ") << endl
				<< dye::bright_white(" ---------------------------------------------------------------------------------------------------------------------  ") << endl;
			cout << dye::light_yellow("  This is a ") << dye::yellow("legendary") << dye::light_yellow(" item.") << endl;
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
			cout << dye::light_yellow("  You have been ") << dye::light_purple("debuffed") << endl;

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

//void printHealthBar(Player player) {
//	//red portion of health bar (health remaining)
//	int healthRemainingSegments = player.healthPoints / 10;
//	//white portion of health bar (health missing)
//	int numHealthSegments = player.maxHealth / 10;
//	string healthBarText = "Health Remaining: ";
//	cout << healthBarText;
//	for (int i = 0; i < healthRemainingSegments; i++)
//	{
//		cout << dye::red("[]");
//	}
//	for (int i = 0; i < (player.maxHealth - player.healthPoints) / 10; i++) {
//		cout << dye::white("[]");
//	}
//	cout << endl;
//	cout << endl;
//}
//
//void printStaminaBar(Player player) {
//	//green portion of stamina bar (stamina remaining)
//	int staminaRemainingSegments = player.staminaPoints / 10;
//	//white portion of stamina bar (stamina missing)
//	int numStaminaSegments = player.maxStamina / 10;
//	string staminaBarText = "Stamina Remaining: ";
//	cout << staminaBarText;
//	for (int i = 0; i < staminaRemainingSegments; i++)
//	{
//		cout << dye::green("[]");
//	}
//	for (int i = 0; i < (player.maxStamina - player.staminaPoints) / 10; i++) {
//		cout << dye::white("[]");
//	}
//	cout << endl;
//	cout << endl;
//}
//
//void printManaBar(Player player) {
//	//green portion of mana bar (mana remaining)
//	int manaRemainingSegments = player.manaPoints / 10;
//	//white portion of mana bar (mana missing)
//	int nummanaSegments = player.maxMana / 10;
//	string manaBarText = "mana Remaining: ";
//	cout << manaBarText;
//	for (int i = 0; i < manaRemainingSegments; i++)
//	{
//		cout << dye::blue("[]");
//	}
//	for (int i = 0; i < (player.maxMana - player.manaPoints) / 10; i++) {
//		cout << dye::white("[]");
//	}
//	cout << endl;
//	cout << endl;
//}