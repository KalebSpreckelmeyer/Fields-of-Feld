#pragma once
#include "Effect.h"
#include "TimedEffect.h"
#include "Defense.h"

class PassiveEffect :
    public Effect
{
	
};

class FatigueBuff : public TimedEffect
{
public:
	FatigueBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);


	std::string getType() const;
};

class HealthBuff : public TimedEffect
{
public:
	HealthBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class CastSpeed : public TimedEffect
{
public:
	CastSpeed(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class Summon : public TimedEffect
{
public:
	std::shared_ptr<Character> summon;
	Summon(std::shared_ptr<Character> summon, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ArmorBuff : public TimedEffect
{
public:
	Defense defense = Defense::NONE;
	ArmorBuff(Defense defense, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class Healing : public TimedEffect
{
public:
	Healing(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class FatigueRestore : public TimedEffect
{
public:
	FatigueRestore(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;
	
	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const;
};