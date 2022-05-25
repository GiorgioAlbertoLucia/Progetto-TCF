#include "../include/txtFile.hpp"
#include "../include/csvFile.hpp"
#include "../include/data.hpp"
#include "../include/fileFactory.hpp"

#include "../include/leastsquares.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    const char * path = "data/test7.txt";
    TxtFile txt_file(path);

    Data x(path, 0, "x");
    Data y(path, 1, "y");
    Data sy(path, 2, "sy");

    cout << x << endl;
    cout << y << endl;
    cout << sy << endl;
    
    LeastSquares ls(x.get_data(), y.get_data(), sy.get_data());
    ls.fit("pol2");

    cout << "chi = " << ls.get_chisquared() << endl;

    return 0;
}