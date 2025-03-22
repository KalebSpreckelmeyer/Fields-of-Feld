#pragma once
#include "Effect.h"
#include "TimedEffect.h"

class OffensiveEffect :
    public Effect
{
	
};

class BleedEffect : public TimedEffect
{
public:
	BleedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class BurnEffect : public TimedEffect
{
public:
	BurnEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class PoisonEffect : public TimedEffect
{
public:
	PoisonEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class FrostBurstEffect : public TimedEffect
{
public:
	FrostBurstEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ShockEffect : public TimedEffect
{
public:
	ShockEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class SleepEffect : public TimedEffect
{
public:
	SleepEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class StunEffect : public TimedEffect
{
public:
	StunEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class KnockbackEffect : public TimedEffect
{
public:
	KnockbackEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class FearEffect : public TimedEffect
{
public:
	FearEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ArmorPenetrationEffect : public TimedEffect
{
public:
	ArmorPenetrationEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

