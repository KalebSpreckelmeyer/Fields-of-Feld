#pragma once
#include "Effect.h"
#include <unordered_map>
#include <string>
#include <memory>
#include "TimedEffect.h"

//class ConsumableEffect : public Effect
//{
//public:
//    ConsumableEffect() = default;
//    virtual ~ConsumableEffect() = default;
//
//    ConsumableEffect(bool doesDamage, bool applied, std::string name, std::string description, float range, float duration, float magnitude, bool stackable,
//        int stacks, int maxStacks, bool areaOfEffect)
//        : Effect(doesDamage, applied, name, description, range, duration, magnitude, stackable, stacks, maxStacks, areaOfEffect) {}
//
//    virtual nlohmann::json toJson() const override {
//        // Implement the toJson method
//        return json();
//    }
//
//    static std::shared_ptr<Effect> fromJson(const nlohmann::json& j) {
//        // Implement the fromJson method
//        return std::make_shared<ConsumableEffect>();
//    }
//
//    virtual void apply(Character& target) override {
//        // Implement the apply method
//    }
//
//    virtual void tick(Character& target) override {
//        // Implement the tick method
//    }
//
//    virtual bool isExpired() const override {
//        // Implement the isExpired method
//        return false;
//    }
//};

class RestoreHealthEffect : public Effect
{
public:
    RestoreHealthEffect(float mangitude);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

    nlohmann::json toJson() const override;
    static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

    std::string getType() const override;

	bool isExpired() const override;
};

class RestoreFatigueEffect : public Effect
{
public:
	RestoreFatigueEffect(float magnitude);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class MaxHealthEffect : public Effect
{
public:
	MaxHealthEffect(float magnitude, float duration);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class MaxFatigueEffect : public Effect
{
public:
	MaxFatigueEffect(float magnitude);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class HealthRegenEffect : public TimedEffect
{
public:
	HealthRegenEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class FatigueRegenEffect : public TimedEffect
{
public:
	FatigueRegenEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class AttackSpeedEffect : public TimedEffect
{
public:
	AttackSpeedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};

class CastSpeedEffect : public TimedEffect
{
public:
	CastSpeedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};

class SpeedEffect : public TimedEffect
{
public:
	SpeedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class BlockChanceEffect : public TimedEffect
{
public:
	BlockChanceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;
	
	bool isExpired() const override;
};

class DodgeChanceEffect : public TimedEffect
{
public:
	DodgeChanceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};

class CritChanceEffect : public TimedEffect
{
public:
	CritChanceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class ResistanceEffect : public TimedEffect
{
public:
	enum class ResistanceType {
		ALL, 
		ALL_MAGIC,
		ALL_PHYSICAL,
		PIERCE,
		BLUNT,
		SLASH,
		CHOP,
		MAGIC,
		FIRE,
		FROST,
		SHOCK,
		WIND,
		POISON,
		BLEED,
		SLEEP,
		DARK,
		HOLY
	};
	ResistanceType resistance;
	ResistanceEffect(ResistanceType resistance, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};

class EscapeEffect : public TimedEffect
{
public:
	EscapeEffect(int duration);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};

class ResurrectEffect : public Effect
{
public:
	ResurrectEffect();

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const override;

	bool isExpired() const override;
};

class AttributeEffect : public TimedEffect
{
public:
	enum class Attribute {
		HEALTH,
		FATIGUE,
		STRENGTH,
		AGILITY,
		INTELLIGENCE,
		ARCANE,
		FAITH,
		CHARISMA,
		LUCK
	};
	Attribute attribute;
	AttributeEffect(Attribute attribute, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};

class RandomEffect : public TimedEffect
{
public:
	RandomEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const override;

	bool isExpired() const override;
};