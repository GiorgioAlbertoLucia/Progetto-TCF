#include <iostream>
#include "../include/polyfit.hpp"
#include "../include/dataset.hpp"
#include "../include/udouble.hpp"

using namespace std;

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/testFit1.txt";

    Dataset<Udouble> dataset;
    dataset.fill(path);
    dataset.describe();

    PolyFit polyfit(dataset[0], dataset[1]);
    polyfit.fit();
    


    return 0;
}