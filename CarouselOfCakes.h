#pragma once
#include <list>
#include "Cake.h"


class CarouselOfCakes
{
	list<Cake*>storage;
	unsigned int maxCapacity = 10;
	unsigned int lowLimit = 3;
public:
	CarouselOfCakes() {}; 
	bool addCake(Cake* cake); 
	Cake* getCake(string name); 
	int getCurrentCapacity(); 
	int getLowLimit(); 
	int getMaxCapacity(); 
	friend class CommandTaker;
};

bool CarouselOfCakes::addCake(Cake* cake)
{
	if (storage.size() < maxCapacity)
	{
		storage.push_back(cake);
		return true;
	}
	return false;
}


Cake* CarouselOfCakes::getCake(string name)
{
	for (auto i = storage.begin(); i != storage.end(); i++)
	{
		if ((*i)->getName() == name)
		{
			Cake* c = *i;
			storage.erase(i); // daca prajitura a fost gasita, atunci ea va fi luata din carusel
			cout << "Prajitura este impachetata pentru comanda dvs...\n";
			Sleep(700);
			return c;
		}
	}
	cout << "Prajitura nu a putut fi gasita in carusel\n";
	return NULL;
}

int CarouselOfCakes::getCurrentCapacity()
{
	return storage.size();
}

int CarouselOfCakes::getLowLimit()
{
	return lowLimit;
}

int CarouselOfCakes::getMaxCapacity()
{
	return maxCapacity;
}
