#include <iostream>
#include "CommandPanel.h"

using namespace std;

void menu()
{
	int opt;
	CommandPanel panel;
	string name;
	int nrCakes;
	do {
		system("CLS");
		cout << "MENIU APARAT\n\n";
		cout << "1. Prezentarea produselor disponibile in meniu\n"; 
		cout << "2. Prezentarea produselor din carusel\n"; 
		cout << "3. Introducerea unei noi comenzi\n"; 
		cout << "4. Iesire\n";
		cout << "Optiunea dvs. este: ";
		cin >> opt;
		system("CLS");
		switch (opt)
		{
		default:
			cout << "Optiune invalida!";
			break;
		case 1:
			panel.showProducts();
			_getch();
			break;
		case 2:
			panel.showProductsInCarousel();
			_getch();
			break;
		case 3:
			cout << "Introduceti numele prajiturii dorite: ";
			cin >> name;
			cout << "Introduceti numarul de " << name << " dorit: ";
			cin >> nrCakes;
			if (nrCakes == 1) panel.selectProduct(name);
			else panel.selectProduct(name, nrCakes);
			
			break;
		case 4:
			cout << "Aplicatia se va inchide...\nVa multumim ca ati cumparat de la noi!\n";
			Sleep(1000);
			exit(0);
			break;
		}
	} while (1);
}

int main()
{
	menu();
	system("pause");
	return 0;
}