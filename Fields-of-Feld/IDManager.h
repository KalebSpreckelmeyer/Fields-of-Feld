#pragma once
class IDManager
{
public:
	static int getNextId();
private:
	static int currentID;
};

