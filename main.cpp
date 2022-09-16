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

#include "pbPlots/pbPlots.hpp"
#include "pbPlots/supportLib.hpp"

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <format>


using namespace std;

Dataset<double> import_file();

void menu(Dataset<double> &dataset);
void inspect(Dataset<double> &dataset);
void manipulate(Dataset<double> &dataset);
vector<double> fit(Dataset<double> &dataset);
void plot(Dataset<double> &dataset, vector<double> &pars);

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

	

	system(CLS);

	Dataset<double> dataset;
	if (argc == 1) {
		dataset = import_file();
	} 
	else if (argc == 2) {
		dataset.fill(argv[1]);
	} 
	else {
		cout << "Usage:\n"
			 << argv[0] << " [path]" << endl;
		system(PAUSE);
		system(CLS);
		return 1;
	}

	cout << "File imported correctly." << endl;
	usleep(750000);    // µseconds
	system(CLS);

	menu(dataset);

	return 0;
}

Dataset<double> import_file() {
	string path;
	cout << "Enter file path: ";
	cin >> path;

	return {path};
}

void menu(Dataset<double> &dataset) {
	
	// to store fit parameters
	vector<double> pars;

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
				pars = fit(dataset);
				break;
			case 4:
				plot(dataset, pars);
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
			"5. Exit\n"
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
			break;
		default:
			cout << endl;
			cout << "Wrong input" << endl;
	}
	cout << endl;
	system(PAUSE);
}

vector<double> fit(Dataset<double> &dataset) {
	int col_x, col_y, col_sy;
	dataset.head();
	cout << "Column indeces are: 0, 1, 2, ..." << endl;
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	cout << "Enter column index for y-errors: ";
	cin >> col_sy;
	int deg;
	cout << "Enter polynomial degree: ";
	cin >> deg;

	PolyFit polyfit(dataset[col_x], dataset[col_y], dataset[col_sy], deg);
	polyfit.fit(deg);

	system(PAUSE);
	return polyfit.get_parameters();
}

void plot(Dataset<double> &dataset, vector<double> &pars) {
	int col_x, col_y;
	string outfile;
	
	dataset.head();
	cout << "Column indeces are: 0, 1, 2, ..." << endl;
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	
	cout << "Enter name for the output file: ";
	cin >> outfile;
	outfile = "graphs/" + outfile + ".png";
	
	Data<double> x = dataset[col_x];
	Data<double> y = dataset[col_y];

	// WITH FIT LINE
	if (!pars.empty()) {
		bool success;
		StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
		RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    	// points
    	vector<double> xs, ys;
    	xs = x.get_data();
    	ys = y.get_data();

    	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
		series->xs = &xs;       
		series->ys = &ys;
		series->linearInterpolation = false;
		series->pointType = toVector(L"dots");
		series->color = CreateRGBColor(1, 0, 0);


    	// line
    	double step = (x.max() - x.min())/100;
    	vector<double> xline, yline;

    	for (double i = dataset[0].min(); i <= dataset[0].max(); i+=step) 
    	{
    	    xline.push_back(i);
			double ydummy = 0.;
			for (int j = 0; j < pars.size(); j++)	ydummy += pars[j] * pow(i, j);
			yline.push_back(ydummy);
    	}

		


    	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
		series2->xs = &xline;
		series2->ys = &yline;
		series2->lineType = toVector(L"solid");
		series2->lineThickness = 2;
		series2->color = CreateRGBColor(0, 0, 1);

    	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
		settings->width = 600;
		settings->height = 400;
		settings->autoBoundaries = true;
		settings->autoPadding = true;
		settings->title = toVector(L"");
		settings->xLabel = toVector(L"");
		settings->yLabel = toVector(L"");
		settings->scatterPlotSeries->push_back(series);
		settings->scatterPlotSeries->push_back(series2);

    	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

		if(success)
		{
			vector<double> *pngdata = ConvertToPNG(imageReference->image);
			WriteToFile(pngdata, outfile.c_str());
			cout << "File graphs/main.png has been created." << endl;
			DeleteImage(imageReference->image);
		}
		else
		{
			cerr << "Error: ";
			for(wchar_t c : *errorMessage->string)	cerr << c;
			cerr << endl;
		}

		system(PAUSE);
	}

	// WITHOUT FIT LINE
	else {
		bool success;
		StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
		RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    	// points
    	vector<double> xs, ys;
    	xs = x.get_data();
    	ys = y.get_data();

    	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
		series->xs = &xs;       
		series->ys = &ys;
		series->linearInterpolation = false;
		series->pointType = toVector(L"dots");
		series->color = CreateRGBColor(1, 0, 0);

    	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
		settings->width = 600;
		settings->height = 400;
		settings->autoBoundaries = true;
		settings->autoPadding = true;
		settings->title = toVector(L"");
		settings->xLabel = toVector(L"");
		settings->yLabel = toVector(L"");
		settings->scatterPlotSeries->push_back(series);

    	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

		if(success)
		{
			vector<double> *pngdata = ConvertToPNG(imageReference->image);
			WriteToFile(pngdata, outfile.c_str());
			cout << "File graphs/main_unfitted.png has been created." << endl;
			DeleteImage(imageReference->image);
		}
		else
		{
			cerr << "Error: ";
			for(wchar_t c : *errorMessage->string)	cerr << c;
			cerr << endl;
		}

		system(PAUSE);
	}	
	
}