#pragma once
#include "Effect.h"
class TimedEffect : public Effect {
  
public:
    int duration; // in turns
    float magnitude;
    bool stackable;
    int stacks;
    int maxStacks;

    TimedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks);
    virtual ~TimedEffect() override = default;

    virtual void apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier) override = 0;
    void tick(std::shared_ptr<Character> wielder) override;
	void burst(std::shared_ptr<Character> target) override;

    bool isExpired() const override;

    int getDuration() const;
    void setDuration(int newDuration);
};