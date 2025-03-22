#ifndef Potion_h
#define Potion_h

#include <string>
#include <vector>
#include "Consumable.h"

class Potion : public Consumable {
public:
	enum effect { 
		NONE, 
		HEALING, 
		FATIGUE, 
		MAXHEALTH,
		MAXFATIGUE,
		HEALTHREGEN,
		FATIGUEREGEN,
		ATTACKSPEED,
		CASTSPEED,
		SPEED,
		PHYSICALRESISTANCE,
		MAGICRESISTANCE,
		FIRERESISTANCE,
		FROSTRESISTANCE,
		LIGHTNINGRESISTANCE,
		DARKRESISTANCE,
		HOLYRESISTANCE,
		WINDRESISTANCE,
		BLEEDRESISTANCE,
		POISONRESISTANCE,
		SLEEPRESISTANCE,
		ALLRESISTANCE,
		BLOCKCHANCE,
		DODGECHANCE,
		CRITCHANCE,
		ESCAPE,
		STRENGTH,
		AGILITY,
		INTELLIGENCE,
		CHARISMA,
		ARCANE,
		FAITH,
		LUCK, 
		TELEPORT, 
		RESURRECT,
		RANDOM,
	};

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Potion() = default;

	Potion(std::string name, std::string description,
		float magnitude, float weight, float quantity, float value);

	~Potion() = default;

	void use() override;
};

#endif // !Potion_h
