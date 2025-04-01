#include "OffensiveEffect.h"
#include "Character.h"
#include <iostream>
#include "color.hpp"
#include "HelperFunctions.h"
// ------------------------------------------ DAMAGE EFFECT ------------------------------------------ //

DamageEffect::DamageEffect(DamageTypes damageType, float damage) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), damageTypes(damageType), damageMagnitude(damage)
{
	
}

std::string DamageEffect::getType() const
{
	return "Damage";
}

void DamageEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->healthPoints -= this->getEffectDamage(target, shared_from_this());
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " takes " << this->getEffectDamage(target, shared_from_this()) << " points of damage!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " takes " << this->getEffectDamage(target, shared_from_this()) << " points of damage!" << std::endl;
	
	if (target->healthPoints <= 0) target->killCharacter();
}

void DamageEffect::tick(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

void DamageEffect::burst(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

nlohmann::json DamageEffect::toJson() const {
	return {
		{"type", getType()},
		{"damageTypes", damageTypesToString(damageTypes)},
		{"damageMagnitude", damageMagnitude},
	};
}

std::shared_ptr<Effect> DamageEffect::fromJson(const nlohmann::json& j) {
	auto damageType = stringToDamageTypes(j.at("damageTypes"));
	float damageValue = j.at("damageMagnitude");
	return std::make_shared<DamageEffect>(damageType, damageValue);
}

// ------------------------------------------ BLEED EFFECT ------------------------------------------ //
BleedEffect::BleedEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{

}

std::string BleedEffect::getType() const
{
	return "Bleed";
}

void BleedEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float bleedPoints = magnitude;
	this->setDamage(DamageTypes::BLEED, bleedPoints);
	bleedPoints = this->getEffectDamage(target, shared_from_this());
	target->bleedPoints += bleedPoints;
	if (target->bleedPoints > target->maxBleedPoints)
	{
		target->bleedPoints = 0;
		burst(target);
	}
}

void BleedEffect::tick(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

void BleedEffect::burst(std::shared_ptr<Character> target)
{
	float bleedDamage = target->maxHealthPoints * 0.2f;
	target->healthPoints -= bleedDamage;
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is " << dye::light_red("BLEEDING") << " and takes " 
		<< bleedDamage << " points of damage!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is " << dye::light_red("BLEEDING") << " and takes "
		<< bleedDamage << " points of damage!" << std::endl;
	if (target->healthPoints <= 0) target->killCharacter();
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

void BurnEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float burnPoints = magnitude;
	this->setDamage(DamageTypes::FIRE, burnPoints);
	burnPoints = this->getDamage(DamageTypes::FIRE);
	target->burnPoints += burnPoints;

	//check if target is already on fire, disallow burst if already on fire (you can't be more on fire)
	bool onFire = false;
	for (const auto& eff : target->effects)
	{
		if (eff->getType() == "BurnDamageEffect")
		{
			onFire = true;
		}
	}
	if (onFire)
	{
		if (target->burnPoints > target->maxBurnPoints)
		{
			target->burnPoints = target->maxBurnPoints;
		}
	}
	else if (target->burnPoints > target->maxBurnPoints)
	{
		target->burnPoints = 0;
		burst(target);
	}
}

void BurnEffect::tick(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

void BurnEffect::burst(std::shared_ptr<Character> target)
{
	//damage player
	float burnDamage = magnitude;
	this->setDamage(DamageTypes::FIRE, burnDamage);
	target->healthPoints -= this->getEffectDamage(target, shared_from_this());
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is " << dye::light_red("BURNING") << " and takes "
		<< this->getEffectDamage(target, shared_from_this()) << " points of damage!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is " << dye::light_red("BURNING") << " and takes "
		<< this->getEffectDamage(target, shared_from_this()) << " points of damage!" << std::endl;

	//kill player if health is less than or equal to 0
	if (target->healthPoints <= 0) target->killCharacter();

	//applies burning and fear status effects
	std::shared_ptr<BurnDamageEffect> burnDamageEffect = std::make_shared<BurnDamageEffect>(4, burnDamage, false, 1, 1);
	std::shared_ptr<FearEffect> fearEffect = std::make_shared<FearEffect>(1, 0.0f, false, 1, 1);
	burnDamageEffect->apply(target, target, 1.0f);
	fearEffect->apply(target, target, 1.0f);
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

// ------------------------------------------ BURN DAMAGE EFFECT ------------------------------------------ //

BurnDamageEffect::BurnDamageEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string BurnDamageEffect::getType() const
{
	return "BurnDamage";
}

void BurnDamageEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//add incoming effect to target
	target->effects.push_back(shared_from_this());
}

void BurnDamageEffect::tick(std::shared_ptr<Character> target)
{
	//decrements duration
	if (duration > 0) --duration;
	//applies burning damage
	if (duration != 0) burst(target);
	if (duration == 0) target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());
}

void BurnDamageEffect::burst(std::shared_ptr<Character> target)
{
	//damage player
	if (target->isAlive)
	{
		float burnDamage = magnitude;
		this->setDamage(DamageTypes::FIRE, burnDamage);
		target->healthPoints -= this->getDamage(DamageTypes::FIRE);
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is " << dye::light_red("BURNING") << " and takes "
			<< this->getDamage(DamageTypes::FIRE) << " points of damage!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is " << dye::light_red("BURNING") << " and takes "
			<< this->getDamage(DamageTypes::FIRE) << " points of damage!" << std::endl;

		//kill player if health is less than or equal to 0
		if (target->healthPoints <= 0) target->killCharacter();
	}
}

nlohmann::json BurnDamageEffect::toJson() const
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

std::shared_ptr<Effect> BurnDamageEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<BurnDamageEffect>(duration, magnitude, stackable, stacks, maxStacks);
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

void PoisonEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float poisonBuildup = magnitude;
	this->setDamage(DamageTypes::POISON, poisonBuildup);
	poisonBuildup = this->getDamage(DamageTypes::POISON);
	target->poisonPoints += poisonBuildup;
	if (target->poisonPoints > target->maxPoisonPoints)
	{
		target->poisonPoints = 0;
		burst(target);
	}
}

void PoisonEffect::tick(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

void PoisonEffect::burst(std::shared_ptr<Character> target)
{
	//Initial proc of poison effect
	//damage player
	if (target->isAlive)
	{
		float poisonDamage = target->maxHealthPoints * 0.05f;
		target->healthPoints -= poisonDamage;
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is " << dye::light_green("POISONED") << " and takes "
			<< poisonDamage << " points of damage!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is " << dye::light_green("POISONED") << " and takes "
			<< poisonDamage << " points of damage!" << std::endl;

		//kill player if health is less than or equal to 0
		if (target->healthPoints <= 0) target->killCharacter();

		//checks if the player has a poison damage effect already on them. If so, increment the stacks of that effect. If not, add one
		bool hasPoison = false;
		for (auto& eff : target->effects)
		{
			if (eff->getType() == "PoisonDamage" && target->isAlive)
			{
				auto poison = std::dynamic_pointer_cast<PoisonDamageEffect>(eff);
				if (poison)
				{
					poison->stacks += 1;
					if (poison->stacks > poison->maxStacks) poison->stacks = poison->maxStacks;
					hasPoison = true;
				}
			}
		}
		if (!hasPoison)
		{
			std::shared_ptr<PoisonDamageEffect> poisonDamageEffect = std::make_shared<PoisonDamageEffect>(duration, poisonDamage, stackable, 1, maxStacks);
			poisonDamageEffect->apply(target, target, 1.0f);
		}
	}
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

// ------------------------------------------ POISON DAMAGE EFFECT ------------------------------------------ //

PoisonDamageEffect::PoisonDamageEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string PoisonDamageEffect::getType() const
{
	return "PoisonDamage";
}

void PoisonDamageEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//add incoming effect to target if they don't already have the maximum poison stacks
	if(stacks < maxStacks) target->effects.push_back(shared_from_this());
}

void PoisonDamageEffect::tick(std::shared_ptr<Character> target)
{
	//decrements duration
	if (duration > 0) --duration;
	//applies poison damage
	if (duration > 0) burst(target);
	if (duration == 0) target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());
}

void PoisonDamageEffect::burst(std::shared_ptr<Character> target)
{
	if (target->isAlive)
	{
		//damage player
		for (int i = 0; i < stacks; i++)
		{
			target->healthPoints -= magnitude;
			if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is " << dye::light_green("POISONED") << " and takes "
				<< magnitude << " points of damage!" << std::endl;
			if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is " << dye::light_green("POISONED") << " and takes "
				<< magnitude << " points of damage!" << std::endl;
			//kill player if health is less than or equal to 0
			if (target->healthPoints <= 0)
			{
				target->killCharacter();
				break;
			}
		}
	}
}

nlohmann::json PoisonDamageEffect::toJson() const
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

std::shared_ptr<Effect> PoisonDamageEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<PoisonDamageEffect>(duration, magnitude, stackable, stacks, maxStacks);
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

void FrostBurstEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Apply frost points
	float frostBuildup = magnitude;
	this->setDamage(DamageTypes::FROST, frostBuildup);
	frostBuildup = this->getDamage(DamageTypes::FROST);
	target->frostPoints += frostBuildup;
	bool isSlowed = false;

	//Check if the target is already suffering from the slowing effect of a frost burst
	for (auto& eff : target->effects)
	{
		if (eff->getType() == "Slow")
		{
			isSlowed = true;
		}
	}
	//If they're already slowed, don't apply another frost burst but keep the frost buildup
	if (isSlowed)
	{
		if (target->frostPoints > target->maxFrostPoints)
		{
			target->frostPoints = target->maxFrostPoints;
		}
	}
	//If they're not slowed, apply the frost burst
	else if (target->frostPoints > target->maxFrostPoints)
	{
		target->frostPoints = 0;
		burst(target);
	}
}

