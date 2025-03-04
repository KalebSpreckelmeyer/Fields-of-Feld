#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<sstream>

#include "Inventory.h"

using namespace std;

class Actor
{
private:
	int actorID;
	string name;
	bool isAlive;
	int health;
	int healthPoints;
	int maxHealthPoints;
	int mana;
	int manaPoints;
	int maxManaPoints;
	int stamina;
	int staminaPoints;
	int maxStaminaPoints;
	int strength;
	int agility;
	int arcane;
	int faith;
	int luck;
	int dodgeChance;
	int critChance;
	int speed;
	int level;
	int gold;
	Inventory inventory;

public:
	Actor(int actorID,
		string name,
		bool isAlive,
		int health,
		int healthPoints,
		int maxHealthPoints,
		int mana,
		int manaPoints,
		int maxManaPoints,
		int stamina,
		int staminaPoints,
		int maxStaminaPoints,
		int strength,
		int agility,
		int arcane,
		int faith,
		int luck,
		int dodgeChance,
		int critChance,
		int speed,
		int level,
		int gold,
		Inventory inventory);
	virtual ~Actor();

	const string toString()
	{

	}
};

