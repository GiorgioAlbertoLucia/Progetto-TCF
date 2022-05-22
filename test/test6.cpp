#include <iostream>
#include <vector>

#include "../include/udouble.hpp"
#include "../include/partder.hpp"

#define PI 3.14159265

using namespace std;

// test udouble
int main()
{
    map<string, double> dx {{"x", 1.},};
    map<string, double> dy {{"y", 1},};

    PartDer x0(PI, dx);
    PartDer y0(3, dy);

    Udouble x(x0, 1), y(y0, 2), f;
    f = sin(x) + y * cos(x);    

    cout << endl << x << endl << y << endl << f << endl;

    return 0;
}