#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>

#include "../Eigen/Dense"
#include "../include/leastsquares.hpp"

LeastSquares::LeastSquares(){}
LeastSquares::LeastSquares(const std::vector<double> x, const std::vector<double> y, const std::vector<double> sx, const std::vector<double> sy, const char * fit)
{
    LeastSquares::n = x.size();

    LeastSquares::x.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::x[i] = x.at(i);

    LeastSquares::sx.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::sx[i] = sx.at(i);

    LeastSquares::y.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::y[i] = y.at(i);

    LeastSquares::sy.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::sy[i] = sy.at(i);

    LeastSquares::fit = fit;
}
LeastSquares::LeastSquares(const std::vector<double> x, const std::vector<double> y, const std::vector<double> sy, const char * formula)
{
    LeastSquares::n = x.size();

    LeastSquares::x.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::x[i] = x.at(i);

    LeastSquares::y.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::y[i] = y.at(i);

    LeastSquares::sy.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::sy[i] = sy.at(i);

    LeastSquares::formula = formula;
}

void LeastSquares::set_ssquared(const char * formula)
{
    if formula == pol

}

void LeastSquares::fit(const char * formula)
{


    LeastSquares::coeff_matrix.resize(n, n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            std::vector<double> sum_elem;
            for(int k = 0; k < n; k++)  sum_elem.push_back( pow(x[k],i+j)/pow(ssquared.at(k),2) );
            LeastSquares::coeff_matrix[i,j] = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
        }
    }
}