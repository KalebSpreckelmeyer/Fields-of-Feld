#ifndef Ammo_h
#define Ammo_h
#include <string>

class Ammo {
public:
	std::string name;
	int damage;
	int weight;
	int quantity;

	Ammo();

	Ammo(std::string name, int damage, int weight, int quantity);

	~Ammo();
};
#endif // !Ammo_h

