//
//  
//

#include "include/udouble.hpp"
#include "include/dataset.hpp"
#include "include/polyfit.hpp"

#include "pbPlots/pbPlots.hpp"
#include "pbPlots/supportLib.hpp"

#include <iostream>
#include <random>

using namespace std;




int main()
{
    
    // import data from file 
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/testFit1.txt";
    Dataset<Udouble> dataset(path);
    cout << "Dataset originale" << endl;
    dataset.head();
    // dataset[0] -> x +- sx
    // dataset[1] -> y +- sy



    // create a new variable: z = x^2 + x
    Data<Udouble> z;
    z = pow(dataset[1], 2) + dataset[1];
    z.set_name("z");

    // add gaussian noise to the variable
    const double mean = 0.;
    const double stddev = 0.1;
    z.add_noise(mean, stddev);

    // add variable to the dataset
    dataset.add(z);
    cout << "Dataset modificato" << endl;
    dataset.head();
    // dataset[2] -> z +- sz

    // add variable to the file (rewrite dataset inside the file)
    const char * path2 = "/Users/giogi/Documents/TCF/Progetto/data/testFit1_copy.txt";
    dataset.write(path2);




    // fit
    PolyFit polyfit(dataset[0], dataset[2]);
    polyfit.fit(2);
    vector<double> pars = polyfit.get_parameters();




    // plots
    bool success;
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    // points
    vector<double> xs, ys;
    xs = dataset[0].get_values();
    ys = dataset[2].get_values();

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;       
	series->ys = &ys;
	series->linearInterpolation = false;
	series->pointType = toVector(L"dots");
	series->color = CreateRGBColor(1, 0, 0);


    // line
    double step = (dataset[0].max() - dataset[0].min())/100;
    vector<double> xline, yline;

    for (double i = dataset[0].min(); i <= dataset[0].max(); i+=step) 
    {
        xline.push_back(i);
        yline.push_back(pars[0] + pars[1]*i + pars[2]*i*i);
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
	settings->title = toVector(L"Data Analysis Example");
	settings->xLabel = toVector(L"x");
	settings->yLabel = toVector(L"y");
	settings->scatterPlotSeries->push_back(series);
	settings->scatterPlotSeries->push_back(series2);

    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

	if(success){
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, "graphs/data_analysis_example.png");
		DeleteImage(imageReference->image);
	}else{
		cerr << "Error: ";
		for(wchar_t c : *errorMessage->string){
			cerr << c;
		}
		cerr << endl;
	}


    
    return 0;

}