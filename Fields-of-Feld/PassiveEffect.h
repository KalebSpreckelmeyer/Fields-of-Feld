#pragma once
#include "Effect.h"
#include "TimedEffect.h"

class PassiveEffect :
    public Effect
{
	
};

class FatigueBuff : public TimedEffect
{
public:
	FatigueBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target);
	void tick(Character& target);

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);


	std::string getType() const;
};

class HealthBuff : public TimedEffect
{
public:
	HealthBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target);
	void tick(Character& target);

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class CastSpeed : public TimedEffect
{
public:
	CastSpeed(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target);
	void tick(Character& target);

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class Summon : public TimedEffect
{
public:
	Summon(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target);
	void tick(Character& target);

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ArmorBuff : public TimedEffect
{
public:
	ArmorBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target);
	void tick(Character& target);

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class Healing : public TimedEffect
{
public:
	Healing(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target);
	void tick(Character& target);

	nlohmann::json toJson() const;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};