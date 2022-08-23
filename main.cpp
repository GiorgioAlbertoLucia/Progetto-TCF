#ifdef _WIN32
#include <Windows.h>
const char *cls = "CLS";
#else

#include <unistd.h>

const char *cls = "clear";
#endif


#include "include_t/dataset_t.hpp"

#include <iostream>
#include <string>
#include <stdlib.h>


using namespace std;

Dataset<double> import_file();

void menu(Dataset<double> *dataset);

void inspect(Dataset<double> *dataset);

int main() {
	/*
	int t = 5;
	int *tPtr = &t;
	t      -> t
	&t     -> indirizzo di t
	tPtr   -> variabile con l'indirizzo di t
	*tPtr  -> piglia quello che sta all'indirizzo di t (ovvero t)
	&tPtr  -> l'indirizzo della variabile tPtr
	&*tPtr -> prendi quello che sta all'indirizzo di t (ovvero t) e dammi il suo indirizzo (ovvero l'indirizzo di t)
	*&tPtr -> quello che sta all'indirizzo di tPtr (ovvero l'indirizzo di t)
	*/

	system(cls);

	Dataset<double> dataset = import_file();
//	dataset.head();

	menu(&dataset);

//	system("read -n 1 -s -p \"Press any key to continue...\"");
//	system(cls);
	return 0;
}

Dataset<double> import_file() {
	string path = "data/test7.txt";
//	cout << "Enter file path: ";
//	cin >> path;

	cout << "File imported correctly." << endl;
	sleep(1);
	system(cls);

	return {path};
}

void menu(Dataset<double> *dataset) {
	int choice;
	bool exit_cond = false;
	do {
		cout << "1. Inspect data\n"
				"2. Fit\n"
				"3. Plot\n"
				"4. Exit\n"
				"Enter your choice: ";
		cin >> choice;
		system(cls);
		switch (choice) {
			case 1:
				inspect(dataset);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				exit_cond = true;
				break;
		}
		system(cls);
	} while (!exit_cond);
}

void inspect(Dataset<double> *dataset) {
	int choice;
	cout << "1. head()\n"
			"2. head(n)\n"
			"3. describe()\n"
			"4. size()\n"
			"Enter your choice: ";
	cin >> choice;
	cout << endl;

	switch (choice) {
		case 1:
			dataset->head();
			system("read -n 1 -s -p \"Press any key to continue...\"");
			break;
		case 2:
			int n;
			cout << "Enter the number of rows: ";
			cin >> n;
			dataset->head(n);
			system("read -n 1 -s -p \"Press any key to continue...\"");
			break;
		case 3:
			dataset->describe();
			system("read -n 1 -s -p \"Press any key to continue...\"");
			break;
		case 4:
			cout << dataset->size() << endl;
			system("read -n 1 -s -p \"Press any key to continue...\"");
			break;
		default:
			cout << "Wrong input" << endl;
			system("read -n 1 -s -p \"Press any key to continue...\"");
			system(cls);
			inspect(dataset);
	}
}
