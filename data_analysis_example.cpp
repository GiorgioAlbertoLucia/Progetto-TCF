//
//
//

#include "include/udouble.hpp"
#include "include/dataset.hpp"
#include "include/polyfit.hpp"

#include <iostream>
#include <random>

#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>

using namespace std;

void data_analysis_example()
//int main()
{
    
    // import data from file 
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/testFit1.txt";
    Dataset<Udouble> dataset(path);
    // dataset[0] -> x +- sx
    // dataset[1] -> y +- sy

    // create a new variable: z = x^2 + x
    Data<Udouble> z;
    z = pow(dataset[1], 2) + dataset[1];
    z.set_name("z");
    z.head();

    // add gaussian noise to the variable
    const double mean = 0.;
    const double stddev = 0.1;
    z.add_noise(mean, stddev);
    z.head();

    // add variable to the dataset
    dataset.add(z);
    // dataset[2] -> z +- sz

    // fit
    PolyFit polyfit(dataset[0], dataset[2]);
    polyfit.fit(2);

    TCanvas * c = new TCanvas("c", "c", 600, 600);
    TGraphErrors * g = new TGraphErrors(dataset.size(), &dataset[0].values()[0], &dataset[2].values()[0], 
                                            &dataset[0].errors()[0], &dataset[2].errors()[0]);
    g->Draw();
    c->SaveAs("graphs/analysis_example.png");
            





    
    //return 0;

}