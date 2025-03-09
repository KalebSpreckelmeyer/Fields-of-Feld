#include "Ammo.h"
#include <stdexcept>
Ammo::Ammo() = default;

Ammo::Ammo(std::string name, int damage, float weight, int quantity, ammo_Types ammoType) {
	this->name = name;
	this->damage = damage;
	this->weight = weight;
	this->quantity = quantity;
	this->ammoType = ammoType;
}

Ammo::~Ammo() {

}