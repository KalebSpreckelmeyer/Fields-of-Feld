#include "Consumable.h"
#include <string>
#include "Potion.h"
#include "Drink.h"
#include "Book.h"
#include "Food.h"

Consumable::Consumable(std::string name, std::string description,
	float magnitude, float weight, float quantity, float value)
	: Item(name, description, value, weight, quantity, slot), magnitude(magnitude)
{
}

