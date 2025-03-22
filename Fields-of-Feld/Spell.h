#ifndef SPELL_H
#define SPELL_H
#include <string>
#include <vector>
#include "Effect.h"
#include <unordered_map>
#include "memory"

class Spell {
public:
	
	std::unordered_map<PhysicalDamageType, float>physicalDamages;
	std::unordered_map<MagicDamageType, float> magicDamages;

	PhysicalDamageType physType = PhysicalDamageType::BLUNT;
	MagicDamageType magType = MagicDamageType::NONE;

	std::vector<std::shared_ptr<Effect>> effects;
	std::string name;
	std::string description;
	bool areaOfEffect = false;
	bool summon = false;
	bool doesDamage = false;
	bool healing = false;
	bool useOnAlly = false;
	bool useOnSelf = false;
	bool buff = false;
	int duration;
	float magnitude;
	bool stackable;
	int stacks;
	int maxStacks;
	float intelligenceScaling = 0.0f;
	float faithScaling = 0.0f;
	float arcaneScaling = 0.0f;
	float luckScaling = 0.0f;
	float charismaScaling = 0.0f;
	float fatigueCost = 0.0f;
	float attackSpeed = 0.0f;
	float range = 0.0f;
	

	Spell() = default;
	Spell(bool areaOfEffect, bool summon, bool doesDamage, bool healing, bool useOnAlly, bool useOnSelf, bool buff, int duration,
		float magnitude, bool stackable, int stacks, int maxStacks, float intelligenceScaling, float faithScaling, float arcaneScaline,
		float luckScaling, float charismaScaling, float fatigueCost, float attackSpeed, float range);
	~Spell() = default;

	nlohmann::json toJson() const;
	static std::shared_ptr<Spell> fromJson(const nlohmann::json& j);

	float calculateSpellDamage(std::shared_ptr<Character> target, Spell spell);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	//SORCERIES
	//NECROMANCY
	std::shared_ptr<Spell> getBonetrousleEffect(Character& caster);
	//GEOMANCY
	std::shared_ptr<Spell> getSummonAnimalAllyEffect(Character& caster);
	std::shared_ptr<Spell> getOakenArmorEffect(Character& caster);
	std::shared_ptr<Spell> getFruitOfTheEarthEffect(Character& caster);
	//CRYOMANCY
	std::shared_ptr<Spell> getEndothermicGraspEffect(Character& caster);
	//MELODIC ARTS
	//MIRACLES
	std::shared_ptr<Spell> getForceBurstEffect(Character& caster);
	//PYROMANCY
	std::shared_ptr<Spell> getFireBallEffect(Character& caster);
	//AEROMANCY
	//FULGURAMANCY
	//VENOMANCY
	std::string getScalingGrade(float scalingValue);

};
#endif // !SPELL_H
