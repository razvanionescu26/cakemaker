#pragma once
#include "Cake.h"
#include "RecipeCake.h"
#include <thread>
#include <chrono>
#include <Windows.h>
#include <conio.h>

void loadingBar(int time)
{
	// initializare caractere pentru afisare loading bar
	char a = 177, b = 219;
	cout << "\n\n\n\n";
	cout << "\n\n\n\n\t\t\t\t\tComanda este in curs de pregatire...\n\n";
	cout << "\t\t\t\t\t";
	// bara goala ( fara progres )
	for (int i = 0; i < 26; i++)
		cout << a;
	cout << "\r";
	cout << "\t\t\t\t\t";
	// "animatia" pentru bara de incarcare
	for (int i = 0; i < 26; i++) 
	{
		cout << b;
		Sleep(time*10);
	}
	cout << "\n\n\t\t\t\t\tComanda dvs. este gata pentru ridicare!\n\n";
	_getch();
	system("CLS");
}



class CakeMaker
{
public:
	CakeMaker() {};
	Cake* takeCommand(RecipeCake* recipe);
};

Cake* CakeMaker::takeCommand(RecipeCake* recipe)
{
	Cake* c = new Cake(recipe->getName());
	loadingBar(recipe->getTime());
	return c;
}
