#pragma once
#include<vector>
#include<iostream>
#include<fstream>

class Game
{
private:
	//Variables
	bool quit;
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Functions
	bool getQuit();
	void update();
};