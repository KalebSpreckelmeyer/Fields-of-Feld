#ifndef Potion_h
#define Potion_h

#include <string>
#include <vector>
#include "Consumable.h"

class Potion : public Consumable {
public:
	int id;
	enum PotionEffect { 
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
	
	PotionEffect potionEffect = PotionEffect::NONE;

	std::vector<std::shared_ptr<Effect>> effects;

	nlohmann::json toJson() const override;

	static std::shared_ptr<Item> fromJson(const nlohmann::json& j);

	Potion();

	Potion(std::string name, std::string description,
		float magnitude, float weight, float quantity, float value, PotionEffect effect);

	~Potion() = default;

	void use(std::shared_ptr<Character> consumer) override;
};

#endif // !Potion_h
