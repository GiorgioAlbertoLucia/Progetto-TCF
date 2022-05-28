#include <iostream>
#include <vector>

#include "../include/udouble.hpp"
#include "../include/partder.hpp"

#define PI 3.14159265

using namespace std;

// STATUS: OK

// test udouble
int main()
{
    map<string, double> dx {{"x", 1.},};
    map<string, double> dy {{"y", 1},};

    PartDer x0(PI, dx);
    PartDer y0(3, dy);

    Udouble x(x0, 1, "x"), y(y0, 2, "y"), f;

    cout << "check count " << Udouble::get_count() << endl;

    f = sin(x) + y * cos(x); 

    cout << "check count " << Udouble::get_count() << endl;

    map<string, double> m = f.get_errorsmap();

    cout << "Print error map (f): " << endl;
    for (map<string, double>::const_iterator i = m.begin(); i != m.end(); i++)
    {
        cout << i->first << " " << i->second << endl;
    }
    

    cout << endl << x << endl << y << endl << f << endl;
    cout << sqrt(5) << endl;

    return 0;
}