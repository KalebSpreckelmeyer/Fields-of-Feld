#pragma once
#include "Effect.h"
class TimedEffect : public Effect {
protected:
    int duration; // in turns
	float magnitude;
	bool stackable;
	int stacks;
	int maxStacks;
public:
    TimedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
    virtual ~TimedEffect() override = default;

    void tick(Character& target) override;
    bool isExpired() const override;

    int getDuration() const;
    void setDuration(int newDuration);
};