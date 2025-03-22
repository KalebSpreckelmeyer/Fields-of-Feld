#include "OffensiveEffect.h"
// ------------------------------------------ BLEED EFFECT ------------------------------------------ //
BleedEffect::BleedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{

}

std::string BleedEffect::getType() const
{
	return "Bleed";
}

void BleedEffect::apply(Character& target)
{

}

void BleedEffect::tick(Character& target)
{
	if (duration > 0)
	{
		//take damage
		--duration;
	}
}


nlohmann::json BleedEffect::toJson() const
{
	return {
		{"type", getType()},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> BleedEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");

	return std::make_shared<BleedEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ BURN EFFECT ------------------------------------------ //

BurnEffect::BurnEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{

}

std::string BurnEffect::getType() const
{
	return "Burn";
}

void BurnEffect::apply(Character& target)
{
}

void BurnEffect::tick(Character& target)
{
}

//bool BurnEffect::isExpired()

nlohmann::json BurnEffect::toJson() const
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

std::shared_ptr<Effect> BurnEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<BurnEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ POISON EFFECT ------------------------------------------ //

PoisonEffect::PoisonEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string PoisonEffect::getType() const
{
	return "Poison";
}

void PoisonEffect::apply(Character& target)
{
}

void PoisonEffect::tick(Character& target)
{
}

nlohmann::json PoisonEffect::toJson() const
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

std::shared_ptr<Effect> PoisonEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<PoisonEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ FROSTBURST EFFECT  ---------------------------------------- //

FrostBurstEffect::FrostBurstEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FrostBurstEffect::getType() const
{
	return "FrostBurst";
}

void FrostBurstEffect::apply(Character& target)
{
}

void FrostBurstEffect::tick(Character& target)
{
}

nlohmann::json FrostBurstEffect::toJson() const
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

std::shared_ptr<Effect> FrostBurstEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FrostBurstEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ SHOCK EFFECT ------------------------------------------ //

ShockEffect::ShockEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string ShockEffect::getType() const
{
	return "Shock";
}

void ShockEffect::apply(Character& target)
{
}

void ShockEffect::tick(Character& target)
{
}

nlohmann::json ShockEffect::toJson() const
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

std::shared_ptr<Effect> ShockEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ShockEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ SLEEP EFFECT ------------------------------------------ //

SleepEffect::SleepEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string SleepEffect::getType() const
{
	return "Sleep";
}

void SleepEffect::apply(Character& target)
{
}

void SleepEffect::tick(Character& target)
{
}

nlohmann::json SleepEffect::toJson() const
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

std::shared_ptr<Effect> SleepEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<SleepEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ STUN EFFECT ------------------------------------------ //

StunEffect::StunEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string StunEffect::getType() const
{
	return "Stun";
}

void StunEffect::apply(Character& target)
{
}

void StunEffect::tick(Character& target)
{
}

nlohmann::json StunEffect::toJson() const
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

std::shared_ptr<Effect> StunEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<StunEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ KNOCKBACK EFFECT ------------------------------------------ //

KnockbackEffect::KnockbackEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string KnockbackEffect::getType() const
{
	return "Knockback";
}

void KnockbackEffect::apply(Character& target)
{
}

void KnockbackEffect::tick(Character& target)
{
}

nlohmann::json KnockbackEffect::toJson() const
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

std::shared_ptr<Effect> KnockbackEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<KnockbackEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ FEAR EFFECT ------------------------------------------ //

FearEffect::FearEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FearEffect::getType() const
{
	return "Fear";
}

void FearEffect::apply(Character& target)
{
}

void FearEffect::tick(Character& target)
{
}

nlohmann::json FearEffect::toJson() const
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

std::shared_ptr<Effect> FearEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FearEffect>(duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ ARMOR PENETRATION ------------------------------------------ //

ArmorPenetrationEffect::ArmorPenetrationEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string ArmorPenetrationEffect::getType() const
{
	return "ArmorPenetration";
}

void ArmorPenetrationEffect::apply(Character& target)
{
}

void ArmorPenetrationEffect::tick(Character& target)
{
}

nlohmann::json ArmorPenetrationEffect::toJson() const
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

std::shared_ptr<Effect> ArmorPenetrationEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ArmorPenetrationEffect>(duration, magnitude, stackable, stacks, maxStacks);
}