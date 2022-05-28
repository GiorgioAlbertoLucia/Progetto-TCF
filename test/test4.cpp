#include <iostream>
#include <vector>
#include <map>

#include "../include/partder.hpp"

#define PI 3.14159265

// STATUS: OK

using namespace std;

// test partder
int main()
{
    map<string, double> dx {{"x", 1.},};
    map<string, double> dy {{"y", 1},};

    PartDer * x = new PartDer(PI, dx);
    PartDer * y = new PartDer(2, dy);

    PartDer f;
    //f = sin(*x) + *y * cos(*x);
    f = *x^(*y);

    x->print();
    y->print();
    f.print();

    delete x;
    delete y;

    return 0;
}