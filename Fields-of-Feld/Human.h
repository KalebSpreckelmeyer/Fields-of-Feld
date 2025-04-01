#ifndef HUMAN_H
#define HUMAN_H
#include "Character.h"
#include <string>
#include "Armor.h"
#include "Weapon.h"
#include "Trinket.h"
#include <vector>
class Human :
	public Character 
{
public:
	int id;
	bool isPlayer = false;
	std::string classChoice = "Default";
	enum Personality { GENERIC, COWARDLY, BRAVE, EAGER, CRUEL, BRUTE, ROYAL, PEASANT, YOUNG, OLD };
	Personality personality = Personality::GENERIC;
	float health = 10.0f;
	float fatigue = 10.0f;
	float strength = 10.0f;
	float agility = 10.0f;
	float charisma = 10.0f;
	float intelligence = 10.0f;
	float arcane = 10.0f;
	float faith = 10.0f;
	float luck = 10.0f;
	float weightBurden = 0.0f;
	float maxWeightBurden = 100.0f;
	float castSpeed = 100.0f;
	double experience = 0.0;
	double experienceToNextLevel = 100.0;
	int gold = 0;

	//Virtual functions to retrieve human specific values in areas where it's difficult to access
	virtual float getLuck() const override { return luck; }
	virtual float getFaith() const override { return faith; }
	virtual float getArcane() const override { return arcane; }
	virtual float getIntelligence() const override { return intelligence; }
	virtual float getCharisma() const override { return charisma; }
	virtual float getAgility() const override { return agility; }
	virtual float getStrength() const override { return strength; }
	virtual float getFatigue() const override { return fatigue; }
	virtual float getHealth() const override { return health; }
	virtual float getSpeed() const override { return agility; }
	virtual float getLevel() const override { return experience; }

	nlohmann::json toJson() const override;
	static std::shared_ptr<Character> fromJson(const nlohmann::json& j);

	Human();

	Human(bool isPlayer, bool isAlly, std::string classChoice, Personality personality, float health, float fatigue, float strength, float agility, float charisma,
		float intelligence, float arcane, float faith, float luck, float weightBurden, float maxWeightBurden, float castSpeed,
		double experience, double experienceToNextLevel,
		int gold);

	~Human() override = default;

	//DESC: Prints the human's stats in a detailed format
	//PRE: Human must be initialized
	//POST: Human's stats will be printed to the console
	void printHumanStats();
	//DESC: Prints the user's attuned spells with their respective stats
	//PRE: Human must be initialized
	//POST: Human's attuned spells will be printed to the console
	void printAttunedSpells();
	//DESC: Sets the human's class based on user input
	//PRE: Human must be initialized
	//POST: Human's class will be set, stats will be initialized, equipment will be dispursed
	std::shared_ptr<Human> setCharacterClass(std::vector<std::shared_ptr<Item>> items, std::vector<std::shared_ptr<Spell>> spells);
	//DESC: Performs initial calculations on player stats to determine derived stats like speed, block chance, etc...
	//PRE: Human must be initialized
	//POST: Human's derived stats will be calculated and set
	void setInitialHumanStats();
	//DESC: Updates the human's stats based on their equipment. To be called upon any time the character equipment or stats are changed
	//PRE: Human must be initialized
	//POST: Human's stats will be updated based on their equipment
	void updateHumanStats();
	//DESC: 
	//PRE:
	//POST:
	float softCapMultiplier(float statValue);

};

#endif // !HUMAN_H


