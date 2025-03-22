#ifndef AMMUNITION_H
#define AMMUNITION_H
#include "Item.h"
#include <vector>
#include "Enchantment.h"
#include "PhysicalDamageType.h"
#include "MagicDamageType.h"
#include <unordered_map>

class Enchantment;

class Ammunition :
    public Item
{
public:

	std::unordered_map<PhysicalDamageType, float> physicalDamage;
	std::unordered_map<MagicDamageType, float> magicDamage;

	PhysicalDamageType physType = PhysicalDamageType::BLUNT;
	MagicDamageType magType = MagicDamageType::NONE;

	bool specialDamage = false; //bonus damage to ghosts, skeletons, etc... used for silver arrows, holy water arrows, etc...
	float range = 0.0f;
	enum class AmmoType { ARROW, GREATARROW, MINIBOLT, BOLT, BALLISTABOLT, CANNONSHELL };
	AmmoType ammoType = AmmoType::ARROW;

	std::vector<std::shared_ptr<Enchantment>> enchantments;

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getAmmoDamage(std::shared_ptr<Character> target, std::shared_ptr<Ammunition> ammo);

	nlohmann::json toJson() const override;

	static std::shared_ptr<Ammunition> fromJson(const nlohmann::json& j);


	Ammunition() = default;

	Ammunition(bool specialDamage, bool hasBeenInitialized, std::string name, std::string description,
		 float value, float weight, float quantity, 
		EquipSlots slot, float range, AmmoType ammoType);

	~Ammunition() = default;
};
#endif // !AMMUNITION_H



