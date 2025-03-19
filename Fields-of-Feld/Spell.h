#ifndef SPELL_H
#define SPELL_H
#include <string>
#include <vector>
#include "Effect.h"
#include <unordered_map>	

class Spell : public Effect {
public:
	
	std::unordered_map<PhysicalDamageType, float>physicalDamages;
	std::unordered_map<MagicDamageType, float> magicDamages;

	//PhysicalDamageType physDmgType = PhysicalDamageType::BLUNT;
	//MagicDamageType magDmgType = MagicDamageType::NONE;

	std::vector<Effect*> effects;
	float intelligenceScaling = 0.0f;
	float faithScaling = 0.0f;
	float arcaneScaling = 0.0f;
	float luckScaling = 0.0f;
	float charismaScaling = 0.0f;
	float fatigueCost = 0.0f;
	float attackSpeed = 0.0f;
	float range = 0.0f;
	bool areaOfEffect = false;
	bool summon = false;
	bool doesDamage = false;	
	bool healing = false;
	bool useOnAlly = false;
	bool useOnSelf = false;
	bool buff = false;

	Spell();
	Spell(bool buff, bool useOnSelf , bool healing, bool useOnAlly, bool summon, bool areaOfEffect, bool applied, std::string name, std::string description,
		PhysicalDamageType physDmg, MagicDamageType magDmg, float range, float magnitude, bool stackable,
		int stacks, int maxStacks, float fatigueCost, float arcaneScaling, float intelligenceScaling,
		float faithScaling, float charismaScaling, float luckScaling, float attackSpeed, bool doesDamage);
	~Spell();

	float calculateSpellDamage(Character* target, Spell spell);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	//SORCERIES
	//NECROMANCY
	Spell* getBonetrousleEffect(Character& caster);
	//GEOMANCY
	Spell* getSummonAnimalAllyEffect(Character& caster);
	Spell* getOakenArmorEffect(Character& caster);
	Spell* getFruitOfTheEarthEffect(Character& caster);
	//CRYOMANCY
	Spell* getEndothermicGraspEffect(Character& caster);
	//MELODIC ARTS
	//MIRACLES
	Spell* getForceBurstEffect(Character& caster);
	//PYROMANCY
	Spell* getFireBallEffect(Character& caster);
	//AEROMANCY
	//FULGURAMANCY
	//VENOMANCY
	std::string getScalingGrade(float scalingValue);

};
#endif // !SPELL_H
