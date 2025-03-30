#include "ConsumableEffect.h"
// -------------------------- RESTORE HEALTH EFFECT -------------------------- //

RestoreHealthEffect::RestoreHealthEffect(float magnitude)
	: Effect(false, false, "Restore Health", "Instantly restores health to the target",
		0.0f, 0.0f, magnitude, false, 1, 
		1, false){
}

void RestoreHealthEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void RestoreHealthEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void RestoreHealthEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool RestoreHealthEffect::isExpired() const {
	return true;
}

nlohmann::json RestoreHealthEffect::toJson() const {
	return{
		{"type", getType()},
		{"magnitude", magnitude}
	};
}

std::shared_ptr<Effect> RestoreHealthEffect::fromJson(const nlohmann::json& j) {
	float magnitude = j.at("magnitude");
	return std::make_shared<RestoreHealthEffect>(magnitude);
}

std::string RestoreHealthEffect::getType() const {
	return "RestoreHealth";
}

// -------------------------- RESTORE FATIGUE EFFECT -------------------------- //

RestoreFatigueEffect::RestoreFatigueEffect(float magnitude)
	: Effect(false, false, "Restore Fatigue", "Instantly restores fatigue of the target",
		0.0f, 0.9f, magnitude, false, 1,
		1, false) {
}

void RestoreFatigueEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void RestoreFatigueEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void RestoreFatigueEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool RestoreFatigueEffect::isExpired() const {
	return true;
}

nlohmann::json RestoreFatigueEffect::toJson() const {
	return{
		{"type", getType()},
		{"magnitude", magnitude}
	};
}

std::shared_ptr<Effect> RestoreFatigueEffect::fromJson(const nlohmann::json& j) {
	float magnitude = j.at("magnitude");
	return std::make_shared<RestoreFatigueEffect>(magnitude);
}

std::string RestoreFatigueEffect::getType() const {
	return "RestoreFatigue";
}

// -------------------------- MAX HEALTH EFFECT -------------------------- //

MaxHealthEffect::MaxHealthEffect(float magnitude, float duration)
	: Effect(false, false, "Max Health", "Instantly increases the maximum health of the target",
		0.0f, duration, magnitude, false, 1,
		1, false) {
}

void MaxHealthEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void MaxHealthEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void MaxHealthEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool MaxHealthEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json MaxHealthEffect::toJson() const {
	return{
		{"type", getType()},
		{"magnitude", magnitude},
		{ "duration", duration } 
	};
}

std::shared_ptr<Effect> MaxHealthEffect::fromJson(const nlohmann::json& j) {
	float magnitude = j.at("magnitude");
	float duration = j.at("duration");
	return std::make_shared<MaxHealthEffect>(magnitude, duration);
}

std::string MaxHealthEffect::getType() const {
	return "MaxHealth";
}

// -------------------------- MAX FATIUGE EFFECT -------------------------- //

MaxFatigueEffect::MaxFatigueEffect(float magnitude, float duration)
	: Effect(false, false, "Max Fatigue", "Instantly increases the maximum fatiuge of the target",
		0.0f, duration, magnitude, false, 1,
		1, false) {
}

void MaxFatigueEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void MaxFatigueEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void MaxFatigueEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool MaxFatigueEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json MaxFatigueEffect::toJson() const {
	return{
		{"type", getType()},
		{"magnitude", magnitude},
		{ "duration", duration }
	};
}

std::shared_ptr<Effect> MaxFatigueEffect::fromJson(const nlohmann::json& j) {
	float magnitude = j.at("magnitude");
	float duration = j.at("duration");
	return std::make_shared<MaxFatigueEffect>(magnitude, duration);
}

std::string MaxFatigueEffect::getType() const {
	return "MaxFatigue";
}

// -------------------------- HEALTH REGEN EFFECT -------------------------- //

HealthRegenEffect::HealthRegenEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void HealthRegenEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void HealthRegenEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void HealthRegenEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool HealthRegenEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json HealthRegenEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> HealthRegenEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<HealthRegenEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string HealthRegenEffect::getType() const {
	return "HealthRegen";
}

// -------------------------- FATIGUE REGEN EFFECT -------------------------- //

FatigueRegenEffect::FatigueRegenEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void FatigueRegenEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void FatigueRegenEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void FatigueRegenEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool FatigueRegenEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json FatigueRegenEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FatigueRegenEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FatigueRegenEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string FatigueRegenEffect::getType() const {
	return "FatigueRegen";
}

// -------------------------- ATTACK SPEED EFFECT -------------------------- //

AttackSpeedEffect::AttackSpeedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void AttackSpeedEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void AttackSpeedEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void AttackSpeedEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool AttackSpeedEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json AttackSpeedEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> AttackSpeedEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<AttackSpeedEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string AttackSpeedEffect::getType() const {
	return "AttackSpeed";
}

// -------------------------- CAST SPEED EFFECT -------------------------- //

