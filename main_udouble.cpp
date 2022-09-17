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
#include "include/udouble.hpp"

#include "pbPlots/pbPlots.hpp"
#include "pbPlots/supportLib.hpp"

#include "exprtk/exprtk.hpp"

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <format>


using namespace std;

Dataset<Udouble> import_file(string file_path);

void menu(Dataset<Udouble> &dataset, string path);
void inspect(Dataset<Udouble> &dataset);
void manipulate(Dataset<Udouble> &dataset, string path);
vector<double> fit(Dataset<Udouble> &dataset);
void plot(Dataset<Udouble> &dataset, vector<double> &pars);

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

	string path;

	system(CLS);

	Dataset<Udouble> dataset;
	if (argc == 1) {
		dataset = import_file(path);
	} 
	else if (argc == 2) {
		path = string(argv[1]);
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

	menu(dataset, path);

	return 0;
}

Dataset<Udouble> import_file(string file_path) {
	string path;
	cout << "Enter file path: ";
	cin >> path;
	file_path = path;

	return {path};
}

void menu(Dataset<Udouble> &dataset, string path) {
	
	// to store fit parameters
	vector<double> pars;
	Dataset<Udouble> new_dataset;
	new_dataset = dataset;

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
				inspect(new_dataset);
				break;
			case 2:
				manipulate(new_dataset, path);
				break;
			case 3:
				pars = fit(new_dataset);
				break;
			case 4:
				plot(new_dataset, pars);
				break;
			case 5:
				exit_cond = true;
				break;
			default:
				cout << "Wrong input\n";
				system(PAUSE);
		}
		system(CLS);
	} while (!exit_cond);
}

void inspect(Dataset<Udouble> &dataset) {
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

void manipulate(Dataset<Udouble> &dataset, string path) {

	int n_vars, n_consts, index;
	vector<vector<double>> val_vec, err_vec;
	string input_string, new_name;
	string answer;

	typedef exprtk::symbol_table<double> symbol_table_t;
   	typedef exprtk::expression<double>   expression_t;
   	typedef exprtk::parser<double>       parser_t;

   	symbol_table_t symbol_table;

	vector<double> y;
	vector<Udouble> uy;

	dataset.head();
	cout << "Define a new variable as a function of already existing ones. In the algebraic expression, refer to those as v0[i], ";
	cout << "v1[i], v2[i], ..." << endl;

	cout << "How many variables will you be using? ";
	cin >> n_vars;
	cout << "Column indeces are: 0, 1, 2, ..." << endl;
	for (int i = 0; i < n_vars; i++) 
	{
		cout << "Enter column index for variable v" << i << ": ";
		cin >> index;
		if (i == 0)	for (Udouble u: dataset[index].get_data())	y.push_back(0.);
		string var_name = "v" + to_string(i);

		val_vec.push_back(dataset[index].get_values());
		err_vec.push_back(dataset[index].get_errors());

		symbol_table.add_vector(var_name, &dataset[index].get_values()[0], dataset[index].get_values().size());
	}
	symbol_table.add_vector("y", y);
	
	cout << "Enter a name for the new variable: ";
	cin >> new_name;
	cout << "Enter the expression. \nnew_var = ";
	cin >> input_string;
	string expression_string = 
					" for (var i := 0; i < v0[]; i += 1) 									"
					" {																		"
					" 	y[i] := " + input_string + "; 										"
					" }																		";
	
	expression_t expression;
   	expression.register_symbol_table(symbol_table);

	parser_t parser;
   	parser.compile(expression_string,expression);

	expression.value();

	for (int i = 0; i < y.size(); i++)	
	{
		double err = 0.;
		for (int j = 0; j < n_vars; j++)	
		{
			string var_name = "v" + to_string(i) + "[" + to_string(j) + "]";
			double deriv = derivative(expression, var_name);
			err += pow(deriv * err_vec[j][i], 2);
		}
		cout << y[i] << " +- " << sqrt(err) << endl;
		Udouble u(y[i], sqrt(err));
		uy.push_back(u);
	}


	Data<Udouble> d(uy, new_name.c_str());

	dataset.add(d);
	//cout << "Add the variable to file? (y/n) ";
	//cin >> answer;
	//if (answer == string("y"))	dataset.write(path.c_str());
	
	system(PAUSE);
}

vector<double> fit(Dataset<Udouble> &dataset) {
	int col_x, col_y;
	dataset.head();
	cout << "Column indeces are: 0, 1, 2, ..." << endl;
	cout << "Enter column index for x-values: ";
	cin >> col_x;
	cout << "Enter column index for y-values: ";
	cin >> col_y;
	int deg;
	cout << "Enter polynomial degree: ";
	cin >> deg;

	PolyFit polyfit(dataset[col_x], dataset[col_y]);
	polyfit.fit(deg);

	system(PAUSE);
	return polyfit.get_parameters();
}

void plot(Dataset<Udouble> &dataset, vector<double> &pars) {
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
	
	Data<Udouble> x = dataset[col_x];
	Data<Udouble> y = dataset[col_y];

	// WITH FIT LINE
	if (!pars.empty()) {
		bool success;
		StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
		RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    	// points
    	vector<double> xs, ys;
    	xs = x.get_values();
    	ys = y.get_values();

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
			cout << "File " << outfile.c_str() << " has been created." << endl;
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
    	xs = x.get_values();
    	ys = y.get_values();

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
			cout << "File " << outfile.c_str() << " has been created." << endl;
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