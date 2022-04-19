#include <iostream>
#include <vector>

#include "../include/udouble.hpp"
#include "../include/upartder.hpp"

#define PI 3.14159265

using namespace std;

// test partder
int main()
{
    Udouble x0(PI, 1), y0(3, 2);
    vector<double> dx, dy;
    dx.push_back(1);    dx.push_back(0);
    dy.push_back(0);    dy.push_back(1);
    UPartDer * x = new UPartDer(x0, dx, "x");
    UPartDer * y = new UPartDer(y0, dy, "y");

    UPartDer f;
    
    f = sin(*x) + *y * cos(*x);

    x->print();
    y->print();
    f.print();
    f.print_dict();
    Udouble f0 = f.get_f();
    cout << endl << f0 << endl;

    return 0;
}