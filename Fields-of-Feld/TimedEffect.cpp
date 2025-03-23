#include "TimedEffect.h"

TimedEffect::TimedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
    : duration(duration), magnitude(magnitude), stackable(stackable), stacks(stacks), maxStacks(maxStacks) {
}

void TimedEffect::tick(std::shared_ptr<Character> wielder) {
    if (duration > 0)
        --duration;
}

void TimedEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}
bool TimedEffect::isExpired() const {
    return duration <= 0;
}

void TimedEffect::setDuration(int newDuration) {
    duration = newDuration;
}