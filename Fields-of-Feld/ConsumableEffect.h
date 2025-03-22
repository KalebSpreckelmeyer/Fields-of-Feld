#pragma once
#include "Effect.h"
#include <unordered_map>
#include <string>
#include <memory>

class ConsumableEffect : public Effect
{
public:
    ConsumableEffect() = default;
    virtual ~ConsumableEffect() = default;

    ConsumableEffect(bool doesDamage, bool applied, std::string name, std::string description, float range, float duration, float magnitude, bool stackable,
        int stacks, int maxStacks, bool areaOfEffect)
        : Effect(doesDamage, applied, name, description, range, duration, magnitude, stackable, stacks, maxStacks, areaOfEffect) {}

    virtual nlohmann::json toJson() const override {
        // Implement the toJson method
        return json();
    }

    static std::shared_ptr<Effect> fromJson(const nlohmann::json& j) {
        // Implement the fromJson method
        return std::make_shared<ConsumableEffect>();
    }

    virtual void apply(Character& target) override {
        // Implement the apply method
    }

    virtual void tick(Character& target) override {
        // Implement the tick method
    }

    virtual bool isExpired() const override {
        // Implement the isExpired method
        return false;
    }
};
