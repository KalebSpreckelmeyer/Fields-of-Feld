#ifndef AMMUNITION_H
#define AMMUNITION_H
#include "Item.h"
#include <vector>
#include "Enchantment.h"
#include "PhysicalDamageType.h"
#include "DamageTypes.h"
#include <unordered_map>
#include "Potion.h"

class Enchantment;

class Ammunition :
    public Item
{
public:
	int id;
	std::unordered_map<DamageTypes, float> damageTypes;

	DamageTypes physType = DamageTypes::BLUNT;

	bool specialDamage = false; //bonus damage to ghosts, skeletons, etc... used for silver arrows, holy water arrows, etc...
	float range = 0.0f;
	enum class AmmoType { ARROW, GREATARROW, MINIBOLT, BOLT, BALLISTABOLT, CANNONSHELL };
	AmmoType ammoType = AmmoType::ARROW;

	std::vector<std::shared_ptr<Enchantment>> enchantments;

	void setDamage(DamageTypes damageType, float damageValue);

	float getDamage(DamageTypes damageType);

	float getAmmoDamage(std::shared_ptr<Character> target, std::shared_ptr<Ammunition> ammo);

	nlohmann::json toJson() const override;

	static std::shared_ptr<Ammunition> fromJson(const nlohmann::json& j);


	Ammunition() = default;

	Ammunition(bool specialDamage, std::string name, std::string description,
		 float value, float weight, float quantity, 
		EquipSlots slot, float range, AmmoType ammoType);

	~Ammunition() = default;
};
#endif // !AMMUNITION_H



