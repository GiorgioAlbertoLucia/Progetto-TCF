#include <iostream>
#include "../include/polyfit.hpp"
#include "../include/dataset.hpp"

using namespace std;

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/testFit1.csv";

    Dataset<double> dataset;
    dataset.fill(path);
    dataset.describe();

    vector<double> errvec;
    for(int i = 0; i < dataset[0].size(); i++)     errvec.push_back(dataset[1].std());
    //Data<double> err(errvec, "err");    

    //dataset.add(err);

    PolyFit polyfit(dataset[0], dataset[1], dataset[2]);
    polyfit.fit();
    


    return 0;
}