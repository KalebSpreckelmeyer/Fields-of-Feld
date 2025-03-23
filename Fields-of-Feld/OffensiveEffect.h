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

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class BurnEffect : public TimedEffect
{
public:
	BurnEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class BurnDamageEffect : public TimedEffect
{
public:
	BurnDamageEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class PoisonEffect : public TimedEffect
{
public:
	PoisonEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class PoisonDamageEffect : public TimedEffect
{
public:
	PoisonDamageEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};
class FrostBurstEffect : public TimedEffect
{
public:
	FrostBurstEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ShockEffect : public TimedEffect
{
public:
	bool burstTriggered = false;
	ShockEffect(bool burstTriggered, int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class SleepEffect : public TimedEffect
{
public:
	bool burstTriggered = false;
	SleepEffect(bool burstTriggered, int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class StunEffect : public TimedEffect
{
public:
	StunEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class FreezeEffect : public TimedEffect
{
public:
	FreezeEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;
	
	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const;
};
class KnockbackEffect : public TimedEffect
{
public:
	KnockbackEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class FearEffect : public TimedEffect
{
public:
	FearEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ArmorPenetrationEffect : public TimedEffect
{
public:
	ArmorPenetrationEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class ExplosionEffect : public TimedEffect
{
public:
	float range = 0.0f;
	MagicDamageType magicDamage = MagicDamageType::NONE;
	PhysicalDamageType physDamage = PhysicalDamageType::NONE;
	ExplosionEffect(MagicDamageType magicDamage, PhysicalDamageType physDamage, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class SlowEffect : public TimedEffect
{
public:
	bool burstTriggered = false;
	SlowEffect(bool burstTriggered, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const;
};

class FieryExplosionEffect : public ExplosionEffect
{
public:
	FieryExplosionEffect(float range, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> wielder) override;
	void burst(std::shared_ptr<Character> target) override;
	
	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const;
};