void FrostBurstEffect::tick(std::shared_ptr<Character> target)
{	
	//default implementation does nothing
}

void FrostBurstEffect::burst(std::shared_ptr<Character> target)
{
	if (target->isAlive)
	{
		float armorLoss = magnitude * 1.1f;
		target->healthPoints -= target->maxHealthPoints * 0.1f;
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " suffers from a " << dye::light_blue("FROST BURST") << " and takes "
			<< target->maxHealthPoints * 0.1f << " points of damage!" << std::endl;
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << "'s physical defenses have been lowered!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " suffers from a " << dye::light_blue("FROST BURST") << " and takes "
			<< target->maxHealthPoints * 0.1f << " points of damage!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << "'s physical defenses have been lowered!" << std::endl;
		if (target->healthPoints <= 0) target->killCharacter();
		std::shared_ptr<ArmorPenetrationEffect> armorPen = std::make_shared<ArmorPenetrationEffect>(3, armorLoss, false, 1, 1);
		armorPen->apply(target, target, 1.0f);
	}
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

ShockEffect::ShockEffect(bool burstTriggered, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), burstTriggered(burstTriggered)
{
}

std::string ShockEffect::getType() const
{
	return "Shock";
}

void ShockEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float shockBuildup = magnitude;
	this->setDamage(DamageTypes::SHOCK, shockBuildup);
	shockBuildup = this->getDamage(DamageTypes::SHOCK);
	target->shockPoints += shockBuildup;
	float shockDamage = shockBuildup * 1.0f;
	target->healthPoints -= shockDamage;
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is" << dye::light_purple(" SHOCKED") << " and takes " << shockDamage << " points of damage!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << target->name << " is" << dye::light_purple(" SHOCKED") << " and takes " << shockDamage << " points of damage!" << std::endl;
	target->effects.push_back(shared_from_this());
	if (target->healthPoints <= 0)
	{
		target->healthPoints = 0;
		target->killCharacter();
		return;
	}
	if (target->shockPoints > target->maxShockPoints)
	{
		burst(target);
		target->shockPoints = 0;
	}
}

