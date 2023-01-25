#pragma once
#include <iostream>

using namespace std;

class RecipeCake
{
	string name;
	int time;
public:
	RecipeCake() {};
	RecipeCake(string name, int time); 
	string getName(); 
	int getTime(); 
};

RecipeCake::RecipeCake(string name, int time)
{
	this->name = name;
	this->time = time;
}

string RecipeCake::getName()
{
	return name;
}

int RecipeCake::getTime()
{
	return time;
}