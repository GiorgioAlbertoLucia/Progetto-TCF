//clang++ -std=c++14 main.cpp src_t/csvFile_t.cpp src_t/txtFile_t.cpp src_t/udouble.cpp src_t/partder.cpp src_t/polyfit.cpp -o main
//clang++ -std=c++14 main.cpp -I /Library/Frameworks/Python.framework/Versions/3.9/include/python3.9 -I /Library/Frameworks/Python.framework/Versions/3.9/lib/python3.9/site-packages/numpy/core/include/ -L /Library/Frameworks/Python.framework/Versions/3.9/lib -lpython3.9 src/*.cpp -o exe/main
//clang++ -std=c++14 -I /Users/francescomarchisotti/.pyenv/versions/3.10.6/include/python3.10/ -I /Users/francescomarchisotti/.pyenv/versions/3.10.6/lib/python3.10/site-packages/numpy/core/include -L /Users/francescomarchisotti/.pyenv/versions/3.10.6/lib/ -lpython3.10 src/*.cpp main.cpp -o main
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
#include "matplotlib-cpp-master/matplotlibcpp.h"

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>


using namespace std;
namespace plt = matplotlibcpp;

Dataset<double> import_file();

void menu(Dataset<double> &dataset, bool &fit_exists, vector<double> pars);

void inspect(Dataset<double> &dataset);

void manipulate(Dataset<double> &dataset);

void fit(Dataset<double> &dataset, bool &fit_exists, vector<double> pars);

void plot(Dataset<double> &dataset, bool &fit_exists, vector<double> pars);

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
	usleep(750000);    // µseconds
	system(CLS);

	menu(dataset, fit_exists, fit_params);

	return 0;
}

Dataset<double> import_file() {
	string path;
	cout << "Enter file path: ";
	cin >> path;

	return {path};
}

void menu(Dataset<double> &dataset, bool &fit_exists, vector<double> pars) {
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
				fit(dataset, fit_exists, pars);
				break;
			case 4:
				plot(dataset, fit_exists, pars);
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

void inspect(Dataset<double> &dataset) {
	int choice;
	cout << "1. First 5 rows\n"
			"2. First n rows\n"
			"3. Column names\n"
			"4. Column description\n"
			"5. size()\n"   // ------------- secondo me questo non serve molto - sono d'accordo
			"6. Exit\n"
			"Enter your choice: ";
	cin >> choice;

	switch (choice) {
		case 1:
			cout << endl;
			dataset.head();
			break;
		case 2:
			int n;
			cout << "Enter the number of rows: ";
			cin >> n;
			cout << endl;
			dataset.head(n);
			break;
		case 3:
			cout << endl;
			cout << "[ ";
			for (std::string c: dataset.get_columns()) cout << c << ", ";
			cout << " ]" << endl;
			break;
		case 4:
			cout << endl;
			dataset.describe();
			break;
		case 5:
			cout << endl;
			cout << dataset.size() << endl;
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

void fit(Dataset<double> &dataset, bool &fit_exists, vector<double> pars) {
	int col_x, col_y, col_sy;
	dataset.head();
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	cout << "Enter column index for y-errors: ";
	cin >> col_sy;
	int deg;
	cout << "Enter polynomial degree: ";
	cin >> deg;

	// initialize pars vector just in case
	if (!pars.empty()) {
		pars.clear();
	}

	fit_exists = false;	// if unsuccessful fit then there is no available fit

	PolyFit polyfit(dataset.get_data(col_x), dataset.get_data(col_y), dataset.get_data(col_sy), deg);
	polyfit.fit(deg);
	pars = polyfit.get_parameters();
	fit_exists = true;

	system(PAUSE);
}

void plot(Dataset<double> &dataset, bool &fit_exists, vector<double> pars) {
	int col_x, col_y, col_sy;
	dataset.head();
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	cout << "Enter column index for y-errors: ";
	cin >> col_sy;

	vector<double> x = dataset.get_data(col_x).get_data();
	vector<double> y = dataset.get_data(col_y).get_data();
	vector<double> sy = dataset.get_data(col_sy).get_data();

	if (fit_exists) {
		int n_points = 100;	// might need some way to compute this, something like (x_max - x_min) * 100 or something
		vector<double> xdense, ydense;	// può diventare un array (meglio per le performance)?
		double x_min = *min_element(x.begin(), x.end());
		double x_max = *max_element(x.begin(), x.end());
		for (int i = 0; i < n_points; i++) {
			xdense.push_back(x_min + i * (x_max - x_min) / 100);	// equivalent to np.linspace(x_min, x_max, n_points)
			ydense.push_back(0.);
			for (int j = 0; j < pars.size(); j++) {
				ydense[i] += pars[j] * pow(xdense[i], j);
			}
		}
		// blocco commentato perché matplotlib ha la mamma
		plt::plot(x, y, {{"marker", "o"}, {"linestyle", "none"}});
		plt::plot(xdense, ydense);
	
		//plot formatting shenanigans
	
		plt::show();
		plt::savefig("graphs/output_test.png");  // ------- specificare nome del file
		
	} else {
		plt::plot(x, y, {{"marker", "o"}, {"linestyle", "none"}});
	
		//plot formatting shenanigans
	
		plt::show();
		plt::savefig("graphs/output_test.png");
		
	}

}