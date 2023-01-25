#pragma once
#include <iostream>

using namespace std;

class Cake
{
	string name;
public:
	Cake(string name); 
	string getName(); 
};

Cake::Cake(string name)
{
	this->name = name;
}

string Cake::getName()
{
	return name;
}