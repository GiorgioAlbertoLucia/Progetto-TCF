#include <iostream>
#include "../include/udouble.hpp"

using namespace std;

// test udouble
int main()
{
    Udouble * u1 = new Udouble(10, 3);
    Udouble * u2 = new Udouble(5, 4);

    double m1 = 10;
    double err1 = 3;
    double m2 = 5;
    double err2 = 4;

    Udouble u3;
    u3 = sin(*u1)*tan(*u2) - exp(*u1);

    double m3, err3, err4, err5, err6, err7, err8;
    m3 = sin(m1)*tan(m2) - exp(m1);
    err3 = sqrt(err1*err1*pow(cos(m1)*tan(m2) + 1, 2) + err2*err2*pow(sin(m1)/(cos(m2)*cos(m2)), 2));
    err4 = err1*cos(m1);
    err5 = err2/(cos(m2)*cos(m2));
    err6 = sqrt(tan(m2)*tan(m2)*err4*err4 + sin(m1)*sin(m1)*err5*err5);
    err7 = err1*exp(m1);
    err8 = sqrt(err6*err6 + err7*err7);

    cout << u3 << endl << m3 << " +/- " << err3 << endl << err8 << endl;


    return 0;
}