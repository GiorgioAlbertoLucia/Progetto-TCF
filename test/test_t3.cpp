#include <iostream>
#include "../include_t/polyfit.hpp"

using namespace std;

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/income_data.txt";

    Dataset<double> dataset(path);
    dataset.describe();

    vector<double> errvec;
    for(int i = 0; i < dataset.size(); i++)     errvec.push_back(0.);
    Data<double> err(errvec, "err");    

    dataset.add(err);

    PolyFit polyfit(dataset[0], dataset[1], err);
    polyfit.fit();
    


    return 0;
}