void ShockEffect::tick(std::shared_ptr<Character> target)
{
	if (duration <= 0) 
	{
		if (burstTriggered)
		{
			target->speed += magnitude;
			if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " has recovered from the" << dye::light_purple(" ELECTROCUTION") << " and has their speed restored!" << std::endl;
			if (!target->namedCharacter) std::cout << "The " << target->name << " has recovered from the" << dye::light_purple(" ELECTROCUTION") << " and has their speed restored!" << std::endl;
		}
		target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());
	}
	if (duration > 0) --duration;
}

void ShockEffect::burst(std::shared_ptr<Character> target)
{
	float shockSlow = magnitude;
	burstTriggered = true;
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " suffers an" << dye::light_purple(" ELECTROCUTION") << " and has their speed reduced by " << shockSlow << " points!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << target->name << " suffers an" << dye::light_purple(" ELECTROCUTION") << " and has their speed reduced by " << shockSlow << " points!" << std::endl;
	target->speed -= shockSlow;
}

nlohmann::json ShockEffect::toJson() const
{
	return{
		{"type", getType()},
		{"burstTriggered", burstTriggered},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ShockEffect::fromJson(const nlohmann::json& j)
{
	bool burstTriggered = j.at("burstTriggered");
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ShockEffect>(burstTriggered, duration, magnitude, stackable, stacks, maxStacks);
}
// ------------------------------------------ LIGHTNING BOLT EFFECT ------------------------------------------ //

LightningArcEffect::LightningArcEffect(float magnitude, float range, float arcChance, float arcRange) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), magnitude(magnitude), range(range), arcChance(arcChance), arcRange(arcRange)
{
	this->setDamage(DamageTypes::SHOCK, magnitude);
}

std::string LightningArcEffect::getType() const
{
	return "LightningArc";
}

void LightningArcEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Chance to arc to allies. Chance is increased by wielder's luck and by the provided arcChance
	//Each arc does less and less damage
	int randomNum = (rand() % 100 - (wielder->getLuck() + arcChance)) + 1;
	float arcDamage = this->getDamage(DamageTypes::SHOCK);
	for (auto& ally : target->allies)
	{
		if (randomNum >= 50 && ally->position[target->getId()] <= arcRange)
		{
			ally->healthPoints -= arcDamage;
			if (ally->namedCharacter) std::cout << dye::light_yellow(ally->name) << " is" << dye::light_purple(" SHOCKED") << " by the arcing bolt and takes " << arcDamage << " points of damage!" << std::endl;
			if (!ally->namedCharacter) std::cout << "The " << ally->name << " is" << dye::light_purple(" SHOCKED") << " by the arcing bolt and takes " << arcDamage << " points of damage!" << std::endl;
			arcDamage -= arcDamage * 0.3f;
			if (ally->healthPoints <= 0)
			{
				ally->healthPoints = 0;
				ally->killCharacter();
			}
		}
	}
	return;
}

