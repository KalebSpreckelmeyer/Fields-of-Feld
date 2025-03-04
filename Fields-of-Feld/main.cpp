#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include "color.hpp"

using namespace std;

#pragma region character

class Character
{
public:
	bool dead;
	bool active;
	string characterClass;
	int health;
	int stamina;
	int mana;
	int strength;
	int agility;
	int arcane;
	int faith;
	int luck;
	int speed;

	int maxHealth;
	int maxMana;
	int maxStamina;
	int characterLevel;
	int experiencePoints;
	int experienceToLevel;
	int healthPoints;
	int manaPoints;
	int staminaPoints;
	int armorValue;

	int maxHunger;
	int currentHunger;
	int maxThirst;
	int currentThirst;
	int maxExhaustion;
	int currentExhaustion;

	void setCharacterAttributes(int armorWeight = 0)
	{                                                                                               // should only be run one time in the class initialization section
		characterLevel = health + mana + stamina + strength + agility + arcane + faith + luck - 81; // 82 is sum of all starting points for all classes
		healthPoints = (health * 10) + (strength * 2);
		maxHealth = healthPoints;

		dead = false;
		active = true;
		// sets manaPoints to mainly rely on mana, with a small bonus from the higher stat between faith and arcane and an even smaller bonus
		//     from the unfavored of the two
		(arcane >= faith) ? manaPoints = (mana * 10) + (arcane * 2) + (faith * 1) : (mana * 10) + (arcane * 1) + (faith * 2);
		manaPoints = (mana * 10) + (arcane);
		maxMana = manaPoints;

		//Sets stamina points to mainly rely on stamina, with a small bonus from the higher between agility and strength with an even smaller 
		//    bonus coming from the unfavored of the two stats
		(agility >= strength) ? staminaPoints = (stamina * 10) + (agility * 2) : staminaPoints = (stamina * 10) + (agility * 2);
		maxStamina = staminaPoints;
		speed = (agility * 20) - armorWeight;
		experiencePoints = 0;
		experienceToLevel = characterLevel * 100;

		// placeholder
		armorValue = armorWeight;

		maxHunger = 100;
		currentHunger = maxHunger;
		maxThirst = 100;
		currentThirst = maxThirst;
		maxExhaustion = 100;
		currentExhaustion = maxExhaustion;
	}

	void updateCharacterAttributes(int armorWeight = 0)
	{ // should be run after a change in character attributes to adjust values accordingly
		healthPoints = health * 10;
		manaPoints = mana * 10;
		staminaPoints = stamina * 10;
		experienceToLevel = characterLevel * 100;
		speed = (agility * 20) - armorWeight;
	}
	void takeDamage(int damageTaken)
	{
		healthPoints -= damageTaken;
	}
	void receiveHealing(int healingReceived)
	{
		healthPoints += healingReceived;
	}
	void gainExperience(int experienceGained)
	{
		experiencePoints += experienceGained;
	}
	void loseExperience(int experienceLost)
	{
		experiencePoints -= experienceLost;
	}
	void statDebuff(int statToLower, int amountToLower)
	{
		switch (statToLower)
		{
		case 1:
			health -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
			break;
		case 2:
			mana -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
			break;
		case 3:
			stamina -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
		case 4:
			strength -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
		case 5:
			agility -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
		case 6:
			arcane -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
		case 7:
			faith -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
		case 8:
			luck -= amountToLower;
			characterLevel -= 1;
			updateCharacterAttributes();
		case 9:
			maxHealth -= amountToLower;
			updateCharacterAttributes();
		default:
			break;
		}
	}
	void statUpgrade(int statToIncrease, int amountToIncrease)
	{
		switch (statToIncrease)
		{
		case 1:
			health += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
			break;
		case 2:
			mana += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
			break;
		case 3:
			stamina += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
		case 4:
			strength += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
		case 5:
			agility += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
		case 6:
			arcane += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
		case 7:
			faith += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
		case 8:
			luck += amountToIncrease;
			characterLevel += 1;
			updateCharacterAttributes();
		case 9:
			maxHealth += amountToIncrease;
			updateCharacterAttributes();
		default:
			break;
		}
	}
	void printStats()
	{
		if (active == true)
		{
			cout << "The: " << dye::blue(characterClass) << endl;
			cout << "---------------------------------" << endl;
			cout << "Attributes: " << endl;
			cout << dye::red("Health: ") << dye::red(health) << endl;
			cout << dye::light_aqua("Mana: ") << dye::light_aqua(mana) << endl;
			cout << dye::green("Stamina: ") << dye::green(stamina) << endl;
			cout << "Strength: " << strength << endl;
			cout << "Agility: " << agility << endl;
			cout << "Arcane: " << arcane << endl;
			cout << "Faith: " << faith << endl;
			cout << "Luck: " << luck << endl;
			cout << "---------------------------------" << endl;
			cout << "Derived Stats: " << endl;
			cout << dye::red("Health Points: ") << dye::red(healthPoints) << "/" << dye::red(maxHealth) << endl;
			cout << dye::light_aqua("Mana Points: ") << dye::light_aqua(manaPoints) << "/" << dye::light_aqua(maxMana) << endl;
			cout << dye::green("Stamina Points: ") << dye::green(staminaPoints) << "/" << dye::green(maxStamina) << endl;
			cout << dye::yellow("Speed: ") << dye::yellow(speed) << endl;
		}
		else
		{
			cout << "No character found." << endl;
		}
	}
};
#pragma endregion character

#pragma region function declarations
//DESC: Sets the current character based on integer input
//PRE: None
//POST: None
Character selectCharacter(int num);

