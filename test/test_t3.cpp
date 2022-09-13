#include <iostream>
#include "../include/polyfit.hpp"
#include "../include/dataset.hpp"
#include "../include/udouble.hpp"

using namespace std;

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/testFit1.txt";

    std::string option("udouble");

    if (option == std::string("udouble"))
    {
        
        Dataset<Udouble> dataset;
        dataset.fill(path);
        dataset.head();

        Data<Udouble> data;
        data = dataset[0] + dataset[1];
        data.head();
        
        //PolyFit polyfit(dataset[0], dataset[1]);
        //polyfit.fit();
    }

    if (option == std::string("double"))
    {
        Dataset<double> dataset;
        dataset.fill(path);
        dataset.describe();
        dataset.head();

        Data<double> data;
        data = dataset[0] + dataset[2];
        data.head();

        //PolyFit polyfit(dataset[0], dataset[2], dataset[3]);
        //polyfit.fit();

    }

    
    return 0;
}