#include "IDManager.h"

int IDManager::currentID = 1000;

int IDManager::getNextId()
{
	return currentID++;
}