//DESC: These print out a stylized bar based on the character's current and max health, stamina, and mana
//PRE: None
//POST: None
void printHealthBar(Character character);
void printStaminaBar(Character character);
void printManaBar(Character character);

#pragma endregion function declarations

int main()
{
#pragma region game
	int menuInput;
	Character character;
	do
	{
		cout << endl;
		cout << "---------------------------------" << endl;
		cout << "Fields of Feld - Main Menu" << endl;
		cout << "---------------------------------" << endl;
		cout << "1. Start a new game" << endl;
		cout << "2. Continue your adventure" << endl;
		cout << "3. Check the stats of your character" << endl;
		cout << "4. Exit the game (progress will not be saved)" << endl;

		do
		{
			cout << ">> ";
			cin >> menuInput;
			if (cin.fail())
			{
				cout << "Please enter a valid number from 1 - 4" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		} while (cin.fail());
		switch (menuInput)
		{
		case 1:
		{
			cout << endl;
			cout << "---------------------------------" << endl;
			cout << "Select your character..." << endl;
			cout << "---------------------------------" << endl;
			cout << "1. The Wizard" << endl;
			cout << "2. The Knight" << endl;
			cout << "3. The Cleric" << endl;
			cout << "4. The Archer" << endl;

			int classSelection;
			do
			{
				cout << ">> ";
				cin >> classSelection;
				if (cin.fail())
				{
					cout << "Please enter a valid number between 1 - 4" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}
			} while (cin.fail());

			character = selectCharacter(classSelection);
			// After character selection
			printHealthBar(character);
			cout << "Take 50 points of health damage!" << endl;
			character.healthPoints -= 50;
			printHealthBar(character);
			printStaminaBar(character);
			cout << "Take 50 points of stamina damage!" << endl;
			character.staminaPoints -= 50;
			printStaminaBar(character);
			printManaBar(character);
			cout << "Take 50 points of mana damage!" << endl;
			character.manaPoints -= 50;
			printManaBar(character);
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			character.printStats();
			break;
		}
		case 4:
		{
			cout << "Exiting program..." << endl;
			break;
		}
		}
	} while (menuInput != 4);
#pragma endregion game
	return 0;
}

Character selectCharacter(int num)
{
	Character character;
	switch (num)
	{
	case 1:
	{
		character.characterClass = "Wizard";
		character.health = 10;
		character.mana = 20;
		character.stamina = 7;
		character.strength = 7;
		character.agility = 7;
		character.arcane = 20;
		character.faith = 1;
		character.luck = 10;
		// placeholder values for armor inside function
		character.setCharacterAttributes(5);
		break;
	}
	case 2:
	{
		character.characterClass = "Knight";
		character.health = 16;
		character.mana = 5;
		character.stamina = 15;
		character.strength = 16;
		character.agility = 10;
		character.arcane = 5;
		character.faith = 5;
		character.luck = 10;
		// placeholder values for armor inside function
		character.setCharacterAttributes(40);
		break;
	}
	case 3:
	{
		character.characterClass = "Cleric";
		character.health = 10;
		character.mana = 15;
		character.stamina = 10;
		character.strength = 10;
		character.agility = 5;
		character.arcane = 2;
		character.faith = 20;
		character.luck = 10;
		// placeholder values for armor inside function
		character.setCharacterAttributes(15);
		break;
	}
	case 4:
	{
		character.characterClass = "Archer";
		character.health = 10;
		character.mana = 5;
		character.stamina = 15;
		character.strength = 7;
		character.agility = 20;
		character.arcane = 10;
		character.faith = 5;
		character.luck = 10;
		// placeholder values for armor inside function
		character.setCharacterAttributes(25);
		break;
	}
	default:
	{
		cout << "INVALID CLASS SELECTION" << endl;
		break;
	}
	}
	return character;
}

void printHealthBar(Character character) {
	//red portion of health bar (health remaining)
	int healthRemainingSegments = character.healthPoints / 10;
	//white portion of health bar (health missing)
	int numHealthSegments = character.maxHealth / 10;
	string healthBarText = "Health Remaining: ";
	cout << healthBarText;
	for (int i = 0; i < healthRemainingSegments; i++)
	{
		cout << dye::red("[]");
	}
	for (int i = 0; i < (character.maxHealth - character.healthPoints) / 10; i++) {
		cout << dye::white("[]");
	}
	cout << endl;
	cout << endl;
}

void printStaminaBar(Character character) {
	//green portion of stamina bar (stamina remaining)
	int staminaRemainingSegments = character.staminaPoints / 10;
	//white portion of stamina bar (stamina missing)
	int numStaminaSegments = character.maxStamina / 10;
	string staminaBarText = "Stamina Remaining: ";
	cout << staminaBarText;
	for (int i = 0; i < staminaRemainingSegments; i++)
	{
		cout << dye::green("[]");
	}
	for (int i = 0; i < (character.maxStamina - character.staminaPoints) / 10; i++) {
		cout << dye::white("[]");
	}
	cout << endl;
	cout << endl;
}

void printManaBar(Character character) {
	//green portion of mana bar (mana remaining)
	int manaRemainingSegments = character.manaPoints / 10;
	//white portion of mana bar (mana missing)
	int nummanaSegments = character.maxMana / 10;
	string manaBarText = "mana Remaining: ";
	cout << manaBarText;
	for (int i = 0; i < manaRemainingSegments; i++)
	{
		cout << dye::blue("[]");
	}
	for (int i = 0; i < (character.maxMana - character.manaPoints) / 10; i++) {
		cout << dye::white("[]");
	}
	cout << endl;
	cout << endl;
}