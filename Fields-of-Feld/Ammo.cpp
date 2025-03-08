#include "Ammo.h"
Ammo::Ammo() = default;

Ammo::Ammo(std::string name, int damage, int weight, int quantity) {
	this->name = name;
	this->damage = damage;
	this->weight = weight;
	this->quantity = quantity;
}

Ammo::~Ammo() {

}