#include "../include/txtFile.hpp"
#include "../include/csvFile.hpp"
#include "../include/data.hpp"
#include "../include/fileFactory.hpp"

#include "../include/leastsquares.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// STATUS: CHECK IF LEASTSQUARES CODE IS WRITTEN PROPERLY 

int main()
{
    const char * path = "data/example.txt";
    TxtFile txt_file(path);

    Data x(path, 1, "x");
    Data y(path, 0, "y");
    Data sy(path, 2, "sy");

    cout << x << endl;
    cout << y << endl;
    cout << sy << endl;
    
    LeastSquares ls(x, y, sy);
    ls.fit("pol1");

    cout << "chi = " << ls.get_chisquared() << endl;
    cout << "yfit" << endl;
    std::vector<double> v = ls.get_yfit();
    for (std::vector<double>::const_iterator i = v.begin(); i != v.end(); i++)
    {
        cout << *i << endl;
    }
    cout << endl;
    

    return 0;
}