CastSpeedEffect::CastSpeedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void CastSpeedEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void CastSpeedEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void CastSpeedEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool CastSpeedEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json CastSpeedEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> CastSpeedEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<CastSpeedEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string CastSpeedEffect::getType() const {
	return "CastSpeed";
}

// -------------------------- SPEED EFFECT -------------------------- //

SpeedEffect::SpeedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void SpeedEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void SpeedEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void SpeedEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool SpeedEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json SpeedEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> SpeedEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<SpeedEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string SpeedEffect::getType() const {
	return "Speed";
}

// -------------------------- BLOCK CHANCE EFFECT -------------------------- //

BlockChanceEffect::BlockChanceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void BlockChanceEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void BlockChanceEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void BlockChanceEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool BlockChanceEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json BlockChanceEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> BlockChanceEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<BlockChanceEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string BlockChanceEffect::getType() const {
	return "BlockChance";
}

// -------------------------- DODGE CHANCE EFFECT -------------------------- //

DodgeChanceEffect::DodgeChanceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void DodgeChanceEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void DodgeChanceEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void DodgeChanceEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool DodgeChanceEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json DodgeChanceEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> DodgeChanceEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<DodgeChanceEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string DodgeChanceEffect::getType() const {
	return "DodgeChance";
}

// -------------------------- CRIT CHANCE EFFECT -------------------------- //

CritChanceEffect::CritChanceEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void CritChanceEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void CritChanceEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void CritChanceEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool CritChanceEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json CritChanceEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> CritChanceEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<CritChanceEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string CritChanceEffect::getType() const {
	return "CritChance";
}

// -------------------------- RESISTANCE EFFECT -------------------------- //

ResistanceEffect::ResistanceEffect(ResistanceType type, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), resistance(resistance) {
}

void ResistanceEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void ResistanceEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

bool ResistanceEffect::isExpired() const {
	return duration <= 0.0f;
}

void ResistanceEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

nlohmann::json ResistanceEffect::toJson() const {
	return{
		{"type", getType()},
		{"resistance", static_cast<int>(resistance)},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ResistanceEffect::fromJson(const nlohmann::json& j) {
	ResistanceType resistance = static_cast<ResistanceType>(j.at("resistance"));
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ResistanceEffect>(resistance, duration, magnitude, stackable, stacks, maxStacks);
}

std::string ResistanceEffect::getType() const {
	return "Resistance";
}

// -------------------------- ESCAPE EFFECT -------------------------- //

EscapeEffect::EscapeEffect(int duration) : TimedEffect(duration, 0, false, 0, 0) {
}

void EscapeEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void EscapeEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

bool EscapeEffect::isExpired() const {
	return duration <= 0.0f;
}

void EscapeEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

nlohmann::json EscapeEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration}
	};
}

std::shared_ptr<Effect> EscapeEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	return std::make_shared<EscapeEffect>(duration);
}

std::string EscapeEffect::getType() const {
	return "Escape";
}

// -------------------------- RESURRECT EFFECT -------------------------- //

ResurrectEffect::ResurrectEffect() : Effect(false, false, "Resurrection", "Brings the target back from the dead",
	0.0f, 0.0f, 0.0f, false, 1,
	1, false) {
}

void ResurrectEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void ResurrectEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void ResurrectEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool ResurrectEffect::isExpired() const {
	return true;
}

nlohmann::json ResurrectEffect::toJson() const {
	return{
		{"type", getType()}
	};
}

std::shared_ptr<Effect> ResurrectEffect::fromJson(const nlohmann::json& j) {
	return std::make_shared<ResurrectEffect>();
}

std::string ResurrectEffect::getType() const {
	return "Resurrect";
}

// -------------------------- ATTRIBUTE EFFECT -------------------------- //

AttributeEffect::AttributeEffect(Attribute attribute, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), attribute(attribute){
}

void AttributeEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void AttributeEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void AttributeEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool AttributeEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json AttributeEffect::toJson() const {
	return{
		{"type", getType()},
		{"attribute", static_cast<int>(attribute)},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> AttributeEffect::fromJson(const nlohmann::json& j) {
	Attribute attribute = static_cast<Attribute>(j.at("attribute"));
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<AttributeEffect>(attribute, duration, magnitude, stackable, stacks, maxStacks);
}

std::string AttributeEffect::getType() const {
	return "Attribute";
}

// -------------------------- RANDOM EFFECT -------------------------- //

RandomEffect::RandomEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void RandomEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target) {
	// Implement the apply method
}

void RandomEffect::tick(std::shared_ptr<Character> wielder) {
	// Implement the tick method
}

void RandomEffect::burst(std::shared_ptr<Character> target) {
	// Default implementation does nothing
}

bool RandomEffect::isExpired() const {
	return duration <= 0.0f;
}

nlohmann::json RandomEffect::toJson() const {
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> RandomEffect::fromJson(const nlohmann::json& j) {
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<RandomEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

std::string RandomEffect::getType() const {
	return "Random";
}