void LightningArcEffect::tick(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

void LightningArcEffect::burst(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

nlohmann::json LightningArcEffect::toJson() const
{
	return{
		{"type", getType()},
		{"magnitude", magnitude},
		{"range", range},
		{"arcChance", arcChance},
		{"arcRange", arcRange}
	};
}

std::shared_ptr<Effect> LightningArcEffect::fromJson(const nlohmann::json& j)
{
	float magnitude = j.at("magnitude");
	float range = j.at("range");
	float arcChance = j.at("arcChance");
	float arcRange = j.at("arcRange");
	return std::make_shared<LightningArcEffect>(magnitude, range, arcChance, arcRange);
}

// ------------------------------------------ SLEEP EFFECT ------------------------------------------ //

SleepEffect::SleepEffect(bool burstTriggered, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), burstTriggered(burstTriggered)
{
}

std::string SleepEffect::getType() const
{
	return "Sleep";
}

void SleepEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float sleepBuildup = magnitude;
	this->setDamage(DamageTypes::SLEEP, sleepBuildup);
	sleepBuildup = this->getDamage(DamageTypes::SLEEP);

	//Adds effect so duration can be reduced and additional effects can be applied
	target->effects.push_back(shared_from_this());

	target->sleepPoints += sleepBuildup;
	if (target->sleepPoints > target->maxSleepPoints)
	{
		burst(target);
		target->sleepPoints = 0;
	}
}

void SleepEffect::tick(std::shared_ptr<Character> target)
{
	if (duration > 0) --duration;
	if (duration <= 0)
	{
		if (burstTriggered)
		{
			for (auto& flag : target->combatFlags)
			{
				if (flag == Character::CombatFlags::SLEEPY)
				{
					target->combatFlags.erase(std::remove(target->combatFlags.begin(), target->combatFlags.end(), Character::CombatFlags::SLEEPY), target->combatFlags.end());
				}
			}
			target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());
			if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " has woken up from their" << dye::light_blue(" SLUMBER") << "!" << std::endl;
			if (!target->namedCharacter) std::cout << "The " << target->name << " has woken up from their" << dye::light_blue(" SLUMBER") << "!" << std::endl;
		}
	}
}

