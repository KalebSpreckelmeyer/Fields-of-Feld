#include "ConsumableEffect.h"
// -------------------------- RESTORE HEALTH EFFECT -------------------------- //

RestoreHealthEffect::RestoreHealthEffect(float magnitude)
	: Effect(doesDamage, applied, name, description, 
		range, duration, magnitude, stackable, stacks, 
		maxStacks, areaOfEffect){
}

void RestoreHealthEffect::apply(Character& target) {
	// Implement the apply method
}

void RestoreHealthEffect::tick(Character& target) {
	// Implement the tick method
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
	: Effect(doesDamage, applied, name, description,
		range, duration, magnitude, stackable, stacks,
		maxStacks, areaOfEffect) {
}

void RestoreFatigueEffect::apply(Character& target) {
	// Implement the apply method
}

void RestoreFatigueEffect::tick(Character& target) {
	// Implement the tick method
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

MaxHealthEffect::MaxHealthEffect(float magnitude)
	: Effect(doesDamage, applied, name, description,
		range, duration, magnitude, stackable, stacks,
		maxStacks, areaOfEffect) {
}

void MaxHealthEffect::apply(Character& target) {
	// Implement the apply method
}

void MaxHealthEffect::tick(Character& target) {
	// Implement the tick method
}

nlohmann::json MaxHealthEffect::toJson() const {
	return{
		{"type", getType()},
		{"magnitude", magnitude}
	};
}

std::shared_ptr<Effect> MaxHealthEffect::fromJson(const nlohmann::json& j) {
	float magnitude = j.at("magnitude");
	return std::make_shared<MaxHealthEffect>(magnitude);
}

std::string MaxHealthEffect::getType() const {
	return "MaxHealth";
}

// -------------------------- MAX FATIUGE EFFECT -------------------------- //

MaxFatigueEffect::MaxFatigueEffect(float magnitude)
	: Effect(doesDamage, applied, name, description,
		range, duration, magnitude, stackable, stacks,
		maxStacks, areaOfEffect) {
}

void MaxFatigueEffect::apply(Character& target) {
	// Implement the apply method
}

void MaxFatigueEffect::tick(Character& target) {
	// Implement the tick method
}

nlohmann::json MaxFatigueEffect::toJson() const {
	return{
		{"type", getType()},
		{"magnitude", magnitude}
	};
}

std::shared_ptr<Effect> MaxFatigueEffect::fromJson(const nlohmann::json& j) {
	float magnitude = j.at("magnitude");
	return std::make_shared<MaxFatigueEffect>(magnitude);
}

std::string MaxFatigueEffect::getType() const {
	return "MaxFatigue";
}

// -------------------------- HEALTH REGEN EFFECT -------------------------- //

HealthRegenEffect::HealthRegenEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks)
	: TimedEffect(duration, magnitude, stackable, stacks, maxStacks) {
}

void HealthRegenEffect::apply(Character& target) {
	// Implement the apply method
}

void HealthRegenEffect::tick(Character& target) {
	// Implement the tick method
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

void FatigueRegenEffect::apply(Character& target) {
	// Implement the apply method
}

void FatigueRegenEffect::tick(Character& target) {
	// Implement the tick method
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

void AttackSpeedEffect::apply(Character& target) {
	// Implement the apply method
}

void AttackSpeedEffect::tick(Character& target) {
	// Implement the tick method
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

void CastSpeedEffect::apply(Character& target) {
	// Implement the apply method
}

void CastSpeedEffect::tick(Character& target) {
	// Implement the tick method
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

void SpeedEffect::apply(Character& target) {
	// Implement the apply method
}

void SpeedEffect::tick(Character& target) {
	// Implement the tick method
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

void BlockChanceEffect::apply(Character& target) {
	// Implement the apply method
}

void BlockChanceEffect::tick(Character& target) {
	// Implement the tick method
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

void DodgeChanceEffect::apply(Character& target) {
	// Implement the apply method
}

void DodgeChanceEffect::tick(Character& target) {
	// Implement the tick method
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

void CritChanceEffect::apply(Character& target) {
	// Implement the apply method
}

void CritChanceEffect::tick(Character& target) {
	// Implement the tick method
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

void ResistanceEffect::apply(Character& target) {
	// Implement the apply method
}

void ResistanceEffect::tick(Character& target) {
	// Implement the tick method
}

nlohmann::json ResistanceEffect::toJson() const {
	return{
		{"type", getType()},
		{"resistance", resistance},
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

void EscapeEffect::apply(Character& target) {
	// Implement the apply method
}

void EscapeEffect::tick(Character& target) {
	// Implement the tick method
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

ResurrectEffect::ResurrectEffect() : Effect(doesDamage, applied, name, description,
	range, duration, magnitude, stackable, stacks,
	maxStacks, areaOfEffect) {
}

void ResurrectEffect::apply(Character& target) {
	// Implement the apply method
}

void ResurrectEffect::tick(Character& target) {
	// Implement the tick method
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

void AttributeEffect::apply(Character& target) {
	// Implement the apply method
}

void AttributeEffect::tick(Character& target) {
	// Implement the tick method
}

nlohmann::json AttributeEffect::toJson() const {
	return{
		{"type", getType()},
		{"attribute", attribute},
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

void RandomEffect::apply(Character& target) {
	// Implement the apply method
}

void RandomEffect::tick(Character& target) {
	// Implement the tick method
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