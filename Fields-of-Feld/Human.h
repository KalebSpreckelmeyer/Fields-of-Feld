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
	bool isPlayer = false;
	enum CharacterClass { DEFAULT, WIZARD, BATTLEMAGE, FROSTMAGE, NECROMANCER, GEOMANCER, DRUID, PYROMANCER, PRIEST, CLERIC, BARD,
		HUNTER, KNIGHT, BANDIT, WRETCH, HIGHLANDER, SWORDSMAN, NOBLE };
	CharacterClass classChoice = CharacterClass::DEFAULT;
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
	float flatDefense = 0.0f;
	float weightBurden = 0.0f;
	float maxWeightBurden = 100.0f;
	float castSpeed = 99.0f;
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


	Human();

	Human(bool isPlayer, bool isAlly, CharacterClass classChoice, Personality personality, float flatDefense, float health, float fatigue, float strength, float agility, float charisma,
		float intelligence, float arcane, float faith, float luck, float weightBurden, float maxWeightBurden, float castSpeed,
		double experience, double experienceToNextLevel,
		int gold);

	~Human() override = default;

	//DESC:
	//PRE:
	//POST:
	void setInitialHumanStats();

	//DESC:
	//PRE:
	//POST:
	void updateHumanStats();

	//DESC:
	//PRE:
	//POST:
	void getSpells();
	//DESC:
	//PRE:
	//POST:
	Human* setCharacterClass(Human::CharacterClass classChoice);

	//DESC:
	//PRE:
	//POST:
	float softCapMultiplier(float statValue);

	//DESC:
	//PRE:
	//POST:
	void takeDamage(Character* attacker, Character* target, Weapon* weapon, Ammunition* ammunition,
		ThrownConsumable* consumable, Spell* spell, std::optional<std::vector<Character*>>& allies,
		std::optional<std::vector<Character*>>& enemyAllies) override;

};

#endif // !HUMAN_H


