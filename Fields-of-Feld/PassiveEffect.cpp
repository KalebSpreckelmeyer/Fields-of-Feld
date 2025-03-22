#include "PassiveEffect.h"
FatigueBuff::FatigueBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FatigueBuff::getType() const
{
	return "FatigueBuff";
}

void FatigueBuff::apply(Character& target)
{
}

void FatigueBuff::tick(Character& target)
{
}

nlohmann::json FatigueBuff::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FatigueBuff::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FatigueBuff>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ HEALTH BUFF ------------------------------------------ //

HealthBuff::HealthBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string HealthBuff::getType() const
{
	return "HealthBuff";
}

void HealthBuff::apply(Character& target)
{
}

void HealthBuff::tick(Character& target)
{
}

nlohmann::json HealthBuff::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> HealthBuff::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<HealthBuff>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ CAST SPEED ------------------------------------------ //

CastSpeed::CastSpeed(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string CastSpeed::getType() const
{
	return "CastSpeed";
}

void CastSpeed::apply(Character& target)
{
}

void CastSpeed::tick(Character& target)
{
}

nlohmann::json CastSpeed::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> CastSpeed::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<CastSpeed>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ SUMMON ------------------------------------------ //

Summon::Summon(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

void Summon::apply(Character& target)
{
}

void Summon::tick(Character& target)
{
}

std::string Summon::getType() const
{
	return "Summon";
}

nlohmann::json Summon::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> Summon::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<Summon>(duration, magnitude, stackable, stacks, maxStacks);
}
// ------------------------------------------ ARMOR BUFF ------------------------------------------ //

ArmorBuff::ArmorBuff(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string ArmorBuff::getType() const
{
	return "ArmorBuff";
}

void ArmorBuff::apply(Character& target)
{
}

void ArmorBuff::tick(Character& target)
{
}

nlohmann::json ArmorBuff::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ArmorBuff::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ArmorBuff>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ HEALING ------------------------------------------ //

Healing::Healing(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string Healing::getType() const
{
	return "Healing";
}

void Healing::apply(Character& target)
{
}

void Healing::tick(Character& target)
{
}

nlohmann::json Healing::toJson() const
{
	return{
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> Healing::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<Healing>(duration, magnitude, stackable, stacks, maxStacks);
}