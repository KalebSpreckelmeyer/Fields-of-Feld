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

	std::vector<Enchantment*> enchantments;

	void setPhysicalDamage(PhysicalDamageType physType, float physDamage);

	void setMagicDamage(MagicDamageType magType, float magDamage);

	float getPhysicalDamage(PhysicalDamageType physType);

	float getMagicDamage(MagicDamageType magType);

	float getAmmoDamage(Character* target, Ammunition ammo);

	Ammunition();

	Ammunition(bool specialDamage, bool hasBeenInitialized, std::string name, std::string description,
		PhysicalDamageType physType, MagicDamageType magType, float value, float weight, float quantity, 
		EquipSlots slot, float range, AmmoType ammoType);

	~Ammunition();
};
#endif // !AMMUNITION_H



