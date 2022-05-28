#include <iostream>

#include "../include/dataset.hpp"
#include "../include/data.hpp"

using namespace std;

// STATUS: CHECK DATA NAMES

int main()
{
    Data * data = new Data("data/test7.txt", 0);
    cout << *data << endl;
    delete data;

    Dataset * dataset = new Dataset("data/test7.txt", 0, "Dataset 1");
    Dataset * dataset2 = new Dataset("data/test7.txt", 1, "Dataset 2");

    cout << *dataset << endl << *dataset2 << endl;
    delete dataset;
    delete dataset2;

    return 0;
}