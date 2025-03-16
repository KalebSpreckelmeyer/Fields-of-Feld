#ifndef AMMUNITION_H
#define AMMUNITION_H
#include "Item.h"

class Ammunition :
    public Item
{
public:
	bool specialDamage = false; //bonus damage to ghosts, skeletons, etc... used for silver arrows, holy water arrows, etc...
	float damage = 0.0f;
	float range = 0.0f;
	enum class AmmoType { ARROW, GREATARROW, MINIBOLT, BOLT, BALLISTABOLT, CANNONSHELL };
	AmmoType ammoType = AmmoType::ARROW;
	enum class AmmoDamageType { PIERCE, BLUNT };
	AmmoDamageType ammoDamageType = AmmoDamageType::BLUNT;

	std::vector<Enchantment*> enchantments;

	Ammunition();

	Ammunition(bool specialDamage, bool hasBeenInitialized, std::string name, std::string description, float value, float weight, float quantity, 
		EquipSlots slot, float damage, float range, AmmoType ammoType, AmmoDamageType ammoDamageType);

	~Ammunition();
};
#endif // !AMMUNITION_H



