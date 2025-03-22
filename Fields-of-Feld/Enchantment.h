#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include <vector>
#include "Effect.h"

class Enchantment 
{
public:
	std::unordered_map<PhysicalDamageType, float>physicalDamage;
	std::unordered_map<MagicDamageType, float> magicDamage;

	PhysicalDamageType physType = PhysicalDamageType::BLUNT;
	MagicDamageType magType = MagicDamageType::NONE;

	std::vector<std::shared_ptr<Effect>> effects;
	std::string name;
	std::string description;
	bool areaOfEffect = false;
	bool summon = false;
	bool doesDamage = false;
	bool healing = false;
	bool useOnAlly = false;
	bool useOnSelf = false;
	bool buff = false;
	int duration = 0;
	float magnitude = 0.0f;
	bool applied = false;
	bool stackable = false;
	int stacks = 0;
	int maxStacks = 0;

	nlohmann::json toJson() const;
	static std::shared_ptr<Enchantment> fromJson(const nlohmann::json& j);

	Enchantment() = default;

	virtual ~Enchantment();

	Enchantment(std::string name, std::string description, bool areaOfEffect, bool summon, bool doesDamage, 
		bool healing, bool useOnAlly, bool useOnSelf, bool buff, float duration, float magnitude, bool applied, bool stackable,
		int stacks, int maxStacks);

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getEnchantmentDamage(std::shared_ptr<Character> target, Enchantment Enchantment);

	void applyOffensiveEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target);

	void applyDefensiveEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Character> attacker);

	void applyPassiveEnchantment(std::shared_ptr<Character> wielder);

	void removeEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Enchantment> enchant);

	void interactWith(Enchantment& otherEnchantment);

	//WEAPON ENCHANTMENTS
	std::shared_ptr<Enchantment> getMagicWeaponEffect(Character& wielder);
	//ARMOR ENCHANTMENTS
	std::shared_ptr<Enchantment> getMagicArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getLightningArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getBloodArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getFrostArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getFireArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getPoisonArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getWindArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getEarthenArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getSleepArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getHolyArmorEffect(Character& wielder);
	std::shared_ptr<Enchantment> getDarkArmorEffect(Character& wielder);
	//TRINKET ENCHANTMENTS
};

#endif // !ENCHANTMENT_H


