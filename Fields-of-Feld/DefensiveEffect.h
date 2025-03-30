#pragma once
#include "Effect.h"
#include "TimedEffect.h"
#include "DamageTypes.h"

class ThornsEffect : public TimedEffect
{
public:
	float range;
	DamageTypes damageType;
	ThornsEffect(DamageTypes damageType, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class AuraEffect : public TimedEffect
{
public:
	float range;
	DamageTypes damageType;
	AuraEffect(DamageTypes magicDamage, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	
	std::string getType() const;
};
