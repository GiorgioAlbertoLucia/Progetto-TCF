#ifdef _WIN32
#include <Windows.h>
const char *CLS = "CLS";
const char *PAUSE = "PAUSE";
#else

#include <unistd.h>

const char *CLS = "clear";
const char *PAUSE = "read -n 1 -s -p \"Press any key to continue...\"";
#endif


#include "include_t/dataset_t.hpp"

#include <iostream>
#include <string>
#include <stdlib.h>


using namespace std;

Dataset<double> import_file();

void menu(Dataset<double> *dataset);

void inspect(Dataset<double> *dataset);

void manipulate(Dataset<double> *dataset);

void fit(Dataset<double> *dataset);

void plot(Dataset<double> *dataset);

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

	system(CLS);

	Dataset<double> dataset = import_file();
	menu(&dataset);

//	system(PAUSE);
//	system(CLS);
	return 0;
}

Dataset<double> import_file() {
	string path = "data/test7.txt";
//	cout << "Enter file path: ";
//	cin >> path;

	cout << "File imported correctly." << endl;
	sleep(1);
	system(CLS);

	return {path};
}

void menu(Dataset<double> *dataset) {
	int choice;
	bool exit_cond = false;
	do {
		cout << "1. Inspect data\n"
				"2. Manipulate data\n"
				"3. Fit\n"
				"4. Plot\n"
				"5. Exit\n"
				"Enter your choice: ";
		cin >> choice;
		system(CLS);
		switch (choice) {
			case 1:
				inspect(dataset);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				exit_cond = true;
				break;
			default:
				cout << "Wrong input";
				system(PAUSE);
		}
		system(CLS);
	} while (!exit_cond);
}

void inspect(Dataset<double> *dataset) {
	int choice;
	cout << "1. head()\n"
			"2. head(n)\n"
			"3. columns()\n"
			"4. describe()\n"
			"5. size()\n"
			"Enter your choice: ";
	cin >> choice;
	cout << endl;

	switch (choice) {
		case 1:
			dataset->head();
			break;
		case 2:
			int n;
			cout << "Enter the number of rows: ";
			cin >> n;
			dataset->head(n);
			break;
		case 3:
			dataset->print_columns();
			break;
		case 4:
			dataset->describe();
			break;
		case 5:
			cout << dataset->size() << endl;
			break;
		default:
			cout << "Wrong input" << endl;
	}
	cout << endl;
	system(PAUSE);
}

void fit(Dataset<double> *dataset) {
	int deg;
	cout << "Enter polynomial degree: ";
	cin >> deg;
}
