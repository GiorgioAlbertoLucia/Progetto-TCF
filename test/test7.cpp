#include "../include/txtFile.hpp"
#include "../include/csvFile.hpp"
#include "../include/data.hpp"
#include "../include/fileFactory.hpp"

#include "../include/polyfit.hpp"
#include "../matplotlib-cpp-master/matplotlibcpp.h"

#include <iostream>
#include <string>
#include <vector>

namespace plt = matplotlibcpp;
using namespace std;

// STATUS: NOT WORKING

int main()
{
    const char * path = "../data/test7.txt";
    TxtFile txt_file(path);

    Data x(path, 0, "x");
    Data y(path, 1, "y");
    Data sy(path, 2, "sy");

    cout << data1 << endl;
    cout << data2 << endl;
    cout << data3 << endl;
    
    LeastSquares ls(x.get_data(), y.get_data(), sy.get_data());
    ls.fit("pol2");

    plt::figsize(1200, 780);
    plt::scatter(x.get_data(), y.get_data());
    plt::plot(x.get_data(), ls.get_yfit(), "r--");
    plt::save("../graphs/test7.png");

    return 0;
}