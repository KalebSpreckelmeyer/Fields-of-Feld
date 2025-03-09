#ifndef Ammo_h
#define Ammo_h
#include <string>

class Ammo {
public:
	std::string name;
	int damage;
	float weight;
	int quantity;
	enum ammo_Types { BOLT, ARROW };
	ammo_Types ammoType;

	Ammo();

	Ammo(std::string name, int damage, float weight, int quantity, ammo_Types ammoType);

	~Ammo();

};
#endif // !Ammo_h

