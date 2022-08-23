#include "include_t/dataset_t.hpp"

#include <iostream>
#include <string>

using namespace std;

void menu();

void file_submenu();

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

	menu();

	return 0;
}

void menu() {
	int choice = 1;
//	do {
//		cout << "Enter the corresponding number:\n"
//				"1. Import data from file\n";
//		cin >> choice;
//	} while (choice <= 0 && choice > 1);

	switch (choice) {
		case 1:
			string path;
			cout << "Enter file path: ";
			cin >> path;

			Dataset<double> dataset(path);
			dataset.head();
	}
}

//void file_submenu() {
//	string path;
//	cout << "Open file" << endl;
//	cout << "Enter file path" << endl;
//	cin >> path;
//
//	FileFactory ff;
//	File *file = ff.create_file(path);
//
//}