//clang++ -std=c++14 main.cpp src_t/csvFile_t.cpp src_t/txtFile_t.cpp src_t/udouble.cpp src_t/partder.cpp src_t/polyfit.cpp -o main

#ifdef _WIN32
#include <Windows.h>
const char *CLS = "CLS";
const char *PAUSE = "PAUSE";
#else

#include <unistd.h>

const char *CLS = "clear";
const char *PAUSE = "read -n 1 -s -p \"Press any key to continue...\"";
#endif


#include "include/polyfit.hpp"
#include "include/dataset.hpp"
//#include "matplotlib-cpp-master/matplotlibcpp.h"

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
//namespace plt = matplotlibcpp;

Dataset<double> import_file();

void menu(Dataset<double> *dataset);

void inspect(Dataset<double> *dataset);

void manipulate(Dataset<double> *dataset);

void fit(Dataset<double> *dataset);

void plot(Dataset<double> *dataset);

int main(int argc, char *argv[]) {
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

	// Variable to detect if there is a successful fit in order to handle fit plotting
	bool fit_exists = false;
	vector<double> fit_params = {};

	system(CLS);

	Dataset<double> dataset;
	if (argc == 1) {
		dataset = import_file();
	} else if (argc == 2) {
		dataset.fill(argv[1]);
	} else {
		cout << "Usage:\n"
			 << argv[0] << " [path]" << endl;
		system(PAUSE);
		system(CLS);
		return 1;
	}

	cout << "File imported correctly." << endl;
	usleep(750000);	// µseconds
	system(CLS);

	menu(&dataset);

	return 0;
}

Dataset<double> import_file() {
	string path;
	cout << "Enter file path: ";
	cin >> path;

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
				fit(dataset);
				break;
			case 4:
				// For the time being I will only plot data
				// The ability to plot a fitted function will come later
				plot(dataset);
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
			"6. Exit\n"
			"Enter your choice: ";
	cin >> choice;

	switch (choice) {
		case 1:
			cout << endl;
			dataset->head();
			break;
		case 2:
			int n;
			cout << "Enter the number of rows: ";
			cin >> n;
			cout << endl;
			dataset->head(n);
			break;
		case 3:
			cout << endl;
			cout << "[ ";
			for(std::string c : dataset->get_columns())		cout << c << ", ";
			cout << " ]" << endl;
			break;
		case 4:
			cout << endl;
			dataset->describe();
			break;
		case 5:
			cout << endl;
			cout << dataset->size() << endl;
			break;
		case 6:
			break;
		default:
			cout << endl;
			cout << "Wrong input" << endl;
	}
	cout << endl;
	system(PAUSE);
}

void fit(Dataset<double> *dataset) {
	int col_x, col_y, col_sy;
	dataset->head();
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	cout << "Enter column index for y-errors: ";
	cin >> col_sy;
	int deg;
	cout << "Enter polynomial degree: ";
	cin >> deg;

	PolyFit polyfit(dataset->get_data(col_x), dataset->get_data(col_y), dataset->get_data(col_sy), deg);
	polyfit.fit(deg);

	system(PAUSE);
}

void plot(Dataset<double> *dataset) {
	int col_x, col_y, col_sy;
	dataset->head();
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	cout << "Enter column index for y-errors: ";
	cin >> col_sy;

//	plt::errorbar(dataset->get_data(col_x), dataset->get_data(col_y), dataset->get_data(col_sy));
}