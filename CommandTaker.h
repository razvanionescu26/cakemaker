#pragma once
#include "RecipeCake.h"
#include "CakeMaker.h"
#include "CarouselOfCakes.h"
#include <fstream>
#include <conio.h>

using namespace std;

class CommandTaker
{
	RecipeCake carouselRecipe;
	CakeMaker cakeMaker;
	CarouselOfCakes carousel;
public:
	CommandTaker() {};
	Cake* takeCommand(RecipeCake* recipe); 
	list<Cake*> takeCommand(RecipeCake* recipe, int NrOfCakes);
	/*Cake takeCommand(string NameOfCake);*/
	list<Cake*> getCakesFromCarousel(); 
private:
	bool checkCarouselOfCakes(); 
	void refillCarousel(); 
};

Cake* CommandTaker::takeCommand(RecipeCake* recipe)
{
	if (!checkCarouselOfCakes())
	{
		if (carousel.getCurrentCapacity() == 0)
		{
			refillCarousel(); 
			cout << "\nCaruselul a fost incarcat cu prajituri!\n"; // daca caruselul nu are nicio prajitura, atunci acesta va fi umplut
			_getch();
		}
		else if (carousel.getCurrentCapacity() == 3)
		{
			refillCarousel();
			cout << "\nCaruselul a fost reincarcat cu prajituri!\n"; // pentru cazul in care se ajunge la lowLimit
			_getch();
		}
	}
	cout << "\n";
	auto c = carousel.getCake(recipe->getName());
	if (c != NULL) // cautam prajitura in carusel 
	{
		cout << "Comanda dvs. este gata pentru ridicare!\n"; // daca prajitura este gasita in carusel, atunci aceasta va fi predata clientului
		_getch();
		return NULL; 
	}
	else
	{
		system("CLS");
		cakeMaker.takeCommand(recipe); // daca prajitura nu este gasita in carusel, atunci vom transmite comanda la CakeMaker
		return c; 
	}
}

list<Cake*> CommandTaker::takeCommand(RecipeCake* recipe, int NrOfCakes)
{
	if (!checkCarouselOfCakes())
	{
		if (carousel.getCurrentCapacity() == 0)
		{
			refillCarousel();
			cout << "\nCaruselul a fost incarcat cu prajituri!\n"; // daca caruselul nu are nicio prajitura, atunci acesta va fi umplut
			_getch();
		}
		else if (carousel.getCurrentCapacity() == 3)
		{
			refillCarousel();
			cout << "\nCaruselul a fost reincarcat cu prajituri!\n"; // pentru cazul in care se ajunge la lowLimit
			_getch();
		}
	}
	int counter = 0;
	list<Cake*> carouselOfCakes = getCakesFromCarousel();
	for (auto i = carouselOfCakes.begin(); i != carouselOfCakes.end(); i++)
		if (recipe->getName() == (*i)->getName()) counter++; // numaram cate astfel de produse se afla in carusel
	int RequiredForCakeMaker = counter - NrOfCakes; // cate prajituri vor fi necesare pentru a fi facute la CakeMaker ( daca este cazul )
	if (RequiredForCakeMaker >= 0) // cazul pentru care se pot da exact numarul de prajituri cerute DOAR din carusel
	{
		cout << "\n";
		while (NrOfCakes != 0) // dau toate cake-urile necesare
		{
			carousel.getCake(recipe->getName());
			NrOfCakes--;
		}
		cout << "Comanda dvs. este gata pentru ridicare!";
		_getch();
		return carouselOfCakes;
	}
	if (counter == 0)// cazul pentru care nu exista nicio prajitura ceruta in carusel
	{
		RecipeCake* RecipeCombined = new RecipeCake(recipe->getName(), RequiredForCakeMaker * recipe->getTime()); // fac o noua reteta care va face animatia de CakeMaker sa se realizeze o singura data ( nu de mai multe ori )
		system("CLS");
		cakeMaker.takeCommand(recipe);
	}
	if (RequiredForCakeMaker < 0) // cazul pentru care exista prajituri cerute in carusel, dar NU SUFICIENTE pentru a onora comanda
	{
		int aux = NrOfCakes;
		cout << "\n";
		while (counter != 0) // dau cate pot din carusel
		{
			carousel.getCake(recipe->getName());
			counter--;
			NrOfCakes--;
		}
		Sleep(1000);
		system("CLS");
		RecipeCake* RecipeCombined = new RecipeCake(recipe->getName(), (-1)*RequiredForCakeMaker * recipe->getTime()); // fac o noua reteta care va face animatia de CakeMaker sa se realizeze o singura data ( nu de mai multe ori )
		system("CLS");
		cakeMaker.takeCommand(recipe);
	}
	return carouselOfCakes;
}

list<Cake*> CommandTaker::getCakesFromCarousel() // returneaza torturile din carusel
{
	return carousel.storage;
}

bool CommandTaker::checkCarouselOfCakes() // verificam daca CarouselOfCakes este in parametrii optimi
{
	if (carousel.getCurrentCapacity() > carousel.getLowLimit()) return true; 
	else return false;
}

void CommandTaker::refillCarousel() 
{
	list<Cake*> MenuOfCakes;
	ifstream f("cakes.txt");
	string name;
	int time;
	while (!f.eof()) // refacem meniul pentru a putea introduce elementele in CarouselOfCakes
	{
		f >> name >> time;
		MenuOfCakes.push_back(new Cake(name));
	}
	Cake* c = nullptr;
	do  // introducem cate un element in CarouselOfCakes pana la limita impusa - maxCapacity
	{
		for (auto i = MenuOfCakes.begin(); i != MenuOfCakes.end(); i++)
		{
			c = *i;
			carousel.addCake(c);
		}
	} while (carousel.addCake(c));
	f.close();
}