void SleepEffect::burst(std::shared_ptr<Character> target)
{
	//Check if they already have the sleepy flag
	bool isSleepy = false;
	for (auto& flag : target->combatFlags)
	{
		if (flag == Character::CombatFlags::SLEEPY)
		{
			isSleepy = true;
		}
	}
	//If they're already asleep don't do anything
	if (isSleepy)
	{
		return;
	}
	else
	{
		target->combatFlags.push_back(Character::CombatFlags::SLEEPY);
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " has fallen into a" << dye::light_blue(" SLUMBER") << " and cannot attack!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << target->name << " has fallen into a" << dye::light_blue(" SLUMBER") << " and cannot attack!" << std::endl;
	}
}

nlohmann::json SleepEffect::toJson() const
{
	return{
		{"type", getType()},
		{"burstTriggered", burstTriggered},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> SleepEffect::fromJson(const nlohmann::json& j)
{
	bool burstTriggered = j.at("burstTriggered");
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<SleepEffect>(burstTriggered, duration, magnitude, stackable, stacks, maxStacks);
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

void StunEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Add incoming effect to target
	target->effects.push_back(shared_from_this());
	//Check if target is already stunned
	bool isStunned = false;
	for (auto& flag : target->combatFlags)
	{
		if (flag == Character::CombatFlags::STUNNED)
		{
			isStunned = true;
		}
	}
	//If they're already stunned, don't apply another stun effect
	if (isStunned)
	{
		return;
	}
	else
	{
		target->combatFlags.push_back(Character::CombatFlags::STUNNED);
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is" << dye::light_blue(" STUNNED") << " and cannot attack!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is" << dye::light_blue(" STUNNED") << " and cannot attack!" << std::endl;
	}
}

void StunEffect::tick(std::shared_ptr<Character> target)
{
	if (duration > 0) --duration;
	if (duration == 0)
	{
		target->combatFlags.erase(std::remove(target->combatFlags.begin(), target->combatFlags.end(), Character::CombatFlags::STUNNED), target->combatFlags.end());
	}
}

void StunEffect::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
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

// ------------------------------------------ FREEZE EFFECT ------------------------------------------ //

FreezeEffect::FreezeEffect(int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
}

std::string FreezeEffect::getType() const
{
	return "Freeze";
}

void FreezeEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Add incoming effect to target
	target->effects.push_back(shared_from_this());
	//Check if target is already frozen
	bool isFrozen = false;
	for (auto& flag : target->combatFlags)
	{
		if (flag == Character::CombatFlags::FROZEN)
		{
			isFrozen = true;
		}
	}
	//If they're already frozen, don't apply another freeze effect
	if (isFrozen)
	{
		return;
	}
	else
	{
		if (target->healthPoints >= target->maxHealthPoints * 0.3f || target->level >= wielder->level * 0.5f || target->confidenceLevel >= 20)
		{
			if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is unfazed by the" << dye::light_blue(" FROST") << "!" << std::endl;
			if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is unfazed by the" << dye::light_blue(" FROST") << "!" << std::endl;
			return;
		}
		else
		{
			target->combatFlags.push_back(Character::CombatFlags::FROZEN);
			if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is" << dye::light_blue(" FROZEN") << " and cannot attack!" << std::endl;
			if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is" << dye::light_blue(" FROZEN") << " and cannot attack!" << std::endl;
		}
	}
}

void FreezeEffect::tick(std::shared_ptr<Character> target)
{
	if (duration > 0) --duration;
	if (duration == 0)
	{
		target->combatFlags.erase(std::remove(target->combatFlags.begin(), target->combatFlags.end(), Character::CombatFlags::FROZEN), target->combatFlags.end());
	}
}

void FreezeEffect::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json FreezeEffect::toJson() const
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

std::shared_ptr<Effect> FreezeEffect::fromJson(const nlohmann::json& j)
{
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FreezeEffect>(duration, magnitude, stackable, stacks, maxStacks);
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

void KnockbackEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	target->position[wielder->getId()] += magnitude;
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is" << dye::light_blue(" KNOCKED BACK") << " by " << magnitude << " units!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is" << dye::light_blue(" KNOCKED BACK") << " by " << magnitude << " units!" << std::endl;
}

void KnockbackEffect::tick(std::shared_ptr<Character> target)
{
	//no implementation for this effect
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

void FearEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Add incoming effect to target
	target->effects.push_back(shared_from_this());

	//Check if target is terrified
	if (target->level <= wielder->level * 0.5f || target->confidenceLevel <= 20 || target->healthPoints <= target->maxHealthPoints * 0.3f)
	{
		target->combatFlags.push_back(Character::CombatFlags::FEAR);
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is terrified by the flames that engulf them and cannot attack!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is terrified by the flames that engulf them and cannot attack!" << std::endl;
	}
	else
	{
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " is unfazed by the flames that engulf them!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " is unfazed by the flames that engulf them!" << std::endl;
	}
}

void FearEffect::tick(std::shared_ptr<Character> target)
{
	if (duration > 0) --duration;
	if (duration == 0)
	{
		target->combatFlags.erase(std::remove(target->combatFlags.begin(), target->combatFlags.end(), Character::CombatFlags::FEAR), target->combatFlags.end());
	}
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

void ArmorPenetrationEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Add incoming effect to target
	target->effects.push_back(shared_from_this());

	//Reduce target's armor (allowing it to go negative on purpose)
	target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) - magnitude);
	target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) - magnitude);
	target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) - magnitude);
	target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) - magnitude);
}

