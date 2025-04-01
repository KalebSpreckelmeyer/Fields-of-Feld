#pragma once
#include "Effect.h"
#include "TimedEffect.h"

class WeaponArtEffect :
    public Effect
{
};

class PerserveranceEffect : public TimedEffect
{
	PerserveranceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
	void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier) override;
	void tick(std::shared_ptr<Character> target) override;
	void burst(std::shared_ptr<Character> target) override;
	nlohmann::json toJson() const override;
	static std::shared_ptr<Effect> fromJson(const nlohmann::json& j);
	std::string getType() const;
};