#include "Inventory.h"

//Private Functions

void Inventory::initialize(const unsigned from)
{
	for (size_t i = from; i < this->cap; i++)
	{
		this->items[i] = nullptr;
	}
}

void Inventory::expand()
{
	this->cap *= 2;
	Item** temp = new Item * [this->cap];
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		temp[i] = this->items[i];
	}
	delete[] this->items;
	this->items = temp;
	this->initialize(this->numberOfItems);
}
//Constructor / Destructors
Inventory::Inventory(unsigned cap)
{
	this->cap = cap;
	this->numberOfItems = 0;
	this->items = new Item*[cap];

	this->initialize();
}	

//Copy Inventory
Inventory::Inventory(const Inventory* other)
{
	this->cap = other->cap;
	this->numberOfItems = other->numberOfItems;

	this->items = new Item * [this->cap];

	this->initialize();

	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		this->items[i] = new Item(*other->items[i]);
	}
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		delete this->items[i];
	}
	delete[] this->items;
}

//Operators

void Inventory::operator=(const Inventory& other)
{
	if (this != &other)
	{
		for (size_t i = 0; i < this->numberOfItems; i++)
		{
			delete this->items[i];
		}
		delete[] this->items;

		this->cap = other.cap;
		this->numberOfItems = other.numberOfItems;

		this->items = new Item * [this->cap];

		this->initialize();

		for (size_t i = 0; i < this->numberOfItems; i++)
		{
			this->items[i] = new Item(*other.items[i]);
		}
	}
}

Item& Inventory::operator[](const unsigned index)
{
	if (index < 0 || index >= this->numberOfItems)
	{
		throw "OUT OF BOUNDS";
	}
	else
	{
		return *this->items[index];
	}
}

//Accessors

const unsigned& Inventory::size() const
{
	return this->numberOfItems;
}

const unsigned& Inventory::capacity() const
{
	return this->cap;
}

//Item& Inventory::at(const unsigned index)
//{
//	// TODO: insert return statement here
//}

//Functions
void Inventory::add(const Item& item)
{
	if (this->numberOfItems >= this->cap)
	{
		this->expand();
	}

	this->items[this->numberOfItems++] = new Item(item);
}

void Inventory::remove(const unsigned index)
{

}

std::string Inventory::toString() const
{
	std::stringstream ss;
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		ss << i << ": " << " " << "\n";
	}
	return ss.str();
}
