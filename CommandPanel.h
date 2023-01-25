#pragma once
#include "CommandTaker.h"
#include "TextTable.h"
#include <string>
#include <fstream>



class CommandPanel
{
	list<RecipeCake*> menu;
	CommandTaker commandTaker;
public:
	CommandPanel(); 
	void showProducts(); 
	void selectProduct(string name); 
	void selectProduct(string name, int numberOfProducts); 
	void showProductsInCarousel(); 
};

CommandPanel::CommandPanel() // introducerea prajiturilor in meniu prin intermediul unui fisier
{
	ifstream f("cakes.txt"); 
	string name;
	int time;
	while (!f.eof())
	{
		f >> name >> time;
		RecipeCake* recipe = new RecipeCake(name, time);
		menu.push_back(recipe);
	}
	f.close();
}

void CommandPanel::showProducts()
{
	TextTable* t = new TextTable('-', '|', '+'); // prezentarea meniului sub forma de tabel pentru client
	cout << "-> Lista prajiturilor disponibile <-\n\n";
	t->add("Nume prajitura");
	t->add("Timp preparare");
	t->endOfRow();
	for (auto i = menu.begin(); i != menu.end(); i++)
	{
		t->add((*i)->getName());
		string time = to_string((*i)->getTime());
		t->add(time);
		t->endOfRow();
	}
	t->setAlignment(2, TextTable::Alignment::LEFT);
	cout << *t;
	delete t;
}

void CommandPanel::selectProduct(string name) 
{
	try
	{
		for (auto i = menu.begin(); i != menu.end(); i++)
		{
			if ((*i)->getName() == name)
			{
				RecipeCake* recipe = *i;
				commandTaker.takeCommand(recipe); // daca a fost gasita prajitura in meniu, atunci se va pasa mai departe comanda la commandTaker pentru realizarea ei
				return;
			}
		}
		throw new exception("Error!"); // aruncarea unei exceptii in cazul in care clientul doreste un produs care nu exista in meniu
	}
	catch (exception)
	{
		cout << "\nPrajitura nu a putut fi gasita in meniu!\n";
		return;
		// PENTRU CAZUL IN CARE CLIENTUL DORESTE O PRAJITURA CARE NU ESTE NORMAL VALABILA IN MENIU 

		/*cout << "La urmatoarea accesare a aparatului, produsul va fi disponibil in meniu!\n";*/
		// TORTURILE SA FIE ACCESIBILE IN MENIU LA URMATOAREA REDESCHIDERE A MENIULUI
		// int cookTime;
		//ofstream f("cakes.txt", ios::app);
		//srand(time(NULL)); // random seed 
		//cookTime = rand() % 10 + 1;
		//RecipeCake* recipe = new RecipeCake(name, cookTime);
		//menu.push_back(recipe);
		//f.close();
		//exit(0);
	}
}

void CommandPanel::selectProduct(string name, int numberOfProducts)
{
	try
	{
		for (auto i = menu.begin(); i != menu.end(); i++)
		{
			if ((*i)->getName() == name)
			{
				RecipeCake* recipe = *i;
				commandTaker.takeCommand(recipe,numberOfProducts); // daca a fost gasita prajitura in meniu, atunci se va pasa mai departe comanda la commandTaker pentru realizarea ei
				return;
			}
		}
		throw new exception("Error!"); // aruncarea unei exceptii in cazul in care clientul doreste un produs care nu exista in meniu
	}
	catch (exception)
	{
		cout << "\nPrajitura nu a putut fi gasita in meniu!\n";
		return;
		// PENTRU CAZUL IN CARE CLIENTUL DORESTE O PRAJITURA CARE NU ESTE NORMAL VALABILA IN MENIU 

		/*cout << "La urmatoarea accesare a aparatului, produsul va fi disponibil in meniu!\n";*/
		// TORTURILE SA FIE ACCESIBILE IN MENIU LA URMATOAREA REDESCHIDERE A MENIULUI
		// int cookTime;
		//ofstream f("cakes.txt", ios::app);
		//srand(time(NULL)); // random seed 
		//cookTime = rand() % 10 + 1;
		//RecipeCake* recipe = new RecipeCake(name, cookTime);
		//menu.push_back(recipe);
		//f.close();
		//exit(0);
	}
}

void CommandPanel::showProductsInCarousel()
{
	list<Cake*> ProductsInCarousel = commandTaker.getCakesFromCarousel();
	if (ProductsInCarousel.size() == 0) // verificam cazul pentru care nu exista produse in carusel
	{
		cout << "Nu exista prajituri in carusel!\n";
		return; 
	}
	cout << "->PRAJITURILE DIN CARUSEL<-\n\n";
	for (auto i = ProductsInCarousel.begin(); i != ProductsInCarousel.end(); i++)
		cout << (*i)->getName() << "\n";
}
