#ifndef SPELL_H
#define SPELL_H
#include <string>
#include <vector>
#include "Effect.h"
#include <unordered_map>
#include "memory"
#include "IDManager.h"
#include "StatScaling.h"

class Spell {
public:
	int id;

	std::unordered_map<StatScaling, int> statRequirements;
	std::vector<std::shared_ptr<Effect>> effects;
	std::string name;
	std::string description;
	bool useOnAlly = false;
	bool useOnSelf = false;
	bool useOnEnemy = false;
	float intelligenceScaling = 0.0f;
	float faithScaling = 0.0f;
	float arcaneScaling = 0.0f;
	float luckScaling = 0.0f;
	float charismaScaling = 0.0f;
	float fatigueCost = 0.0f;
	float attackSpeed = 0.0f;
	float range = 0.0f;
	

	Spell();
	Spell(std::string name, std::string description, bool useOnAlly, bool useOnSelf, bool useOnEnemy, float intelligenceScaling, 
		float faithScaling, float arcaneScaline, float luckScaling, float charismaScaling, float fatigueCost, float attackSpeed, float range);
	~Spell() = default;

	nlohmann::json toJson() const;
	static std::shared_ptr<Spell> fromJson(const nlohmann::json& j);;

	void setStatRequirements(StatScaling stat, int value);
	std::unordered_map<std::string, int> getStatRequirements();

	bool checkSpellRequirements(std::shared_ptr<Spell> spell, std::shared_ptr<Character> caster);

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
	std::shared_ptr<Spell> getWarmthOfTheGodsEffect(Character& caster);
	//PYROMANCY
	std::shared_ptr<Spell> getFireBallEffect(Character& caster);
	//AEROMANCY
	//FULGURAMANCY
	std::shared_ptr<Spell> getThunderboltEffect(Character& caster);
	std::shared_ptr<Spell> getLightningArmamentEffect(Character& caster);
	//VENOMANCY

	std::string getScalingGrade(float scalingValue);

};
#endif // !SPELL_H
