#include "Actor.h"
using namespace std;

Actor::Actor(int actorID,
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
	Inventory inventory)
{
	this->actorID = actorID;
	this->name = name;
	this->isAlive = isAlive;
	this->health = health;
	this->healthPoints = healthPoints;
	this->maxHealthPoints = maxHealthPoints;
	this->mana = mana;
	this->manaPoints = manaPoints;
	this->maxManaPoints = maxManaPoints;
	this->stamina = stamina;
	this->staminaPoints = staminaPoints;
	this->maxStaminaPoints = maxStaminaPoints;
	this->strength = strength;
	this->agility = agility;
	this->arcane = arcane;
	this->faith = faith;
	this->luck = luck;
	this->speed = speed;
	this->dodgeChance = dodgeChance;
	this->critChance = critChance;
	this->level = level;
	this->gold = gold;
	this->inventory = inventory;
	this->inventory.add(Item("Iron Short Sword", WEAPON, COMMON, 10, 10));
} 

Actor::~Actor()
{

}	