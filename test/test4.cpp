#include <iostream>
#include <vector>

#include "../include/partder.hpp"

#define PI 3.14159265

using namespace std;

// test udouble
int main()
{
    vector<double> dx, dy;
    dx.push_back(1);    dx.push_back(0);
    dy.push_back(0);    dy.push_back(1);
    PartDer * x = new PartDer(PI, dx);
    PartDer * y = new PartDer(0, dy);

    PartDer f;
    f = sin(*x) + *y;

    x->print();
    y->print();
    f.print();

    return 0;
}