void ArmorPenetrationEffect::tick(std::shared_ptr<Character> target)
{
	if (duration > 0) --duration;
	if (duration == 0)
	{
		//Restore target's armor
		target->setDefenseValue(Defense::CHOP, target->getDefenseValue(Defense::CHOP) + magnitude);
		target->setDefenseValue(Defense::PIERCE, target->getDefenseValue(Defense::PIERCE) + magnitude);
		target->setDefenseValue(Defense::BLUNT, target->getDefenseValue(Defense::BLUNT) + magnitude);
		target->setDefenseValue(Defense::SLASH, target->getDefenseValue(Defense::SLASH) + magnitude);

		//Remove effect from target
		target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());

		//Inform user that the effect has expired
		if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << "'s physical defenses have recovered!" << std::endl;
		if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << "'s physical defenses have recovered!" << std::endl;
	}
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

// ------------------------------------------ Explosion ------------------------------------------ //

ExplosionEffect::ExplosionEffect(DamageTypes damageType, float range, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks)
{
	this->setDamage(damageType, magnitude);
	this->range = range;
}

std::string ExplosionEffect::getType() const
{
	return "Explosion";
}

void ExplosionEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float explosionDamge = this->getDamage(damageType) + this->getDamage(damageType);
	float splashDamage = explosionDamge * 0.3f;

	//Damage the main target
	target->healthPoints -= explosionDamge;
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " takes " << explosionDamge << " points of damage!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " takes " << explosionDamge << " points of damage!" << std::endl;

	//Iterate through all the target's allies
	for (auto& ally : target->allies)
	{
		//Find targets in range of enemy who got hit by the explosion
		if (ally->position[target->getId()] <= range)
		{
			//Damage the target
			ally->healthPoints -= splashDamage;
			if (ally->namedCharacter) std::cout << dye::light_yellow(ally->name) << " takes " << splashDamage << " points of splash damage!" << std::endl;
			if (!ally->namedCharacter) std::cout << "The " << dye::light_yellow(ally->name) << " takes " << splashDamage << " points of splash damage!" << std::endl;
			if (ally->healthPoints <= 0) ally->killCharacter();
		}
	}
}

void ExplosionEffect::tick(std::shared_ptr<Character> target)
{
	// default implementation does nothing
}

