#include <iostream>

#include "dataset.h"
#include "data.h"

using namespace std;

int main()
{
    cout << "Start session" << endl;
    Data * data = new Data("test2.txt", 0);
    cout << "computing..." << endl;
    cout << * data << endl;
    cout << "computing..." << endl;
    delete data;

    cout << "computing..." << endl;
    Dataset * dataset = new Dataset("test2.txt");
    cout << "computing..." << endl;
    Dataset * dataset2 = new Dataset("test2.txt", 1);

    cout << "computing..." << endl;
    cout << dataset << dataset << endl;
    cout << "computing..." << endl;
    delete dataset;
    cout << "computing..." << endl;
    delete dataset2;

    return 0;
}