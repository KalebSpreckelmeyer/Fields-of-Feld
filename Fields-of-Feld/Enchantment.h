#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include <vector>
#include "Effect.h"
#include "IDManager.h"

class Enchantment 
{
public:
	int id;

	std::vector<std::shared_ptr<Effect>> effects;
	std::string name;
	std::string description;
	bool useOnEnemy = false;
	bool useOnAlly = false;
	bool useOnSelf = false;


	nlohmann::json toJson() const;
	static std::shared_ptr<Enchantment> fromJson(const nlohmann::json& j);

	Enchantment() = default;

	~Enchantment();

	Enchantment(std::string name, std::string description,bool useOnEnemy, bool useOnAlly, bool useOnSelf);

	//void applyOffensiveEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Character> target);

	//void applyDefensiveEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Character> attacker);

	//void applyPassiveEnchantment(std::shared_ptr<Character> wielder);

	void removeEnchantment(std::shared_ptr<Character> wielder, std::shared_ptr<Enchantment> enchant);

	void interactWith(Enchantment& otherEnchantment);

	////WEAPON ENCHANTMENTS
	//std::shared_ptr<Enchantment> getMagicWeaponEffect(Character& wielder);
	////ARMOR ENCHANTMENTS
	//std::shared_ptr<Enchantment> getMagicArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getLightningArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getBloodArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getFrostArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getFireArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getPoisonArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getWindArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getEarthenArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getSleepArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getHolyArmorEffect(Character& wielder);
	//std::shared_ptr<Enchantment> getDarkArmorEffect(Character& wielder);
	//TRINKET ENCHANTMENTS
};

#endif // !ENCHANTMENT_H


