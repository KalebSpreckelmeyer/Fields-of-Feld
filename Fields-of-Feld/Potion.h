#ifndef Potion_h
#define Potion_h

#include <string>
#include "Item.h"

class Potion : public Item {
public:
	std::string name;
	std::string description;
	int magnitude;
	int value;
	int weight;
	int quantity;
	enum effect { HEALING, MANA, CUREDISEASE };
	effect effects;

	Potion();

	Potion(std::string name, std::string description, int magnitude, int value, int weight, int quantity, effect effects);

	~Potion();

	Potion createPotion(std::string name, std::string description, int magnitude, int value, int weight, int quantity, Potion::effect effect);
};
#endif // !Potion_h
