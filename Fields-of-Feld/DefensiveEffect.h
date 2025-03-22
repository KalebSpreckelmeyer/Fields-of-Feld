#pragma once
#include "Effect.h"
#include "TimedEffect.h"
class DefensiveEffect :
    public Effect
{
};

class ThornsEffect : public TimedEffect
{
public:
	float range;
	ThornsEffect(float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks);

	void apply(Character& target) override;
	void tick(Character& target) override;

	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);

	std::string getType() const;
};

class AuraEffect : public TimedEffect
{
public:
	float range;
	AuraEffect(float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(Character& target) override;
	void tick(Character& target) override;
	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	std::string getType() const;
};
