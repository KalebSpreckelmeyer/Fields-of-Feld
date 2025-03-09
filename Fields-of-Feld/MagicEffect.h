#ifndef MagicEffect_h
#define MagicEffect_h
#include <string>	

class MagicEffect
{
public:
	std::string name;
	std::string description;
	int damage;
	int healing;
	int turnsActive;
	int turnsRemaining;
	int magnitude;
	enum stats_effected {
		NONE, MAXHEALTH, MAXMANA, MAXSTAMINA, STRENGTH, AGILITY,
		ARCANE, FAITH, LUCK, SPEED, BLOCKCHANCE, BLOCKAMOUNT, CRITCHANCE, DAMAGEREDUCTION
	};
	stats_effected statEffected;

	MagicEffect();

	MagicEffect(std::string name, std::string description, int damage, int healing,
		int turnsActive, int turnsRemaining, int magnitude, stats_effected statEffected);

	~MagicEffect();
};

#endif // !MagicEffect_h