nlohmann::json ExplosionEffect::toJson() const
{
	return{
		{"type", getType()},
		{"damageType", damageTypesToString(damageType)},
		{"range", range},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> ExplosionEffect::fromJson(const nlohmann::json& j)
{
	DamageTypes damage = stringToDamageTypes(j.at("damageType"));
	float range = j.at("range");
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<ExplosionEffect>(damage, range, duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ SLOW EFFECT ------------------------------------------ //

SlowEffect::SlowEffect(bool burstTriggered, int duration, float magnitude, bool stackable, int stacks, int maxStacks) :
	TimedEffect(duration, magnitude, stackable, stacks, maxStacks), burstTriggered(burstTriggered)
{
}

std::string SlowEffect::getType() const
{
	return "Slow";
}

void SlowEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	//Add incoming effect to target
	target->effects.push_back(shared_from_this());
	target->speed -= magnitude;
}

void SlowEffect::tick(std::shared_ptr<Character> target)
{
	if (duration > 0) --duration;
	if (duration == 0)
	{
		if (burstTriggered)
		{
			target->speed += magnitude;
		}
		target->effects.erase(std::remove(target->effects.begin(), target->effects.end(), shared_from_this()), target->effects.end());
	}
}

void SlowEffect::burst(std::shared_ptr<Character> target)
{
	// Default implementation does nothing
}

nlohmann::json SlowEffect::toJson() const
{
	return{
		{"type", getType()},
		{"burstTriggered", burstTriggered},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> SlowEffect::fromJson(const nlohmann::json& j)
{
	bool burstTriggered = j.at("burstTriggered");
	int duration = j.at("duration");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<SlowEffect>(burstTriggered, duration, magnitude, stackable, stacks, maxStacks);
}

// ------------------------------------------ FIERY EXPLOSION EFFECT ------------------------------------------ //

FieryExplosionEffect::FieryExplosionEffect(float range, float magnitude, bool stackable, int stacks, int maxStacks) :
	ExplosionEffect(damageType, range, duration, magnitude, stackable, stacks, maxStacks)
{
	this->setDamage(DamageTypes::FIRE, magnitude);
}

std::string FieryExplosionEffect::getType() const
{
	return "FieryExplosion";
}

void FieryExplosionEffect::apply(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target, float modifier)
{
	float explosionDamage = this->getDamage(DamageTypes::FIRE);
	float splashDamage = explosionDamage * 0.3f;

	//Damage the main target
	target->healthPoints -= explosionDamage;
	if (target->namedCharacter) std::cout << dye::light_yellow(target->name) << " takes " << explosionDamage << " points of fire damage!" << std::endl;
	if (!target->namedCharacter) std::cout << "The " << dye::light_yellow(target->name) << " takes " << explosionDamage << " points of fire damage!" << std::endl;

	if (target->healthPoints <= 0) target->killCharacter(); return;

	//Burn the main target	
	target->burnPoints += explosionDamage;
	if (target->burnPoints > target->maxBurnPoints)
	{
		target->burnPoints = 0;
		burst(target);
	}

	//Iterate through all the target's allies
	for (auto& ally : target->allies)
	{
		//Find targets in range of enemy who got hit by the explosion
		if (ally->position[target->getId()] <= range)
		{
			//Damage the target
			ally->healthPoints -= splashDamage;
			if (ally->namedCharacter) std::cout << dye::light_yellow(ally->name) << " is scorched by the explosion and takes "
				<< splashDamage << " points of splash damage damage!" << std::endl;
			if (!ally->namedCharacter) std::cout << "The " << dye::light_yellow(ally->name) << " is scorched by the explosion and takes "
				<< splashDamage << " points of splash damage damage!" << std::endl;
			if (ally->healthPoints <= 0) ally->killCharacter(); return;

			//Burn the target
			ally->burnPoints += explosionDamage;
			if (ally->burnPoints > ally->maxBurnPoints)
			{
				ally->burnPoints = 0;
				burst(ally);
			}
		}
	}
}

void FieryExplosionEffect::tick(std::shared_ptr<Character> target)
{
	//default implementation does nothing
}

void FieryExplosionEffect::burst(std::shared_ptr<Character> target)
{
	//Burn target
	std::shared_ptr<BurnDamageEffect> burnDamageEffect = std::make_shared<BurnDamageEffect>(1, magnitude, false, 1, 1);
	burnDamageEffect->apply(target, target, 1.0f);
	//Fear target
	std::shared_ptr<FearEffect> fearEffect = std::make_shared<FearEffect>(1, magnitude, false, 1, 1);
	fearEffect->apply(target, target, 1.0f);
}
nlohmann::json FieryExplosionEffect::toJson() const
{
	return{
		{"type", getType()},
		{"range", range},
		{"duration", duration},
		{"magnitude", magnitude},
		{"stackable", stackable},
		{"stacks", stacks},
		{"maxStacks", maxStacks}
	};
}

std::shared_ptr<Effect> FieryExplosionEffect::fromJson(const nlohmann::json& j)
{
	float range = j.at("range");
	float magnitude = j.at("magnitude");
	bool stackable = j.at("stackable");
	int stacks = j.at("stacks");
	int maxStacks = j.at("maxStacks");
	return std::make_shared<FieryExplosionEffect>(range, magnitude, stackable, stacks, maxStacks);
}

