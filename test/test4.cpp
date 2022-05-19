#include <iostream>
#include <vector>
#include <map>

#include "../include/partder.hpp"

#define PI 3.14159265

using namespace std;

// test partder
int main()
{
    map<string, double> dx {{"x", 1.},};
    map<string, double> dy {{"y", 1},};

    PartDer * x = new PartDer(PI, dx);
    PartDer * y = new PartDer(3, dy);

    PartDer f;
    f = sin(*x) + *y * cos(*x);

    x->print();
    y->print();
    f.print();

    return 0;
}